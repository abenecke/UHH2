
#pragma once

#include "UHH2/core/plugins/NtupleWriterModule.h"
#include "UHH2/core/include/PuppiParticle.h"

namespace uhh2 {

class NtupleWriterPuppi: public NtupleWriterModule {
public:
    void fill_puppi_info(PuppiParticle & particle, int ctr,reco::CandidateView::const_iterator itPF);

    explicit NtupleWriterPuppi(Config & cfg, const edm::ParameterSet& iConfig);

    virtual void process(const edm::Event &, uhh2::Event &,  const edm::EventSetup&);

    virtual ~NtupleWriterPuppi();
private:

    edm::InputTag src;

    Event::Handle<std::vector<PuppiParticle>> handle; 
    edm::Handle<double> nalgosHandle;
    edm::Handle<std::vector<double>> rawAlphas;
    edm::Handle<std::vector<double>> TheAlphas;
    edm::Handle<std::vector<double>> TheAlphasMed;
    edm::Handle<std::vector<double>> TheAlphasRms; 
    edm::Handle<std::vector<double>> ThePuppiWeight; 
    edm::Handle<std::vector<double>> TheweightwoWeightCut; 
    edm::Handle<std::vector<double>> ThepTunweighted; 
    edm::Handle<reco::CandidateView> hPFProduct;
    // Tokens
    edm::EDGetTokenT<double> nAlgosToken_;
    edm::EDGetTokenT<std::vector<double>> rawAlphasToken_;
    edm::EDGetTokenT<std::vector<double>> alphasToken_;
    edm::EDGetTokenT<std::vector<double>> alphasMedToken_;
    edm::EDGetTokenT<std::vector<double>> alphasRmsToken_;
    edm::EDGetTokenT<std::vector<double>> puppiweightsToken_;
    edm::EDGetTokenT<std::vector<double>> weightwoWeightCutToken_;
    edm::EDGetTokenT<std::vector<double>> pTunweightedToken_;
    edm::EDGetTokenT<reco::CandidateView> packedPFCandidatesToken_;

    const pat::PackedCandidate *lPack;

    float fDZCut;
  };



}//namespace uhh2
