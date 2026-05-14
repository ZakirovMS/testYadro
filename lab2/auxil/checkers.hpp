#ifndef CHECKERS_HPP
#define CHECKERS_HPP
#include <istream>
#include <sstream>

namespace aux
{
  bool checkBounds(int num, int left, int right);
  bool checkStreams(std::istream & in, std::stringstream & ss, char lastSymbol = EOF);
}

#endif
