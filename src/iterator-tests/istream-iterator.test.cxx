#include <iostream>
#include <sstream>
#include "istream-iterator.hxx"

using ribomation::containers::InputStreamIterator;


int main() {
    auto buffer = std::istringstream{"1 2 3 4 5 6 7 8 9 10"};
    auto first  = InputStreamIterator<int>{buffer};
    auto last   = InputStreamIterator<int>{};
    auto sum    = 0;
    auto cnt    = 0;
    while (first != last) {
        std::cout << *first << " ";
        sum += *first;
        ++cnt;
        ++first;
    }
    std::cout << "\nSUM: " << sum << " (" << cnt * (cnt + 1) / 2 << ")\n";
}

