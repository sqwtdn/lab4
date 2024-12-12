#ifndef TUPLEID_HH
#define TUPLEID_HH

#include"G4AnalysisManager.hh"

struct TupleID
{
    G4AnalysisManager *analysisManager;
    int leftCalID, rightCalID, leftTrackID, rightTrackID;
};

#endif