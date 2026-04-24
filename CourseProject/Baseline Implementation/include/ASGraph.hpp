#pragma once

#include "AS.hpp"
#include "Announcement.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <string>
#include <cstdint>

// ASGraph.hpp
// ------------
// Owns all AS nodes and drives the simulation. Responsibilities:
//
//   1. Parse the CAIDA topology file into AS nodes + adjacency lists.
//   2. Detect cycles in provider/customer relationships (peer cycles are OK).
//   3. Flatten the DAG into rank-ordered vectors for propagation.
//   4. Seed announcements into the appropriate ASes' local RIBs.
//   5. Run the three-phase propagation (up to providers, across to peers,
//      down to customers) — Section 3.5 of the spec.
//   6. Dump the final state to a CSV.
//
// Node ownership: the graph owns the AS objects via shared_ptr. All
// adjacency lists on AS objects hold raw pointers into this storage.

class ASGraph {
public:
    // Primary storage. Map from ASN to the AS node, so lookups by ASN
    // during parsing and seeding are O(1).
    std::unordered_map<ASN, std::shared_ptr<AS>> as_map;

    // Flattened propagation order. propagation_ranks[i] holds all ASes
    // at rank i. Built by flatten(). Used by the up and down phases.
    std::vector<std::vector<AS*>> propagation_ranks;

    // --- Construction ---

    // Read the CAIDA topology file. Each line specifies a relationship:
    // either provider-to-customer or peer-to-peer. Creates AS nodes on
    // demand and wires up the three adjacency lists.
    // Throws or exits non-zero on a cycle (per spec).
    void build_from_caida_file(const std::string& path);

    // Apply the ROV policy to the ASNs listed in the given file (one per
    // line). Must be called AFTER build_from_caida_file (so the AS nodes
    // exist) but BEFORE seeding.
    void apply_rov_policies(const std::string& rov_asns_path);

    // Scan provider/customer relationships for cycles. Peer cycles are
    // expected and ignored. Returns true if a cycle exists; the caller
    // should print and exit non-zero on true.
    bool has_provider_customer_cycle() const;

    // Assign propagation_rank to every AS and populate propagation_ranks.
    // Rank 0 = no customers. Rank(X) = max(rank(customers of X)) + 1.
    void flatten();

    // --- Simulation ---

    // Seed each announcement into the origin AS's local RIB directly
    // (no propagation yet). Per Section 3.4.
    void seed_announcements(const std::vector<Announcement>& anns);

    // The main event. Runs the three phases in order:
    //   1. propagate_up()     — rank 0 up to the top
    //   2. propagate_across() — single hop over peer edges
    //   3. propagate_down()   — top rank down to 0
    void propagate();

    // --- Output ---

    // Write every (asn, prefix, as_path) triple from every AS's local RIB.
    // as_path is serialized as a space- or hyphen-separated list of ASNs.
    void write_ribs_csv(const std::string& output_path) const;

private:
    // Phase helpers. Each one iterates ranks in the appropriate direction,
    // has ASes send to the relevant neighbor set, then has the receivers
    // process their queues before the next rank.
    void propagate_up();       // customer -> provider, rank by rank upward
    void propagate_across();   // peer -> peer, single hop, all ASes at once
    void propagate_down();     // provider -> customer, rank by rank downward

    // Called during up/down phases: AS `from` forwards each local-RIB entry
    // to every AS in `neighbors`, setting next_hop_asn = from.asn and
    // stamping the appropriate received_from_relationship.
    void send_announcements(AS& from,
                            const std::vector<AS*>& neighbors,
                            Relationship neighbor_relationship);

    // Get-or-create an AS node by ASN. Used during topology parsing.
    AS* get_or_create_as(ASN asn);
};
