#include <iostream>
#include "double-linked-list.hxx"

using ribomation::containers::DoubleLinkedList;

int main() {
    {
        auto lst   = DoubleLinkedList<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto first = lst.begin();
        auto last  = lst.end();
        while (first != last) {
            std::cout << *first << " ";
            ++first;
        }
        std::cout << "\n";
    }

    {
        auto lst   = DoubleLinkedList<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        auto first = lst.rbegin();
        auto last  = lst.rend();
        while (first != last) {
            std::cout << *first << " ";
            --first;
        }
        std::cout << "\n";
    }
}
