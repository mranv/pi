/*
 * Vikman Fernandez-Castro
 * February 28, 2022
 */

package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"os"
	"time"
)

type result struct {
	Pi        string  `json:"pi"`
	Precision uint    `json:"precision"`
	Duration  float64 `json:"time_ms"`
}

func printOut(pi *Pi, nanoseconds int64) {
	if fileInfo, _ := os.Stdout.Stat(); (fileInfo.Mode() & os.ModeCharDevice) != 0 {
		fmt.Println("Pi =", pi.String())
		fmt.Println("Precision =", pi.Precision(), "digits")
		fmt.Println("Time =", float64(nanoseconds)/1e6, "ms")
	} else {
		data := result{Pi: pi.String(), Precision: pi.Precision(), Duration: float64(nanoseconds) / 1e6}
		payload, _ := json.Marshal(data)
		fmt.Print(string(payload))
	}
}

func main() {
	var precision = flag.Uint("p", 10000, "Precision in bits")
	flag.Parse()

	if *precision == 0 {
		fmt.Fprintln(os.Stderr, "invalid value \"0\" for flag -p: only positive values allowed")
		flag.Usage()
		os.Exit(1)
	}

	pi := NewPi(*precision)

	start := time.Now()
	pi.Compute()
	elapsed := time.Since(start)

	printOut(pi, elapsed.Nanoseconds())
}
