#pragma once

// Relationship.hpp
// -----------------
// Represents how one AS is connected to another, or how an announcement
// arrived at an AS. The numeric ordering matters: higher value = more
// preferred during conflict resolution (Step 3.6 of the spec).
//
// Priority order (highest to lowest):
//   ORIGIN   -- we announced this prefix ourselves; beats everything
//   CUSTOMER -- received from a customer (we earn money routing this)
//   PEER     -- received from a peer (free traffic exchange)
//   PROVIDER -- received from a provider (costs us money)

enum class Relationship : int {
    PROVIDER = 1,  // announcement came from our provider (least preferred)
    PEER     = 2,  // announcement came from our peer
    CUSTOMER = 3,  // announcement came from our customer
    ORIGIN   = 4   // we originated this announcement (most preferred)
};
