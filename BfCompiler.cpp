#include "BfCompiler.hpp"

BfCompiler::BfCompiler(std::string codeBuffer, unsigned long long memorySize)
{
    this->codeBuffer = codeBuffer;
    this->memorySize = memorySize;
    this->pointer = 0;

    this->startLoop = std::stack<unsigned long>();
    this->endLoop = std::stack<unsigned long>();

    this->memoryBuffer = (signed char *) malloc(memorySize * sizeof(signed char));
    for (unsigned long i = 0; i < memorySize; i++)
        memoryBuffer[i] = 0;
}

BfCompiler::~BfCompiler()
{
    free(memoryBuffer);
}

int BfCompiler::Compile()
{
    for (unsigned long counter = 0; counter < codeBuffer.size(); counter++)
    {
        char op = codeBuffer[counter];
        switch (op)
        {
            case '>':
                // Increases Memory Pointer
                pointer = (pointer + 1) % memorySize;
                break;
            case '<':
                // Decreases Memory Pointer
                pointer = !pointer ? memorySize - 1 : pointer - 1;
                break;
            case '+':
                // Increases Value at memoryBuffer[pointer]
                memoryBuffer[pointer]++;
                break;
            case '-':
                // Decreases Value at memoryBuffer[pointer]
                memoryBuffer[pointer]--;
                break;
            case '[':
                // If memoryBuffer[pointer] != 0 : Loop
                if (!CompleteLoop(counter))
                    return 2;
                if (!memoryBuffer[pointer])
                {
                    counter = endLoop.top();
                    startLoop.pop();
                    endLoop.pop();
                }
                break;
            case ']':
                // If memoryBuffer[loopPointer] != 0 : Jump to Loop
                if (!endLoop.size() || endLoop.top() != counter)
                    return 2;
                if (!memoryBuffer[pointer])
                {
                    startLoop.pop();
                    endLoop.pop();
                } else
                {
                    counter = startLoop.top();
                }
                break;
            case ',':
                // Get Character
                std::cin >> memoryBuffer[pointer];
                break;
            case '.':
                // Put Character
                std::cout << memoryBuffer[pointer];
                break;
            case '\n':
                // Skip
            case ' ':
                // Skip
                break;
            default:
                return 1;
        }
    }

    return 0;
}

bool BfCompiler::CompleteLoop(unsigned long position)
{
    for (int i = position + 1; i < codeBuffer.size(); i++)
    {
        if (codeBuffer[i] == ']')
        {
            startLoop.push(position);
            endLoop.push(i);
            return true;
        }
    }

    return false;
}