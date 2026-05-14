#ifndef OUTSTRUCT_HPP
#define OUTSTRUCT_HPP
#include <cstddef>
#include <list>
#include <ostream>
namespace aux
{
  struct EdgeStruct
  {
    size_t time;
    size_t id;
    size_t prodType;
    size_t machineId;
  };

  struct readyStruct
  {
    size_t time;
    size_t id;
    size_t machineId;
  };

  struct waitStruct
  {
    size_t time;
    size_t id;
    size_t prodType;
    size_t machineId;
    size_t beforeQuantity;
  };

  struct UnifiedStruct
  {
    std::list< EdgeStruct > finishProds;
    std::list< EdgeStruct > startProds;
    std::list< readyStruct > readyProds;
    std::list< waitStruct > waitProds;
  };

  template < typename T >
  void reportType(std::ostream & out, const std::list< T > & prods, const std::string & message);
  void reportStruct(std::ostream & out, const aux::UnifiedStruct & uni);

  std::ostream & operator<<(std::ostream & os, const aux::EdgeStruct & e);

  std::ostream & operator<<(std::ostream & os, const aux::readyStruct & r);

  std::ostream & operator<<(std::ostream & os, const aux::waitStruct & w);
}

template< typename T >
void aux::reportType(std::ostream & out, const std::list< T > & prods, const std::string & message)
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
