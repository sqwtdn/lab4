#ifndef PIDECAYGENERATOR_HH
#define PIDECAYGENERATOR_HH

#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include <TGenPhaseSpace.h>
#include <CLHEP/Random/RandomEngine.h>
#include <CLHEP/Units/PhysicalConstants.h>
#include <Randomize.hh>
#include "vector"

using namespace CLHEP;

struct Particle
{
    int pdgID;
    double energy;
    G4ThreeVector momentum;

    static Particle fromDecay(int pdgID, TLorentzVector *particleFromDecay)
    {
        Particle particle;
        particle.pdgID = pdgID;
        particle.energy = particleFromDecay->E();
        particle.momentum = G4ThreeVector(particleFromDecay->Px(), particleFromDecay->Py(), particleFromDecay->Pz());

        return particle;
    }
};

class PiDecayGenerator
{
    public:
        PiDecayGenerator();
        ~PiDecayGenerator();

        std::vector<Particle> decayPi();

    private:
        HepRandomEngine *rand;
        const double PI0_MASS = 134.9766*MeV;
        const double PROBABILITY_OF_GG_DECAY = 0.98823;

        std::vector<Particle> decayPiOnTwoPhotons();
        std::vector<Particle> decayPiOnElectrPositrAndPhoton();
};

#endif