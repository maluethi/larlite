/**
 * \file CFAlgoStartPointMatch.h
 *
 * \ingroup CMTool
 * 
 * \brief Class def header for a class CFAlgoStartPointMatch
 *
 * @author david
 */

/** \addtogroup CMTool

    @{*/
#ifndef RECOTOOL_CFALGOSTARTPOINTMATCH_H
#define RECOTOOL_CFALGOSTARTPOINTMATCH_H

#include "CMTool/CMToolBase/CFloatAlgoBase.h"
#include <math.h>

namespace cmtool {
  /**
     \class CFAlgoStartPointMatch
     User implementation for CFloatAlgoBase class
     doxygen documentation!
  */
  class CFAlgoStartPointMatch : public CFloatAlgoBase {
    
  public:
    
    /// Default constructor
    CFAlgoStartPointMatch();
    
    /// Default destructor
    virtual ~CFAlgoStartPointMatch(){};

    //
    // Author should be aware of 3 functions at least: Float, Report, 
    // and Reset. More possibly-useful functions can be found in the later 
    // part but commented out. All of these functions are virtual and defined
    // in the base class.

    /**
       Core function: given a set of CPANs, return a float which indicates 
       the compatibility the cluster combination.
    */
    virtual float Float(const std::vector<const cluster::cluster_params*> &clusters);

    /**
       Optional function: called after each iterative approach if a manager class is
       run with verbosity level <= kPerIteration. Maybe useful for debugging.
    */
    virtual void Report();
    
    /// Function to reset the algorithm instance, called together with manager's Reset()
    virtual void Reset();

    double Area2D( double Ax, double Ay,
		   double Bx, double By,
		   double Cx, double Cy);

    double Area3D( double Ax, double Ay, double Az,
		   double Bx, double By, double Bz,
		   double Cx, double Cy, double Cz);

    void UseTime( bool on ) { _time = on; }
    
    void SetMaxArea( double area ) { _MaxArea = area; }

    /**
       Optional function: called at the beginning of 1st iteration. This is called per event.
     */
    //virtual void EventBegin(const std::vector<cluster::ClusterParamsAlg> &clusters);

    /**
       Optional function: called at the end of event ... after the last merging iteration is over.
     */
    //virtual void EventEnd();
 
    /**
       Optional function: called at the beggining of each iterative loop.
       This provides all clusters' information in case the algorithm need them. Note this
       is called per iteration which may be more than once per event.
     */
    //virtual void IterationBegin(const std::vector<cluster::ClusterParamsAlg> &clusters);

    /**
       Optional function: called at the end of each iterative loop.
     */
    //virtual void IterationEnd();

  private:

    double _w2cm, _t2cm;
    double _MaxArea;
    bool _time;  /// Use Time to compute intersection and trinagle area

  };


}
#endif
/** @} */ // end of doxygen group 

