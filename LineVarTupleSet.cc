#include "LineVarTupleSet.h"

void LineVarTupleSet::initialize(const SpecificationFile &specificationFile,
                                 const unsigned array_size) {

  const Options &options = specificationFile.getOptions();
  unsigned strength = specificationFile.getStrenth();
  unsigned index = specificationFile.getIndex();
  unsigned MaxSize = 0;
  for (std::vector<unsigned> tuple = combinadic.begin(strength);
       tuple[strength - 1] < options.size(); combinadic.next(tuple)) {
    unsigned blockSize = 1;
    for (unsigned i = 0; i < strength; ++i) {
      blockSize *= options.symbolCount(tuple[i]);
    }
    MaxSize += blockSize;
  }
  varMapping.resize(MaxSize);
    for (unsigned i = 0; i < MaxSize; ++i) {
        varMapping[i].resize(strength);
        for (unsigned j = 0; j < strength; ++j) {
            varMapping[i][j].resize(index);
        }
    }

  lineVarTupleSet.resize(array_size);
  for (unsigned i = 0; i < array_size; ++i) {
    lineVarTupleSet[i].resize(options.allSymbolCount());
  }

  lineOneCoveredCount.resize(array_size, 0);
}

void LineVarTupleSet::pushOneCoveredTuple(
    const Coverage &coverage, std::vector<vector<int>> &coverByLineindex,unsigned index) {
  for (unsigned encode = 0; encode < coverage.tupleCount(); ++encode) {
    if (coverage.coverCount(encode) == index) {        //qin
            push(encode, coverByLineindex[encode][0], coverage.getTuple(encode),coverByLineindex);}
    
  }
}

void LineVarTupleSet::push(const unsigned encode, const unsigned lineIndex,
                           const std::vector<unsigned> &tuple, std::vector<vector<int>> &coverByLineindex) {
 
  /*  lineOneCoveredCount[lineIndex+1]++;
    for (size_t i = 0; i < tuple.size(); ++i) {
      unsigned var = tuple[i];
      varMapping[encode][i] = lineVarTupleSet[lineIndex+1][var].size();
      lineVarTupleSet[lineIndex+1][var].push_back({encode, i});
    }*/
    for(int t=0;t<coverByLineindex[encode].size();t++)
    {
    lineOneCoveredCount[coverByLineindex[encode][t]]++;

    for (size_t i = 0; i < tuple.size(); ++i) {
      unsigned var = tuple[i];
        varMapping[encode][i][t].row_index=coverByLineindex[encode][t];
        varMapping[encode][i][t].column_index =lineVarTupleSet[coverByLineindex[encode][t]][var].size();
      //  varMapping[encode].push_back({11,2});
      lineVarTupleSet[coverByLineindex[encode][t]][var].push_back({encode, i});
    }
    }
    
}

void LineVarTupleSet::pop(const unsigned encode, const unsigned lineIndex,
                          const std::vector<unsigned> &tuple, std::vector<vector<int>> &coverByLineindex, int size) {
    for(int t=0;t<coverByLineindex[encode].size();t++)
    {
    lineOneCoveredCount[coverByLineindex[encode][t]]--;
   
        for (size_t i = 0; i < tuple.size(); ++i)
        {
            unsigned var = tuple[i];
            std::vector<ECEntry> &varTS = lineVarTupleSet[coverByLineindex[encode][t]][var];
            for(unsigned p = 0; p<varMapping[encode][i].size();p++)
            {

                if(varMapping[encode][i][p].row_index == coverByLineindex[encode][t])
                {
                    varTS[varMapping[encode][i][p].column_index] = *varTS.rbegin();
                    for(unsigned q = 0; q<varMapping[varTS.rbegin()->encode][varTS.rbegin()->column_index].size();q++)
                    {
                        if(varMapping[varTS.rbegin()->encode][varTS.rbegin()->column_index][q].row_index==coverByLineindex[encode][t])
                        {
                            varMapping[varTS.rbegin()->encode][varTS.rbegin()->column_index][q].column_index =
                            varMapping[encode][i][p].column_index;
                        }
                    }
                }
            }
                varTS.pop_back();
                
        }
        }
      }
    

 
