#ifndef BFCOMPILER_H
#define BFCOMPILER_H

#include <iostream>
#include <string>
#include <stack>

class BfCompiler
{
private:
    std::string codeBuffer;
    unsigned long memorySize;
    signed char *memoryBuffer;
    unsigned long pointer;
    std::stack<unsigned long> startLoop;
    std::stack<unsigned long> endLoop;
public:
    BfCompiler(std::string codeBuffer, unsigned long long memorySize);
    ~BfCompiler();
    int Compile();
    bool CompleteLoop(unsigned long position);
};

#endif