#pragma once
#include <iosfwd>
#include <string>

namespace ribomation::containers {
    using namespace std::string_literals;

    template<typename T>
    class OstreamOutputIterator {
        std::ostream* output = nullptr;
        std::string   separator{};
        bool          first = true;

    public:
        using iterator_category = std::output_iterator_tag;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
        using difference_type   = std::ptrdiff_t;

        OstreamOutputIterator(std::ostream& os, std::string sep = ""s)
            : output(&os), separator(std::move(sep)) {}

        auto operator=(T const& value) -> OstreamOutputIterator& {
            if (first) first = false; else (*output) << separator;
            (*output) << value;
            return *this;
        }

        auto& operator*() { return *this; }
        auto& operator++() { return *this; }

        friend bool operator==(OstreamOutputIterator const& lhs, OstreamOutputIterator const& rhs) {
            return lhs.output == rhs.output && lhs.separator == rhs.separator;
        }
        friend bool operator!=(OstreamOutputIterator const& lhs, OstreamOutputIterator const& rhs) {
            return !(lhs == rhs);
        }
    };

}
