
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
  void handleUntilNext(std::ostream & out);
private:

  template < typename T >
  void reportType(std::ostream & out, const std::list< T > & prods, const std::string & message);
  int prodTypes_;
  int machinesQuantity_;
  std::vector< Machine > machines_;
  size_t currTime_;
  size_t timeUntilNext_;

  UnifiedStruct prevVal;
};

template< typename T >
void Factory::reportType(std::ostream & out, const std::list< T > & prods, const std::string & message)
{
  if (prods.empty())
  {
    return;
  }

  auto it = prods.begin();
  out << message << ' ' << *it;
  ++it;
  for (; it != prods.end(); ++it)
  {
    out << "\n" << message << ' ' << *it;
  }
}
#endif
