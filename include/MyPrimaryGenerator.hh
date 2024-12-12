#ifndef MYPRIMARYGEERATOR_HH
#define MYPRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"

#include "PiDecayGenerator.hh"

class MyPrimaryGenerator: public G4VUserPrimaryGeneratorAction
{
    public:
        MyPrimaryGenerator(bool isPiDecay);
        ~MyPrimaryGenerator();
        virtual void GeneratePrimaries(G4Event*);

    private:
        bool isPiDecay;
        G4ParticleGun *fParticleGun;
        PiDecayGenerator *piDecay;
        G4ParticleTable *particleTable;
};

#endif