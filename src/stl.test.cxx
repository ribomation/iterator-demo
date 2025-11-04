#include <print>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>
#include <random>

#include "istream-iterator.hxx"
#include "ostream-iterator.hxx"
#include "single-linked-list.hxx"
#include "double-linked-list.hxx"
#include "simple-vector.hxx"

using namespace ribomation::containers;

int main() {
    {
        std::println("--- input & output iterators ---");
        auto buffer = std::istringstream{"10 20 30 40 50"};
        auto in = InputStreamIterator<int>{buffer};
        auto eof = InputStreamIterator<int>{};
        auto out = OstreamOutputIterator<int>{std::cout, " "s};
        std::copy(in, eof, out);
        std::println();
    }

    {
        std::println("--- forward iterators ---");
        auto lst = SingleLinkedList<int>{1,2,3,4,5,6,7,8,9,10};
        for (auto x : lst) std::print("{} ", x);
        std::println();

        std::transform(lst.begin(), lst.end(), lst.begin(), [](int x){ return x*x; });
        for (auto x : lst) std::print("{} ", x);
        std::println();
    }

    {
        std::println("--- bidirectional iterator ---");
        auto lst = DoubleLinkedList<int>{1,2,3,4,5,6,7,8,9,10};
        for (auto x : lst) std::print("{} ", x);
        std::println();

        std::reverse(lst.begin(), lst.end());
        for (auto x : lst) std::print("{} ", x);
        std::println();
    }

    {
        std::println("--- random-access iterator ---");
        auto vec = SimpleVector<int>{1,2,3,4,5,6,7,8,9,10};
        for (auto x : vec) std::print("{} ", x);
        std::println();

        auto r = std::default_random_engine{ std::random_device{}() };
        std::shuffle(vec.begin(), vec.end(), r);
        for (auto x : vec) std::print("{} ", x);
        std::println();
    }
}
