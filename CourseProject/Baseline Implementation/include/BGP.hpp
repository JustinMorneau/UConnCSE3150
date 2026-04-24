#pragma once

#include "Policy.hpp"

// BGP.hpp
// --------
// The vanilla BGP policy: store everything, resolve conflicts using the
// standard three-tier tiebreak. This is the baseline policy every AS gets
// unless they're on the ROV-deploying list.

class BGP : public Policy {
public:
    // Push the announcement onto received_queue under its prefix key.
    // No validation — we accept everything and sort it out in process_incoming.
    void receive_announcement(const Announcement& ann) override;

    // For each prefix in received_queue:
    //   - pick the best candidate using announcement_wins
    //   - prepend own_asn to the winner's AS-path
    //   - compare to existing local_rib entry (if any) and install the better one
    // Then clear received_queue.
    void process_incoming_announcements(ASN own_asn) override;
};
