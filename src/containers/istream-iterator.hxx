#pragma once
#include <iosfwd>

namespace ribomation::containers {

    template<typename T>
    class InputStreamIterator {
        std::istream*  input  = nullptr;
        bool           at_eof = true;
        T value{};

        void read_next_token() {
            if (!input) {
                at_eof = true;
            } else if (*input >> value) {
                at_eof = false;
            } else {
                input = nullptr;
                at_eof = true;
            }
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
        using difference_type   = std::ptrdiff_t;

        InputStreamIterator() = default;
        InputStreamIterator(std::istream& input_) : input(&input_) {
            read_next_token();
        }

        reference operator *()   { return value; }
        pointer   operator ->()  { return &value; }

        auto& operator ++() {
            read_next_token();
            return *this;
        }
        auto operator ++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator ==(InputStreamIterator const& lhs, InputStreamIterator const& rhs) {
            if (lhs.at_eof && rhs.at_eof) return true;
            return lhs.input == rhs.input && lhs.at_eof == rhs.at_eof;
        }
        friend bool operator !=(InputStreamIterator const& lhs, InputStreamIterator const& rhs) {
            return !(lhs == rhs);
        }
    };

}
