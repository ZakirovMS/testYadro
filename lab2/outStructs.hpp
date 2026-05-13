#ifndef OUTSTRUCT_HPP
#define OUTSTRUCT_HPP
#include <cstddef>

struct UnifiedStruct
{
  std::list< EdgeStruct > prevStartProds;
  std::list< EdgeStruct > prevFinishProds;
  std::list< readyStruct > prevReadyProds;
  std::list< waitStruct > prevWaitProds;
};


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

std::ostream & operator<<(std::ostream & os, const EdgeStruct & e)
{
  os << e.time << " " << e.id << " " << e.prodType << " " << e.machineId;
  return os;
}
std::ostream & operator<<(std::ostream & os, const readyStruct & r)
{
  os << r.time << " " << r.id << " " << r.machineId;
  return os;
}
std::ostream & operator<<(std::ostream & os, const waitStruct & w)
{
  os << w.time << " " << w.id << " " << w.prodType << " " << w.machineId << " " << w.beforeQuantity;
  return os;
}

#endif