/**
 * \file ParticleGraph.h
 *
 * \ingroup ERTool
 * 
 * \brief Class def header for a class ParticleGraph
 *
 * @author kazuhiro
 */

/** \addtogroup ERTool

    @{*/
#ifndef ERTOOL_PARTICLEGRAPH_H
#define ERTOOL_PARTICLEGRAPH_H

#include "Particle.h"
#include "RecoObjBase.h"
#include <deque>
namespace ertool {
  class Manager;
  
  class ParticleGraph {
    friend class Manager;
  public:
    
    ParticleGraph() {}

    Particle& CreateParticle();
    Particle& GetParticle(const NodeID_t id);
    const Particle& GetParticle(const NodeID_t id) const;
    const std::deque< ::ertool::Particle >& GetParticleArray() const;

    size_t GetNumParticles () const;
    size_t GetNumPrimaries () const;
    const std::vector<NodeID_t> GetAllDescendants(const NodeID_t target) const;
    const std::vector<NodeID_t> GetSiblings(const NodeID_t target) const;
    const std::vector<NodeID_t> GetParticles ( const RecoType_t type      = kINVALID_RECO_TYPE,
					       const bool unassessed_only = false,
					       const int pdg_code = 0 ) const;
    const std::vector<NodeID_t> GetPrimaries ( const RecoType_t type = kINVALID_RECO_TYPE,
					       const bool unassessed_only = false,
					       const int pdg_code = 0) const;
    const CombinationSet_t GetCombinations( const size_t combination_size,
					    const RecoType_t type = kINVALID_RECO_TYPE,
					    const bool unassessed_only = false,
					    const int pdg_code = 0) const;

    void SetParentage    ( const NodeID_t parent, const NodeID_t child,  const float score = kDEFAULT_SCORE);
    void SetSiblings     ( const NodeID_t his_id, const NodeID_t her_id, const float score = kDEFAULT_SCORE);
    void SameParticle    ( const NodeID_t a,      const NodeID_t b      );


    std::string Diagram() const;
    std::string Diagram(const NodeID_t id) const;

  private:
    Particle& CreateParticle(const RecoObjBase& reco_obj);
    void ValidNode(const NodeID_t& id) const;
    void UpdateLayerID(const NodeID_t target, const LayerID_t layer);
    void UpdateParentID(const NodeID_t target, const NodeID_t parent);
    void UpdateAncestorID(const NodeID_t target, const NodeID_t ancestor);
    void UpdateRecoInfo(const NodeID_t target, const RecoType_t reco_type, const RecoID_t reco_id );    
    void AddChild(const NodeID_t target, const NodeID_t child, const float score = kDEFAULT_SCORE);
    void Diagram(const NodeID_t target, std::string& res, std::string prefix="") const;
    void Reset();

    std::deque< ::ertool::Particle > _particle_v;
    
  };

}

#endif
/** @} */ // end of doxygen group 

