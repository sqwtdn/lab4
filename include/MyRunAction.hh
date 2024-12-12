#ifndef MYRUNACTION_HH
#define MYRUNACTION_HH

#include "G4UserRunAction.hh"

#include "TupleID.hh"
#include "GeometrySize.hh"

class MyRunAction: public G4UserRunAction
{
    public:
        MyRunAction(TupleID *tupleID);
        ~MyRunAction();

        virtual void BeginOfRunAction(const G4Run *aRun);
        virtual void EndOfRunAction(const G4Run *aRun);

    private:
        TupleID *tupleID;
};

#endif