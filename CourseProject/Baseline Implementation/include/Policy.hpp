#pragma once

#include "Announcement.hpp"
#include "Prefix.hpp"
#include <unordered_map>
#include <vector>
#include <memory>

// Policy.hpp
// -----------
// Abstract base class for an AS's BGP policy. Each AS holds a pointer to
// a concrete Policy (BGP or ROV). This lets us swap behaviors per-AS
// without touching AS or the propagation code — classic polymorphism.
//
// Two pieces of state live here because both BGP and ROV need them:
//   - local_rib: prefix -> the single best announcement we've chosen
//   - received_queue: prefix -> all announcements that arrived this round
//                     but haven't been processed yet
//
// The split matters for the propagation algorithm: we want every AS at a
// given rank to *receive* all its announcements before any of them decides
// what to store. See Section 3.5 of the spec.

class Policy {
public:
    // Hashmap of the best announcement per prefix. One entry per prefix.
    std::unordered_map<Prefix, Announcement> local_rib;

    // Incoming announcements waiting to be processed. Multiple per prefix
    // are possible (we might hear about the same prefix from several
    // neighbors in the same round).
    std::unordered_map<Prefix, std::vector<Announcement>> received_queue;

    virtual ~Policy() = default;

    // Called when another AS sends us an announcement. Default behavior
    // is to push it onto received_queue. ROV will override to drop invalid
    // ones before they hit the queue.
    virtual void receive_announcement(const Announcement& ann) = 0;

    // Walk received_queue, pick the winner for each prefix (using the
    // conflict-resolution rules from Section 3.6), prepend own_asn to
    // the winner's AS-path, update local_rib, and clear the queue.
    virtual void process_incoming_announcements(ASN own_asn) = 0;

    // Conflict resolution: returns true if `a` is strictly better than `b`.
    // Tiebreak order (Section 3.6):
    //   1. Best relationship wins (origin > customer > peer > provider)
    //   2. Shortest AS-path wins
    //   3. Lowest next_hop_asn wins
    // Defined here (not virtual) because all policies use the same rules.
    static bool announcement_wins(const Announcement& a, const Announcement& b);
};
