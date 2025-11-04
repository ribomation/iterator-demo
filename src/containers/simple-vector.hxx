#pragma once
#include <initializer_list>


namespace ribomation::containers {

    template<typename T>
    class SimpleVector {
        unsigned size_;
        unsigned capacity_;
        T* storage;

        auto full() const { return size() == capacity(); }

        void relocate() {
            auto old_storage = storage;
            auto old_capacity = capacity_;
            capacity_ *= 2;
            storage = new T[capacity_];
            for (auto k = 0U; k < old_capacity; ++k)
                storage[k] = old_storage[k];
            delete [] old_storage;
        }

    public:
        SimpleVector() : size_(0), capacity_(2) {
            storage = new T[capacity_];
        }

        SimpleVector(std::initializer_list<T> args) : size_(0), capacity_(args.size()) {
            storage = new T[capacity_];
            for (auto x: args) push(x);
        }

        auto size() const { return size_; }
        auto capacity() const { return capacity_; }
        auto empty() const { return size() == 0U; }

        void push(T x) {
            if (full()) relocate();
            storage[size_++] = x;
        }

        T pop() {
            return storage[--size_];
        }

        struct iterator {
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using pointer = T *;
            using reference = T&;
            using difference_type = std::ptrdiff_t;

            SimpleVector* owner = nullptr;
            difference_type current_index = 0;

            explicit iterator(SimpleVector* owner, difference_type start_index = 0) : owner(owner), current_index(start_index) {}
            iterator() = default;

            reference operator*() const { return owner->storage[current_index]; }
            pointer operator->() const { return &(owner->storage[current_index]); }

            bool operator==(iterator const& rhs) const {
                return owner == rhs.owner && current_index == rhs.current_index;
            }
            bool operator!=(iterator const& rhs) const { return !(*this == rhs); }

            bool operator<(iterator const& rhs) const { return current_index < rhs.current_index; }
            bool operator>(iterator const& rhs) const { return rhs < *this; }
            bool operator<=(iterator const& rhs) const { return !(rhs < *this); }
            bool operator>=(iterator const& rhs) const { return !(*this < rhs); }

            iterator& operator++() {
                ++current_index;
                return *this;
            }

            iterator operator ++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator& operator--() {
                --current_index;
                return *this;
            }

            iterator operator --(int) {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

            iterator& operator+=(difference_type offset) {
                current_index += offset;
                return *this;
            }

            iterator& operator-=(difference_type offset) {
                current_index -= offset;
                return *this;
            }

            reference operator[](difference_type index) const {
                return owner->storage[index];
            }

            friend iterator operator+(iterator it, difference_type offset) {
                it += offset;
                return it;
            }
            friend iterator operator+(difference_type offset, iterator it) {
                it += offset;
                return it;
            }

            friend iterator operator-(iterator it, difference_type offset) {
                it -= offset;
                return it;
            }
            friend difference_type operator-(iterator const& lhs, iterator const& rhs) {
                return lhs.current_index - rhs.current_index;
            }
        };

        auto begin() { return iterator{this, 0}; }
        auto end() { return iterator{this, static_cast<iterator::difference_type>(size())}; }
        auto rbegin() { return iterator{this, static_cast<iterator::difference_type>(size() - 1)}; }
        auto rend() { return iterator{this, -1}; }
    };

}
