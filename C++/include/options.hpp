/*
 * Vikman Fernandez-Castro
 * February 5, 2022
 */

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

class Options {
public:
    Options(int argc, char * const argv[]);

    enum Mode { Double, Multi };

    inline Mode mode() const {
        return _mode;
    }

    inline long precision() const {
        return _precision;
    }

private:
    Mode _mode;
    long _precision;
};

#endif
