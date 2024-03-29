#include "HexLGPrimaryGeneratorAction.hh"
#include "HexLGPrimaryGeneratorMessenger.hh"
#include "HexLGDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGPrimaryGeneratorAction::HexLGPrimaryGeneratorAction(HexLGDetectorConstruction* detector)
:G4VUserPrimaryGeneratorAction(), fDetector(detector)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  fGunMessenger = new HexLGPrimaryGeneratorMessenger(this);

 
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
 
  G4String particleName;
  fParticleGun->SetParticleDefinition(particleTable->
                                     FindParticle(particleName="opticalphoton"));
  //Default energy,position,momentum
  fParticleGun->SetParticleEnergy(3.2*eV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.0 , 0.0, .0*cm));

  //G4double angle = G4UniformRand();//*360.0*deg;
  G4double angle = G4UniformRand() * 360.0*deg;
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(std::cos(angle),std::sin(angle),0.));   
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGPrimaryGeneratorAction::~HexLGPrimaryGeneratorAction(){
    delete fParticleGun;
    delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  G4cout << "Gun x-position: " << fDetector->GetGunPosX() << G4endl;
  fParticleGun->SetParticlePosition(G4ThreeVector(fDetector->GetGunPosX() , fDetector->GetGunPosY(), 0.0*cm));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle){
  if (fParticleGun->GetParticleDefinition()->GetParticleName()!="opticalphoton"){
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }

 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton);
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 fParticleGun->SetParticlePolarization(polar);

}