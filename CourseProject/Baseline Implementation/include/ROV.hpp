#pragma once

#include "BGP.hpp"

// ROV.hpp
// --------
// Route Origin Validation policy. Identical to BGP except: if an incoming
// announcement has rov_invalid == true, we drop it on the floor instead
// of queuing it. Simulates a real-world defense against prefix hijacks.
//
// We inherit from BGP (not directly from Policy) so we reuse BGP's
// process_incoming_announcements logic for free.

class ROV : public BGP {
public:
    // Override only the receive step. If the announcement is rov_invalid,
    // return immediately without queuing. Otherwise, delegate to BGP.
    void receive_announcement(const Announcement& ann) override;
};
