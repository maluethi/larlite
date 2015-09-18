/**
 * \file dQdxModule.h
 *
 * \ingroup ModularAlgo
 * 
 * \brief Class def header for a class dQdx2DModule
 *
 * @authors David Caratelli, Nevis, dcaratelli@nevis.columbia.edu
 */

/** \addtogroup ModularAlgo

    @{*/
#ifndef DQDXMODULE_H
#define DQDXMODULE_H

#include <iostream>
#include "ShowerRecoModuleBase.h"
/**
   \class dQdxModule : ShowerRecoModuleBase
   This is meant to compute the 2D dQdx along the start of the shower. 
 */
namespace showerreco {

  class dQdxModule : ShowerRecoModuleBase{

  public:

    /// Default constructor
    dQdxModule();

    /// Default destructor
    ~dQdxModule(){}

    void do_reconstruction(const ShowerClusterSet_t &, Shower_t &);
    
    void initialize();

  private:
    //This variable will contain the average dQdx from the start of a shower projected into the 3 planes.
    //it is inteded to be filled such that element 1 contains the average dQdx for the U-plane, 
    //element 2 contains the same for the V-plane, and element 3 will be for the Y-plane. 
    std::vector<double> fdQdx; 
    int _n_hits;
    double _length;
    int    _pl;
    double _dQ;
    double _dQdx;
    double _dQdx_pitch;
    
    // ADC -> e- conversion factors
    double _fC_to_e;
    double _ADC_to_mV;
    double _shp_time;
    double _asic_gain;
    double _charge_conversion;
    
  };

} // showerreco

#endif
/** @} */ // end of doxygen group 

