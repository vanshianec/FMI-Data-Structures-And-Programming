#ifndef _EXECUTABLE_H
#define _EXECUTABLE_H

class Executor;

class Executable
{
public:
    virtual void accept(Executor*) = 0;
};

#endif
