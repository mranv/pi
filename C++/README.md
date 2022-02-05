# Calculating the number π (C++)

This folder contains an C++ implementation to calculate Pi through two methods:

- Arccosine of -1 for double-precision floating point.
- Brent-Salamin algorithm for multi-precision ([MPFR library](https://www.mpfr.org/algorithms.pdf)).

## Build

### Requirements

- G++ 4.9 or later.
- CMake 3.10 or later.
- MPFR library.

#### Installation on Ubuntu

```sh
sudo apt-get update
sudo apt-get install g++ cmake libmpfr-dev
```

### Build

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Run

- Run in terminal mode:
```
$ ./pi -mmulti -p256
Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286198
Precision = 79 digits
Time = 0.031736 ms
```

- Run in non-terminal mode (JSON):
```sh
$  ./pi -mmulti -p256 | cat
```
```json
{"pi":"3.141592653589793238462643383279502884197169399375105820974944592307816406286198","precision":79, "time_ms:":0.028523}
```

## Usage

```
pi [ -h ] [ -m <method> ] [ -p <precision> ]
```

|Option|Description|Range|Default|
|---|---|---|---|
|`-h`|Show this help|||
|`-m`|Calculation method|`double` or `multi`|`multi`|
|`-p`|Precision for multi-precision, in bits|Positive integer|`10000`|
