/*
 * Vikman Fernandez-Castro
 * February 28, 2022
 */

package main

import (
	"fmt"
	"math"
	"math/big"
)

type Pi struct {
	value *big.Float
}

func NewPi(precision uint) *Pi {
	pi := Pi{value: new(big.Float).SetPrec(precision).SetInt64(0)}
	return &pi
}

func (pi *Pi) Compute() *Pi {
	steps := int(math.Log2(float64(pi.value.Prec())))
	two := new(big.Float).SetPrec(pi.value.Prec()).SetInt64(2)
	a := new(big.Float).SetPrec(pi.value.Prec()).SetInt64(1)

	b := new(big.Float).SetPrec(pi.value.Prec()).SetInt64(2)
	b.Sqrt(b)
	b.Quo(a, b)

	t := new(big.Float).SetPrec(pi.value.Prec()).SetInt64(4)
	t.Quo(a, t)

	p := new(big.Float).SetPrec(pi.value.Prec()).SetInt64(1)
	x := new(big.Float)
	y := new(big.Float)
	z := new(big.Float)

	for i := 0; i <= steps; i++ {
		// x = (a + b) / 2
		x.Add(a, b)
		x.Quo(x, two)

		// y = sqrt(a, b)
		y.Mul(a, b)
		y.Sqrt(y)

		// t = t - p(a - x)^2
		z.Sub(a, x)
		z.Mul(z, z)
		z.Mul(p, z)
		t.Sub(t, z)

		// a = x
		a.Set(x)

		// b = y
		b.Set(y)

		// p = 2 * p
		p.Mul(two, p)
	}

	pi.value.Add(a, b)
	pi.value.Mul(pi.value, pi.value)
	pi.value.Quo(pi.value, t)
	pi.value.Quo(pi.value, two)
	pi.value.Quo(pi.value, two)

	return pi
}

func (pi *Pi) Format(s fmt.State, format rune) {
	pi.value.Format(s, format)
}

func (pi *Pi) Precision() uint {
	return uint(1 + math.Ceil(float64(pi.value.Prec())*math.Log(2)/math.Log(10)))
}

func (pi *Pi) String() string {
	return pi.value.Text('f', int(pi.Precision())-1)
}
