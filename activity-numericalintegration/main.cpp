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
  int x, sum;
  int functionid, a, b, n, intensity;
  functionid = atoi(argv[1]);
  a = atoi(argv[2]);
  b = atoi(argv[3]);
  n = atoi(argv[4]);
  intensity = atoi(argv[5]);

  /* test
  std::cout << functionid << std::endl;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << n << std::endl;
  std::cout << intensity << std::endl; */

  // start time measurement
  auto start = std::chrono::system_clock::now();
  
  // sum of function from 0 to n - 1
  for ( int i = 0; i < n; i++) {
    sum += (a + (i + .5) * ((b - a) / n));
  }

  // **CHECK SUM**
  
  // multiply sum with (b - a) / n
  x = ((b - a) / n) * sum;

  // **CHECK X**

  // determine which function to calculate
  if (functionid == 1) {
    integral = f1(x, intensity);
  }
  else if (functionid == 2) {
    integral = f2(x, intensity);
  }
  else if (functionid == 3) {
    integral = f3(x, intensity);
  }
  else if (functionid == 4) {
    integral = f4(x, intensity);
  }

  //stop time measurement and calculate total
  auto end = std::chrono::system_clock::now();

  // **MAKE MORE ACCURATE**
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  float newTime = time.count() / 1000.000;
  
  std::cout << integral << std::endl;
  std::cerr << newTime << std::endl;
  
  
  return 0;
}
