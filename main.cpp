#include <iostream>
#include <string>
#include <math.h>
#include <limits>

// Macro to calculate a random number between 0 and 1
#define UNIT_RAND()    (rand() / (1.0 + RAND_MAX))

// Function to generate a random number with normal distribution
double rand_normal(double mean, double dev)
{
  // Save value from previous iteration
  static int saved = 0;
  static double y;

  // Variables for generating a random point in the unit circle
  double px, py, d2, x, u;

  // Check if the value from the previous iteration is saved
  if (saved) {
    saved = 0;
    return y * dev + mean;
  }

  // Find a random point in the unit circle
  do {
    px = UNIT_RAND() * 2.0 - 1.0; /* random between [-1,1) */
    py = UNIT_RAND() * 2.0 - 1.0;
    d2 = px * px + py * py;
  } while (d2 == 0.0 || d2 > 1.0);

  u = sqrt(-2.0 * log(d2) / d2);
  x = px * u;
  y = py * u; // Save the other value for the next call
  saved = 1;
  return x * dev + mean;
}

int main()
{
  // User input to set the size of the array
  int n;

  // Loop until the user inputs a positive integer within the limits
  do {
    std::cout << "Enter a positive integer (less than 10000): ";
    std::cin >> n;
  } while (n <= 0 || n > 10000);

  // Dynamically create two arrays
  double *arr = new double[n];
  double *X0 = new double[n];

  // Fill the first array with random numbers with normal distribution
  for (int i = 0; i < n; i++) {
    double x = rand_normal(0, 1);
    arr[i] = x;
  }

  // Loop until consensus is reached
  bool not_consensus = true;
  int iteration = 0;
  while (not_consensus) {
    // Update the values in the second array
    for (int i = 0; i < n; i++) {
      int left = i == 0 ? n - 1 : i - 1;
      int right = i == n - 1 ? 0 : i + 1;
      arr[i] = (X0[left] + X0[i] + X0[right]) / 3.0;
    }

    // Check if consensus has been reached
    not_consensus = false;
    for (int i = 0; i < n; i++) {
      if (X0[i] != arr[i]) {
        not_consensus = true;
        break;
      }
    }

    // Update the first array with the new values
    for (int i = 0; i < n; i++) {
      X0[i] = arr[i];
    }

    iteration++;
  }

  // Print the number of iterations required for consensus
  std::cout << "consensus in " << iteration << " iterations" << std::endl;

  delete[] X0;
  delete[] arr;
  return 0;
}