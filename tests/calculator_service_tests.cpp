#include "CalculatorService.h"

#include "mocks/MockCalculator.h"
#include "mocks/MockRepository.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Throw;

//
// 1. repo.find() устанавливает SUCCESS → метод должен просто выйти
//
TEST(CalculatorServiceTest, ReturnsImmediatelyWhenRepoSetsSuccess) {
    MockRepository repo;
    MockCalculator calc;
    CalculatorService service(repo, calc);

    OperationData data{};

    EXPECT_CALL(repo, find(_)).WillOnce(Invoke([](OperationData& d) {
        d.status = OperationData::Status::success;
    }));

    EXPECT_CALL(calc, calculate(_)).Times(0);
    EXPECT_CALL(repo, save(_)).Times(0);

    service.calculate(data);
}

//
// 2. repo.find() устанавливает INVALID_ARGUMENT → должен быть выброшен
// std::invalid_argument
//
TEST(CalculatorServiceTest, ThrowsInvalidArgumentWhenRepoSetsInvalidArgument) {
    MockRepository repo;
    MockCalculator calc;
    CalculatorService service(repo, calc);

    OperationData data{};

    EXPECT_CALL(repo, find(_)).WillOnce(Invoke([](OperationData& d) {
        d.status = OperationData::Status::invalid_argument;
    }));

    EXPECT_THROW(service.calculate(data), std::invalid_argument);
}

//
// 3. repo.find() устанавливает OVERFLOW_ERROR → должен быть выброшен
// std::overflow_error
//
TEST(CalculatorServiceTest, ThrowsOverflowErrorWhenRepoSetsOverflowError) {
    MockRepository repo;
    MockCalculator calc;
    CalculatorService service(repo, calc);

    OperationData data{};

    EXPECT_CALL(repo, find(_)).WillOnce(Invoke([](OperationData& d) {
        d.status = OperationData::Status::overflow_error;
    }));

    EXPECT_THROW(service.calculate(data), std::overflow_error);
}

//
// 4. repo.find() не находит → должен быть вызван calc.calculate()
//    затем save() со статусом SUCCESS
//
TEST(CalculatorServiceTest, CalculatesAndSavesSuccess) {
    MockRepository repo;
    MockCalculator calc;
    CalculatorService service(repo, calc);

    OperationData data{};

    EXPECT_CALL(repo, find(_)).Times(1);

    EXPECT_CALL(calc, calculate(_)).Times(1);

    EXPECT_CALL(repo, save(_)).WillOnce(Invoke([](const OperationData& d) {
        EXPECT_EQ(d.status, OperationData::Status::success);
    }));

    service.calculate(data);
}

//
// 5. calc.calculate() бросает std::invalid_argument → save() должен быть вызван
// со статусом INVALID_ARGUMENT
//
TEST(
    CalculatorServiceTest,
    SavesInvalidArgumentWhenCalculatorThrowsInvalidArgument
) {
    MockRepository repo;
    MockCalculator calc;
    CalculatorService service(repo, calc);

    OperationData data{};

    EXPECT_CALL(repo, find(_)).Times(1);

    EXPECT_CALL(calc, calculate(_))
        .WillOnce(Throw(std::invalid_argument("bad")));

    EXPECT_CALL(repo, save(_)).WillOnce(Invoke([](const OperationData& d) {
        EXPECT_EQ(d.status, OperationData::Status::invalid_argument);
    }));

    EXPECT_THROW(service.calculate(data), std::invalid_argument);
}

//
// 6. calc.calculate() бросает std::overflow_error → save() должен быть вызван
// со статусом OVERFLOW_ERROR
//
TEST(
    CalculatorServiceTest, SavesOverflowErrorWhenCalculatorThrowsOverflowError
) {
    MockRepository repo;
    MockCalculator calc;
    CalculatorService service(repo, calc);

    OperationData data{};

    EXPECT_CALL(repo, find(_)).Times(1);

    EXPECT_CALL(calc, calculate(_))
        .WillOnce(Throw(std::overflow_error("overflow")));

    EXPECT_CALL(repo, save(_)).WillOnce(Invoke([](const OperationData& d) {
        EXPECT_EQ(d.status, OperationData::Status::overflow_error);
    }));

    EXPECT_THROW(service.calculate(data), std::overflow_error);
}
