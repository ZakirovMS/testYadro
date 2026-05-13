#include <sstream>
#include <string>
#include "factory.hpp"
#include "machine.hpp"
#include "auxil/auxiliary.hpp"

Factory::Factory(std::istream & in)
{
  std::string currLine;
  getline(in, currLine);
  std::stringstream currStream(currLine);
  currStream >> productTypes_ >> machineQuantity_;

  if (!aux::checkStreams(in, currStream) || !aux::checkBounds(productTypes_, 1, 100) || !aux::checkBounds(machineQuantity_, 1, 100))
  {
    throw std::logic_error(currLine);
  }

  machines_ = std::vector< Machine >(machineQuantity_, Machine(productTypes_));
  for (size_t i = 0; i < productTypes_ - 1; ++i)
  {
    getline(in, currLine);
    std::stringstream currStream(currLine);
    int currTime = 0;
    for (size_t j = 0; j < machineQuantity_; ++j)
    {
      currStream >> currTime;
      if (!aux::checkBounds(currTime, 0, 10000))
      {
        throw std::logic_error(currLine);
      }

      machines_[j].setTime(i, currTime);
    }

    if (!aux::checkStreams(in, currStream))
    {
      throw std::logic_error(currLine);
    }
  }

  size_t idCounter = 0;
  for (size_t i = 0; i < machineQuantity_; ++i)
  {
    machines_[i].readIncomingBox(in, productTypes_, idCounter);
  }
  
  if (idCounter > 100000)
  {
    throw std::logic_error(currLine);
  }
}
