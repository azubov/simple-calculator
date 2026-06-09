# Simple Calculator

Простой калькулятор на C++ для работы с целыми числами (`std::int64_t`).  
Использует библиотеку [mathlib](https://github.com/azubov/mathlib) для безопасных математических операций с проверкой переполнений и ошибок.  
Поддерживает сохранение и поиск операций в `PostgreSQL`.

## 📂 Структура проекта

```bash
tree --dirsfirst -I 'build|.*'
```

```
.
├── db
│   ├── migrations
│   │   ├── V1__create_schema.sql
│   │   └── V2__create_operations_table.sql
│   ├── docker-compose.yaml
│   ├── start.sh
│   └── stop.sh
├── example
│   └── input.json
├── src
│   ├── logging
│   │   ├── Logger.h
│   │   ├── NullLogger.h
│   │   ├── OperationDataFormatter.h
│   │   └── SpdLogger.h
│   ├── Application.cpp
│   ├── Application.h
│   ├── CachedCalculatorRepository.cpp
│   ├── CachedCalculatorRepository.h
│   ├── Calculator.h
│   ├── CalculatorRepository.h
│   ├── CalculatorService.cpp
│   ├── CalculatorService.h
│   ├── Checker.cpp
│   ├── Checker.h
│   ├── CMakeLists.txt
│   ├── CpuHeavyCalculator.cpp
│   ├── CpuHeavyCalculator.h
│   ├── Log.h
│   ├── main.cpp
│   ├── OperationData.h
│   ├── Parser.cpp
│   ├── Parser.h
│   ├── PGConnection.cpp
│   ├── PGConnection.h
│   ├── PGResult.h
│   ├── PostgresCalculatorRepository.cpp
│   ├── PostgresCalculatorRepository.h
│   ├── Printer.cpp
│   ├── Printer.h
│   ├── Runner.cpp
│   ├── Runner.h
│   ├── Server.h
│   ├── SimpleCalculator.cpp
│   ├── SimpleCalculator.h
│   ├── StatementInitializer.cpp
│   ├── StatementInitializer.h
│   ├── SystemSignal.cpp
│   ├── SystemSignal.h
│   ├── ZmqServer.cpp
│   └── ZmqServer.h
├── tests
│   ├── integration
│   │   ├── client.cpp
│   │   ├── CMakeLists.txt
│   │   └── test_cases.txt
│   ├── mocks
│   │   ├── MockCalculator.h
│   │   ├── MockRepository.h
│   │   └── MockServer.h
│   ├── cached_calculator_repository_tests.cpp
│   ├── calculator_service_tests.cpp
│   ├── checker_tests.cpp
│   ├── CMakeLists.txt
│   ├── leak_memchecked_test.cpp
│   ├── main.cpp
│   ├── parser_tests.cpp
│   ├── printer_tests.cpp
│   ├── runner_tests.cpp
│   ├── simple_calculator_tests.cpp
│   └── TestHelper.h
├── calculator.service
├── CMakeLists.txt
├── CMakePresets.json
└── README.md
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
./build/debug/calc
```

Остановка:
```bash
ps aux | grep calc
kill -TERM <PID>
```

Запуск тестового клиента для **debug** версии
```bash
(cd build/debug/tests/integration && ./client)
```
Можно передать время стресс теста в секундах (5 сек по умолчанию)
```bash
(cd build/debug/tests/integration && ./client 1)
```

Сборка **debug-valgrind** версии:
```bash
cmake --preset debug-valgrind
cmake --build --preset debug-valgrind
ctest --preset debug-valgrind --output-on-failure
```

Запуск **debug-valgrind** версии:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./build/debug-valgrind/calc
```

Остановка:
```bash
ps aux | grep valgrind
kill -TERM <PID>
```

Сборка **perf** версии:
```bash
cmake --preset perf
cmake --build --preset perf
```

Запуск **perf** версии:
```bash
perf record -o build/perf/perf.data -- ./build/perf/calc
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
./build/release/calc
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

Очистить таблицу:

```sql
TRUNCATE TABLE calc.operations;
```

## Systemd Support

Проект включает готовую конфигурацию `calculator.service` для запуска в режиме демона Linux.

### 1. Установка unit-файлов
```bash
sudo cp calculator.service /etc/systemd/system/
```

### 2. Обновить systemd
```bash
sudo systemctl daemon-reload
```

### 3. Запуск
```bash
sudo systemctl start calculator
```

### 4. Проверка
```bash
systemctl status calculator
```

### 5. Перезапуск
```bash
sudo systemctl restart calculator
```

### 6. Остановка
```bash
sudo systemctl stop calculator
```