# Simple Calculator

Простой калькулятор на C++ для работы с целыми числами (`std::int64_t`).  
Использует библиотеку [mathlib](https://github.com/azubov/mathlib) для безопасных математических операций с проверкой переполнений и ошибок.  
Поддерживает сохранение и поиск операций в `PostgreSQL`.

## 📂 Структура проекта

```
simple-calculator/
├── CMakeLists.txt
├── CMakePresets.json
├── README.md
└── src/
    └── CMakeLists.txt
    └── logging/
        └── Logger.h
        └── SpdLogger.h
        └── NullLogger.h
        └── OperationDataFormatter.h
    └── Log.h
    └── OperationData.h
    └── Runner.cpp
    └── Runner.h
    └── Parser.cpp
    └── Parser.h
    └── Checker.cpp
    └── Checker.h
    └── PGConnection.cpp
    └── PGConnection.h
    └── PGResult.h
    └── StatementInitializer.h
    └── StatementInitializer.cpp
    └── CalculatorRepository.h
    └── CachedCalculatorRepository.h
    └── CachedCalculatorRepository.cpp
    └── PostgresCalculatorRepository.h
    └── PostgresCalculatorRepository.cpp
    └── CalculatorService.cpp
    └── CalculatorService.h
    └── Calculator.h
    └── SimpleCalculator.h
    └── SimpleCalculator.cpp
    └── CpuHeavyCalculator.h
    └── CpuHeavyCalculator.cpp
    └── Printer.cpp
    └── Printer.h
    └── main.cpp
└── tests/
    └── mocks/
    └── CMakeLists.txt
    └── runner_tests.cpp
    └── parser_tests.cpp
    └── checker_tests.cpp
    └── simple_calculator_tests.cpp
    └── calculator_service_tests.cpp
    └── cached_calculator_repository_tests.cpp
    └── printer_tests.cpp
    └── leak_memchecked_test.cpp
    └── main.cpp
└── example/
    └── input.json
└── db/
    └── migrations/
    └── docker-compose.yaml
    └── start.sh
    └── stop.sh
```

## 🚀 Возможности

Калькулятор поддерживает следующие операции:

- `+` — сложение
- `-` — вычитание
- `*` — умножение
- `/` — деление (с проверкой деления на ноль и переполнения)
- `^` — возведение в степень (только для неотрицательных показателей)
- `!` — факториал (только для неотрицательных чисел)

Все операции выполняются с проверкой переполнений.  
Результаты вычислений сохраняются в `PostgreSQL`, чтобы избежать повторных вычислений.

## 🧩 Пример использования

```bash
./calc 3 + 5      # 8
./calc 10 - 7     # 3
./calc 2 * 3      # 6
./calc 10 / 2     # 5
./calc 2 ^ 3      # 8
./calc 4 !        # 24
```

Справка по командам:
```bash
./calc --help
```

## 🛠️ Сборка через CMakePresets

В проекте используется файл `CMakePresets.json`, который описывает готовые профили сборки и автоматически включает нужные флаги компиляции.

### Доступные пресеты

- **debug** — сборка в режиме `Debug`, включает тесты, `clang-tidy`, строгие предупреждения (`-Wall -Wextra -Wpedantic -Werror`) и санитайзеры (`address`, `undefined`).
- **debug-valgrind** — сборка в режиме `Debug`, включает тесты и запускает их под `Valgrind` с расширенной проверкой утечек памяти.
- **perf** — оптимизированная сборка для анализа производительности приложения с использованием утилиты `perf`. Без тестов, без предупреждений компилятора.
- **release** — оптимизированная сборка в режиме `Release`, без тестов, с мягкими предупреждениями.

### Использование

Сборка **debug** версии:
```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

Запуск **debug** версии:
```bash
./build/debug/calc < ./example/input.json
```

Сборка **debug-valgrind** версии:
```bash
cmake --preset debug-valgrind
cmake --build --preset debug-valgrind
ctest --preset debug-valgrind --output-on-failure
```

Запуск **debug-valgrind** версии:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./build/debug-valgrind/calc < ./example/input.json
```

Сборка **perf** версии:
```bash
cmake --preset perf
cmake --build --preset perf
```

Запуск **perf** версии:
```bash
perf record -o build/perf/perf.data -- ./build/perf/calc < ./example/input.json
```

Анализ отчета производительности **perf**:
```bash
perf report -i build/perf/perf.data
```

Сборка **release** версии:
```bash
cmake --preset release
cmake --build --preset release
```

Запуск **release** версии:
```bash
./build/release/calc < ./example/input.json
```
## 🗄️ Запуск базы данных PostgreSQL

Проект включает готовую конфигурацию `Docker Compose` для локального запуска `PostgreSQL`.

Запуск базы:

```bash
./db/start.sh
```

Остановка базы:

```bash
./db/stop.sh
```

Подключение к бд через `psql`:

```bash
docker exec -it postgres psql -U postgres -d calc-db
```

Посмотреть данные таблицы:

```sql
SELECT * FROM calc.operations;
```