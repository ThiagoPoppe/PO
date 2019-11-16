#ifndef PAIR_LIST_H
#define PAIR_LIST_H

#include <list>

class PairList {
private:
    std::list<std::pair<unsigned int, unsigned int>> pairs;

public:
    PairList();
    ~PairList();

    void InsertPair(unsigned int x, unsigned int y);
    void RemoveInvalidPairs(unsigned int numVariables, unsigned int numConstrains);
    void PrintPairs();

    bool IsEmpty();

    std::list<std::pair<unsigned int, unsigned int>> GetPairs();
};

#endif