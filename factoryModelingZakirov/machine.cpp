#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <string>
#include "machine.hpp"
#include "product.hpp"
#include "auxil/checkers.hpp"

Machine::Machine(size_t productTypes):
  timeMtx_(productTypes),
  waitTime_(0),
  handledTime_(0),
  isStarted_(false)
{}

void Machine::addProduct(Product nextPr)
{
  if (!currentProduct_.has_value())
  {
    currentProduct_ = nextPr;
  }
  else
  {
    incomingBox_.push(nextPr);
    waitTime_ += getTime(nextPr.getOperation());
  }
}

std::optional< Product > Machine::handleProduct(size_t time)
{
  if (!currentProduct_.has_value())
  {
    return std::nullopt;
  }

  handledTime_ += time;
  if (handledTime_ == getTime(currentProduct_.value().getOperation()))
  {
    Product processed = currentProduct_.value();
    currentProduct_ = std::nullopt;
    processed.execOperation();
    handledTime_ = 0;
    return processed;
  }
  else if (handledTime_ > getTime(currentProduct_.value().getOperation()))
  {

    throw std::logic_error("Error: more time has passed than required");
  }

  return std::nullopt;
}

void Machine::initiateHandle()
{
  if (!isIncomingBoxEmpty() && !currentProduct_.has_value())
  {
    currentProduct_ = incomingBox_.front();
    incomingBox_.pop();
    waitTime_ -= getTime(currentProduct_.value().getOperation());
  }
}

void Machine::readIncomingBox(std::istream & in, size_t productTypes, size_t & idCounter)
{
  std::string currLine;
  getline(in, currLine);
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
    if (!aux::checkBounds(currOper, 0, productTypes - 1))
    {
      throw std::logic_error(currLine);   
    }

    addProduct(Product(idCounter++, currOper));
  }

  if (!aux::checkStreams(in, currStream))
  {
    throw std::logic_error(currLine);
  }
}

bool Machine::isStarted() const
{
  return isStarted_;
}

bool Machine::isIncomingBoxEmpty() const
{
  return incomingBox_.empty();
}

void Machine::setStarted(bool val)
{
  isStarted_ = val;
}

void Machine::setTime(size_t operPos, int time)
{
  timeMtx_[operPos] = time;
}

int Machine::getTime(size_t operPos) const
{
  return timeMtx_[operPos];
}

size_t Machine::getIncomingBoxSize() const
{
  return incomingBox_.size();
}

size_t Machine::getWaitTime() const
{
  return waitTime_;
}

size_t Machine::getHandledTime() const
{
  return handledTime_;
}

size_t Machine::getUntilNextTime() const
{
  if (currentProduct_.has_value())
  {
    return getTime(currentProduct_.value().getOperation()) - handledTime_; 
  }

  throw std::logic_error("No products in the machine");
}

const std::optional< Product > & Machine::getCurrProd() const
{
  return currentProduct_;
}
