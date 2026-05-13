#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <string>
#include "product.cpp"

namespace
{
  bool checkBounds(int num, int left, int right)
  {
    if (num < left || num > right)
    {
      return false;
    }

    return true;
  }
}

class Machine
{
public:
  Machine(size_t productTypes);
  void setTime(size_t operPos, int time);
  int getTime(size_t operPos);
  void addProduct(Product nextPr);
  Product handleProduct();
  size_t getWaitTime();
private:
  size_t waitTime_;
  std::queue< Product > incomingBox_;
  std::vector< int > timeMtx_;
};

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
