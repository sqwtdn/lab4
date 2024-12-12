#include "PiDecayGenerator.hh"

PiDecayGenerator::PiDecayGenerator()
{
    rand = G4Random::getTheEngine();
}

PiDecayGenerator::~PiDecayGenerator()
{}

std::vector<Particle> PiDecayGenerator::decayPi()
{
    double sample = rand->flat();

    if(sample < PROBABILITY_OF_GG_DECAY)
    {
        return decayPiOnTwoPhotons();
    } 
    else 
        {
            return decayPiOnElectrPositrAndPhoton();
        }
}

std::vector<Particle> PiDecayGenerator::decayPiOnTwoPhotons()
{
    Particle firstPhoton;
    Particle secondPhoton;

    double p = PI0_MASS/2;
    double phi = 2*M_PI*rand->flat();
    double theta = acos(2*rand->flat() - 1);

    firstPhoton.energy = p;
    firstPhoton.pdgID = 22;
    firstPhoton.momentum = G4ThreeVector(p*sin(theta)*cos(phi), p*sin(theta)*sin(phi), p*cos(theta));

    secondPhoton.energy = p;
    secondPhoton.pdgID = 22;
    secondPhoton.momentum = -1*firstPhoton.momentum;

    return std::vector<Particle>({firstPhoton, secondPhoton});
}

std::vector<Particle> PiDecayGenerator::decayPiOnElectrPositrAndPhoton()
{
    Particle photon;
    Particle electron;
    Particle positron;

    TGenPhaseSpace *event = new TGenPhaseSpace();
    TLorentzVector W(0., 0., 0., PI0_MASS);

    double masses[3] = {electron_mass_c2, electron_mass_c2, 0};

    event->SetDecay(W, 3, masses);

    while(true)
    {
        double weight = event->Generate();

        if(rand->flat() < weight)
        {
            TLorentzVector *particleFromDecay = event->GetDecay(0);
            electron = Particle::fromDecay(11, particleFromDecay);

            particleFromDecay = event->GetDecay(1);
            positron = Particle::fromDecay(-11, particleFromDecay);

            particleFromDecay = event->GetDecay(2);
            photon = Particle::fromDecay(22, particleFromDecay);

            break;
        }
    }

    return std::vector<Particle>({photon, electron, positron});
}