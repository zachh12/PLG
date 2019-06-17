#include "HexLGPMTSD.hh"
#include "HexLGPMTHit.hh"
#include "HexLGDetectorConstruction.hh"
#include "HexLGUserTrackInformation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HexLGPMTSD::HexLGPMTSD(G4String name)
  : G4VSensitiveDetector(name),fPMTHitCollection(nullptr)
{
  collectionName.insert("pmtHitCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGPMTSD::~HexLGPMTSD() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPMTSD::Initialize(G4HCofThisEvent* hitsCE){
  fPMTHitCollection = new HexLGPMTHitsCollection
                      (SensitiveDetectorName,collectionName[0]);
  //Store collection with event and keep ID
  static G4int hitCID = -1;
  if(hitCID<0){
    hitCID = GetCollectionID(0);
  }
  hitsCE->AddHitsCollection( hitCID, fPMTHitCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool HexLGPMTSD::ProcessHits(G4Step* ,G4TouchableHistory* ){
  return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Generates a hit and uses the postStepPoint's mother volume replica number
//PostStepPoint because the hit is generated manually when the photon is
//absorbed by the photocathode

G4bool HexLGPMTSD::ProcessHits_constStep(const G4Step* aStep,
                                       G4TouchableHistory* ){
  G4cout << "Processing hits! " << G4endl;

  //need to know if this is an optical photon
  if(aStep->GetTrack()->GetDefinition()
     != G4OpticalPhoton::OpticalPhotonDefinition()) return false;
 
  //User replica number 1 since photocathode is a daughter volume
  //to the pmt which was replicated
  G4int pmtNumber=
    aStep->GetPostStepPoint()->GetTouchable()->GetReplicaNumber(1);
  G4VPhysicalVolume* physVol=
    aStep->GetPostStepPoint()->GetTouchable()->GetVolume(1);
    //aStep->GetTrack()->GetVolume();//->GetName();
  G4double ePhoton = 
    aStep->GetPostStepPoint()->GetKineticEnergy();
  G4ThreeVector pos=
    aStep->GetPostStepPoint()->GetPosition();
    

  //Find the correct hit collection
  G4int n = fPMTHitCollection->entries();
  G4cout << "Number of hit collections: " << n << G4endl;
  HexLGPMTHit* hit = nullptr;
  for(G4int i=0;i<n;i++){
    if((*fPMTHitCollection)[i]->GetPMTNumber()==pmtNumber){
      hit=(*fPMTHitCollection)[i];
      break;
    }
  }
 
  if (hit == nullptr) {//this pmt wasnt previously hit in this event
    hit = new HexLGPMTHit(); //so create new hit


    hit->SetPMTNumber(pmtNumber);
    hit->SetPMTPhysVol(physVol);
    hit->SetPMTEnergy(ePhoton);
    hit->SetPMTPos(pos);
    fPMTHitCollection->insert(hit);

    //hit->SetPMTPos((*fPMTPositionsX)[pmtNumber],(*fPMTPositionsY)[pmtNumber],
    //               (*fPMTPositionsZ)[pmtNumber]);
  }

  hit->IncPhotonCount(); //increment hit for the selected pmt

    HexLGUserTrackInformation* trackInfo=
      (HexLGUserTrackInformation*)aStep->GetTrack()->GetUserInformation();
    if(trackInfo->GetTrackStatus())
      hit->SetDrawit(true);
  

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPMTSD::EndOfEvent(G4HCofThisEvent* ) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPMTSD::clear() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPMTSD::DrawAll() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGPMTSD::PrintAll() {}