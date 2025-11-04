#include <iostream>
using std::cout;

template<typename Iterator, typename Function>
void foreach(Iterator first, Iterator last, Function fn) {
    while (first != last) {
        fn(*first);
        ++first;
    }
}

void pr(int x) { std::cout << x << " "; }

template<typename T, unsigned long N>
auto first_of(T (&array)[N]) { return array; }

template<typename T, unsigned long N>
auto last_of(T (&array)[N]) { return array + N; }

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    auto const N  = sizeof(numbers)/sizeof(numbers[0]);
    {
        auto first = &numbers[0];
        auto last  = &numbers[N];
        while (first != last) {
            std::cout << *first << " ";
            ++first;
        }
        std::cout << "\n";
    }
    {
        auto first = numbers;
        auto last  = numbers + N;
        while (first != last) {
            std::cout << *first << " ";
            ++first;
        }
        std::cout << "\n";
    }
    {
        foreach(numbers, numbers + N, [](int x){ std::cout << x << " "; });
        std::cout << "\n";
    }
    {
        foreach(numbers, numbers + N, pr);
        std::cout << "\n";
    }
    {
        foreach(first_of(numbers), last_of(numbers), pr);
        std::cout << "\n";
    }

}

