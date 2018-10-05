#include "TH3.h"
#include "TFile.h"
#include <utility>      // std::pair, std::make_pair
#include <iostream>     // std::cout

int gen_offsets(void) {
		
	int x_bins = 2;
	int y_bins = 2;
	int z_bins = 2;
	
	std::pair <int, int> x_range (0,2);
	std::pair <int, int> y_range (0,10);
	std::pair <int, int> z_range (0,2);
	TH3F cor_x = TH3F("Reco_Displacement_X","Reco Displacement X", x_bins, x_range.first, x_range.second,
								  y_bins, y_range.first, y_range.second,
								  z_bins, z_range.first, z_range.second);
        TH3F cor_y = TH3F("Reco_Displacement_Y","Reco Displacement Y", x_bins, x_range.first, x_range.second,
                                                                  y_bins, y_range.first, y_range.second,
                                                                  z_bins, z_range.first, z_range.second);
        TH3F cor_z = TH3F("Reco_Displacement_Z","Reco Displacement Z", x_bins, x_range.first, x_range.second,
                                                                  y_bins, y_range.first, y_range.second,
                                                                  z_bins, z_range.first, z_range.second);
	
	for (int idx=0; idx < x_bins; idx++){
		for (int idy=0; idy<y_bins; idy++) {
			for (int idz=0; idz<z_bins; idz++) {
				std::cout << "id: " << idx << "/" << idy << "/" << idz << std::endl;
				cor_x.SetBinContent(idx+1, idy+1, idz+1, idx);			
				cor_y.SetBinContent(idx+1, idy+1, idz+1, 1);
				cor_z.SetBinContent(idx+1, idy+1, idz+1, 1);

				auto cen_x = cor_x.GetXaxis()->GetBinCenter(idx+1);
				auto cen_y = cor_x.GetYaxis()->GetBinCenter(idx+1);
				auto cen_z = cor_x.GetZaxis()->GetBinCenter(idx+1);
				std::cout << " c: " << cen_x <<", " << cen_y << ", " << cen_z << std::endl;
			}
		}
	}

	//auto interp_x 
	TFile OutputFile("LaserCorrectionTest.root", "recreate");

	cor_x.Write();	
	cor_y.Write();
	cor_z.Write();

	OutputFile.Close();

	return true;
}
