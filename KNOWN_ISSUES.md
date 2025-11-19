# Known Issues

## Test Failures (8 total)

### File Reading Tests (2 failures)
- `CountFileLines.LoadFrankenstein` - Test data file not found
- `CountFileLines.EmptyFile_ReturnsZero` - Test data file not found

**Issue**: Test data files are not in the expected location.

### Number Validation Tests (6 failures)

#### isInteger Issues
- `'+789'` - Incorrectly returns `true` for numbers with leading `+` sign
- `'1a2b3c'` - Incorrectly returns `true` for mixed alphanumeric strings

#### isFloat Issues
- `'5.'` - Incorrectly returns `false` for numbers with trailing decimal point
- `'1.5x10^3'` - Incorrectly returns `true` for scientific notation (should be `false`)
- `'2.0X10^-2'` - Incorrectly returns `true` for scientific notation with uppercase X
- `'3.5*10^5'` - Incorrectly returns `true` for scientific notation with asterisk
- `'1a2b3c'` - Incorrectly returns `true` for mixed alphanumeric strings

**Expected behavior**: `isFloat()` should only return `true` for standard decimal notation, not scientific notation. Scientific notation should only be validated by `isScientificNumber()` and `isNumber()`.

## Test Results Summary
- **Passing**: 250/258 tests (96.9%)
- **Failing**: 8/258 tests (3.1%)

## Benchmarks
All benchmarks pass successfully ✓
