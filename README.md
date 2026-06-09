# Simple Calculator

Простой калькулятор на `C++` для работы с целыми числами (`std::int64_t`).  
Сервис принимает `JSON`‑запросы по `ZeroMQ`, выполняет безопасные математические операции, кеширует результаты в `PostgreSQL` и работает как `systemd‑демон`.  
Использует библиотеку [mathlib](https://github.com/azubov/mathlib) для безопасных вычислений с защитой от переполнений.

## 📂 Структура проекта

```
.
├── db/                     # PostgreSQL + миграции
├── example/                # Примеры входных данных
├── packaging/              # postinst/prerm для DEB-пакета
├── src/                    # Исходный код приложения
├── tests/                  # Unit и integration тесты
├── calculator.service      # systemd unit
├── CMakeLists.txt          # корневой CMake
├── CMakePresets.json       # пресеты сборки
└── README.md
```
Подробнее:
```bash
tree --dirsfirst -I 'build|.*'
```

## 🧩 Архитектура
Основные компоненты:
| Компонент | Назначение |
| --- | --- |
| **Parser** | парсинг JSON |
| **Checker** | валидация данных |
| **CalculatorService** | кеш + вычисления |
| **SimpleCalculator / CpuHeavyCalculator** | реализация операций |
| **PostgresCalculatorRepository** | сохранение результатов |
| **ZmqServer** | ZeroMQ REP‑сервер |
| **Runner** | главный цикл обработки запросов |
| **Printer** | форматирование ответа |
| **Application** | инициализация и запуск сервиса |

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

## 🧩 Протокол взаимодействия (ZeroMQ)

Сервис работает как REP‑сокет на `tcp://*:5555`  
Клиент отправляет строку `JSON`:

```bash
{ "first": 3,  "operation": "+", "second": 5 }      # 8
{ "first": 10, "operation": "-", "second": 7 }      # 3
{ "first": 2,  "operation": "*", "second": 3 }      # 6
{ "first": 10, "operation": "/", "second": 2 }      # 5
{ "first": 2,  "operation": "^", "second": 3 }      # 8
{ "first": 4,  "operation": "1" }                   # 24
```

Справка по командам:
```bash
--help
```

## 🛠️ Сборка через CMakePresets

В проекте используется файл `CMakePresets.json`, который описывает готовые профили сборки и автоматически включает нужные флаги компиляции.

### Доступные пресеты

- **debug** — сборка в режиме `Debug`, включает тесты, тестовый клиент, `clang-tidy`, строгие предупреждения (`-Wall -Wextra -Wpedantic -Werror`) и санитайзеры (`address`, `undefined`).
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

Логи:
```bash
tail -f ./build/debug/calculator.log
```

Запуск тестового клиента для **debug** версии
```bash
(cd build/debug/tests/integration && ./client)
```
Можно передать время стресс теста в секундах (5 сек по умолчанию)
```bash
(cd build/debug/tests/integration && ./client 1)
```

Остановка:
```bash
ps aux | grep calc
kill -TERM <PID>
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
## Ручная установка

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

### 7. Удаление unit-файла
```bash
sudo rm /etc/systemd/system/calculator.service
```

## Systemd Support
## Установка DEB-пакета с помощью CPack

### 1. Сборка проекта в **release-режиме**
```bash
cmake --preset release
cmake --build --preset release
```

### 2. Сборка DEB-пакета с помощью CPack:
```bash
(cd build/release && cpack)
```
Результат: `simple-calculator-1.0.0-amd64.deb`

### 3. Проверить содержимое пакета (без установки)
```bash
(cd build/release && dpkg-deb --contents simple-calculator-1.0.0-amd64.deb)
```

### 4. Установка и запуск:
Перед выполнением команды нужно убедиться что БД `Postgres` запущена
```bash
(cd build/release && sudo dpkg -i simple-calculator-1.0.0-amd64.deb)
```

### 5. Удаление:
```bash
sudo dpkg -r simple-calculator
```

## Лог приложения при запуске через Systemd
```bash
tail -f /var/lib/calculator/calculator.log
```