#include <iostream>
#include <cmath>
#include <iomanip>

int main () {
    double n, m, k;
    double result = 0;
    std::cin >> n >> m >> k;
    result = (n * m) * (1 - pow((1 - 1 / (m * n)), k));
    std::cout << std::setprecision(13) << result;
    return 0;
}