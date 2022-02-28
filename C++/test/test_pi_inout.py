"""
Vikman Fernandez-Castro
February 28, 2022
"""

from subprocess import run
from json import loads
from re import match, fullmatch
import pytest

PI_BIN = '../pi'


def test_default_run():
    """Test that pi runs without arguments."""
    run([PI_BIN], capture_output=True, check=True)


def test_default_json():
    """Test that pi prints a valid JSON object."""
    result = run([PI_BIN], capture_output=True, check=True)
    loads(result.stdout)


def test_default_json_pi():
    """Check that the JSON contains a member 'pi' that approximates to pi."""
    result = run([PI_BIN], capture_output=True, check=True)
    data = loads(result.stdout)
    assert fullmatch(r'3\.[0-9]+', data['pi'])


def test_default_json_precision():
    """Check that the precision reported is 3012 by default."""
    result = run([PI_BIN], capture_output=True, check=True)
    data = loads(result.stdout)
    assert 3012 == data['precision']


def test_default_json_time():
    """Check that the JSON contains a float member 'time_ms'."""
    result = run([PI_BIN], capture_output=True, check=True)
    data = loads(result.stdout)
    assert isinstance(data['time_ms'], float)


def test_help():
    """Check that pi accepts the help argument."""
    run([PI_BIN, '-h'], capture_output=True, check=True)


def test_help_message():
    """Validate the help message."""
    result = run([PI_BIN, '-h'], capture_output=True, check=True)
    assert match(r'Pi calculator - v\d+\.\d+\n+Usage:.+-h.+-m.+-p',
                 result.stdout.decode())


def test_invalid_arg():
    """Test that pi fails and reports an error with an unknown argument."""
    result = run([PI_BIN, '-a'], capture_output=True, check=False)
    assert result.returncode == 1
    assert b'ERROR: Invalid option -a.\n' == result.stderr


def test_double_run():
    """Check a valid execution using the double-precision method."""
    result = run([PI_BIN, '-md'], capture_output=True, check=True)
    loads(result.stdout)


def test_double_precision():
    """Check that the precision member in double-precision mode is 16."""
    result = run([PI_BIN, '-md'], capture_output=True, check=True)
    data = loads(result.stdout)
    assert 16 == data['precision']


def test_double_precision_ignored():
    """Check that pi ignores option -p in double-precision mode."""
    result = run([PI_BIN, '-md', '-p2'], capture_output=True, check=True)
    assert b'WARNING: Precision parameter will be ignored in double mode.\n' == result.stderr


def test_multi_precision_run():
    """Check a valid execution using the multi-precision method."""
    run([PI_BIN, '-mm', '-p10'], capture_output=True, check=True)


def test_multi_precision():
    """Check the precision value with a given precision of 10 bits."""
    result = run([PI_BIN, '-mm', '-p10'], capture_output=True, check=True)
    data = loads(result.stdout)
    assert 5 == data['precision']


def test_invalid_method():
    """Check that pi fails and reports an error with an unknown method."""
    result = run([PI_BIN, '-ma'], capture_output=True, check=False)
    assert result.returncode == 1
    assert b'ERROR: Invalid value for option -m.\n' == result.stderr


@pytest.mark.parametrize('inval', [-1, 0, 9223372036854775552])
def test_precision_invalid(inval):
    """Check that pi fails and reports an error with some invalid precision values."""
    result = run([PI_BIN, '-p' + str(inval)], capture_output=True, check=False)
    assert result.returncode == 1
    assert b'ERROR: Invalid value for option -p.\n' == result.stderr


def test_cannot_allocate():
    """Check that pi aborts due to memory allocation error when the precision is too high."""
    result = run([PI_BIN, '-p9223372036854775551'],
                 capture_output=True, check=False)
    assert result.returncode == -6
    assert b'GNU MP: Cannot allocate memory (size=1152921504606846952)\n' == result.stderr


def test_tty_run():
    """Check the standard output in TTY mode."""
    result = run(['script', '-qc', PI_BIN], capture_output=True, check=True)
    assert fullmatch(r'Pi = 3\.\d+\r\nPrecision = 3012 digits\r\nTime = \d+\.\d+ ms\r\n',
                     result.stdout.decode())
