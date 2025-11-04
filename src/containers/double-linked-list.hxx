#pragma once
#include <initializer_list>

namespace ribomation::containers {

    template<typename T>
    class DoubleLinkedList {
        struct Link {
            T payload;
            Link* prev;
            Link* next;

            Link(T payload_) : payload(payload_) {
                prev = next = this;
            }

            void insert_before(Link* node) {
                node->next = this;
                node->prev = this->prev;
                this->prev = node;
                node->prev->next = node;
            }

            void insert_after(Link* node) {
                node->prev = this;
                node->next = this->next;
                this->next = node;
                node->next->prev = node;
            }

            Link* unlink() {
                this->prev->next = this->next;
                this->next->prev = this->prev;
                this->prev = this->next = this;
                return this;
            }
        };

        Link* head = nullptr;
        unsigned size_ = 0;

    public:
        DoubleLinkedList() : head(new Link{T{}}) {
            head->prev = head;
            head->next = head;
        }

        DoubleLinkedList(std::initializer_list<T> args) : DoubleLinkedList() {
            for (auto iter = std::begin(args); iter != std::end(args); ++iter)
                push(*iter);
        }

        void push(T x) {
            head->insert_before(new Link{x});
            ++size_;
        }

        T pop() {
            if (empty()) throw std::out_of_range{"empty list"};
            auto* first = head->next->unlink();
            T x = std::move(first->payload);
            delete first;
            --size_;
            return x;
        }

        auto size() const { return size_; }
        bool empty() const { return size() == 0; }

        struct iterator {
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;
            using difference_type   = std::ptrdiff_t;

            DoubleLinkedList* owner = nullptr;
            Link* current = nullptr;
            iterator(DoubleLinkedList* owner_, Link* current_) : owner(owner_), current(current_) {}

            iterator() = default;

            bool operator ==(iterator const& rhs) const { return current == rhs.current; }
            bool operator !=(iterator const& rhs) const { return current != rhs.current; }

            reference operator *() const { return current->payload; }
            pointer operator ->() const { return &current->payload; }

            iterator& operator ++() {
                current = current->next;
                return *this;
            }
            iterator operator ++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator& operator --() {
                current = current->prev;
                return *this;
            }
            iterator operator --(int) {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

        };

        auto begin() { return iterator{this, head->next}; }
        auto end() { return iterator{this, head}; }
        auto rbegin() { return iterator{this, head->prev}; }
        auto rend() { return iterator{this, head}; }
    };

}
