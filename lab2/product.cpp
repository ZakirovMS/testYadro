#include <cstddef>
#include "product.hpp"

Product::Product(size_t id, size_t initOper):
  id_(id),
  currOper_(initOper)
{}

size_t Product::getId()
{
  return id_;
}

void Product::execOperation()
{
  ++currOper_;
}

size_t Product::getOperation()
{
  return currOper_;
}
