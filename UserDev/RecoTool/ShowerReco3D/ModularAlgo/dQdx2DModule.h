/**
 * \file dQdx2DModule.h
 *
 * \ingroup ModularAlgo
 * 
 * \brief Class def header for a class dQdx2DModule
 *
 * @authors Joseph Zennamo, UChicago, jzennamo@uchicago.edu
 * @authors Brooke Russell, Yale U, brooke.russell@yale.edu
 */

/** \addtogroup ModularAlgo

    @{*/
#ifndef DQDX2DMODULE_H
#define DQDX2DMODULE_H

#include <iostream>
#include "ShowerRecoModuleBase.h"
#include "TVector2.h"
/**
   \class dQdx2DModule : ShowerRecoModuleBase
   This is meant to compute the 2D dQdx along the start of the shower. 
 */
namespace showerreco {

  class dQdx2DModule : ShowerRecoModuleBase{

  public:

    /// Default constructor
    dQdx2DModule(){_name = "dQdx2DModule";}

    /// Default destructor
    ~dQdx2DModule(){}

    void do_reconstruction(const ShowerClusterSet_t &, Shower_t &);

    void initialize();

  private:
    //This variable will contain the average dQdx from the start of a shower projected into the 3 planes.
    //it is inteded to be filled such that element 1 contains the average dQdx for the U-plane, 
    //element 2 contains the same for the V-plane, and element 3 will be for the Y-plane. 
    std::vector<double> dQdx; 

    std::vector<double> Len;
    double _length;
    double _dQdx0;
    double _dQdx1;
    double _dQdx2;
    double _Q0;
    double _Q1;
    double _Q2;
    double _StartW;
    double _StartT;
    double _ShowW;
    double _ShowT;
    double _BestdQdx;
    
  };

} // showerreco

#endif
/** @} */ // end of doxygen group 
