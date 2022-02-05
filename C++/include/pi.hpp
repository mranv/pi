/*
 * Vikman Fernandez-Castro
 * February 5, 2022
 */

#ifndef PI_HPP
#define PI_HPP

#include <mpfr.h>
#include <iostream>

class PiBase {
public:
    virtual ~PiBase() { }
    virtual void compute() = 0;
    virtual long precision() const = 0;

    friend std::ostream & operator << (std::ostream & os, const PiBase & pi);

private:
    virtual std::ostream & print(std::ostream & os) const = 0;
};

template <class T> class Pi : public PiBase {
public:
    Pi(long precision = 0);
    ~Pi();

    virtual void compute() override;
    long precision() const override {
        return _precision;
    }

private:
    virtual std::ostream & print(std::ostream & os) const override;

    T _value;
    long _precision;
};

typedef class Pi<double> PiDouble;
typedef class Pi<mpfr_t> PiMulti;

#endif
