#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <list>
#include <istream>
#include <vector>
#include "machine.hpp"
#include "product.hpp"
#include "auxil/checkers.hpp"
#include "auxil/outStructs.hpp"

class Factory
{
public:
  Factory(std::istream & in);
  void handleUntilNext(std::ostream & out);
  bool isEnd() const;

private:
  void correctInsert(std::list< aux::EdgeStruct > & str, aux::EdgeStruct ins);
  size_t selectOptimalMachine() const;

  int prodTypes_;
  int machinesQuantity_;
  bool end_;
  size_t currTime_;
  size_t timeUntilNext_;
  std::vector< Machine > machines_;
  aux::UnifiedStruct prevStructs_;
};

#endif
