#ifndef __SPACECHARGEMICROBOONE_H__
#define __SPACECHARGEMICROBOONE_H__
////////////////////////////////////////////////////////////////////////
// \file SpaceChargeLaser.h
//
// \brief header of class for storing/accessing space charge distortions for Laser
//
// \author mrmooney@bnl.gov
// 
////////////////////////////////////////////////////////////////////////

#include "LArUtilBase.h"

// ROOT includes
#include "TGraph.h"
#include "TH3.h"
#include "TFile.h"
#include "TVector3.h"

// C/C++ standard libraries
#include <string>
#include <vector>

namespace larutil{
  
  class SpaceChargeLaser : public LArUtilBase {
 
    public:

      SpaceChargeLaser();
      SpaceChargeLaser(std::string filename);
      virtual ~SpaceChargeLaser();
      
      bool Configure(std::string filename);
	
      static SpaceChargeLaser* GetME(){
		if(!_me) _me = new SpaceChargeLaser();
		return _me;
	}
      
      TVector3 GetCorrection(double xVal, double yVal, double zVal);
    
    protected:
	virtual void ClearData();
	virtual bool ReadTree(); 

   
    private:
	static SpaceChargeLaser* _me;	
	bool InsideGrid(double x, double y, double z);
	TH3F corr_x;
	TH3F corr_y;
	TH3F corr_z;
	
	unsigned int xbins, ybins, zbins;
#ifndef __CINT__

#ifndef __CLING__
      
    #endif
    #endif
  }; // class SpaceChargeLaser
}
#endif
