#pragma once

#include "Announcement.hpp"
#include "Policy.hpp"
#include <vector>
#include <memory>
#include <cstdint>

// AS.hpp
// -------
// A single Autonomous System — one node in the AS graph. Holds:
//   - its ASN (unique ID)
//   - three adjacency lists (providers, customers, peers)
//   - a propagation rank (computed by graph flattening)
//   - a policy pointer (BGP or ROV) that owns the local RIB and received queue
//
// Design note on adjacency lists:
// For the first pass we store raw pointers to other AS objects. The graph
// itself owns the AS objects (via shared_ptr or a vector<unique_ptr> in
// ASGraph), and the adjacency lists just reference them. Raw pointers are
// fine here because the graph outlives every traversal.
//
// If you optimize later, the hot-path alternative is to store adjacencies
// as vector<ASN> and look up the AS via an ASN->index table — that gives
// you contiguous memory and better cache behavior.

class AS {
public:
    ASN asn = 0;                 // the unique identifier for this AS

    // Adjacency lists. Raw pointers — not owning. The ASGraph owns the nodes.
    std::vector<AS*> providers;  // ASes we pay for transit
    std::vector<AS*> customers;  // ASes that pay us for transit
    std::vector<AS*> peers;      // ASes we exchange traffic with for free

    // Propagation rank, assigned by ASGraph::flatten().
    // Rank 0 = no customers (edge of the graph).
    // Higher ranks = further up the provider chain.
    // -1 means "not yet assigned".
    int propagation_rank = -1;

    // The policy handling announcement storage/processing for this AS.
    // shared_ptr for the first pass — simple and safe. Could become a
    // unique_ptr later since nothing else should co-own it.
    std::shared_ptr<Policy> policy;

    AS() = default;
    explicit AS(ASN n) : asn(n) {}

    // Convenience wrappers that delegate to the policy. Keep the AS class
    // itself thin — it's mostly a bag of data plus a policy handle.
    void receive_announcement(const Announcement& ann);
    void process_incoming_announcements();
};
