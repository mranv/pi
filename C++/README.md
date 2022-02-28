# Calculating the number π (C++)

[![Build](https://github.com/vikman90/pi/actions/workflows/build.yml/badge.svg)](https://github.com/vikman90/pi/actions/workflows/build.yml)

This folder contains an C++ implementation to calculate Pi through two methods:

- Arccosine of -1 for double-precision floating point.
- Brent-Salamin algorithm for multi-precision ([MPFR library](https://www.mpfr.org/algorithms.pdf)).

## Setup

### Requirements

- G++ 4.9 or later.
- CMake 3.10 or later.
- MPFR library 4.1 or later.

#### Installation on Ubuntu 21.04

```sh
sudo apt-get update
sudo apt-get install g++ cmake libmpfr-dev
```

### Build

```sh
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF
cmake --build build
```

### Install

```sh
sudo cmake --install build
```

### Uninstall

```sh
sudo xargs rm -v < build/install_manifest.txt
```

## Run

- Run in terminal mode:
```
$ pi -mmulti -p256
Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286198
Precision = 79 digits
Time = 0.031736 ms
```

- Run in non-terminal mode (JSON):
```sh
$  pi -mmulti -p256 | cat
```
```json
{"pi":"3.141592653589793238462643383279502884197169399375105820974944592307816406286198","precision":79,"time_ms":0.028523}
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

## Test

### Extra requirements

- Google Test 1.11 or later.

```sh
git submodule update --init
```

- Pytest 6.2.5 or later.

```sh
pip3 install -r ../requirements.txt
```

### Build

```sh
cmake -Bbuild
cmake --build build
```

### Run tests

```sh
cd build
ctest
```
