#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1


#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"




class G4Event;
class G4GeneralParticleSource;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{

public:
	PrimaryGeneratorAction();    
	virtual ~PrimaryGeneratorAction() override;
public:
	virtual void GeneratePrimaries(G4Event*) override;

private:


  G4GeneralParticleSource* fParticleGun;
};

#endif
