#pragma once

#include "Announcement.hpp"
#include <string>
#include <vector>
#include <cstdint>

// CSVIO.hpp
// ----------
// File I/O helpers. Kept separate from ASGraph so the parsing logic can be
// unit-tested without spinning up a full graph.

namespace CSVIO {

    // Read the seed announcements CSV. Expected columns: asn, prefix, rov_invalid.
    // The returned announcements will have:
    //   - prefix set
    //   - as_path = [asn]
    //   - next_hop_asn = asn
    //   - received_from_relationship = ORIGIN
    //   - rov_invalid from the file
    std::vector<Announcement> read_announcements(const std::string& path);

    // Read a file where each non-empty line is an ASN that deploys ROV.
    // Blank lines and lines starting with '#' are ignored.
    std::vector<ASN> read_rov_asns(const std::string& path);

}  // namespace CSVIO
