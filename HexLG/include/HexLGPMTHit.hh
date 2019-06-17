#ifndef HexLGPMTHit_h
#define HexLGPMTHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"

#include "tls.hh"

class G4VTouchable;

class HexLGPMTHit : public G4VHit
{
  public:
 
    HexLGPMTHit();
    virtual ~HexLGPMTHit();
    HexLGPMTHit(const HexLGPMTHit &right);

    const HexLGPMTHit& operator=(const HexLGPMTHit &right);
    G4int operator==(const HexLGPMTHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
 
    virtual void Draw();
    virtual void Print();

    inline void SetDrawit(G4bool b){fDrawit=b;}
    inline G4bool GetDrawit(){return fDrawit;}

    inline void IncPhotonCount(){fPhotons++;}
    inline G4int GetPhotonCount(){return fPhotons;}

    inline void SetPMTNumber(G4int n) { fPmtNumber = n; }
    inline G4int GetPMTNumber() { return fPmtNumber; }

    inline void SetPMTPhysVol(G4VPhysicalVolume* physVol){this->fPhysVol=physVol;}
    inline G4VPhysicalVolume* GetPMTPhysVol(){return fPhysVol;}

    inline void SetPMTPos(G4ThreeVector pos){this->fPos=pos;}
    inline G4ThreeVector GetPMTPos(){return fPos;}
    
    inline void SetPMTEnergy(G4double e){fPhotEnergy = e;}
    inline G4double GetPhotEnergy(){return fPhotEnergy;}
 


  private:

    G4int fPmtNumber;
    G4int fPhotons;
    G4ThreeVector fPos;
    G4VPhysicalVolume* fPhysVol;
    G4double fPhotEnergy;
    G4bool fDrawit;

};

typedef G4THitsCollection<HexLGPMTHit> HexLGPMTHitsCollection;

extern G4ThreadLocal G4Allocator<HexLGPMTHit>* HexLGPMTHitAllocator;

inline void* HexLGPMTHit::operator new(size_t){
  if(!HexLGPMTHitAllocator)
      HexLGPMTHitAllocator = new G4Allocator<HexLGPMTHit>;
  return (void *) HexLGPMTHitAllocator->MallocSingle();
}

inline void HexLGPMTHit::operator delete(void *aHit){
  HexLGPMTHitAllocator->FreeSingle((HexLGPMTHit*) aHit);
}

#endif