#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <cstddef>

class Product
{
public:
  Product::Product() = default;
  Product(size_t id, size_t initOper);
  size_t getId() const;
  void execOperation();
  size_t getOperation() const;
private:
  size_t id_;
  size_t currOper_;
};

#endif
