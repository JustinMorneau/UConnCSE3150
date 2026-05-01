#pragma once
#include "Deck.h"
#include <string>

class FileReader {
public:
    static Deck readDeck(const std::string& path);
};
