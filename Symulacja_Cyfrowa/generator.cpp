#include "generator.h"
#include <cmath>
#include <iostream>

UniformGenerator::UniformGenerator(int kernel) : kernel_(kernel)
{
  // empty
}

UniformGenerator::~UniformGenerator()
{

}

double UniformGenerator::Rand() //jednostajny
{
  int h = kernel_ / kQ;
  kernel_ = kA * (kernel_ - kQ * h) - kR * h;
  if (kernel_ < 0)
    kernel_ = kernel_ + static_cast<int>(kM);
  return kernel_ / kM;
}

int UniformGenerator::ReturnKernel()
{
  return kernel_;
}

int UniformGenerator::Rand(int min, int max)
{
  return Rand() * (max - min) + min;
}

int UniformGenerator::RandEXP(double lambda) //wykladniczy
{
  auto number = Rand();
  
  double value = -(1.0 / lambda) * log(number);
  return value;
}

int UniformGenerator::RandZeroOne(double probability) //rownomierny
{ 
  auto number = Rand();
  if (number < probability) return 1;
  else return 0;
}