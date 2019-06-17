#ifndef QuLGPMTSD_h
#define QuLGPMTSD_h 1

#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VProcess.hh"
#include "QuLGPMTHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class QuLGPMTSD : public G4VSensitiveDetector
{

  public:

    QuLGPMTSD(G4String name);
    virtual ~QuLGPMTSD();
 
    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
 
    //A version of processHits that keeps aStep constant
    G4bool ProcessHits_constStep(const G4Step* ,
                                 G4TouchableHistory* );
    virtual void EndOfEvent(G4HCofThisEvent* );
    virtual void clear();
    void DrawAll();
    void PrintAll();
 
    //Initialize the arrays to store pmt possitions
    /*inline void InitPMTs(G4int nPMTs){
      if(fPMTPositionsX)delete fPMTPositionsX;
      if(fPMTPositionsY)delete fPMTPositionsY;
      if(fPMTPositionsZ)delete fPMTPositionsZ;
      fPMTPositionsX=new G4DataVector(nPMTs);
      fPMTPositionsY=new G4DataVector(nPMTs);
      fPMTPositionsZ=new G4DataVector(nPMTs);
    }*/

    //Store a pmt position
    //void SetPmtPositions(const std::vector<G4ThreeVector>& positions);

  private:

    QuLGPMTHitsCollection* fPMTHitCollection;

    //G4DataVector* fPMTPositionsX;
    //G4DataVector* fPMTPositionsY;
    //G4DataVector* fPMTPositionsZ;
};

#endif