#include <sstream>
#include <string>
#include <list>
#include <limits>
#include "factory.hpp"
#include "machine.hpp"
#include "auxil/auxiliary.hpp"
#include "outStructs.hpp"

Factory::Factory(std::istream & in):
  currTime_(0),
  timeUntilNext_(std::numeric_limits< size_t >::max())
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
  for (size_t i = 0; i < machinesQuantity_ - 1; ++i)
  {
    getline(in, currLine);
    std::stringstream currStream(currLine);
    machines_[i].readIncomingBox(currStream, prodTypes_, idCounter);
    if (!aux::checkStreams(in, currStream))
    {
      throw(currLine);
    }
  }

  getline(in, currLine);
  std::stringstream currStream(currLine);
  machines_[machinesQuantity_ - 1].readIncomingBox(currStream, prodTypes_, idCounter);
  if (!aux::checkStreams(in, currStream, EOF))
  {
    throw(currLine);
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
    out << "stop " << currTime_;
    return;
  }

  std::list< EdgeStruct > startProds;
  std::list< EdgeStruct > finishProds;
  std::list< readyStruct > readyProds;
  std::list< waitStruct > waitProds;

  std::optional< Product > handled = std::nullopt;
  size_t newTimeUntilNext = std::numeric_limits< size_t >::max();
  for (size_t i = 0; i < machinesQuantity_; ++i)
  {
    if (machines_[i].isIncomingBoxEmpty())
    {
      continue;
    }
    
    if (machines_[i].getHandledTime() == 0 && !machines_[i].isStarted())
    {
      const Product & started = machines_[i].getCurrProd();
      startProds.push_back({currTime_, started.getId(), started.getOperation(), i});
    }
    else if (machines_[i].isStarted())
    {
      machines_[i].setStarted(false);
    }

    handled = machines_[i].handleProduct(timeUntilNext_);
    if (handled != std::nullopt)
    {
      const Product & finished = machines_[i].getCurrProd();
      finishProds.push_back({currTime_ + timeUntilNext_, finished.getId(), finished.getOperation(), i});
      if (finished.getOperation() == prodTypes_ - 1)
      {
        readyProds.push_back({currTime_ + timeUntilNext_, finished.getId(), i});
      }
      else
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

        if (!machines_[mcID].isIncomingBoxEmpty())
        {
          waitProds.push_back({currTime_ + timeUntilNext_, finished.getId(), finished.getOperation(),
            mcID, machines_[mcID].getIncomingBoxSize()});
        }
        else
        {
          startProds.push_back({currTime_ + timeUntilNext_, finished.getId(), finished.getOperation(), mcID});
          machines_[mcID].setStarted(true);
        }

        machines_[mcID].addProduct(finished);
      }
    }

    if (!machines_[i].isIncomingBoxEmpty() && newTimeUntilNext > machines_[i].getUntilNextTime())
    {
      newTimeUntilNext = machines_[i].getUntilNextTime();
    }
  }

  reportType(out, finishProds, "finish");
  reportType(out, startProds, "start");
  reportType(out, waitProds, "wait");
  reportType(out, readyProds, "ready");
  currTime_ += timeUntilNext_;
  timeUntilNext_ = newTimeUntilNext;
}
