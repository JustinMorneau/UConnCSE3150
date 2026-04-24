// main.cpp
// ---------
// Top-level driver. Wires up the whole simulator in the order prescribed
// by the spec. Command-line args (adjust as you like):
//
//   argv[1] = path to CAIDA topology file
//   argv[2] = path to announcements CSV
//   argv[3] = path to ROV ASNs file
//   argv[4] = output path for ribs.csv

#include "ASGraph.hpp"
#include "CSVIO.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0]
                  << " <caida_topology> <announcements.csv>"
                     " <rov_asns.txt> <output_ribs.csv>\n";
        return 1;
    }

    const std::string topo_path     = argv[1];
    const std::string anns_path     = argv[2];
    const std::string rov_path      = argv[3];
    const std::string out_path      = argv[4];

    ASGraph graph;

    // 1. Build the graph from CAIDA data. Creates AS nodes and wires up
    //    providers/customers/peers. Every AS gets a default BGP policy.
    graph.build_from_caida_file(topo_path);

    // 2. Reject topologies with provider/customer cycles. Peer cycles are OK.
    if (graph.has_provider_customer_cycle()) {
        std::cerr << "Error: provider/customer cycle detected in topology.\n";
        return 2;
    }

    // 3. Swap BGP policy for ROV policy on the listed ASNs. Must happen
    //    before seeding so invalid announcements are dropped from the start.
    graph.apply_rov_policies(rov_path);

    // 4. Flatten the DAG into propagation ranks. Required before propagate().
    graph.flatten();

    // 5. Read announcements from CSV and seed them into origin ASes' local RIBs.
    const auto announcements = CSVIO::read_announcements(anns_path);
    graph.seed_announcements(announcements);

    // 6. Run the three-phase propagation: up to providers, across to peers,
    //    down to customers. Valley-free routing is enforced by phase ordering.
    graph.propagate();

    // 7. Dump (asn, prefix, as_path) for every AS's local RIB.
    graph.write_ribs_csv(out_path);

    return 0;
}
