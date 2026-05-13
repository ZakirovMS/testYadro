#include <sstream>
#include <string>
#include <list>
#include <limits>
#include <utility>
#include "factory.hpp"
#include "machine.hpp"
#include "auxil/auxiliary.hpp"
#include "outStructs.hpp"

Factory::Factory(std::istream & in):
  currTime_(0),
  timeUntilNext_(0),
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
  for (size_t i = 0; i < machinesQuantity_ - 1; ++i)
  {
    getline(in, currLine);
    currStream.str(currLine);
    machines_[i].readIncomingBox(currStream, prodTypes_, idCounter);
    if (!aux::checkStreams(in, currStream))
    {
      throw(currLine);
    }
  }

  getline(in, currLine);
  currStream.str(currLine);
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
    reportType(out, prevStructs_.finishProds, "finish");
    reportType(out, prevStructs_.startProds, "start");
    reportType(out, prevStructs_.waitProds, "wait");
    reportType(out, prevStructs_.readyProds, "ready");
    out << "stop " << currTime_;
    end_ = true;
    return;
  }

  UnifiedStruct currStructs;
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
      correctInsert(prevStructs_.startProds, {currTime_, started.getId(), started.getOperation(), i});
    }
    else if (machines_[i].isStarted())
    {
      machines_[i].setStarted(false);
    }

    handled = machines_[i].handleProduct(timeUntilNext_);
    if (handled != std::nullopt)
    {
      const Product & finished = machines_[i].getCurrProd();
      currStructs.finishProds.push_back({currTime_ + timeUntilNext_, finished.getId(), finished.getOperation(), i});
      if (finished.getOperation() == prodTypes_ - 1)
      {
        currStructs.readyProds.push_back({currTime_ + timeUntilNext_, finished.getId(), i});
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
          currStructs.waitProds.push_back({currTime_ + timeUntilNext_, finished.getId(), finished.getOperation(),
            mcID, machines_[mcID].getIncomingBoxSize()});
        }
        else
        {
          correctInsert(currStructs.startProds, {currTime_ + timeUntilNext_, finished.getId(), finished.getOperation(), mcID});
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

  reportType(out, prevStructs_.finishProds, "finish");
  reportType(out, prevStructs_.startProds, "start");
  reportType(out, prevStructs_.waitProds, "wait");
  reportType(out, prevStructs_.readyProds, "ready");
  std::swap(currStructs, prevStructs_);
  currTime_ += timeUntilNext_;
  timeUntilNext_ = newTimeUntilNext;
}

bool Factory::isEnd()
{
  return end_;
}

void Factory::correctInsert(std::list< EdgeStruct > & str, EdgeStruct ins) {
    auto it = str.begin();
    while (it != str.end() && it->id < ins.id)
    {
        ++it;
    }

    str.insert(it, ins);
}
