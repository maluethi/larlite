/**
 * \file AlgoMichelE.h
 *
 * \ingroup ERTool
 * 
 * \brief Class def header for a class AlgoMichelE
 *
 * @author davidkaleko
 */

/** \addtogroup ERTool

    @{*/

#ifndef ERTOOL_ALGOMICHELE_H
#define ERTOOL_ALGOMICHELE_H

#include "ERTool/Algo/AlgoEMPart.h"
#include "ERTool/Base/AlgoBase.h"

namespace ertool {

  /**
     \class AlgoMichelE
     User custom SPAFilter class made by davidkaleko
   */
  class AlgoMichelE : public AlgoBase {
  
  public:

    /// Default constructor
    AlgoMichelE(const std::string& name="MichelE");

    /// Default destructor
    ~AlgoMichelE(){};

    /// Reset function
    void Reset() {}
    
    void Finalize();

    /// What to do before event-loop begins
    void ProcessBegin();

    /// What to do once event-loop is over
    void ProcessEnd(TFile* fout);

    void InitializeHistos();

    /// Config setter
    void AcceptPSet(const ::fcllite::PSet& cfg);

    /// Function to evaluate input showers and determine a score
    bool Reconstruct(const EventData &data, ParticleGraph& graph);
    
  protected:
    
    AlgoEMPart _alg_emp;
    TH1F* michel_energy;
    TH1F* shower_st_to_track_end;
  };
}
#endif

/** @} */ // end of doxygen group 
