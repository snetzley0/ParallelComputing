// Stephen Netzley
// 9/15/2021
// ITCS-3145

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>

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

  if (argc < 6) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity>"<<std::endl;
    return -1;
  }

  float integral;
  float x;
  float a, b, n, sum, width;
  int functionid, intensity;
  
  functionid = atoi(argv[1]);
  a = atoi(argv[2]);
  b = atoi(argv[3]);
  n = atoi(argv[4]);
  intensity = atoi(argv[5]);

  // start time measurement
  auto start = std::chrono::system_clock::now();

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
  
  // calculate width
  width = ((b - a) / n);
  
  // **CHECK FINAL**
  integral = width * sum;

  // stop time measurement and calculate total
  auto end = std::chrono::system_clock::now();

  // calculate final time and format
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  float newTime = time.count() / 1000.000;

  // output results
  std::cout << integral << std::endl;
  std::cerr << newTime << std::endl;
  
  // END
  return 0;
}
