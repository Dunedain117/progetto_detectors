
#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  fParticleGun = new G4GeneralParticleSource();

}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries( G4Event* anEvent )
{
  /*G4ParticleTable *particleTable= G4ParticleTable::GetParticleTable();
  G4String particleName="proton";
  G4ParticleDefinition *particle = particleTable->FindParticle("proton");

  G4ThreeVector pos (-0.5*cm,0.,0.);
  G4ThreeVector mom(1.,0.,0.);

  
  fParticleGun->SetParticlePosition( pos );
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(150.*MeV);
  fParticleGun->SetParticleDefinition(particle);*/

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

