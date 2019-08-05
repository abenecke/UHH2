
#include "UHH2/core/plugins/NtupleWriterPuppi.h"
#include "UHH2/core/include/AnalysisModule.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

using namespace uhh2;
using namespace std;

NtupleWriterPuppi::NtupleWriterPuppi(Config & cfg, const edm::ParameterSet& iConfig){
    handle = cfg.ctx.declare_event_output<vector<PuppiParticle>>(cfg.dest_branchname,cfg.dest );
    nAlgosToken_ = cfg.cc.consumes<double>(iConfig.getParameter<edm::InputTag>("nAlgos"));
    rawAlphasToken_ = cfg.cc.consumes<std::vector<double>>(iConfig.getParameter<edm::InputTag>("rawAlphas"));
    alphasToken_ = cfg.cc.consumes<std::vector<double>>(iConfig.getParameter<edm::InputTag>("alphas"));
    alphasMedToken_ = cfg.cc.consumes<std::vector<double>>(iConfig.getParameter<edm::InputTag>("alphasMed"));
    alphasRmsToken_ =cfg.cc.consumes<std::vector<double>>(iConfig.getParameter<edm::InputTag>("alphasRms"));
    puppiweightsToken_ =cfg.cc.consumes<std::vector<double>>(iConfig.getParameter<edm::InputTag>("mypuppiweight"));
    weightwoWeightCutToken_ = cfg.cc.consumes<std::vector<double>>(iConfig.getParameter<edm::InputTag>("weightwoWeightCut"));
    pTunweightedToken_ = cfg.cc.consumes<std::vector<double>>(iConfig.getParameter<edm::InputTag>("pTunweighted"));

    packedPFCandidatesToken_ = cfg.cc.consumes<reco::CandidateView>(cfg.src);
    fDZCut = iConfig.getParameter<double>("DeltaZCut");
    src = cfg.src;

}


NtupleWriterPuppi::~NtupleWriterPuppi(){}


void NtupleWriterPuppi::process(const edm::Event & event, uhh2::Event & uevent,  const edm::EventSetup& iSetup){
 


 
  event.getByToken(rawAlphasToken_, rawAlphas);
  event.getByToken(alphasToken_, TheAlphas);
  event.getByToken(alphasMedToken_, TheAlphasMed);
  event.getByToken(alphasRmsToken_, TheAlphasRms);
  event.getByToken(puppiweightsToken_, ThePuppiWeight);
  event.getByToken(weightwoWeightCutToken_, TheweightwoWeightCut);
  event.getByToken(pTunweightedToken_, ThepTunweighted);
  event.getByToken(packedPFCandidatesToken_, hPFProduct);
  const reco::CandidateView *pfCol = hPFProduct.product(); 
  event.getByToken(nAlgosToken_, nalgosHandle);
  
  std::vector<PuppiParticle> puppiparticles;
  int ctr = 0;
  for(reco::CandidateView::const_iterator itPF = pfCol->begin(); itPF!=pfCol->end(); itPF++) {
     
    puppiparticles.emplace_back();
    
    PuppiParticle& puppiparticle = puppiparticles.back();

    lPack = dynamic_cast<const pat::PackedCandidate*>(&(*itPF));
    try {
      
      fill_puppi_info(puppiparticle, ctr, itPF);
    }
    catch(runtime_error & ex){
      
      cerr << "Exception in fill_jet_info in NtupleWriterJets::process for jets with src=" << src << endl;
      throw;
    }
    
    ctr++;
  }
  uevent.set(handle, move(puppiparticles));

  
}


void NtupleWriterPuppi::fill_puppi_info(PuppiParticle & particle, int ctr, reco::CandidateView::const_iterator itPF){
  particle.set_nAlgos(*nalgosHandle);
  particle.set_rawAlphas((*rawAlphas)[ctr]);
  particle.set_alphas((*TheAlphas)[ctr] );
  particle.set_alphasMed((*TheAlphasMed)[ctr]);
  particle.set_alphasRms((*TheAlphasRms)[ctr] );
  particle.set_charge(itPF->charge());
  particle.set_pt(itPF->pt());
  particle.set_eta(itPF->eta());
  particle.set_phi(itPF->phi());
  particle.set_energy(itPF->energy());
  particle.set_vx(itPF->vx());
  particle.set_vy(itPF->vy());
  particle.set_vz(itPF->vz());
  particle.set_fromPV(lPack->fromPV());
  particle.set_puppiweight(lPack->puppiWeight());
  particle.set_mypuppiweight((*ThePuppiWeight)[ctr]);
  particle.set_weightwoWeightCut((*TheweightwoWeightCut)[ctr]);
  particle.set_pTunweighted((*ThepTunweighted)[ctr]);
  particle.set_dz(lPack->dz());
  particle.set_dxy(lPack->dxy());
  particle.set_fdzcut(fDZCut);
}

