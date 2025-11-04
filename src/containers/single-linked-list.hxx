#pragma once
#include <initializer_list>
#include <iterator>

namespace ribomation::containers {
    template<typename T>
    class SingleLinkedList {
        struct Link {
            T payload;
            Link* next;
            Link(T payload_, Link* next_ = nullptr) : payload(payload_), next(next_) {}
        };

        Link* head = nullptr;
        unsigned size_ = 0;

    public:
        SingleLinkedList() = default;

        SingleLinkedList(std::initializer_list<T> args) {
            for (auto iter = std::rbegin(args); iter != std::rend(args); ++iter)
                push(*iter);
        }

        void push(T x) {
            head = new Link{x, head};
            ++size_;
        }

        T pop() {
            auto first = head;
            head = head->next;
            auto x = first->payload;
            delete first;
            --size_;
            return x;
        }

        auto size() const { return size_; }
        bool empty() const { return size() == 0; }

        struct iterator {
            using iterator_category = std::forward_iterator_tag;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;
            using difference_type   = std::ptrdiff_t;

            SingleLinkedList* owner = nullptr;
            Link* current = nullptr;

            iterator(SingleLinkedList* owner_, Link* current_) : owner(owner_), current(current_) {}
            iterator() = default;

            bool operator ==(iterator const&) const { return current == nullptr; }
            bool operator !=(iterator const&) const { return current != nullptr; }

            reference operator *() const { return current->payload; }
            pointer   operator ->() const { return &current->payload; }

            iterator& operator ++() {
                current = current->next;
                return *this;
            }
            iterator operator ++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }
        };

        auto begin() { return iterator{this, head}; }
        auto end() { return iterator{}; }
    };

}
