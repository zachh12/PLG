#include "HexLGPMTHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

G4ThreadLocal G4Allocator<HexLGPMTHit>* HexLGPMTHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGPMTHit::HexLGPMTHit()
  : fPmtNumber(-1),fPhotons(0),fPos(0,0,0),fPhysVol(nullptr),fPhotEnergy(0.0),fDrawit(false) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGPMTHit::~HexLGPMTHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGPMTHit::HexLGPMTHit(const HexLGPMTHit &right) : G4VHit()
{
  fPmtNumber=right.fPmtNumber;
  fPhotons=right.fPhotons;
  fPhysVol=right.fPhysVol;
  fPhotEnergy=right.fPhotEnergy;
  fPos=right.fPos;
  fDrawit=right.fDrawit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const HexLGPMTHit& HexLGPMTHit::operator=(const HexLGPMTHit &right){
  fPmtNumber = right.fPmtNumber;
  fPhotons=right.fPhotons;
  fPhysVol=right.fPhysVol;
  fPhotEnergy=right.fPhotEnergy;
  fPos=right.fPos;
  fDrawit=right.fDrawit;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int HexLGPMTHit::operator==(const HexLGPMTHit &right) const{
  return (fPmtNumber==right.fPmtNumber);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPMTHit::Draw(){
  if(fDrawit&&fPhysVol){ //ReDraw only the PMTs that have hit counts > 0
    //Also need a physical volume to be able to draw anything
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if(pVVisManager){//Make sure that the VisManager exists
      G4VisAttributes attribs(G4Colour(1.,0.,0.));
      attribs.SetForceSolid(true);   
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPMTHit::Print() {}