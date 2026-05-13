#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <cstddef>
#include <vector>
#include <queue>
#include <istream>
#include <optional>
#include "product.hpp"

class Machine
{
public:
  Machine(size_t productTypes);
  void setTime(size_t operPos, int time);
  int getTime(size_t operPos);
  void addProduct(Product nextPr);
  std::optional< Product > handleProduct(size_t time);
  bool isIncomingBoxEmpty();
  size_t getIncomingBoxSize();
  size_t getWaitTime();
  size_t getHandledTime();
  size_t getUntilNextTime();
  const Product & getCurrProd();
  bool isStarted();
  void setStarted(bool val);
  void readIncomingBox(std::stringstream & ss, size_t productTypes, size_t & idCounter);
private:
  size_t waitTime_;
  std::queue< Product > incomingBox_;
  std::vector< int > timeMtx_;
  size_t handledTime_;
  bool isStarted_;
};

#endif
