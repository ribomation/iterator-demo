#include <iostream>
#include <sstream>
#include <string>
#include "ostream-iterator.hxx"

using namespace std::string_literals;
using ribomation::containers::OstreamOutputIterator;


int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto* first   = std::begin(numbers);
    auto* last    = std::end(numbers);

    auto buffer = std::ostringstream{};
    auto iter   = OstreamOutputIterator<int>{buffer, " / "s};
    while (first != last) {
        *iter = *first;
        ++first;
    }
    std::cout << buffer.str() << "\n";
}
