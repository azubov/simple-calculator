#include <gtest/gtest.h>

TEST(LeakMemcheckedTest, DetectsMemoryLeak) {
    GTEST_SKIP() << "Leak test is disabled.";

    // Создаём утечку намеренно
    int* leaked = new int[10];

    // Используем часть памяти, чтобы Valgrind не считал её "still reachable"
    leaked[0] = 42;

    // Не освобождаем память
    SUCCEED();
}
