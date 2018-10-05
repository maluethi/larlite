#ifndef __SPACECHARGEMICROBOONE_CXX__
#define __SPACECHARGEMICROBOONE_CXX__
////////////////////////////////////////////////////////////////////////
// \file SpaceChargeLaser.C
//
// \brief implementation of class for storing/accessing space charge distortions for Laser
//
// \author mrmooney@bnl.gov
// 
////////////////////////////////////////////////////////////////////////

// C++ language includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "math.h"
#include "stdio.h"

#include "TFile.h"
#include "TH3.h"

// LArSoft includes
#include "SpaceChargeLaser.h"
#include "Base/DataFormatConstants.h"

namespace larutil{
  SpaceChargeLaser* SpaceChargeLaser::_me = 0;
  //-----------------------------------------------
  SpaceChargeLaser::SpaceChargeLaser()
  {
    std::string sce_file_path = Form("%s/LArUtil/dat/LaserCorrections.root",getenv("LARLITE_COREDIR"));
    Configure(sce_file_path.c_str());
  }

  //-----------------------------------------------
  SpaceChargeLaser::SpaceChargeLaser(std::string filename)
  {
    Configure(filename);
  }

  //-----------------------------------------------
  SpaceChargeLaser::~SpaceChargeLaser()
  {

  }

  //------------------------------------------------
  bool SpaceChargeLaser::Configure(std::string filename ) {
	TFile *inputfile = new TFile(filename.c_str(),"READ");
	
	auto c_x = (TH3F*) inputfile->Get("Reco_Displacement_X");
	auto c_y = (TH3F*) inputfile->Get("Reco_Displacement_Y");
	auto c_z = (TH3F*) inputfile->Get("Reco_Displacement_Z");
	
	c_x->Copy(corr_x);
	c_y->Copy(corr_y);
	c_z->Copy(corr_z);
	
	xbins = corr_x.GetNbinsX();
	ybins = corr_x.GetNbinsY();
	zbins = corr_x.GetNbinsZ();

	inputfile->Close();
	return true;
 }

  //----------------------------------------------------------------------------
  TVector3 SpaceChargeLaser::GetCorrection(double x, double y, double z)
  {
	
	
	double Dx, Dy, Dz;
	
	Dx = corr_x.Interpolate(x,y,z);
	Dy = corr_y.Interpolate(x,y,z);
	Dz = corr_z.Interpolate(x,y,z);
	
	double eps = 10E-6;
	double too_large = 1000;

	if (fabs(Dx) > too_large || fabs(Dy) > too_large || fabs(Dz) > too_large) {
		throw std::out_of_range ("correction out of bounds");
	}
	if (fabs(Dx) < eps && fabs(Dy) < eps && fabs(Dz) < eps) {
		// I admit this is the worst way to check this, so please
		// improve it. I tried a morning long...		
		throw std::out_of_range ("position is not inside grid");		
	}	
	
	TVector3 corr(Dx, Dy, Dz);
	
	//std::cout << "alive " << Dx << " " << Dy << " " << Dz << std::endl;

	return corr;
  }
bool SpaceChargeLaser::InsideGrid(double x, double y, double z) {
   // Because ROOT is too stupid to handle errors in a standard manner...  
   // and because ROOT is shit, the copy-pasted thing from the interpolation
   // method also is not working...
    std::vector<TH3F> grids = {corr_x, corr_y, corr_z};
    
	for (int axis= 0; axis < grids.size(); axis++) {
	
	auto grid = grids[axis];
	
   	auto Xaxis = grid.GetXaxis();
    	auto Yaxis = grid.GetYaxis();
    	auto Zaxis = grid.GetYaxis();

    	Int_t ubx = Xaxis->FindBin(x);
    	if ( x < Xaxis->GetBinCenter(ubx) ) ubx -= 1;
	    Int_t obx = ubx + 1;
 
    	Int_t uby = Yaxis->FindBin(y);
    	if ( y < Yaxis->GetBinCenter(uby) ) uby -= 1;
    	Int_t oby = uby + 1;
 
    	Int_t ubz = Zaxis->FindBin(z);
    	if ( z < Zaxis->GetBinCenter(ubz) ) ubz -= 1;
    	Int_t obz = ubz + 1;
 	
	if ( grid.IsBinUnderflow(grid.GetBin(ubx, uby, ubz))) return false;
	if ( grid.IsBinOverflow(grid.GetBin(obx, oby, obz)) ) return false;
     	if (ubx <=0 || uby <=0 || ubz <= 0 ||
        	obx > Xaxis->GetNbins() || oby > Yaxis->GetNbins() || obz > Zaxis->GetNbins() ) {
       		return false;
  	}
	}
  return true;
}


bool SpaceChargeLaser::ReadTree() { return true; }
void SpaceChargeLaser::ClearData() {}

}

#endif
