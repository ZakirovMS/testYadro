#include <sstream>
#include <string>
#include <list>
#include <limits>
#include <utility>
#include "factory.hpp"
#include "machine.hpp"
#include "auxil/checkers.hpp"
#include "auxil/outStructs.hpp"

Factory::Factory(std::istream & in):
  currTime_(0),
  timeUntilNext_(std::numeric_limits< size_t >::max()),
  end_(false)
{
  std::string currLine;
  getline(in, currLine);
  std::stringstream currStream(currLine);
  currStream >> prodTypes_ >> machinesQuantity_;

  if (!aux::checkStreams(in, currStream) || !aux::checkBounds(prodTypes_, 1, 100) || !aux::checkBounds(machinesQuantity_, 1, 100))
  {
    throw std::logic_error(currLine);
  }

  machines_ = std::vector< Machine >(machinesQuantity_, Machine(prodTypes_));
  for (size_t i = 0; i < prodTypes_ - 1; ++i)
  {
    getline(in, currLine);
    std::stringstream currStream(currLine);
    int currTime = 0;
    for (size_t j = 0; j < machinesQuantity_; ++j)
    {
      currStream >> currTime;
      if (!aux::checkBounds(currTime, 0, 10000))
      {
        throw std::logic_error(currLine);
      }

      machines_[j].setTime(i, currTime);
    }

    if (!aux::checkStreams(in, currStream))
    {
      throw std::logic_error(currLine);
    }
  }

  size_t idCounter = 0;
  for (size_t i = 0; i < machinesQuantity_; ++i)
  {
    machines_[i].readIncomingBox(in, prodTypes_, idCounter);
    if (machines_[i].getCurrProd() == std::nullopt)
    {
      continue;
    }

    if (timeUntilNext_ > machines_[i].getUntilNextTime())
    {
      timeUntilNext_ = machines_[i].getUntilNextTime();
    }
  }

  if (idCounter > 100000)
  {
    throw std::logic_error(currLine);
  }
}

void Factory::handleUntilNext(std::ostream & out)
{
  if (timeUntilNext_ == std::numeric_limits< size_t >::max())
  {
    aux::reportStruct(out, prevStructs_);
    out << "stop " << currTime_;
    end_ = true;
    return;
  }

  aux::UnifiedStruct currStructs;
  std::optional< Product > handled = std::nullopt;
  size_t newTimeUntilNext = std::numeric_limits< size_t >::max();
  for (size_t i = 0; i < machinesQuantity_; ++i)
  {
    if (machines_[i].getCurrProd() == std::nullopt)
    {
      continue;
    }

    if (machines_[i].getHandledTime() == 0 && !machines_[i].isStarted())
    {
      const Product & started = machines_[i].getCurrProd().value();
      correctInsert(prevStructs_.startProds, {currTime_, started.getId(), started.getOperation(), i});
    }
    else if (machines_[i].isStarted())
    {
      machines_[i].setStarted(false);
    }

    handled = machines_[i].handleProduct(timeUntilNext_);
    if (handled != std::nullopt)
    {
      const Product & finished = handled.value();
      currStructs.finishProds.push_back({currTime_ + timeUntilNext_, finished.getId(), finished.getOperation() - 1, i});
      if (finished.getOperation() == prodTypes_ - 1)
      {
        currStructs.readyProds.push_back({currTime_ + timeUntilNext_, finished.getId(), i});
      }
      else
      {
        size_t mcID = selectOptimalMachine();

        currStructs.waitProds.push_back({currTime_ + timeUntilNext_, finished.getId(), finished.getOperation(), mcID, machines_[mcID].getIncomingBoxSize()});
        machines_[mcID].addProduct(finished);
      }
    }

    machines_[i].initiateHandle();
    if (machines_[i].getCurrProd() != std::nullopt && newTimeUntilNext > machines_[i].getUntilNextTime())
    {
      newTimeUntilNext = machines_[i].getUntilNextTime();
    }
  }

  aux::reportStruct(out, prevStructs_);
  std::swap(currStructs, prevStructs_);
  currTime_ += timeUntilNext_;
  timeUntilNext_ = newTimeUntilNext;
}

bool Factory::isEnd() const
{
  return end_;
}

void Factory::correctInsert(std::list< aux::EdgeStruct > & str, aux::EdgeStruct ins)
{
  auto it = str.begin();
  while (it != str.end() && it->id < ins.id)
  {
    ++it;
  }

  str.insert(it, ins);
}

size_t Factory::selectOptimalMachine() const
{
  size_t minTime = std::numeric_limits< size_t >::max();
  size_t mcID = std::numeric_limits< size_t >::max();
  for (size_t j = 0; j < machinesQuantity_; ++j)
  {
    if (minTime > machines_[j].getWaitTime())
    {
      minTime = machines_[j].getWaitTime();
      mcID = j;
    }
  }

  return mcID;
}
