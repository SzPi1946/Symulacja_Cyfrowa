#ifndef RANDOM_GENERATOR_H_
#define RANDOM_GENERATOR_H_

#include <string>
#include "wirelessnetwork.h"
#include "broadcaststation.h"

class UniformGenerator
{
public:
  UniformGenerator(int kernel);
  virtual ~UniformGenerator();

  // Draws number between <0,1>
  double Rand();
  int ReturnKernel();
  int Rand(int min, int max);
  int RandEXP(double lambda);
  int RandZeroOne(double probability);

  int get_kernel() { return kernel_; };
private:
  int kernel_;
  const double kM = 2147483647.0;
  static const int kA = 16807;
  static const int kQ = 127773;
  static const int kR = 2836;
};


#endif /* RANDOM_GENERATOR_H_ */

