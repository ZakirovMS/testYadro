#include "outStructs.hpp"
#include <ostream>

void aux::reportStruct(std::ostream & out, const aux::UnifiedStruct & uni)
{
  reportType(out, uni.finishProds, "finish");
  reportType(out, uni.startProds, "start");
  reportType(out, uni.waitProds, "wait");
  reportType(out, uni.readyProds, "ready");
}

std::ostream & aux::operator<<(std::ostream & os, const aux::EdgeStruct & e)
{
  os << e.time << " " << e.id << " " << e.prodType << " " << e.machineId;
  return os;
}

std::ostream & aux::operator<<(std::ostream & os, const aux::readyStruct & r)
{
  os << r.time << " " << r.id << " " << r.machineId;
  return os;
}

std::ostream & aux::operator<<(std::ostream & os, const aux::waitStruct & w)
{
  os << w.time << " " << w.id << " " << w.prodType << " " << w.machineId << " " << w.beforeQuantity;
  return os;
}
