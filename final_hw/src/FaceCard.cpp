#include "FaceCard.h"

FaceCard::FaceCard(const std::string& suit, int rank)
    : PlayingCard(suit, rank) {}

void FaceCard::print(std::ostream& os) const {
    std::string name;
    switch (rank_) {
        case 11: name = "Jack";  break;
        case 12: name = "Queen"; break;
        case 13: name = "King";  break;
        default: name = std::to_string(rank_); break;
    }
    os << name << " of " << suit_;
}
