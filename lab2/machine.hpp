#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <cstddef>
#include <vector>
#include <queue>
#include <istream>
#include "product.hpp"

class Machine
{
public:
  Machine(size_t productTypes);
  void setTime(size_t operPos, int time);
  int getTime(size_t operPos);
  void addProduct(Product nextPr);
  Product handleProduct();
  size_t getWaitTime();
  void readIncomingBox(std::istream & in, size_t productTypes, size_t & idCounter);
private:
  size_t waitTime_;
  std::queue< Product > incomingBox_;
  std::vector< int > timeMtx_;
};

#endif
