#ifndef LINEVARTUPLESET_H_MBOTX5KJ
#define LINEVARTUPLESET_H_MBOTX5KJ

#include <vector>

#include "Combinadic.h"
#include "Coverage.h"
#include "SpecificationFile.h"
using namespace std;
struct ECEntry {
public:
  unsigned encode;
  size_t column_index;
};
struct Mapt {
public:
int row_index;
size_t column_index;
};

class LineVarTupleSet {
public:
  LineVarTupleSet(){};
  void initialize(const SpecificationFile &specificationFile,
                  const unsigned array_size);
  void pop(const unsigned encode, const unsigned lineIndex,
           const std::vector<unsigned> &tuple,std::vector<vector<int>> &coverByLineindex,int size);
  void push(const unsigned encode, const unsigned lineIndex,
            const std::vector<unsigned> &tuple,std::vector<vector<int>> &coverByLineindex);

  void pushOneCoveredTuple(const Coverage &coverage,
                           std::vector<vector<int>> &coverByLineindex,unsigned index);

  void exchange_row(unsigned lineIndex1, unsigned lineIndex2) {
    lineVarTupleSet[lineIndex1].swap(lineVarTupleSet[lineIndex2]);
    std::swap(lineOneCoveredCount[lineIndex1], lineOneCoveredCount[lineIndex2]);
  }
  void pop_back_row() {
    lineVarTupleSet.pop_back();
    lineOneCoveredCount.pop_back();
  }

  const std::vector<ECEntry> &getECbyLineVar(unsigned lineIndex, unsigned var) {
    return lineVarTupleSet[lineIndex][var];
  }

  unsigned oneCoveredCount(unsigned lineIndex) {
    return lineOneCoveredCount[lineIndex];
  }

private:
  std::vector<size_t> lineOneCoveredCount;
  
  std::vector<std::vector<std::vector<ECEntry>>> lineVarTupleSet;
  std::vector<std::vector<vector<Mapt>>> varMapping;
};

#endif /* end of include guard: LINEVARTUPLESET_H_MBOTX5KJ */
