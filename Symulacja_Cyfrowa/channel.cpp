#include "channel.h"
#include "logger.h"
#include <iostream>

Channel::Channel(Logger* logger)
{
  log_ = logger;
  log_->Info("The channel has been created");
}

Channel::~Channel()
{
  log_->Info("The channel has been removed");
}


void Channel::CheckError()
{
}

void Channel::CSMA_CA()
{
}

bool Channel::return_free()
{
  return free_;
}

bool Channel::return_collision()
{
  return collision_;
}

void Channel::Set_Status(bool status)
{
  free_ = status;
}