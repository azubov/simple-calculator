#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <zmq.hpp>

enum class MatchType { SUBSTRING, EXACT };

struct TestCase {
    MatchType type;
    std::string request;
    std::string expected;
};

std::vector<TestCase> loadTestCases(const std::string& filename) {
    std::vector<TestCase> cases;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open test cases file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        size_t first_pipe = line.find('|');
        if (first_pipe == std::string::npos) {
            continue;
        }
        size_t second_pipe = line.find('|', first_pipe + 1);
        if (second_pipe == std::string::npos) {
            continue;
        }
        std::string type_str = line.substr(0, first_pipe);
        std::string request =
            line.substr(first_pipe + 1, second_pipe - first_pipe - 1);
        std::string expected = line.substr(second_pipe + 1);

        MatchType match_type =
            (type_str == "EXACT") ? MatchType::EXACT : MatchType::SUBSTRING;
        cases.push_back({match_type, request, expected});
    }
    return cases;
}

void trimTrailingNewlines(std::string& str) {
    while (!str.empty() && (str.back() == '\n' || str.back() == '\r')) {
        str.pop_back();
    }
}

long long runTest(zmq::socket_t& socket, const TestCase& test, size_t index) {
    auto t1 = std::chrono::steady_clock::now();

    socket.send(zmq::buffer(test.request), zmq::send_flags::none);

    zmq::message_t reply{};
    zmq::recv_result_t res;

    try {
        res = socket.recv(reply, zmq::recv_flags::none);
    } catch (const zmq::error_t& e) {
        std::cerr << "\n[NETWORK ERROR] Connection timeout or server died: "
                  << e.what() << " on test " << index << '\n';
        exit(1);
    }

    auto t2 = std::chrono::steady_clock::now();
    auto rtt =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    if (!res) {
        std::cerr << "\n[NETWORK ERROR] Timeout exceeded. No response from "
                     "server on test "
                  << index << '\n';
        exit(1);
    }

    std::string actual_reply = reply.to_string();
    trimTrailingNewlines(actual_reply);

    bool is_success = false;
    if (test.type == MatchType::SUBSTRING) {
        is_success = (actual_reply.find(test.expected) != std::string::npos);
    } else {
        is_success = (actual_reply == test.expected);
    }

    if (!is_success) {
        std::cerr << "\nFAIL: Test case " << index << " failed!\n";
        std::cerr << "Request: " << test.request << '\n';
        std::cerr << "Expected ("
                  << (test.type == MatchType::EXACT ? "Exact" : "Substring")
                  << "): " << test.expected << '\n';
        std::cerr << "Actual reply: " << actual_reply << '\n';
        exit(1);
    }

    return rtt;
}

int main(int argc, char* argv[]) {
    long long seconds_to_run = 5;

    if (argc > 1) {
        try {
            seconds_to_run = std::stoll(argv[1]);
            if (seconds_to_run <= 0) {
                std::cerr
                    << "Error: Seconds count must be a positive number!\n";
                return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: Invalid number format for seconds! Usage: "
                      << argv[0] << " [seconds_count]\n";
            return 1;
        }
    }

    zmq::context_t context{1};
    zmq::socket_t socket{context, zmq::socket_type::req};

    int timeout_ms = 1000;
    socket.set(zmq::sockopt::rcvtimeo, timeout_ms);

    socket.connect("tcp://localhost:5555");

    std::vector<TestCase> test_cases;
    try {
        test_cases = loadTestCases("test_cases.txt");
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    if (test_cases.empty()) {
        std::cerr << "Error: Test cases list is empty!\n";
        return 1;
    }

    auto duration = std::chrono::seconds(seconds_to_run);
    std::cout << "Running Integration Tests in a loop for " << duration.count()
              << " seconds...\n";

    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + duration;

    size_t total_executed = 0;
    long long total_rtt = 0;

    while (std::chrono::steady_clock::now() < end_time) {
        size_t case_index = total_executed % test_cases.size();

        total_rtt += runTest(socket, test_cases[case_index], total_executed);
        total_executed++;

        if (total_executed % 5000 == 0) {
            std::cout << "[PROGRESS] Executed " << total_executed
                      << " tests...\n";
        }
    }

    auto real_elapsed_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start_time
        )
            .count();

    std::cout << "\n[SUCCESS] Stress testing finished!\n";

    double seconds_elapsed = static_cast<double>(real_elapsed_ms) / 1000.0;
    std::cout << "Executed " << total_executed << " tests in "
              << seconds_elapsed << " seconds.\n";

    if (total_executed > 0 && real_elapsed_ms > 0) {
        long long avg_rtt = total_rtt / static_cast<long long>(total_executed);
        long long rps =
            (static_cast<long long>(total_executed) * 1000) / real_elapsed_ms;
        std::cout << "Average RTT = " << avg_rtt << " us\n";
        std::cout << "Throughput  = " << rps << " RPS (Requests Per Second)\n";
    }

    return 0;
}