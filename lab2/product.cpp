#include <cstddef>

class Product
{
public:
  Product(size_t id, size_t initOper);
  size_t getId();
  void execOperation();
  size_t getOperation();
private:
  size_t id_;
  size_t currOper_;
};

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
