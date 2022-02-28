# Calculating the number π (Go)

This folder contains a Go implementation of the Brent-Salamin algorithm to calculate Pi.

## Setup

### Requirements

- Go compiler.

#### Installation on Ubuntu 21.04

```sh
sudo apt-get install golang-go
```

### Build

```sh
go build
```

## Run

- Run in terminal mode:

```sh
$ ./pi -p 256
Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286198
Precision = 79 digits
Time = 0.050072 ms
```

- Run in non-terminal mode (JSON):

```sh
$ ./pi -p 256 | cat
{"pi":"3.141592653589793238462643383279502884197169399375105820974944592307816406286198","precision":79,"time_ms":0.044478}
```

## Usage

```
pi [ -h ] [ -p <precision> ]
```

|Option|Description|Range|Default|
|---|---|---|---|
|`-h`|Show this help|||
|`-p`|Precision, in bits|Positive integer|`10000`|
