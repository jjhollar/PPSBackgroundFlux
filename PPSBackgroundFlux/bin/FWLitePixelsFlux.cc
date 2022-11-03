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
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"


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
  std::vector<std::string> inputFiles_; // = parser.stringVector("inputFiles");

  // Set lumisection range
  int MinLumiSection = 1;
  int MaxLumiSection = 279;

  // Run 315557
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/2BCBFE07-1D31-8343-BA7B-75ED3D26F218.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/1AAC80C0-02F6-FC48-89BD-963D19EB0662.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/7B0F6089-1F6A-2040-9958-6C8E1C310421.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/901EB5AE-C8FD-F542-885A-083CDB1996BD.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/948AAAC3-14E6-1A40-815F-161924176386.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/493E492D-62B8-8F45-B6F9-3827F3D858AA.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/31ACC5D3-ADF0-0141-9964-C4B453D9C714.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/38820661-AD76-E340-8EAD-9C8106D2A34F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/B37257FF-9FE8-B34C-A790-C71597F5DCC5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/ABB5A362-AAAF-E54A-B39A-AF939BD97D39.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/A37BBBEE-98D6-5847-A54F-A93A9B201888.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/B175B304-EDE1-1D41-932F-02234244DAA4.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/31C44164-217D-7546-A611-EC87D394210E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/F85D50D2-1448-FF4D-BE35-65F9E0981857.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/D6CB1F12-D07C-E94B-94DB-D3AD225EAC36.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/21820900-FF0F-B649-8C1D-8AA1CFDF4F48.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/4AD3BFC2-46DC-A449-9FD3-123ECE7C7417.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/C5DC070C-2963-754E-BC83-D3A828A38A5B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/546E0DAE-6074-6141-9ED6-A838F6566B14.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/9E28B3CD-9329-FE45-AA5C-33DDC68A60DC.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/6127EBBB-327F-C848-B115-93472880848B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/B6314F4E-4AE9-E94A-899A-1A6D523C55B1.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/7943FB9D-6A0B-DD40-A3C6-96A9BBD9BCAD.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/B50343DC-9E2C-7148-813D-C6A2033CD625.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/846437F0-BE83-EB4A-8F9D-3DAC78E9E509.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/6E324F04-48EF-FD4F-9C70-7C08388ECA5F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/8044D8B0-DEE7-0C46-ADD3-D9F0AE6664FB.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/91686A97-F97F-9343-A432-2C1224AEDFB9.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/8F1152F7-53B1-FC4C-99DA-B662A67FC419.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/270000/B3373973-0B2A-A04A-9C99-2F9F5455EC76.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/5BE9BCA6-1625-4F4C-86B4-EE944FE59A08.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/44194A43-E2DB-5F44-8B56-F68765485F3D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/BFE2D396-778D-7C43-A620-8900B912BEE5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/03C259BD-6DF1-AB4F-89CB-F7F03419D053.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/23586BF7-2A94-094E-946A-5EAE5E5F9634.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/CFEF6345-7AA1-6443-AEB6-6CC87009A3D6.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/0D9E07FB-3D98-964E-B82E-CC6297340A2E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/7C1BDA6B-32B0-FB41-A74B-D75E278C90D3.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/B543A163-2079-FD42-AE1F-5DDAE73B51EB.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/270000/E06538D0-D5B4-DD4D-9C1A-2D7229436A2A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/005C21DE-D5A9-734A-8DAB-08B13EA10DE8.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/ECF0A18D-19B0-434A-A8A2-414B7A00DC31.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/41C79530-AC71-0841-AD35-A3BB0B731A72.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/461577C2-8A32-EC4D-AA4C-E784F2DBF280.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/F21D1713-BCA7-F549-AD37-BD690D760B2E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/91B29144-BF58-9940-838C-4CF95D087A01.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/1EE493A7-2B41-104E-8889-47899E3C35FC.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/31B1BF41-08DF-CC46-8B04-8F7609D55D34.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/697F36A4-3C59-EA41-9494-96C2626B590A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/692B02C2-9FE5-AD49-8878-6ED457F62F3D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/E30A169D-7529-094E-ABAC-34A96C1307F0.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/FEA64E1D-F3F8-FF41-A75A-2A6F8075422E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/DB04C3EC-C711-4C41-B89E-F097E90D21FD.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/BB3B3C0E-55D8-8A49-B78C-D5E32AFD1CDE.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/BB39BED7-73A6-7347-9B9C-F669B5E9E235.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/66770D97-2949-384D-BB0A-3F8A6774B6A2.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/5B69BA4B-AB29-6946-9FA1-45F73CB987C5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/61389F33-A2AD-E34A-AC0B-5C111D9B5074.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/18A77829-1260-334C-88DC-F0C57A040432.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/4FBF6A93-E34C-5D4C-B259-8BFB021CA204.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/D3E8D1D9-2C7D-9747-9FFD-5635AF5D0805.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/0712F70A-8F8C-5442-A839-EED6BB9E050D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/54A0CDA0-1346-B04F-9B79-3C6DEB245F6A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/6394BC55-7448-CB44-93FA-4A91D4C7E165.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/22DDF139-2B51-EF47-8372-8391499AD70D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/68CEA683-C1E1-E247-98FB-4BD6940E1025.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/DFA6D58B-CD2A-5A43-98FF-1D215009ED8E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/72BD485D-20AD-F240-90BE-0E3397B4871D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/7EC9B1FB-1E51-0C45-B824-C5FE9AAFFC5F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/238A5D6C-68D1-BA43-A3C6-89A5843E002B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/87445AC7-4B10-814A-8FCF-B9F0167658EF.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100002/A395F13F-5CE0-0C48-B846-29D3FF66C0F9.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/270000/275562C4-7765-0C48-B47E-D82BC11ACA63.root");

  //Run 315790
  /*
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/011B55E7-775F-0B4A-AD56-955998290919.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/01F316C8-7153-6F42-83F3-5DA6C27F6326.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/072A0604-5464-6A43-972B-A8F60BB7210E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/07ECEFBF-C7A6-E446-8509-89F9628D5362.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/0A502D82-CF40-AB4A-A6AC-C25957E320CD.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/0FDB073D-0794-1540-88B3-48A9E5318B86.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/108A7453-C4F0-D04A-9AB0-7AA383358111.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/12250B64-F92A-F343-88DF-609493E30C4F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/17549463-C7C1-274B-91A4-1F2D8574A714.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/190BFC78-D6DA-834D-8607-74A275F904E0.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/1B64360F-02EE-C147-B9E8-526F44492786.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/1BFF989F-C45C-D04B-AD3E-6EFE7114581A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/1DD44055-884B-9840-BFCB-355DD9EACF82.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/1F1F3B4B-3843-DE49-A6A6-7B04423B8CEE.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/232F6F79-52BE-7149-9C05-DE7DC2378ABC.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/2357206A-C8A0-7F4C-8189-552242516342.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/25687EEB-F43B-6A44-B88E-9E08A31B62C2.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/25D01A05-1B56-D947-841D-09080FE0FCBF.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/25D865FF-EAFA-A547-BF2B-127F9ECD13B8.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/28AA0BD1-C0F9-0E40-9DCB-08A6A33AE559.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/28FA1959-076E-1C4B-9A6C-425202C3C603.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/2CD56253-C9E8-9641-AB7C-5A5B02FC0599.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/2E560B78-6C8B-D648-A933-B46F7B25A302.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/2F9DB23B-29EA-E640-BEAB-21BC677B0A3B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/30C0098E-0A13-E044-9F26-FAA637C0FC13.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/35A78C75-2D6A-D349-9A8A-5656FBF94F26.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/41A5F118-9358-9843-BBC9-F0497B90B8FB.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/4513EBA0-824B-604D-8E37-23F3750A127E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/454849E5-72FE-9F42-A6CD-71D045DE6023.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/4B8975FC-34B5-124D-9F9D-77E00D080B7F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/5992FFB3-8548-084C-85D9-3E449804CCB5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/59A2BEC3-1B74-2040-A515-E5392E3EF139.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/5B883A51-29CF-7748-A806-082DCDD450B3.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/5BEB2DD0-A1C4-4045-AD99-5EE5A7ECB389.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/5E5288A5-05B5-D84F-9EB8-806BBFA1106B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/612AAC16-4EFB-E34A-8412-CE81DB8C05E5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/62353A69-7A38-C242-8C59-7512678FA6A9.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/690CD8B0-F781-184E-882E-007DB1A39F74.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/6A999C45-0AD2-0248-9332-FF15113F79B2.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/6DA5CABB-4463-C142-9742-3BDD22495C19.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/72598E92-D49B-ED45-A400-789CDD6E9767.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/730D7911-6E80-074D-A128-6B59D6298FAF.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/74E7ADD4-A257-2549-A042-64E6D99322EB.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/75821835-293A-F649-AD1D-FA9C582E5E46.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/7953CF3D-1CE0-C64C-B003-74BA45205D0E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/7BDD2325-A29D-E04A-AD03-84A659746661.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/7C07C069-33FE-E349-9E08-481B906626AB.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/7F07E723-2251-CC49-B6AA-FAE58C7351C4.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/7F9D621B-FA9A-6842-AC48-78FF365EF48C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/81DF90DD-852B-6B41-A8E6-F45FA7A30A92.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/8255051E-5D26-DD45-9F18-688B7086BC3F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/8AD6BD0C-3584-A44D-AA8D-B7054696945A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/8D5BD159-B7DD-8C46-ACCF-B01787C40CCF.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/9019573D-5824-A042-9D14-145E425D8FD3.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/95D13397-55FF-2F4A-9A13-245F6CE55481.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/9812F10A-9A7E-A748-810A-E3B2950BA6B6.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/9879E355-AD69-D34F-8E6F-9EC22E48D554.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/98E6D161-EDF0-9A48-8DB6-8FBCFA59445B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/99EAC5D7-790D-AA4F-875A-A66C316EE497.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/9B6B1C4E-5714-BE41-8AF5-1CE0D43BD9C2.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/9BC88C46-044E-B043-BAFE-875E1FBE9265.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/9C55E6FF-F13E-EF42-A22B-0597BC53A902.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/9DCCAE5B-5212-5B4A-B12B-02F48F8A8296.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/9E427128-30C6-3549-BF37-8EA6CCA366ED.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/A233C5CC-902E-9A48-A109-21C1352F9574.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/A6E7F6E9-D89C-9746-9469-A9561DDC411A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/B1E2119C-99E7-014E-B5D5-476E8ADC617E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/B3DF1A57-68BA-064D-8981-E673EC877886.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/B78E9D9C-1E6C-FC43-9DE8-C50810CD6A3F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/B8AAE2CF-31EC-D048-86C5-6CF51D247AB9.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/B9923A9B-CDFD-7142-9E7B-310085D433AD.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/B9E437B4-BDE7-ED42-AEE5-433E12EB4CBC.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/BA34F9B5-0D3B-8245-B95C-E925E81FCF8B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/BAFAD4B8-A4D7-2344-87C2-863143E56100.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/BB760960-0A3E-F44E-8929-722A62018333.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/BD311294-3622-AB4A-A87D-88C7D5403F49.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/BD3E5B33-D45F-9C4F-ACF9-283711432D0F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/BEE24F62-84CA-1C44-B241-83419033851B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/C2755420-4F9E-2F4D-96F4-0E712ADC9AFD.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/C96EBFC5-2D05-8640-820A-FFB3C430FFF2.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/CE1FD436-35EA-B449-8389-6295D71D89B1.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/DB7286DF-43F3-EB4F-B2F8-184BD169E916.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/DD39011E-200F-4840-9B83-C1D2BDD13DD5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/DE6E722D-548E-1144-8EE8-35309E2E715E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/E3C3F41C-BF4C-8343-904D-3FC9699E3F19.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/E5F8586E-572F-0245-B5EE-61A8F2EC5C86.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/EC094879-6BE3-FA45-B00E-F553C322185A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/EDDE7FDD-C712-7A49-B26B-94E2170260B4.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/EE335B38-F10B-6047-9129-F706ED5C5E66.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/EEAFECA9-5DBC-8344-A73A-0E0B1DE135C3.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/F3556CCA-572F-3541-86C5-5D0F6CA77438.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/F5B35381-7DAD-7A4D-9630-326CA5A1D604.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/FBF1654C-49B1-F546-920E-7A3322831940.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100001/1083009F-7CAC-4647-85BF-2BDFC564B41C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100001/4746BCE9-C51A-A84F-8E78-E02C0200C28B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100001/5433C2AC-5B39-C24F-A87D-A9BC82F62E5A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100001/86D030BA-FC7A-C741-88D4-14E06817816A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100001/AA1815A1-063B-8344-832F-0C6B7A8FD269.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100001/B8C32191-51AE-484F-9AC1-969590DEB5CC.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/6A17D919-8639-1E4F-B3BC-C3A729D842EF.root");
  */

  //Run 315764
  /*
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/100000/96769957-439B-5842-BB71-9071BDCFDF46.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/2082D6AA-D1C4-1741-8CC5-5483E6008CCC.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/66461E95-72ED-FB49-9F08-E6A6EAF07BD6.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/BE83C34A-9336-FB40-89E4-49BFCDB0252D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/C4C28077-7AF6-8B4D-A274-D322F1A02F9C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/C9E26742-3C9A-7C4C-9009-F0255064CB09.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/CB9C1DF1-296B-C74A-AA67-F7BD32423C9B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/E56B509A-D856-754E-BB80-FE41DF2FAC26.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/ED207FF3-FACE-C349-9852-6AB880668496.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70000/FFEDE1B5-19B2-F243-BD34-DB6C99DE5AB5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/03AB7B14-0ADC-6147-A46D-74E52CA5364F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/0627115B-9471-BC41-887C-87E75AEB5F0E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/19C83F9B-AFD0-CB44-9E14-81ADE23A8A1C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/19D7B86E-2345-6143-B0F7-6FB5C2260AB7.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/2619382F-CBE3-D54E-926D-9C1BB0B41847.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/2C34B1E3-E06D-4B47-B342-F20FECDAC8F1.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/2D672E3A-AAE6-2E44-B5E8-AA0E613E976C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/30FC13EC-5BA9-5040-93EF-100CEC235339.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/31AA303E-ACC4-8A47-BA43-A5922A92C43A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/33AF0BD4-9BEF-614F-AA0E-FDBF667257B4.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/37D29291-B472-AC4B-88B6-D76AEBA53F9C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/3B13DBA1-9A84-FC4B-B3A7-D265032A9365.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/412D9A4D-AC02-334A-BA87-5ED51DA17308.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/486E23B9-2388-8E4D-90FD-3161797AB8CE.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/5373B377-EFBF-2A45-A08E-3ADB5F173468.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/543E821A-C413-EB43-AA0D-8EC0126996DF.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/5621DD45-A3CA-8140-BFBF-FACE547DE5BA.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/564B4932-030F-6A46-9EB9-19BCB2EB9649.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/5836283C-886F-1840-994F-D1AED0BDB551.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/63BBC052-B916-6946-8A91-7F4561CFBAB9.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/63F640F6-6E68-8C45-BE31-66376FCB1ED9.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/66AE19BA-EF59-0849-B02D-154D706C3FB1.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/69262904-6720-EC4E-9A21-0A3EF100FD84.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/6DB62029-E263-BE4E-B283-3CD0091CE8FF.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/70F33013-0E21-BC4C-80FC-2C90FFB8BC12.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/8B0F7892-189F-7142-9611-1375C383F6E3.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/9165AFFB-C3A6-BB45-B6D0-1AD843D340B6.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/9311F0DC-EEDD-114C-B0B6-82F1C0B25556.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/93AD788F-8B23-034F-AE3B-AE1335C39543.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/96736F96-4087-B141-BC55-6AF71C5059D0.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/98BB012B-EBBD-5945-9E2B-4ABE1D076F89.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/99987FCB-FA48-574E-A017-CB50A13D301F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/B1F48C4C-556A-F941-9287-B7074D8D074B.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/B64D1C67-7454-EB4E-9066-812D4C472BD0.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/BDB0AA78-999C-094E-A0AC-F709AFCBCFC2.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/D14470BA-2818-BC45-AD5D-FAAC5FA3C891.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/D9D998F8-BC8F-3345-BB3E-12F9BD8F5467.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/DD740D3F-48C1-9442-AA71-FB9DDB007647.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/DF03CF13-D01C-6746-AD4C-4E9A21CE1EFD.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/E0E2035E-F5D5-8246-BAF5-5C1F30922C0D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/F4790952-CC54-6940-929E-B56C57A35E29.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/F496D223-BB89-0241-8AE0-F0EF33F5B488.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/F4FB0004-E70E-6646-B066-8FCDBFACAC30.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/F5729845-45BF-DD47-ABEC-F7CC6E625AE8.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018A/ZeroBias/AOD/12Nov2019_UL2018-v2/70001/F7B34A15-5B8F-6A42-9E8D-CE05CF2611D9.root");
  */

   //Run 319678
   /*
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/033193BC-EF72-AA42-A4CD-6011D6D54A8A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/07F3AA04-EA28-EC4B-986B-6B4875E0D064.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/10A22F0E-8718-104E-851A-0B0B34FEDBCC.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/2835477E-0727-254B-B593-7670FC5E435F.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/309567F6-2D63-C14D-8D05-7FAE05DCB355.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/3B3932CE-90FE-B444-83FD-DAD233908CA2.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/3C53A67E-1AD2-A948-8C91-47668EA015A8.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/4313BAFF-EAF4-D14F-BE45-EFA3804DD675.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/4589BF4E-07AE-5D49-AB6B-8F7340A14D3D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/487C2C33-1B81-5247-B331-070A25EA91D1.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/58D63E81-5F11-BC40-BBE1-54E7EA4064B4.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/60B24B8C-ECEA-3B43-8BA3-2CA53BD8609A.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/693F80CE-6E1B-F644-97F7-8ACF8908E892.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/6C64911C-FD2A-2A45-BB96-8740B2FF373C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/6F39720E-A610-414D-8EA6-A36A8F5C00E4.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/71814DC1-7BBF-CC43-A81B-AA2505A9FAB6.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/73A01F76-B557-BD45-890D-C8A1C0900137.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/7A3055BD-FC8B-264E-8F31-80F563738C40.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/82C74C97-BD8A-C746-839A-21A9037CCED3.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/830E85A4-257F-8A43-9EC0-7AFD8714CEC5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/83DF2483-51AE-8345-B41E-B006DD502B9E.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/853E4603-1379-6B45-ABE1-6593A0629458.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/89923A08-F2AC-4E4A-A644-512E9CEC82AB.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/8A077E31-006D-8949-A475-EC7C85A92ECA.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/8C099348-F7F2-BB49-978F-25F4C4FC0BE4.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/8F907D4B-B495-0949-8A7F-1DC9719E375D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/9609D96B-F27C-9A41-9F55-AD558C25DB7D.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/AA3216A2-E154-7D48-8134-A7EBCE0BB988.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/ADD1C8DD-5288-3E49-9756-A88307B9B1F5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/AF071E7A-EC33-7D42-B094-C1DE4077D6C0.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/AF312B7C-56A5-2844-A048-3720F180E537.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/B025B222-4866-3C4E-AB7F-0A915509DFA2.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/C5051172-7E78-6F47-A2A6-7DEF4E99A56C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/D5808E5D-F3DD-5647-B3F2-74CAA8CA84B8.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/D5867EC0-8520-7349-BC74-528D9EDD864C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/D9A1040D-520C-0F4C-8D8C-87159C3952FF.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/DA12726C-0CA1-6C41-95BA-34BE8583D0DB.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/DB467D8B-C8AE-814F-9095-A5EF3D1994D5.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/DCFE5925-1089-6849-BB55-BA3DA673EB5C.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/E2535B7E-ADE7-4D4F-981F-44C5EFBED5E4.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/E53E3564-CC89-C34C-8295-E48298FE8431.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/F5AF6AEF-0DEB-0347-8D58-3F888B51BBAF.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/FA06A056-E173-3E4B-B923-A0AAFD0694BC.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/FA211A25-CB24-744B-B6E7-E89D4F950831.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/10000/FCD70992-3D13-7543-A022-7F381CD7FD37.root");
  inputFiles_.push_back("root://cms-xrd-global.cern.ch//store/data/Run2018C/ZeroBias/AOD/12Nov2019_UL2018_rsb-v1/230000/E875AEAC-29E6-C947-BC79-98B6EAD661FD.root");
   */

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

  for (unsigned int iFile = 0; iFile < inputFiles_.size(); ++iFile) {
    // open input file (can be located on castor)
    TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
    if (inFile) {
      std::cout << "Opening " << inputFiles_[iFile].c_str() << std::endl;
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
		      xy45210pl0_->Fill(rechit.point().x(),rechit.point().y());
		    if(plane == 1)
                      xy45210pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy45210pl2_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 3)
                      xy45210pl3_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 4)
                      xy45210pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy45210pl5_->Fill(rechit.point().x(),rechit.point().y());

		  }
		if(arm == 0 && station == 2)
		  {
		    if(plane == 0)
		      xy45220pl0_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 1)
                      xy45220pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy45220pl2_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 3)
                      xy45220pl3_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 4)
                      xy45220pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy45220pl5_->Fill(rechit.point().x(),rechit.point().y());
		  }
                if(arm == 1 && station == 0)
                  {
		    if(plane == 0)
		      xy56210pl0_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 1)
                      xy56210pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy56210pl2_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 3)
                      xy56210pl3_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 4)
                      xy56210pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy56210pl5_->Fill(rechit.point().x(),rechit.point().y());
                  }
                if(arm == 1 && station == 2)
                  {
		    if(plane == 0)
		      xy56220pl0_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 1)
                      xy56220pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy56220pl2_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 3)
                      xy56220pl3_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 4)
                      xy56220pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy56220pl5_->Fill(rechit.point().x(),rechit.point().y());

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
