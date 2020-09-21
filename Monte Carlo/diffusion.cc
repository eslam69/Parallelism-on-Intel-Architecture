#include <mkl.h>
#include "distribution.h"

int diffusion(const int n_particles,
              const int n_steps,
              const float x_threshold,
              const float alpha,
              VSLStreamStatePtr rnStream)
{
  int n_escaped = 0;
   // Store the Distances of each particle -- Initialize to Zero
  float x[n_particles];
  x [0:n_particles] = 0.0f;

  for (int i = 0; i < n_particles; i++)
  {
    for (int j = 0; j < n_steps; j++)
    {
      // float rn;
      float rn[n_particles];

      //Intel MKL function to generate random numbers
      // vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rnStream, 1, &rn, -1.0, 1.0);
      vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rnStream, n_particles, rn, -1.0, 1.0);

      x += dist_func(alpha, rn);
    }
    for(int x =0 ; x<n_particles; x++){
      if (x > x_threshold)
      n_escaped++;
    }
    
  }
  return n_escaped;
}