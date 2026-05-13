
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <istream>
#include <vector>
#include "machine.hpp"
#include "product.hpp"

class Factory
{
public:
  Factory(std::istream & in);
private:
  int productTypes_;
  int machineQuantity_;
  std::vector< Machine > machines_;
};

#endif
