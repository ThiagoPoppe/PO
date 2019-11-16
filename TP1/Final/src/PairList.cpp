#include <iostream>

#include "PairList.h"

PairList::PairList() { }
PairList::~PairList() { }

void PairList::InsertPair(unsigned int x, unsigned int y) {
    auto newPair = std::make_pair(x, y);

    for (auto p : GetPairs()) {
        if (p.first == x) {
            pairs.remove(p);
            break;
        }
    }

    pairs.push_back(newPair);
}

void PairList::RemoveInvalidPairs(unsigned int numVariables, unsigned int numConstrains) {
    for (auto p : GetPairs()) {
        if (p.second > numVariables)
            pairs.remove(p);
    }
}

void PairList::PrintPairs() {
    for (auto p : pairs) {
        std::cout << "(" << p.first << ", " << p.second << ")" << std::endl;
    }
}

bool PairList::IsEmpty() {
    return pairs.size() == 0;
}

std::list<std::pair<unsigned int, unsigned int>> PairList::GetPairs() {
    return pairs;
}