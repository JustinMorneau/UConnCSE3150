# CSE3150 Course Project: BGP Simulator

A high-performance BGP (Border Gateway Protocol) simulator that models how Autonomous Systems exchange routing announcements and learn about IP prefixes across the internet.

## Overview

This simulator implements a simplified but realistic BGP model based on CAIDA's AS topology data. It processes:
- **AS topology** from CAIDA (provider-customer and peer relationships)
- **IP prefix announcements** seeded from origin ASes
- **ROV (Route Origin Validation)** defense mechanisms
- **Three-phase propagation**: up (to providers), across (to peers), down (to customers)
- **Conflict resolution** when ASes receive multiple announcements for the same prefix

The output is a CSV of each AS's routing table (RIB) showing which paths they learned to each announced prefix.

## Building

```bash
make
```

This produces the `bgp_sim` binary (compiled with `-O2 -fno-inline` for MinGW compatibility).

Optional:
```bash
make parse_test    # Builds a parser sanity-check tool
make clean         # Removes binaries
```

## Usage

```bash
./bgp_sim <caida_topology> <announcements.csv> <rov_asns.txt> <output_ribs.csv>
```

### Parameters

| Argument | Description | Example |
|----------|-------------|---------|
| `<caida_topology>` | CAIDA as-rel2 format file with AS relationships | `bench/many/CAIDAASGraphCollector_2025.10.15.txt` |
| `<announcements.csv>` | CSV: `seed_asn,prefix,rov_invalid` | `bench/many/anns.csv` |
| `<rov_asns.txt>` | One ASN per line; ASes deploying ROV | `bench/many/rov_asns.csv` |
| `<output_ribs.csv>` | Output: `asn,prefix,as_path` | `my_output.csv` |

### Example

```bash
./bgp_sim bench/many/CAIDAASGraphCollector_2025.10.15.txt bench/many/anns.csv bench/many/rov_asns.csv output.csv
```

### Input Formats

**CAIDA Topology (as-rel2)**:
```
# Comment lines starting with # are ignored
4|3|-1                    # AS 4 (provider) -> AS 3 (customer)
4|666|-1                  # AS 4 -> AS 666
4|777|0|bgp               # AS 4 <-> AS 777 (peers, bidirectional)
```

**Announcements CSV**:
```
seed_asn,prefix,rov_invalid
1,10.0.0.0/24,False
2,10.1.0.0/24,True
```

**ROV ASNs** (one per line, `#` comments ignored):
```
174
43
68
```

### Output Format

**Output RIBs CSV**:
```
asn,prefix,as_path
1,10.0.0.0/24,"(1,)"
1,10.16.0.0/24,"(1, 11537, 46)"
4,10.0.0.0/24,"(4, 777, 1)"
```

AS-paths are formatted as Python-style tuples with space-separated ASNs.

## Design Choices

### 1. **Graph Representation**

- **Adjacency Lists**: Each AS holds `vector<AS*>` for providers, customers, and peers. Raw pointers are safe since the `ASGraph` owns all AS nodes via `shared_ptr` and outlives all traversals.
- **Alternative Considered**: Storing adjacencies as `vector<ASN>` with a lookup table for O(1) cache-friendly access. Deferred for future optimization.

### 2. **IP Prefix Storage**

- **String-based (CIDR)**: Prefixes stored as strings (`"8.8.8.0/24"`) for simplicity and clarity.
- **Optimized Alternative**: Use 128-bit integer + prefix length + IPv4/IPv6 flag for faster hashing/comparison. Deferred pending profiling.

### 3. **Policy Pattern (BGP vs ROV)**

Used polymorphism to swap behaviors per-AS:
- `Policy` (abstract base): Defines storage (`local_rib`, `received_queue`) and interface
- `BGP` (concrete): Standard announcement handling with conflict resolution
- `ROV` (concrete): Extends BGP, drops invalid announcements before queuing

This allows per-AS filtering without conditional logic in the propagation engine.

### 4. **Announcement Processing**

**When storing an announcement** (Section 3.5 of spec):
- Pick best candidate from `received_queue` using 3-tier tiebreak
- **Prepend own ASN** to the AS-path (e.g., `[777]` becomes `[4, 777]` when stored at AS 4)
- Compare against existing `local_rib` entry; install if better
- Clear `received_queue`

**Tiebreak order** (Section 3.6):
1. **Relationship**: ORIGIN (4) > CUSTOMER (3) > PEER (2) > PROVIDER (1)
2. **Path Length**: Shorter paths preferred (fewer hops)
3. **Next-Hop ASN**: Lower ASN wins (tiebreaker)

### 5. **Propagation Phases (Valley-Free Routing)**

Three explicit phases enforce valley-free topology (no "valleys" in paths):

1. **Up Phase**: Rank 0 → send to providers; higher ranks process then send
   - Announcements flow from customers toward transit providers
   
2. **Across Phase**: All ASes send to peers; then all process (single hop only)
   - Prevents multi-hop peer chains which would violate valley-free property
   
3. **Down Phase**: Top rank sends to customers; lower ranks process then send
   - Announcements flow from providers toward customers

This ordering naturally enforces that only valid (customer/origin) announcements reach providers and peers.

### 6. **Graph Flattening (Topological Sort)**

- **Kahn's Algorithm** on provider-customer edges assigns propagation ranks
- **Rank 0**: ASes with no customers (leaf nodes, multihomed end-sites)
- **Rank N**: `max(rank of customers) + 1`
- Used to **iterate ranks in order** during up/down phases, ensuring each rank processes after its dependencies

### 7. **Cycle Detection**

- **Iterative DFS** (not recursive) to avoid stack overflow on 100k-node graphs
- Traverses provider edges; back-edge = cycle
- Rejects topologies with provider-customer cycles (peer cycles are OK)

### 8. **Compiler Optimization Workaround**

- **Flag**: `-fno-inline` at `-O2`
- **Reason**: MinGW-W64's aggressive inlining of STL operations (particularly structured bindings and `std::deque` access) exposes undefined behavior in the iterative cycle detection or other STL-heavy code
- **Impact**: Minimal performance cost; correctness takes priority

## Implemented Features

### ✅ Core Simulation

- [x] Parse CAIDA as-rel2 topology (provider-customer, peer-peer relationships)
- [x] Build AS graph with adjacency lists
- [x] Detect cycles in provider-customer hierarchy
- [x] Assign propagation ranks (topological sort)

### ✅ Announcement Processing

- [x] Store announcements in local RIB (routing table)
- [x] 3-tier conflict resolution (relationship, path length, next-hop ASN)
- [x] Prepend own ASN to AS-path when storing
- [x] Distinguish received_from relationship (ORIGIN, CUSTOMER, PEER, PROVIDER)

### ✅ Propagation

- [x] Three-phase propagation (up → across → down)
- [x] Valley-free routing via phase ordering
- [x] Per-AS announcement queuing
- [x] Announce sending with next_hop_asn and relationship stamping

### ✅ ROV (Route Origin Validation)

- [x] Read ROV ASN list from file
- [x] Apply ROV policy to specified ASes
- [x] Drop invalid announcements (rov_invalid=true) before queuing

### ✅ I/O

- [x] Parse CAIDA topology files (handles comments, blank lines, Windows line endings)
- [x] Read announcements CSV (seed_asn, prefix, rov_invalid)
- [x] Read ROV ASN list (one per line, `#` comments)
- [x] Write RIBs CSV (asn, prefix, as_path) with Python-tuple formatting
- [x] Sorted output for deterministic comparison

### ✅ Correctness

- [x] All three benchmarks (many, prefix, subprefix) pass with zero mismatches
- [x] Output matches expected ribs.csv exactly

## Architecture

```
main.cpp                          # Driver: orchestrates all steps
├── ASGraph.hpp / ASGraph.cpp      # Graph structure + CAIDA parsing
├── ASGraph_propagation.cpp        # Cycle detection, flatten, propagate, output
├── CSVIO.hpp / CSVIO.cpp          # CSV reading
├── AS.hpp                         # Single AS node
├── Policy.hpp / BGP.hpp / ROV.hpp # Announcement handling
├── Announcement.hpp               # BGP announcement struct
├── Prefix.hpp                     # IP prefix (CIDR notation)
├── Relationship.hpp               # Enum: ORIGIN, CUSTOMER, PEER, PROVIDER
└── testing/stubs.cpp              # Policy/BGP/ROV/AS implementations
```

## Performance

- **Time**: ~1 minute for full CAIDA topology (78,370 ASes) with ~32 announcements per AS
- **Memory**: < 8GB per spec requirement
- **Output**: 2.96M lines for bench/many dataset
- **Optimization**: `-O2 -fno-inline` balances speed and MinGW compatibility

## Testing

Verified against three benchmark datasets:
- `bench/many/`: 2,963,832 RIB entries ✓
- `bench/prefix/`: 78,022 RIB entries ✓
- `bench/subprefix/`: 155,385 RIB entries ✓

Run with:
./bgp_sim bench/many/CAIDAASGraphCollector_2025.10.15.txt \
          bench/many/anns.csv \
          bench/many/rov_asns.csv \
          output.csv

Then compare with:
./bench/compare_output.sh bench/many/ribs.csv output.csv

Or do both at the same time using:
./bgp_sim bench/many/CAIDAASGraphCollector_2025.10.15.txt bench/many/anns.csv bench/many/rov_asns.csv output.csv && ./bench/compare_output.sh bench/many/ribs.csv output.csv


## Future Optimizations

1. **Prefix representation**: Use 128-bit integer + prefix length for faster hashing
2. **Adjacency cache locality**: Store adjacencies as ASN vectors + lookup table
3. **Parallel propagation**: Process ranks in parallel (respect dependencies)
4. **Memory reuse**: Pool announcement allocations to reduce heap churn
5. **WASM port**: Compile to WebAssembly for browser-based simulation UI

## References

- **CAIDA AS Topology**: https://www.caida.org/data/as-relationships/
- **BGP Specification**: RFC 4271
- **Valley-Free Routing**: Gao, L. "On inferring autonomous system relationships in the internet"

## License

Educational project for UConn CSE3150.
