#include "JokerCard.h"

JokerCard::JokerCard(const std::string& color) : color_(color) {}

int JokerCard::value() const {
    return 14;
}

void JokerCard::print(std::ostream& os) const {
    os << color_ << " Joker";
}
