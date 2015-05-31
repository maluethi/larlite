/**
 * \file Particle.h
 *
 * \ingroup ERTool
 * 
 * \brief Class def header for a class Particle
 *
 * @author kazuhiro
 */

/** \addtogroup ERTool

    @{*/
#ifndef ERTOOL_PARTICLE_H
#define ERTOOL_PARTICLE_H

#include "ERToolTypes.h"
#include "ERToolConstants.h"
#include "GeoAlgo/GeoVector.h"

namespace ertool {
  class ParticleGraph;
  /**
     \class Particle
     @brief Tree-structured data holder to represent a reconstructed particle
     ertool::Particle is meant to represent a reconstructed particle with a hierarchy       \n
     structure (tree data structure). Each ertool::Particle has PDG code which represents   \n
     a specific particle type. Additional parameters include vtx, momentum, energy, daughter \n
     particle list, and a likelihood score. The likelihood score determines how likely this  \n
     representation is correct. The daughter particle list is a set of ertool::Particle that\n
     is generated by the subject particle.
  */
  class Particle {
    friend class ParticleGraph;
  public:

    Particle(const NodeID_t   node=kINVALID_NODE_ID,
	     const RecoType_t reco_type=kInvisible,
	     const RecoID_t   reco_id=kINVALID_RECO_ID);

    const NodeID_t&  ID       () const;
    const NodeID_t&  Parent   () const;
    const NodeID_t&  Ancestor () const;
    const LayerID_t& Layer    () const;
    const std::vector< ::ertool::NodeID_t >& Children() const;
    float RelationshipScore(const NodeID_t id);
    
    bool RelationAssessed() const;
    bool Primary() const;
    bool Lonely() const; ///< ILL DEFINED
    bool HasChild(const NodeID_t id);

    bool HasRecoObject();
    const RecoType_t& RecoType() const;
    const RecoID_t&   RecoID()   const;

    const int&    PdgCode() const;
    const double& Mass() const;
    double Energy() const;
    double KineticEnergy() const;
    const ::geoalgo::Vector& Vertex()   const;
    const ::geoalgo::Vector& Momentum() const;
    float RecoScore();
    
    void SetParticleInfo( const int pdg_code = kINVALID_INT,
			  const double mass  = kINVALID_DOUBLE,
			  const ::geoalgo::Vector& vtx = kINVALID_VERTEX,
			  const ::geoalgo::Vector& mom = kINVALID_MOMENTUM,
			  const float score = 0);

  private:

    void AddChild(const NodeID_t id, const float score = kDEFAULT_SCORE);
    void SetScore(const NodeID_t id, const float score = kDEFAULT_SCORE);
    void SetRecoInfo(const RecoType_t type,
		     const RecoID_t id  = kINVALID_RECO_ID);

    void RemoveChild(const NodeID_t child );
    void UpdateAfterRemoval(const NodeID_t removed);
    
    // Particle information
    int    _pdg_code; ///< PDG code of a particle
    double _mass;     ///< Particle's mass
    ::geoalgo::Vector _vtx; ///< Creation vertex of a particle
    ::geoalgo::Vector _mom; ///< Creation momentum of a particle
    
    // Graph structure information
    NodeID_t  _node_id;     ///< A unique particle identifier
    NodeID_t  _parent_id;   ///< Parent's ID
    NodeID_t  _ancestor_id; ///< Ancestor's ID (useful for grouping particles from the same interaction)
    LayerID_t _layer_id;    ///< Generation level from the primary interaction (0 = Primary)
    std::vector< ::ertool::NodeID_t > _child_v; ///< List of children's ID
    std::vector< float >  _score_v;    ///< List of a correlation score with other particles 

    // Associated reco object information (type & id to retrieve)
    RecoType_t _reco_type; ///< Associated reco object type (shower, track, or invisible)
    RecoID_t   _reco_id;   ///< Associated reco ojbect id
    
  };

}

#endif
/** @} */ // end of doxygen group 

