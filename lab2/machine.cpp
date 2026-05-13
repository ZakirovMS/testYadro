#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <string>
#include "machine.hpp"
#include "product.hpp"
#include "auxil/auxiliary.hpp"

Machine::Machine(size_t productTypes):
  timeMtx_(productTypes),
  waitTime_(0),
  handledTime_(0),
  isStarted_(false)
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

std::optional< Product > Machine::handleProduct(size_t time)
{
  handledTime_ += time;
  Product processed = incomingBox_.front();
  
  if (handledTime_ == getTime(incomingBox_.front().getOperation()))
  {
    incomingBox_.pop();
    waitTime_ -= handledTime_;
    processed.execOperation();
    handledTime_ = 0;
    return processed;
  }
  else if (time > getTime(processed.getOperation()))
  {
    throw std::logic_error("Error: more time has passed than required");
  }

  return std::nullopt;
}

bool Machine::isIncomingBoxEmpty()
{
  return incomingBox_.empty();
}

size_t Machine::getIncomingBoxSize()
{
  return incomingBox_.size();
}

size_t Machine::getWaitTime()
{
  return waitTime_;
}

size_t Machine::getHandledTime()
{
  return handledTime_;
}

size_t Machine::getUntilNextTime()
{
  return getTime(incomingBox_.front().getOperation()) - handledTime_; 
}

const Product & Machine::getCurrProd()
{
  return incomingBox_.front();
}

void Machine::readIncomingBox(std::stringstream & ss, size_t productTypes, size_t & idCounter)
{
  int incomingLength = 0;
  ss >> incomingLength;
  if (!aux::checkBounds(incomingLength, 0, 100000))
  {
    ss.setstate(std::ios::failbit);
    return;
  }

  int currOper = 0;
  for (size_t j = 0; j < incomingLength; ++j)
  {
    ss >> currOper;
    if (!aux::checkBounds(currOper, 0, productTypes - 1))
    {
      ss.setstate(std::ios::failbit);
      return;      
    }

    incomingBox_.push(Product(idCounter++, currOper));
    waitTime_ += timeMtx_[currOper];
  }
}

bool Machine::isStarted()
{
  return isStarted_;
}

void Machine::setStarted(bool val)
{
  isStarted_ = val;
}

