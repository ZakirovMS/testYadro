#include <iostream>
#include <fstream>
#include <string>
#include "factory.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error in arguments" << '\n';
    return 1;
  }

  std::ifstream inFile(argv[1]);
  if (!inFile)
  {
    std::cerr << "Error in file opening" << '\n';
    return 1;
  }

  try
  {
    Factory factory(inFile);
    while (!factory.isEnd())
    {
      factory.handleUntilNext(std::cout);
    }
    std::cout << '\n';
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
