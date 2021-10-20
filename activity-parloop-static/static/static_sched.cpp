#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cmath>
#include "seq_loop.hpp"


#ifdef __cplusplus
extern "C" {
#endif

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif


int main (int argc, char* argv[]) {

  SeqLoop sl;

  if (argc < 7) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads>"<<std::endl;
    return -1;
  }
  
  float integral;
  float x;
  float a, b, n, sum, width;
  int functionid, intensity, nbthreads;
  
  functionid = atoi(argv[1]);
  a = atoi(argv[2]);
  b = atoi(argv[3]);
  n = atoi(argv[4]);
  intensity = atoi(argv[5]);
  nbthreads = atoi(argv[6]);

  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

  sum = 0;
  
   // NEW TEST
  sl.parfor(0, n, 1,
            [&](int i) -> void{
              // calculate x to pass
              x = (a + (i + .5) * ((b - a) / n));

              // determine function to sum and pass x
              if (functionid == 1) {
                sum += f1(x, intensity);
              }
              else if (functionid == 2) {
                sum += f2(x, intensity);
              }
              else if (functionid == 3) {
                sum += f3(x, intensity);
              }
              else if (functionid == 4) {
                sum += f4(x, intensity);
              }
            }
            );
  /*
  // OLD TEST
  sl.parfor<int>(0, n, 1,
	    [&](int& tls) -> void{
	      tls = 0;
	    },
            [&](int i, int& tls) -> void{
              // calculate x to pass
              x = (a + (i + .5) * ((b - a) / n));

              // determine function to sum and pass x
              if (functionid == 1) {
                tls += f1(x, intensity);
              }
              else if (functionid == 2) {
                tls += f2(x, intensity);
              }
              else if (functionid == 3) {
                tls += f3(x, intensity);
              }
              else if (functionid == 4) {
                tls += f4(x, intensity);
              }
	    },
            [&](int tls) -> void{
              sum += tls;
            }
            );
  */    
/*
  // PREVIOUS
  // summation of function
  int i;
  for ( i = 0; i < n; i++) {
    // calculate x to pass
    x = (a + (i + .5) * ((b - a) / n));

    // determine function to sum and pass x
    if (functionid == 1) {
      sum += f1(x, intensity);
    }
    else if (functionid == 2) {
      sum += f2(x, intensity);
    }
    else if (functionid == 3) {
      sum += f3(x, intensity);
    }
    else if (functionid == 4) {
      sum += f4(x, intensity);
    }  
  }
    */
  
  // calculate width
  width = ((b - a) / n);
  
  // **CHECK FINAL**
  integral = width * sum;

  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start;
  
  std::cout<<integral<<std::endl;
  
  std::cerr<<elapsed_seconds.count()<<std::endl;
  
  // END
  return 0;
}
