#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <list>
#include <istream>
#include <vector>
#include "machine.hpp"
#include "product.hpp"
#include "outStructs.hpp"
#include "auxil/auxiliary.hpp"

class Factory
{
public:
  Factory(std::istream & in);
  void handleUntilNext(std::ostream & out);
  bool isEnd();
private:
  template < typename T >
  void reportType(std::ostream & out, const std::list< T > & prods, const std::string & message);
  void correctInsert(std::list< EdgeStruct > & str, EdgeStruct ins);

  bool end_;
  int prodTypes_;
  int machinesQuantity_;
  std::vector< Machine > machines_;
  size_t currTime_;
  size_t timeUntilNext_;
  UnifiedStruct prevStructs_;
};

template< typename T >
void Factory::reportType(std::ostream & out, const std::list< T > & prods, const std::string & message)
{
  if (prods.empty())
  {
    return;
  }

  for (auto it = prods.begin(); it != prods.end(); ++it)
  {
    out << message << ' ' << *it << '\n';
  }
}
#endif
