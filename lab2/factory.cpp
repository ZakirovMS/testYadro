#include <sstream>
#include <string>
#include "machine.cpp"


namespace
{
  bool checkBounds(int num, int left, int right)
  {
    if (num < left || num > right)
    {
      return false;
    }

    return true;
  }
}

class Factory
{
public:
  Factory(std::istream & in);
private:
  int productTypes_;
  int machineQuantity_;
  std::vector< Machine > machines_;
  std::vector< Product > products_;
};

Factory::Factory(std::istream & in)
{
  std::string currLine;
  getline(in, currLine);
  std::stringstream currStream(currLine);
  currStream >> productTypes_ >> machineQuantity_;

  if (in.fail() || currStream.fail() || currStream.peek() != '\n')
  {
    throw std::logic_error(currLine);
  }
  else if (!checkBounds(productTypes_, 1, 100) || !checkBounds(machineQuantity_, 1, 100))
  {
    throw std::logic_error(currLine);
  }

  machines_ = std::vector< Machine >(machineQuantity_, Machine(productTypes_));
  for (size_t i = 0; i < productTypes_ - 1; ++i)
  {
    getline(in, currLine);
    std::stringstream currStream(currLine);
    int currTime = 0;
    for (size_t j = 0; j < machineQuantity_; ++j)
    {
      currStream >> currTime;
      if (!checkBounds(currTime, 0, 10000))
      {
        throw std::logic_error(currLine);
      }

      machines_[j].setTime(i, currTime);
    }

    if (in.fail() || currStream.fail() || !checkBounds(currTime, 0, 10000))
    {
      throw std::logic_error(currLine);
    }
  }

  size_t idCounter = 0;
  int productQuantity = 0;
  int productOper = 0;
  for (size_t i = 0; i < machineQuantity_; ++i)
  {
    getline(in, currLine);
    std::stringstream currStream(currLine);
    currStream >> productQuantity;

    for (size_t j = 0; j < productQuantity; ++j)
    {
      currStream >> productOper;
      if (productOper < 0)
      {
        throw std::logic_error(currLine);
      }

      machines_[i].addProduct(Product(idCounter++, productOper));
    }

    if (in.fail() || currStream.fail() || productQuantity < 0)
    {
      throw std::logic_error(currLine);
    }
  }
}
