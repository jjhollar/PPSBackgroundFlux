# PPSBackgroundFlux

Simple FWLite code and plotting macro to make track-level and hit-level flux maps for the 
PPS pixels in Run 2 data. This can be used for HL-LHC studies of the radiation profile 
and background contribution. 

Requires AOD as input, and a valid grid certificate for non-local files. 

## Instructions to checkout and run FWLite code 

   cmsrel CMSSW_12_4_6 (last release tested, should be OK in newer releases

   cd CMSSW_12_4_6/src

   cmsenv

   git clone git@github.com:jjhollar/PPSBackgroundFlux.git

   scram b

   cd PPSBackgroundFlux/PPSBackgroundFlux/bin

   ../../../../bin/slc7_amd64_gcc10/FWLitePixelsFlux
   
Notes

   - The list of input AOD files, the range of lumisections (MinLumiSection and MaxLumiSection variables), and the 
     trigger (currently HLT_ZeroBias_v6) are currently hard-coded in the FWLitePixelsFlux.cc file. 

   - The output will be a pixelHistogramsRecHits.root file, with 2-D histograms stored in a histograms/ subdirectory. 
     The naming convention is "trxyXXYYY" for track-level histograms (with XX = the arm, 45 or 56, and YYY = the 
     z position, 210 or 220). FOr hit-level histograms it is xyXXYYYplZ (where Z is the plane, 0-5).

## Calculating the luminosity normalization

   To normalize the plots by the integrated luminosity, the standard brilcalc tools can used. The run number and 
   lumisection range can be given by a template JSON file, DummyJSON.json. Then to get the luminosity in nb-1 in 
   a bash session:

   	       source /cvmfs/cms-bril.cern.ch/cms-lumi-pog/brilws-docker/brilws-env 

	       brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -u /nb -i DummyJSON.json --hltpath HLT_ZeroBias_v6	      

## Plotting the normalized background flux maps

   A ROOT macro PlotFlux.C does the normalization and plots the final flux maps, starting from the histograms. It takes the arguments
     int run (several examples are included)

     int tracks (if =1 plot the track-level map, if 0 plot the hit-level map, currently using plane 3 as an example)

     int rebin (factor by which to rebin the plots to avoid low statistics. the final flux map is then corrected by the bin size)

Notes

   - The luminosity obtained from brilcalc is hardcoded for each run

   - The output is provided in units of 10^14 protons/cm^2/fb^-1

   - For the hit-level maps, the pixel "local coordinates" are used, where the x and y axes are inverted.
    