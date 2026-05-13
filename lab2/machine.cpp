#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <string>
#include "machine.hpp"
#include "product.cpp"
#include "auxil/auxiliary.hpp"

Machine::Machine(size_t productTypes):
  timeMtx_(productTypes),
  waitTime_(0)
{}

void Machine::setTime(size_t operPos, int time)
{
  timeMtx_[operPos] = time;
}

int Machine::getTime(size_t operPos)
{
  return timeMtx_[operPos];
}

void Machine::addProduct(Product nextPr)
{
  incomingBox_.push(nextPr);
  waitTime_ += timeMtx_[nextPr.getOperation()];
}

Product Machine::handleProduct()
{
  Product processed = incomingBox_.front();
  waitTime_ -= timeMtx_[processed.getOperation()];
  processed.execOperation();
  return processed;
}

size_t Machine::getWaitTime()
{
  return waitTime_;
}

void Machine::readIncomingBox(std::istream & in, size_t productTypes, size_t & idCounter)
{
  std::string currLine;
  std::stringstream currStream(currLine);
  int incomingLength = 0;
  currStream >> incomingLength;
  if (!aux::checkBounds(incomingLength, 0, 100000))
  {
    throw std::logic_error(currLine);
  }

  int currOper = 0;
  for (size_t j = 0; j < incomingLength; ++j)
  {
    currStream >> currOper;
    if (!aux::checkBounds(currOper, 0, productTypes))
    {
      throw std::logic_error(currLine);
    }

    incomingBox_.push(Product(idCounter++, currOper));
    waitTime_ += timeMtx_[currOper];
  }

  if (!aux::checkStreams(in, currStream))
  {
    throw std::logic_error(currLine);
  }
}
