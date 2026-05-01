#include "FileReader.h"
#include "PlayingCard.h"
#include "FaceCard.h"
#include "JokerCard.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Deck FileReader::readDeck(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    Deck deck;
    std::string line;
    bool hasCards = false;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string col1, col2;

        if (!std::getline(ss, col1, ',') || !std::getline(ss, col2)) {
            throw std::runtime_error("Malformed CSV line: " + line);
        }

        if (col2.empty()) {
            throw std::runtime_error("Malformed CSV line: " + line);
        }

        if (col1 == "Joker") {
            deck.addToBottom(std::make_unique<JokerCard>(col2));
        } else {
            try {
                int rank = std::stoi(col2);
                if (rank >= 11 && rank <= 13) {
                    deck.addToBottom(std::make_unique<FaceCard>(col1, rank));
                } else {
                    deck.addToBottom(std::make_unique<PlayingCard>(col1, rank));
                }
            } catch (const std::exception&) {
                throw std::runtime_error("Invalid rank in CSV: " + col2);
            }
        }
        hasCards = true;
    }

    if (!hasCards) {
        throw std::runtime_error("Empty deck: no cards found in file");
    }

    return deck;
}
