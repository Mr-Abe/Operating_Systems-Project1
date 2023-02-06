#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
#include <limits>
#include <iomanip>

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

  // User input to set the mean and standard deviation
  double mean, dev;
  std::cout << "Enter the mean: ";
  std::cin >> mean;

  do {
    std::cout << "Enter the standard deviation: ";
    std::cin >> dev;
  } while (dev <= 0);

  // Dynamically create two arrays
  double *arr_1 = new double[n];
  double *arr_2 = new double[n];

  // Fill the first array with random numbers with normal distribution
  for (int i = 0; i < n; i++) {
    double x = rand_normal(mean, dev);
    arr_1[i] = x;
  }


  bool consensus = false;
  int iteration = 0;
  const double epsilon = 1e-10; // Set the precision to 10 decimal places after the decimal point
  // timer start
  auto start = std::chrono::high_resolution_clock::now();
  // Loop until consensus is reached
  while (consensus == false) {
    iteration++;
    // Update the values in the second array
    for (int i = 0; i < n; i++) {
      int left = i == 0 ? n - 1 : i - 1; 
      int right = i == n - 1 ? 0 : i + 1; 
      arr_2[i] = (arr_1[left] + arr_1[i] + arr_1[right]) / 3.0;
    }

    // Check if consensus has been reached
    consensus = true;
    for (int i = 0; i < n; i++) {
      if (std::fabs(arr_2[i] - arr_1[i]) > epsilon) {
        consensus = false;
        break;
        }
    }

    // Update the values in the first array
    // Copy the values from arr_2 to arr_1 for the next iteration
    std::copy(arr_2, arr_2 + n, arr_1);

  }

  // timer end
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  // Print the user n, mean, deviation, and number of iterations with time required for consensus
  std::cout << "n: " << n << ", mean: " << mean << ", deviation: " << dev << ", iterations: " << iteration << std::endl;
  std::cout << std::fixed << std::setprecision(10);
  std::cout << "Consensus value: " << arr_2[0] << "\nTime taken: " << elapsed.count() << "s" << std::endl;

  // Free the memory
  delete[] arr_2;
  delete[] arr_1;
  return 0;
}