#ifndef OUTSTRUCT_HPP
#define OUTSTRUCT_HPP
#include <cstddef>
#include <list>
#include <ostream>

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


std::ostream & operator<<(std::ostream & os, const EdgeStruct & e);

std::ostream & operator<<(std::ostream & os, const readyStruct & r);

std::ostream & operator<<(std::ostream & os, const waitStruct & w);

#endif