#pragma once

#include <string>
#include <cstdint>
#include <functional>

// Prefix.hpp
// -----------
// An IP prefix in CIDR notation, like "8.8.8.0/24" (IPv4) or "2001:db8::/32" (IPv6).
// A prefix represents the block of IP addresses that an AS is claiming to own.
//
// Design note: for simplicity in the first pass, we store the prefix as a string
// and use it directly as the key in the local RIB hashmap. This is slow but
// correct. A faster representation would be:
//   - a 128-bit integer holding the address (IPv4 addresses go in the low 32 bits)
//   - a uint8_t prefix length
//   - a bool or enum indicating IPv4 vs IPv6
// We can swap to that later; the whole point of wrapping it in a struct now is
// so we can change the internals without touching the rest of the codebase.

struct Prefix {
    std::string value;  // e.g., "8.8.8.0/24" — canonical string form

    Prefix() = default;
    explicit Prefix(std::string s) : value(std::move(s)) {}

    // Needed so Prefix can be used as a key in std::unordered_map.
    bool operator==(const Prefix& other) const { return value == other.value; }
};

// Hash specialization so std::unordered_map<Prefix, ...> works.
// Delegates to std::hash<std::string> for the first pass.
namespace std {
    template <>
    struct hash<Prefix> {
        std::size_t operator()(const Prefix& p) const noexcept {
            return std::hash<std::string>{}(p.value);
        }
    };
}
