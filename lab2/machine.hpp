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

  void addProduct(Product nextPr);
  std::optional< Product > handleProduct(size_t time);
  void readIncomingBox(std::istream & in, size_t productTypes, size_t & idCounter);

  bool isStarted() const;
  bool isIncomingBoxEmpty() const;
  void setStarted(bool val);
  void setTime(size_t operPos, int time);
  int getTime(size_t operPos) const;
  size_t getIncomingBoxSize() const;
  size_t getWaitTime() const;
  size_t getHandledTime() const;
  size_t getUntilNextTime() const;
  const Product & getCurrProd() const;

private:
  size_t waitTime_;
  std::queue< Product > incomingBox_;
  std::vector< int > timeMtx_;
  size_t handledTime_;
  bool isStarted_;
};

#endif
