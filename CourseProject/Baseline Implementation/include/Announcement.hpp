#pragma once

#include "Prefix.hpp"
#include "Relationship.hpp"
#include <vector>
#include <cstdint>

// Announcement.hpp
// -----------------
// A BGP announcement: "AS X is claiming to own this prefix, and here's the
// path the announcement took to reach you." This is the unit of data that
// flows through the simulator.
//
// Fields correspond to Section 3.1 of the spec, plus rov_invalid from Section 4.
//
// An ASN is up to 32 bits per the BGP RFCs, so uint32_t is the right type.

using ASN = std::uint32_t;

struct Announcement {
    Prefix prefix;                       // which IP block this announcement is for
    std::vector<ASN> as_path;            // ordered path of ASNs; each AS prepends itself
    ASN next_hop_asn = 0;                // the ASN that most recently forwarded this to us
    Relationship received_from_relationship = Relationship::ORIGIN;
                                         // how we got it (customer/peer/provider/origin)
    bool rov_invalid = false;            // true if ROV-deploying ASes should drop this

    Announcement() = default;

    Announcement(Prefix p,
                 std::vector<ASN> path,
                 ASN next_hop,
                 Relationship rel,
                 bool invalid = false)
        : prefix(std::move(p))
        , as_path(std::move(path))
        , next_hop_asn(next_hop)
        , received_from_relationship(rel)
        , rov_invalid(invalid)
    {}
};
