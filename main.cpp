#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<chrono>
#include"BfCompiler.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cout << "Invalid Parameters" << std::endl;
        std::cout << "Default Format: " << "main.exe <file name>" << std::endl;

        return -1;
    }

    std::string filename(argv[1]);
    std::ifstream bfFile(filename);
    if (!bfFile.is_open())
    {
        std::cout << "File Not Found" << std::endl;
        return -1;
    }

    std::stringstream buffer;
    buffer << bfFile.rdbuf();

    std::string bfCodeStr = buffer.str();

    auto startTime = std::chrono::high_resolution_clock::now();
    BfCompiler bfCompiler = BfCompiler(bfCodeStr, 30000);
    int status = bfCompiler.Compile();
    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << std::endl;
    std::chrono::duration<double> duration = endTime - startTime;
    if (!status)
    {
        std::cout << "Successful Compilation in " << duration.count() << " Seconds" << std::endl;
    } else if (status == 1)
    {
        std::cout << "Failed Compilation in " << duration.count() << " Seconds" << std::endl;
        std::cout << "Invalid Character Found" << std::endl;
    }

    return 0;
}