#include <iostream>
#include <string>
#include <math.h>
#include <limits>
//#define UNIT_RAND()    (rand() / (1.0+RAND_MAX))
#define UNIT_RAND()    (rand() / (1.0+RAND_MAX))

//function taken from homework hint
double rand_normal(double mean, double dev)
{
  static int saved = 0;
  static double y;
  double px, py, d2, x, u;

  if (saved) {
    saved = 0;
    return y * dev + mean;
  }

  do {
    px = UNIT_RAND() * 2.0 - 1.0; /* random b/w [-1,1) */
    py = UNIT_RAND() * 2.0 - 1.0;
    d2 = px * px + py * py;
  } while (d2 == 0.0 || d2 > 1.0); // find a random point in a unit circle

  u = sqrt(-2.0 * log(d2) / d2);
  x = px * u;
  y = py * u;            // save the other value for the next call
  saved = 1;
  return x * dev + mean;
}

//main function, creates array with values from rand_normal function with params: 0, 1
int main(){
//user input to create size of array
  int n;
  bool inputValid = false;

  do {
    std::cout << "Enter a positive integer (less than 10000): ";
    std::cin >> n;
  } while (n <= 0 || n > 10000);
  
  double *arr = new double[n]; // dynamically creates array
  
  for (size_t i = 0; i < n; i++) {
    double x = rand_normal(0,1);
    arr[i] = x;
    }

  size_t r = sizeof(arr)/sizeof(arr[0]);

    // loop through and print array elements
    for (size_t i = 0; i < n; i++) {
        std::cout << "Array item (" + std::to_string(i + 1) + "): " + std::to_string(arr[i]) << '\n';
    }

  delete[] arr; //deletes array
  return 0;
}