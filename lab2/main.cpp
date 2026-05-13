#include <iostream>
#include <fstream>
#include <string>
#include "factory.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input file>" << '\n';
    return 1;
  }

  std::ifstream inFile(argv[1]);
  if (!inFile) {
    std::cerr << "Error: cannot open file " << argv[1] << '\n';
    return 1;
  }

  try
  {
    Factory factory(inFile);
    while (!factory.isEnd())
    {
      factory.handleUntilNext(std::cout);
    }

    factory.handleUntilNext(std::cout);
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}