#include <iostream>
#include <string>
#include <math.h>
#include <limits>
#define UNIT_RAND() (rand() / (1.0 + RAND_MAX))

double rand_normal(double mean, double dev) {
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
    y = py * u; // save the other value for the next call
    saved = 1;
    return x * dev + mean;
}

int main() {
    int n;
    bool inputValid = false;

    do {
        std::cout << "Enter a positive integer (less than 10000): ";
        std::cin >> n;
    } while (n <= 0 || n > 10000);

    double *arr = new double[n];

    for (size_t i = 0; i < n; i++) {
        double x = rand_normal(0, 1);
        arr[i] = x;
    }

    size_t r = sizeof(arr) / sizeof(arr[0]);

    int t = 0;
    while (true) {
        double *new_arr = new double[n];
        for (int i = 0; i < n; i++) {
            int left = i == 0 ? n - 1 : i - 1;
            int right = i == n - 1 ? 0 : i + 1;
            new_arr[i] = (arr[left] + arr[i] + arr[right]) / 3.0;
        }
        bool is_consensus = true;
        for (int i = 0; i < n; i++) {
            if (new_arr[i] != new_arr[0]) {
                is_consensus = false;
                break;
            }
        }
        if (is_consensus) {
            break;
        }
        delete[] arr;
        arr = new_arr;
        t++;
    }

    std::cout << "Consensus reached after " << t << " iterations\n";

    delete[] arr;
    return 0;
}