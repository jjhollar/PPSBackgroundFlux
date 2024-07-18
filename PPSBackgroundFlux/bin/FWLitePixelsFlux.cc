#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
//#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"


#include "DataFormats/CTPPSDetId/interface/CTPPSDetId.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSPixelDetId.h"
#include "DataFormats/CTPPSReco/interface/CTPPSPixelRecHit.h"
#include "DataFormats/CTPPSReco/interface/CTPPSLocalTrackLite.h"
#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"

int main(int argc, char* argv[]) {
  // define what muon you are using; this is necessary as FWLite is not
  // capable of reading edm::Views

  // ----------------------------------------------------------------------
  // First Part:
  //
  //  * enable FWLite
  //  * book the histograms of interest
  //  * open the input file
  // ----------------------------------------------------------------------

  // load framework libraries
  gSystem->Load("libFWCoreFWLite");
  FWLiteEnabler::enable();

  // initialize command line parser
  optutl::CommandLineParser parser("Analyze FWLite Histograms");

  // set defaults
  parser.integerValue("maxEvents") = 1000000000;
  parser.integerValue("outputEvery") = 1000;
  parser.stringValue("outputFile") = "pixelHistogramsRecHits.root";

  // parse arguments
  parser.parseArguments(argc, argv);
  int maxEvents_ = parser.integerValue("maxEvents");
  unsigned int outputEvery_ = parser.integerValue("outputEvery");
  std::string outputFile_ = parser.stringValue("outputFile");
  std::vector<std::string> inFiles_; // = parser.stringVector("inputFiles");
  std::string inputfilelist = "InputFiles.txt";
  std::ifstream ifs2(inputfilelist);

  
  std::string filename;
  std::string xrootdprefix = "root://cms-xrd-global.cern.ch/";
  //  std::string xrootdprefix = "";
  //  xrootdprefix = inputfilepath_;

  std::string fullfilename;

  while ( getline (ifs2,filename) )
    {
      fullfilename = xrootdprefix + filename;
      inFiles_.push_back(fullfilename);
    }
  ifs2.close();

  
  // Set lumisection range
  int MinLumiSection = 110;
  int MaxLumiSection = 999;



  // book a set of histograms
  fwlite::TFileService fs = fwlite::TFileService(outputFile_);
  TFileDirectory dir = fs.mkdir("histograms");

  TH2F *trxy45210_ = dir.make<TH2F>("trxy45210","trxy45210",500,-5,25,500,-15,15);
  TH2F *trxy45220_ = dir.make<TH2F>("trxy45220","trxy45220",500,-5,25,500,-15,15);
  TH2F *trxy56210_ = dir.make<TH2F>("trxy56210","trxy56210",500,-5,25,500,-15,15);
  TH2F *trxy56220_ = dir.make<TH2F>("trxy56220","trxy56220",500,-5,25,500,-15,15);

  TH2F *xy45210pl0_ = dir.make<TH2F>("xy45210pl0","xy45210pl0",250,-15,15,250,-15,15);
  TH2F *xy45220pl0_ = dir.make<TH2F>("xy45220pl0","xy45220pl0",250,-15,15,250,-15,15);
  TH2F *xy56210pl0_ = dir.make<TH2F>("xy56210pl0","xy56210pl0",250,-15,15,250,-15,15);
  TH2F *xy56220pl0_ = dir.make<TH2F>("xy56220pl0","xy56220pl0",250,-15,15,250,-15,15);

  TH2F *xy45210pl1_ = dir.make<TH2F>("xy45210pl1","xy45210pl1",250,-15,15,250,-15,15);
  TH2F *xy45220pl1_ = dir.make<TH2F>("xy45220pl1","xy45220pl1",250,-15,15,250,-15,15);
  TH2F *xy56210pl1_ = dir.make<TH2F>("xy56210pl1","xy56210pl1",250,-15,15,250,-15,15);
  TH2F *xy56220pl1_ = dir.make<TH2F>("xy56220pl1","xy56220pl1",250,-15,15,250,-15,15);

  TH2F *xy45210pl2_ = dir.make<TH2F>("xy45210pl2","xy45210pl2",250,-15,15,250,-15,15);
  TH2F *xy45220pl2_ = dir.make<TH2F>("xy45220pl2","xy45220pl2",250,-15,15,250,-15,15);
  TH2F *xy56210pl2_ = dir.make<TH2F>("xy56210pl2","xy56210pl2",250,-15,15,250,-15,15);
  TH2F *xy56220pl2_ = dir.make<TH2F>("xy56220pl2","xy56220pl2",250,-15,15,250,-15,15);

  TH2F *xy45210pl3_ = dir.make<TH2F>("xy45210pl3","xy45210pl3",250,-15,15,250,-15,15);
  TH2F *xy45220pl3_ = dir.make<TH2F>("xy45220pl3","xy45220pl3",250,-15,15,250,-15,15);
  TH2F *xy56210pl3_ = dir.make<TH2F>("xy56210pl3","xy56210pl3",250,-15,15,250,-15,15);
  TH2F *xy56220pl3_ = dir.make<TH2F>("xy56220pl3","xy56220pl3",250,-15,15,250,-15,15);

  TH2F *xy45210pl4_ = dir.make<TH2F>("xy45210pl4","xy45210pl4",250,-15,15,250,-15,15);
  TH2F *xy45220pl4_ = dir.make<TH2F>("xy45220pl4","xy45220pl4",250,-15,15,250,-15,15);
  TH2F *xy56210pl4_ = dir.make<TH2F>("xy56210pl4","xy56210pl4",250,-15,15,250,-15,15);
  TH2F *xy56220pl4_ = dir.make<TH2F>("xy56220pl4","xy56220pl4",250,-15,15,250,-15,15);

  TH2F *xy45210pl5_ = dir.make<TH2F>("xy45210pl5","xy45210pl5",250,-15,15,250,-15,15);
  TH2F *xy45220pl5_ = dir.make<TH2F>("xy45220pl5","xy45220pl5",250,-15,15,250,-15,15);
  TH2F *xy56210pl5_ = dir.make<TH2F>("xy56210pl5","xy56210pl5",250,-15,15,250,-15,15);
  TH2F *xy56220pl5_ = dir.make<TH2F>("xy56220pl5","xy56220pl5",250,-15,15,250,-15,15);

  TH1F *ls = dir.make<TH1F>("ls","ls",2000,0,2000);

  // loop the events
  int ievt = 0;

  int lumiblock_ = -99;

  for (unsigned int iFile = 0; iFile < inFiles_.size(); ++iFile) {
    // open input file (can be located on castor)
    TFile* inFile = TFile::Open(inFiles_[iFile].c_str());
    if (inFile) {
      std::cout << "Opening " << inFiles_[iFile].c_str() << std::endl;
      // ----------------------------------------------------------------------
      // Second Part:
      //
      //  * loop the events in the input file
      //  * receive the collections of interest via fwlite::Handle
      //  * fill the histograms
      //  * after the loop close the input file
      // ----------------------------------------------------------------------
      fwlite::Event ev(inFile);
      for (ev.toBegin(); !ev.atEnd(); ++ev, ++ievt) {
        edm::EventBase const& event = ev;
        // break loop if maximal number of events is reached
        if (maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false)
          break;
        // simple event counter
        if (outputEvery_ != 0 ? (ievt > 0 && ievt % outputEvery_ == 0) : false)
          std::cout << "  processing event: " << ievt << std::endl;

	lumiblock_ = ev.luminosityBlock();

	if(lumiblock_ < MinLumiSection || lumiblock_ > MaxLumiSection)
	  continue;
	
	//        BX = ev.bunchCrossing();
        int passhlt = 0;

	/*
	edm::Handle<edm::TriggerResults> hltResults;
        event.getByLabel(edm::InputTag("TriggerResults","","HLT"),hltResults);
        const edm::TriggerNames & trigNames = event.triggerNames(*hltResults);
        for(unsigned int i=0; i<trigNames.size();i++)
          {
	    // Lumi = 0.099170851 nb-1
	    std::string TriggerName = trigNames.triggerName(i);
            if((hltResults->accept(i)>0)&&(TriggerName == "HLT_ZeroBias_v6"))
              passhlt=1;
          }

        if(passhlt==0)
          continue;
	*/
	
	ls->Fill(lumiblock_);

	edm::Handle<std::vector<CTPPSLocalTrackLite> > ppstracks;
        // Use this for running on standard Physics AOD                                                                                                                 
        event.getByLabel(std::string("ctppsLocalTrackLiteProducer"), ppstracks);
        for (std::vector<CTPPSLocalTrackLite>::const_iterator track0 = ppstracks->begin(); track0 != ppstracks->end(); ++track0)
          {
            if(track0->rpId() == 2014838784)
              {
                trxy45210_->Fill(track0->x(),track0->y());
              }
            if(track0->rpId() == 2031616000)
              {
                trxy56210_->Fill(track0->x(),track0->y());
              }
            if(track0->rpId() == 2040004608)
	      {
		trxy56220_->Fill(track0->x(),track0->y());
	      }
            if(track0->rpId() == 2023227392)
              {
                trxy45220_->Fill(track0->x(),track0->y());
              }
          }


	edm::Handle< edm::DetSetVector<CTPPSPixelRecHit> > pixelRecHits;
	event.getByLabel(std::string("ctppsPixelRecHits"), pixelRecHits);

	for ( const auto& rechits_ds : *pixelRecHits ) 
	  {
	    const CTPPSPixelDetId detidforrh( rechits_ds.detId() );
	    for ( const auto& rechit : rechits_ds ) 
	      {
                int arm = detidforrh.arm();                                                                               
		int plane = detidforrh.plane();                                                                           
		int station = detidforrh.station();

		if(arm == 0 && station == 0)
		  {
		    if(plane == 0)
		      xy45210pl0_->Fill(rechit.point().y(),-1.0*rechit.point().x());
		    if(plane == 1)
                      xy45210pl1_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 2)
                      xy45210pl2_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 3)
                      xy45210pl3_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 4)
                      xy45210pl4_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 5)
                      xy45210pl5_->Fill(rechit.point().y(),-1.0*rechit.point().x());

		  }
		if(arm == 0 && station == 2)
		  {
		    if(plane == 0)
		      xy45220pl0_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 1)
                      xy45220pl1_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 2)
                      xy45220pl2_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 3)
                      xy45220pl3_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 4)
                      xy45220pl4_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 5)
                      xy45220pl5_->Fill(rechit.point().y(),-1.0*rechit.point().x());
		  }
                if(arm == 1 && station == 0)
                  {
		    if(plane == 0)
		      xy56210pl0_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 1)
                      xy56210pl1_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 2)
                      xy56210pl2_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 3)
                      xy56210pl3_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 4)
                      xy56210pl4_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 5)
                      xy56210pl5_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                  }
                if(arm == 1 && station == 2)
                  {
		    if(plane == 0)
		      xy56220pl0_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 1)
                      xy56220pl1_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 2)
                      xy56220pl2_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 3)
                      xy56220pl3_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 4)
                      xy56220pl4_->Fill(rechit.point().y(),-1.0*rechit.point().x());
                    if(plane == 5)
                      xy56220pl5_->Fill(rechit.point().y(),-1.0*rechit.point().x());

                  }
	      }
	  }


      }
      // close input file
      inFile->Close();
    }
    // break loop if maximal number of events is reached:
    // this has to be done twice to stop the file loop as well
    if (maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false)
      break;
  }
  return 0;
}
