#ifndef TAPE_INTERFACE_H
#define TAPE_INTERFACE_H

#include <vector>
#include <string>

class TapeInterface {
public:
    virtual ~TapeInterface() = default;

    virtual void write(int value) = 0;
    virtual int read() = 0;
    virtual bool hasMoreData() const = 0;
    virtual void shift(bool side) = 0;
    virtual void rewind() = 0;
};

#endif // TAPE_INTERFACE_H
