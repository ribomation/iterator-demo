#include <iostream>
#include <algorithm>
#include "single-linked-list.hxx"
#include "ostream-iterator.hxx"

using ribomation::containers::SingleLinkedList;
using ribomation::containers::OstreamOutputIterator;
using namespace std::string_literals;

int main() {
    {
        auto lst   = SingleLinkedList<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto first = lst.begin();
        auto last  = lst.end();
        while (first != last) {
            std::cout << *first << " ";
            ++first;
        }
        std::cout << "\n";
    }

    {
        auto lst   = SingleLinkedList<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::for_each(lst.begin(), lst.end(), [](int x){ std::cout << x << " "; });
        std::cout << "\n";
    }

    {
        auto lst   = SingleLinkedList<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto iter   = OstreamOutputIterator<int>{std::cout, " "s};
        std::copy(lst.begin(), lst.end(), iter);
    }
}
