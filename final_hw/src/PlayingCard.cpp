#include "PlayingCard.h"
#include <string>

PlayingCard::PlayingCard(const std::string& suit, int rank)
    : suit_(suit), rank_(rank) {}

int PlayingCard::value() const {
    return rank_;
}

std::string PlayingCard::rankToString(int rank) {
    switch (rank) {
        case 1:  return "A";
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        default: return std::to_string(rank);
    }
}

void PlayingCard::print(std::ostream& os) const {
    os << rankToString(rank_) << " of " << suit_;
}
