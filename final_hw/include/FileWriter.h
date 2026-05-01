#pragma once
#include "Deck.h"
#include <fstream>
#include <string>

class FileWriter {
private:
    std::ofstream file_;

public:
    explicit FileWriter(const std::string& path);
    void writeRound(int round, const Deck& deckA, const Deck& deckB);
};
