CREATE TABLE IF NOT EXISTS calc.operations (
    id SERIAL PRIMARY KEY,
    first_value BIGINT NOT NULL,
    operation CHAR(1) NOT NULL,
    second_value BIGINT,
    result BIGINT,       
    status INT NOT NULL
);

COMMENT ON TABLE calc.operations IS 'Stores calculator operations, operands, results, and execution status.';

COMMENT ON COLUMN calc.operations.first_value IS 'First operand (int64).';
COMMENT ON COLUMN calc.operations.operation IS 'Operation symbol: +, -, *, /, !, etc.';
COMMENT ON COLUMN calc.operations.second_value IS 'Second operand (nullable for unary operations like factorial).';
COMMENT ON COLUMN calc.operations.result IS 'Result of the operation (nullable if error).';
COMMENT ON COLUMN calc.operations.status IS 'Execution status: 0 = success, non-zero = error code.';
