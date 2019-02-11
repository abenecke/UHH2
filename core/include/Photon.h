#pragma once

#include "RecParticle.h"
#include "Tags.h"
#include "FlavorParticle.h"
#include "source_candidate.h"
#include <vector>


class Photon : public RecParticle {
public:
    
  enum tag {
    // 2016
    cutBasedPhotonID_Spring16_V2p2_loose,
    cutBasedPhotonID_Spring16_V2p2_medium,
    cutBasedPhotonID_Spring16_V2p2_tight,
    mvaPhoID_Spring16_nonTrig_V1_wp90,
    mvaPhoID_Spring16_nonTrig_V1_wp80,
    // 2017 & 2018
    cutBasedPhotonID_Fall17_94X_V2_loose,
    cutBasedPhotonID_Fall17_94X_V2_medium,
    cutBasedPhotonID_Fall17_94X_V2_tight,
    mvaPhoID_Fall17_iso_V2_wp90,
    mvaPhoID_Fall17_iso_V2_wp80
  };

  static tag tagname2tag(const std::string & tagname){
    if(tagname == "cutBasedPhotonID_Spring16_V2p2_loose") return cutBasedPhotonID_Spring16_V2p2_loose;
    if(tagname == "cutBasedPhotonID_Spring16_V2p2_medium") return cutBasedPhotonID_Spring16_V2p2_medium;
    if(tagname == "cutBasedPhotonID_Spring16_V2p2_tight") return cutBasedPhotonID_Spring16_V2p2_tight;
    if(tagname == "mvaPhoID_Spring16_nonTrig_V1_wp90") return mvaPhoID_Spring16_nonTrig_V1_wp90;
    if(tagname == "mvaPhoID_Spring16_nonTrig_V1_wp80") return mvaPhoID_Spring16_nonTrig_V1_wp80;
    if(tagname == "cutBasedPhotonID_Fall17_94X_V2_loose") return cutBasedPhotonID_Fall17_94X_V2_loose;
    if(tagname == "cutBasedPhotonID_Fall17_94X_V2_medium") return cutBasedPhotonID_Fall17_94X_V2_medium;
    if(tagname == "cutBasedPhotonID_Fall17_94X_V2_tight") return cutBasedPhotonID_Fall17_94X_V2_tight;
    if(tagname == "mvaPhoID_Fall17_iso_V2_wp90") return mvaPhoID_Fall17_iso_V2_wp90;
    if(tagname == "mvaPhoID_Fall17_iso_V2_wp80") return mvaPhoID_Fall17_iso_V2_wp80;
    throw std::runtime_error("unknown Photon::tag '" + tagname + "'");
  }
  
  Photon(){
    m_vertex_x = 0; 
    m_vertex_y = 0; 
    m_vertex_z = 0; 
    m_supercluster_eta = 0; 
    m_supercluster_phi = 0; 
    //    m_trackIso = 0;
    m_puppiChargedHadronIso = 0;
    m_puppiNeutralHadronIso = 0;
    m_puppiPhotonIso = 0;
    m_source_candidates.clear();
  }

  float vertex_x() const{return m_vertex_x;} 
  float vertex_y() const{return m_vertex_y;} 
  float vertex_z() const{return m_vertex_z;} 
  float supercluster_eta() const{return m_supercluster_eta;} 
  float supercluster_phi() const{return m_supercluster_phi;} 
  //  float trackIso() const{return m_trackIso;} 
  float puppiChargedHadronIso() const{return m_puppiChargedHadronIso;} 
  float puppiNeutralHadronIso() const{return m_puppiNeutralHadronIso;} 
  float puppiPhotonIso() const{return m_puppiPhotonIso;} 

  
  //  float get_tag(tag t) const{ return tags.get_tag(static_cast<int>(t));}

  void set_vertex_x(float x){m_vertex_x=x;} 
  void set_vertex_y(float x){m_vertex_y=x;} 
  void set_vertex_z(float x){m_vertex_z=x;} 
  void set_supercluster_eta(float x){m_supercluster_eta=x;} 
  void set_supercluster_phi(float x){m_supercluster_phi=x;} 
  //  void set_trackIso(float x){m_trackIso=x;} 
  void set_puppiChargedHadronIso(float x){m_puppiChargedHadronIso=x;} 
  void set_puppiNeutralHadronIso(float x){m_puppiNeutralHadronIso=x;} 
  void set_puppiPhotonIso(float x){m_puppiPhotonIso=x;} 
  
  //  void set_tag(tag t, float value){tags.set_tag(static_cast<int>(t), value);}

  void set_source_candidates(const std::vector<source_candidate>& vsc){ m_source_candidates = vsc; }
  void add_source_candidate (const source_candidate& sc){ m_source_candidates.push_back(sc); }

  bool  has_tag(tag t) const { return tags.has_tag(static_cast<int>(t)); }
  float get_tag(tag t) const { return tags.get_tag(static_cast<int>(t)); }
  void  set_tag(tag t, float value) { tags.set_tag(static_cast<int>(t), value);}

private:
  float m_vertex_x;
  float m_vertex_y;
  float m_vertex_z;
  float m_supercluster_eta;
  float m_supercluster_phi;
  //  float m_trackIso;

  float m_puppiChargedHadronIso;
  float m_puppiNeutralHadronIso;
  float m_puppiPhotonIso;


  std::vector<source_candidate> m_source_candidates;

  Tags tags;
};
