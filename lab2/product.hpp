#ifndef PRODUCT_HPP
#define PRODUCT_HPP

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

#endif
