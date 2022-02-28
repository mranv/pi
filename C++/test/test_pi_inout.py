from subprocess import run
from json import loads
from re import match, fullmatch

def test_default_run():
    global p
    p = run(['../../build/pi'], capture_output=True, check=True)

def test_default_json():
    global data
    data = loads(p.stdout)

def test_default_json_pi():
    assert fullmatch(r'3\.[0-9]+', data['pi'])

def test_default_json_precision():
    assert 3012 == data['precision']

def test_default_json_time():
    assert float == type(data['time_ms'])

def test_help():
    global p
    p = run(['../../build/pi', '-h'], capture_output=True, check=True)

def test_help_message():
    assert match(r'Pi calculator - v\d+\.\d+\n+Usage:.+-h.+-m.+-p', p.stdout.decode())

def test_invalid_arg():
    p = run(['../../build/pi', '-a'], capture_output=True)
    assert p.returncode == 1
    assert b'ERROR: Invalid option -a.\n' == p.stderr

def test_double_run():
    global data
    p = run(['../../build/pi', '-md'], capture_output=True, check=True)
    data = loads(p.stdout)

def test_double_precision():
    assert 16 == data['precision']

def test_double_precision_ignored():
    p = run(['../../build/pi', '-md', '-p2'], capture_output=True, check=True)
    assert b'WARNING: Precision parameter will be ignored in double mode.\n' == p.stderr

def test_multi_precision_run():
    global data
    p = run(['../../build/pi', '-mm', '-p10'], capture_output=True, check=True)
    data = loads(p.stdout)

def test_multi_precision():
    assert 5 == data['precision']

def test_invalid_methd():
    p = run(['../../build/pi', '-ma'], capture_output=True)
    assert p.returncode == 1
    assert b'ERROR: Invalid value for option -m.\n' == p.stderr

def test_negative_precision():
    p = run(['../../build/pi', '-p-1'], capture_output=True)
    assert p.returncode == 1
    assert b'ERROR: Invalid value for option -p.\n' == p.stderr

def test_precision_zero():
    p = run(['../../build/pi', '-p0'], capture_output=True)
    assert p.returncode == 1
    assert b'ERROR: Invalid value for option -p.\n' == p.stderr

def test_precision_overflow():
    p = run(['../../build/pi', '-p9223372036854775552'], capture_output=True)
    assert p.returncode == 1
    assert b'ERROR: Invalid value for option -p.\n' == p.stderr

def test_cannot_allocate():
    p = run(['../../build/pi', '-p9223372036854775551'], capture_output=True)
    assert p.returncode == -6
    assert b'GNU MP: Cannot allocate memory (size=1152921504606846952)\n' == p.stderr

def test_tty_run():
    p = run(['script', '-qc', '../../build/pi'], capture_output=True, check=True)
    assert fullmatch(r'Pi = 3\.\d+\r\nPrecision = 3012 digits\r\nTime = \d+\.\d+ ms\r\n', p.stdout.decode())
