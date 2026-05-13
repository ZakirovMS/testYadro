#include "outStructs.hpp"
#include <ostream>

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