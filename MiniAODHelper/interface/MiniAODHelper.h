#ifndef _MiniAODHelper_h
#define _MiniAODHelper_h

#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath> 
#include <iomanip>
#include <algorithm>
#include "TVector.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#ifdef __MAKECINT__
#pragma link C++ class std::vector< TLorentzVector >+; 
#endif

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "CommonTools/Utils/interface/normalizedPhi.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "MiniAOD/BoostedObjects/interface/SubFilterJet.h"
#include "MiniAOD/BoostedObjects/interface/HTTTopJet.h"

#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/strbitset.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "DataFormats/Math/interface/LorentzVector.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#endif

typedef std::map<std::string, std::string> mparams;
typedef std::vector< TLorentzVector > vecTLorentzVector;
typedef std::vector<std::vector<double> > vvdouble;
typedef std::vector<std::vector<std::string> > vvstring;
typedef std::vector<std::vector<int> > vvint;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;
typedef std::vector<int> vint;

namespace analysisType{ enum analysisType{ LJ, DIL, TauLJ, TauDIL }; }
namespace sysType{enum sysType{NA, JERup, JERdown, JESup, JESdown, hfSFup, hfSFdown, lfSFdown, lfSFup, TESup, TESdown, CSVLFup, CSVLFdown, CSVHFup, CSVHFdown, CSVHFStats1up, CSVHFStats1down, CSVLFStats1up, CSVLFStats1down, CSVHFStats2up, CSVHFStats2down, CSVLFStats2up, CSVLFStats2down, CSVCErr1up, CSVCErr1down, CSVCErr2up, CSVCErr2down }; }
namespace jetID{		enum jetID{			none, jetPU, jetMinimal, jetLooseAOD, jetLoose, jetTight, jetMETcorrection }; }
namespace tauID { enum tauID{ tauNonIso, tauLoose, tauMedium, tauTight }; }
namespace tau { enum ID { nonIso, loose, medium, tight }; }
namespace SelfVetoPolicy { enum SelfVetoPolicy {selfVetoNone=0, selfVetoAll=1, selfVetoFirst=2};}

namespace muonID{		enum muonID{		muonPreselection, muonSide, muonSideLooseMVA, muonSideTightMVA, muonLoose, muonTight, muonPtOnly, muonPtEtaOnly, muonPtEtaIsoOnly, muonPtEtaIsoTrackerOnly, muonRaw, muonLooseCutBased, muonTightCutBased, muonCutBased, muonLooseMvaBased, muonTightMvaBased, muon2lss }; }
namespace electronID{	enum electronID{	electronPreselection, electronSide, electronSideLooseMVA, electronSideTightMVA, electronLoose, electronTight, electronTightMinusTrigPresel, electronLooseMinusTrigPresel, electronRaw, electronLooseCutBased, electronTightCutBased, electronCutBased, electronPhys14L, electronPhys14M, electronPhys14T, electronLooseMvaBased, electronTightMvaBased, electron2lss }; }
namespace hdecayType{	enum hdecayType{ hbb, hcc, hww, hzz, htt, hgg, hjj, hzg }; }
namespace coneSize{ enum coneSize{miniIso,R03,R04};}
namespace corrType{ enum corrType{deltaBeta,rhoEA};}

using namespace std;

//To use when the object is either a reference or a pointer
template<typename T>
T * ptr(T & obj) { return &obj; } //turn reference into pointer!
template<typename T>
T * ptr(T * obj) { return obj; } //obj is already pointer, return it!

class MiniAODHelper{

  // === Functions === //
 public: 
  // Constructor(s) and destructor
  MiniAODHelper();
  virtual ~MiniAODHelper();

  // Set up MiniAODHelper
  void SetUp(string, int, const analysisType::analysisType, bool);
  void SetVertex(const reco::Vertex&);
  void SetRho(double);
  void SetJetCorrector(const JetCorrector*);
  void SetJetCorrectorUncertainty();
  void SetFactorizedJetCorrector();
  void SetPackedCandidates(const std::vector<pat::PackedCandidate> & all, int fromPV_thresh=1, float dz_thresh=9999., bool also_leptons=false);
  
  virtual std::vector<pat::Muon> GetSelectedMuons(const std::vector<pat::Muon>&, const float, const muonID::muonID, const coneSize::coneSize = coneSize::R04, const corrType::corrType = corrType::deltaBeta, const float = 2.4);
  virtual std::vector<pat::Electron> GetSelectedElectrons(const std::vector<pat::Electron>&, const float, const electronID::electronID, const float = 2.4);
  std::vector<pat::Tau> GetSelectedTaus(const std::vector<pat::Tau>&, const float, const tau::ID);
  std::vector<pat::Jet> GetSelectedJets(const std::vector<pat::Jet>&, const float, const float, const jetID::jetID, const char);
  std::vector<pat::Jet> GetUncorrectedJets(const std::vector<pat::Jet>&);
  std::vector<pat::Jet> GetUncorrectedJets(edm::Handle<pat::JetCollection>);
  std::vector<pat::Jet> GetCorrectedJets(const std::vector<pat::Jet>&, const edm::Event&, const edm::EventSetup&, const sysType::sysType iSysType=sysType::NA);
  std::vector<pat::Jet> GetCorrectedJets(const std::vector<pat::Jet>&, const sysType::sysType iSysType=sysType::NA);
  std::vector<boosted::HTTTopJet> GetSelectedTopJets(const std::vector<boosted::HTTTopJet>&, const float, const float, const float, const float, const jetID::jetID);
  std::vector<boosted::SubFilterJet> GetSelectedHiggsJets(const std::vector<boosted::SubFilterJet>&, const float, const float, const float, const float, const jetID::jetID);
  bool isGoodMuon(const pat::Muon&, const float, const float, const muonID::muonID, const coneSize::coneSize, const corrType::corrType);
  bool isGoodElectron(const pat::Electron&, const float, const float, const electronID::electronID);
  bool isGoodTau(const pat::Tau&, const float, const tau::ID);
  bool isGoodJet(const pat::Jet&, const float, const float, const jetID::jetID, const char);
  bool isGoodTopJet(const boosted::HTTTopJet&, const float, const float, const float, const float, const jetID::jetID);
  bool isGoodHiggsJet(const boosted::SubFilterJet&, const float, const float);
  //  virtual float GetMuonRelIso(const pat::Muon&) const;
  float GetMuonRelIso(const pat::Muon&) const;
  float GetMuonRelIso(const pat::Muon&, const coneSize::coneSize, const corrType::corrType) const;
  float GetElectronRelIso(const pat::Electron&) const;
  float GetElectronRelIso(const pat::Electron&, const coneSize::coneSize, const corrType::corrType) const;
  static float GetJetCSV(const pat::Jet&, const std::string = "pfCombinedInclusiveSecondaryVertexV2BJetTags"); 
  bool PassesCSV(const pat::Jet&, const char);
  bool PassElectronPhys14Id(const pat::Electron&, const electronID::electronID) const;
  void addVetos(const reco::Candidate &cand);
  void clearVetos();
  float isoSumRaw(const std::vector<const pat::PackedCandidate *> & cands, const reco::Candidate &cand, float dR, float innerR, float threshold, SelfVetoPolicy::SelfVetoPolicy selfVeto, int pdgId=-1) const;
  int ttHFCategorization(const std::vector<reco::GenJet>&, const std::vector<int>&, const std::vector<int>&, const std::vector<int>&, const std::vector<int>&, const std::vector<reco::GenParticle>&, const std::vector<std::vector<int> >&, const std::vector<int>&, const std::vector<int>&, const std::vector<int>&, const std::vector<int>&, const std::vector<int>&, const std::vector<int>&, const double, const double);
  int GetHiggsDecay(edm::Handle<std::vector<reco::GenParticle> >&);
  std::vector<pat::Jet> GetDeltaRCleanedJets(const std::vector<pat::Jet>&, const std::vector<pat::Muon>&, const std::vector<pat::Electron>&, const double);
  double getJERfactor( const int, const double, const double, const double );

  template <typename T> T GetSortedByPt(const T&);
  template <typename T> T GetSortedByCSV(const T&);
  template <typename T, typename S> std::vector<T> RemoveOverlaps( const std::vector<S>&, const std::vector<T>& );
  template <typename T, typename S> T RemoveOverlap( const std::vector<S>&, const T& );

  template <typename T, typename S> double DeltaR( const S&, const T& );
  template <typename T, typename S> std::vector<T> GetDifference( const std::vector<S>&, const std::vector<T>& );
  template <typename T, typename S> std::vector<T> GetUnion( const std::vector<S>&, const std::vector<T>& );

 protected:
  
  bool isSetUp;
  bool vertexIsSet;
  bool rhoIsSet;
  bool jetcorrectorIsSet;
  bool factorizedjetcorrectorIsSet;
  
  string era;
  int sampleNumber;
  bool isData;
  analysisType::analysisType analysis;
  string samplename;

  float CSVLwp, CSVMwp, CSVTwp;

  double useRho;
  const std::vector<pat::PackedCandidate> * allcands_;
  std::vector<const pat::PackedCandidate *> charged_, neutral_, pileup_;
  //  mutable std::vector<float> weights_;
  std::vector<const reco::Candidate *> vetos_;
  reco::Vertex vertex;

  const JetCorrector* corrector;
  FactorizedJetCorrector* useJetCorrector;
  JetCorrectionUncertainty *jecUnc_;
  
  inline void ThrowFatalError(const std::string& m) const { cerr << "[ERROR]\t" << m << " Cannot continue. Terminating..." << endl; exit(1); };

  inline void CheckSetUp() const { if(!isSetUp){ ThrowFatalError("MiniAODHelper not yet set up."); } };
  inline void CheckVertexSetUp() const { if(!vertexIsSet){ ThrowFatalError("Vertex is not set."); } };
  
}; // End of class prototype


// === Returned sorted input collection, by descending pT === //
template <typename T> T MiniAODHelper::GetSortedByPt(const T& collection){
  T result = collection;
  std::sort(result.begin(), result.end(), [] (typename T::value_type a, typename T::value_type b) { return ptr(a)->pt() > ptr(b)->pt();});
  return result;
}

// === Returned sorted input collection, by descending CSV === //
template <typename T> T MiniAODHelper::GetSortedByCSV(const T& collection){
  T result = collection;
  std::sort(result.begin(), result.end(), [] (typename T::value_type a, typename T::value_type b) { return GetJetCSV(a,"pfCombinedInclusiveSecondaryVertexV2BJetTags") > GetJetCSV(b,"pfCombinedInclusiveSecondaryVertexV2BJetTags");});
  return result;
}

// === Return the difference of the two input collections, sorted by descending pT === //
template <typename PATObj1, typename PATObj2>
std::vector<PATObj1> MiniAODHelper::GetDifference(const std::vector<PATObj2>& col2,const std::vector<PATObj1>& col1 ){

  std::vector<PATObj1> difference;

  for( typename std::vector<PATObj1>::const_iterator iobj1 = col1.begin(); iobj1!=col1.end(); ++iobj1 ){
    bool presentInSecondCollection = false;
    for( typename std::vector<PATObj2>::const_iterator iobj2 = col2.begin(); iobj1!=col2.end(); ++iobj2 ){
      if(DeltaR(iobj1,iobj2) < 0.00001){
	presentInSecondCollection = true;
	bool sameMomentum = (fabs(ptr(*iobj1)->px() - ptr(*iobj2)->px()) < 0.00001) &&
	  (fabs(ptr(*iobj1)->py() - ptr(*iobj2)->py()) < 0.00001) &&
	  (fabs(ptr(*iobj1)->pz() - ptr(*iobj2)->pz()) < 0.00001);
	if(!sameMomentum){ cerr << "ERROR: found two objects with same eta and phi, but different momenta. This may be caused by mixing corrected and uncorrected collections." << endl;
	  cout << setprecision(7) << "Eta1: " << ptr(*iobj1)->eta() << "\tPhi1: " << ptr(*iobj1)->phi() << "\tpT1: " << ptr(*iobj1)->pt() << endl;
	  cout << setprecision(7) << "Eta2: " << ptr(*iobj2)->eta() << "\tPhi2: " << ptr(*iobj2)->phi() << "\tpT2: " << ptr(*iobj2)->pt() << endl;
	  throw std::logic_error("Inside GetDifference");
	}
	break;
      }
    }
    if(!presentInSecondCollection){ difference.push_back(*iobj1); }
  }
  // Sort by descending pT
  return GetSortedByPt(difference);
}

// ===return sum (union) of two collections, with overlap removed === //
template <typename PATObj1, typename PATObj2>
std::vector<PATObj1> MiniAODHelper::GetUnion(const std::vector<PATObj2>& col2,const std::vector<PATObj1>& col1 ){

  std::vector<PATObj1> unions = col1;

  for( typename std::vector<PATObj2>::const_iterator iobj2 = col2.begin(); iobj2!=col2.end(); ++iobj2 ){
    bool presentInSecondCollection = false;
    for( typename std::vector<PATObj1>::const_iterator iobj1 = col1.begin(); iobj1!=col1.end(); ++iobj1 ){
      if(DeltaR(iobj1,iobj2) < 0.00001){
	presentInSecondCollection = true;
	bool sameMomentum = (fabs(ptr(*iobj1)->px() - ptr(*iobj2)->px()) < 0.00001) &&
	  (fabs(ptr(*iobj1)->py() - ptr(*iobj2)->py()) < 0.00001) &&
	  (fabs(ptr(*iobj1)->pz() - ptr(*iobj2)->pz()) < 0.00001);
	if(!sameMomentum){ cerr << "ERROR: found two objects with same eta and phi, but different momenta. This may be caused by mixing corrected and uncorrected collections." << endl;
	  cout << setprecision(7) << "Eta1: " << ptr(*iobj1)->eta() << "\tPhi1: " << ptr(*iobj1)->phi() << "\tpT1: " << ptr(*iobj1)->pt() << endl;
	  cout << setprecision(7) << "Eta2: " << ptr(*iobj2)->eta() << "\tPhi2: " << ptr(*iobj2)->phi() << "\tpT2: " << ptr(*iobj2)->pt() << endl;
	  throw std::logic_error("Inside GetUnion");
	}
	break;
      }
    }
    if(!presentInSecondCollection){ unions.push_back(*iobj2); }
  }
  // Sort by descending pT
  return GetSortedByPt(unions);
}


template <typename PATObj1, typename PATObj2> 
PATObj1 MiniAODHelper::RemoveOverlap( const std::vector<PATObj2>& other, const PATObj1& unclean ){

  unsigned int nSources1 = unclean.numberOfSourceCandidatePtrs();
  bool hasOverlaps = false;

  std::vector<reco::CandidatePtr> overlaps;

  for( typename std::vector<PATObj2>::const_iterator iobj2 = other.begin(); iobj2!=other.end(); ++iobj2 ){

    unsigned int nSources2 = iobj2->numberOfSourceCandidatePtrs();

    for( unsigned int i1=0; i1<nSources1; i1++ ){
      reco::CandidatePtr source1 = unclean.sourceCandidatePtr(i1);

      if( !(source1.isNonnull() && source1.isAvailable()) ) continue;

      for( unsigned int i2=0; i2<nSources2; i2++ ){
	reco::CandidatePtr source2 = iobj2->sourceCandidatePtr(i2);

	if( !(source2.isNonnull() && source2.isAvailable()) ) continue;

	if( source1==source2 ){
	  hasOverlaps = true;
	  overlaps.push_back(source2);
	}
      }

    }
  }// end loop over iobj22


  PATObj1 cleaned = unclean;
  if( hasOverlaps ){
    math::XYZTLorentzVector original = cleaned.p4();

    for( int iOverlap=0; iOverlap<int(overlaps.size()); iOverlap++ ){

      const reco::Candidate & cOverlap = *(overlaps[iOverlap]);
      math::XYZTLorentzVector overlaper = cOverlap.p4();

      original -= overlaper;
    }

    cleaned.setP4( original );
  }

  return cleaned;
}


template <typename PATObj1, typename PATObj2> 
std::vector<PATObj1> MiniAODHelper::RemoveOverlaps( const std::vector<PATObj2>& other, const std::vector<PATObj1>& unclean ){

  std::vector<PATObj1> cleaned;
  
  for( typename std::vector<PATObj1>::const_iterator iobj1 = unclean.begin(); iobj1!=unclean.end(); ++iobj1 ){

    PATObj1 myobj = (*iobj1);
    PATObj1 clean = RemoveOverlap(other, myobj);

    cleaned.push_back(clean);
  }

  return cleaned;
}


template <typename PATObj1, typename PATObj2> 
double MiniAODHelper::DeltaR( const PATObj2& two, const PATObj1& one ){

  double deltaR = reco::deltaR( one->eta(), one->phi(), two->eta(), two->phi() );
  return deltaR;
}

#endif // _MiniAODHelper_h
