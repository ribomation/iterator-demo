#include <iostream>
#include <random>
#include "simple-vector.hxx"

using ribomation::containers::SimpleVector;

template<typename Iterator, typename Function>
void foreach(Iterator first, Iterator last, Function fn) {
    while (first != last) {
        fn(*first);
        ++first;
    }
}

template<typename Container>
auto first_of(Container& c) -> decltype(c.begin()) { return c.begin(); }

template<typename Container>
auto last_of(Container& c) -> decltype(c.end()) { return c.end(); }

void pr(int x) { std::cout << x << " "; }

int main() {
    {
        auto v = SimpleVector<int>{1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
        auto first = v.begin();
        auto last  = v.end();
        while (first != last) {
            std::cout << *first << " ";
            ++first;
        }
        std::cout << "\n";
    }

    {
        auto v = SimpleVector<int>{1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
        foreach(v.begin(), v.end(), [](int x){ std::cout << x << " "; });
        std::cout << "\n";
    }

    {
        auto v = SimpleVector<int>{1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
        foreach(first_of(v), last_of(v), pr);
        std::cout << "\n";
    }

    {
        auto v = SimpleVector<int>{};
        for (auto k = 1; k <= 20; ++k) v.push(k);

        for (auto x: v) std::cout << x << " ";
        std::cout << " siz=" << v.size() << " cap=" << v.capacity() << "\n";

        while (not v.empty()) std::cout << v.pop() << " ";
        std::cout << " siz=" << v.size() << " cap=" << v.capacity() << "\n";
    }

    {
        auto v = SimpleVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        auto first = v.begin();
        auto last  = v.end();
        while (first < last) {
            *first = *first * *first;
            ++first;
        }
        for (auto x: v) std::cout << x << " ";
        std::cout << "\n";
    }

    {
        auto v = SimpleVector<int>{1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
        auto first = v.rbegin();
        auto last  = v.rend();
        while (first != last) {
            std::cout << *first << " ";
            --first;
        }
        std::cout << "\n";
    }

    {
        auto v = SimpleVector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
        auto first = v.begin();
        auto last = v.end();
        while (first < last) {
            std::cout << *first << " ";
            first += 3;
        }
        std::cout << "\n";
    }

    {
        auto v       = SimpleVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        auto r       = std::default_random_engine{ std::random_device{}() };
        auto rnd_idx = std::uniform_int_distribution{0, static_cast<int>(v.size() - 1)};
        auto iter    = v.begin();
        auto N       = 10;
        while (N-- > 0) {
            auto& x = iter[ rnd_idx(r) ];
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}
