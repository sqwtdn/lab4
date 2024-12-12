#include "MyPrimaryGenerator.hh"

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    if(isPiDecay)
    {
        std::vector<Particle> particles = piDecay->decayPi();
        bool flag = false;
        do{
            flag = false;
            particles = piDecay->decayPi();
            for(auto it: particles)
            {
                auto momentum = it.momentum;
                if(momentum.theta()/radian > 0.1 && momentum.theta()/radian < pi - 0.1)
                {
                    flag = true;
                }
            }
        } while(flag);

        for(int iParticle = 0; iParticle < particles.size(); ++iParticle)
        {
            fParticleGun->SetParticleMomentumDirection(particles[iParticle].momentum);
            fParticleGun->SetParticleEnergy(particles[iParticle].energy);

            G4ParticleDefinition *particleDefinition = particleTable->FindParticle(particles[iParticle].pdgID);
            fParticleGun->SetParticleDefinition(particleDefinition);
            fParticleGun->GeneratePrimaryVertex(anEvent);
        }
    }
    else
        {
            G4ThreeVector mom(0., 0., 1.);

            fParticleGun->SetParticleMomentumDirection(mom);
            fParticleGun->SetParticleEnergy(60.0*MeV);

            fParticleGun->SetParticleDefinition(G4Electron::Definition());
            fParticleGun->GeneratePrimaryVertex(anEvent);

            fParticleGun->SetParticleDefinition(G4Gamma::Definition());
            fParticleGun->GeneratePrimaryVertex(anEvent);
        }
}

MyPrimaryGenerator::MyPrimaryGenerator(bool isPiDecay): G4VUserPrimaryGeneratorAction(), isPiDecay(isPiDecay)
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    piDecay = new PiDecayGenerator();
    particleTable = G4ParticleTable::GetParticleTable();
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}