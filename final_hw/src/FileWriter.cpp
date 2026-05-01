#include "FileWriter.h"
#include <stdexcept>
#include <sstream>

FileWriter::FileWriter(const std::string& path) : file_(path) {
    if (!file_.is_open()) {
        throw std::runtime_error("Cannot open output file: " + path);
    }
    file_ << "Round,PlayerA_Count,PlayerB_Count,PlayerA_Cards,PlayerB_Cards\n";
}

void FileWriter::writeRound(int round, const Deck& deckA, const Deck& deckB) {
    std::ostringstream ssa, ssb;
    ssa << deckA;
    ssb << deckB;
    file_ << round << "," << deckA.size() << "," << deckB.size() << ","
          << "\"" << ssa.str() << "\",\"" << ssb.str() << "\"\n";
}
