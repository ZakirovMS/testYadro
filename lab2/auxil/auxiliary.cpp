#include "auxiliary.hpp"

bool aux::checkBounds(int num, int left, int right)
{
  if (num < left || num > right)
  {
      return false;
  }

  return true;
}

bool aux::checkStreams(std::istream & in, std::stringstream & ss)
{
  if (in.fail() || ss.fail() || ss.peek() != '\n')
  {
    return false;
  }

  return true;
}
