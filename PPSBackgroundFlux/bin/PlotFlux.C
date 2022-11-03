void PlotFlux(int run=1, int tracks=1, int rebin=1)
{
  gStyle->SetPadRightMargin(0.25);
  //  gStyle->SetPalette(105);
  //  gStyle->SetLogz();

  TFile *f;

  if(run==1)
    f = TFile::Open("/eos/cms/store/user/jjhollar/PPSHLLHCTimingSimulation/PixelRun2data/pixelHistograms_Run319678_LS49to294.root");
  if(run==2)
    f = TFile::Open("/eos/cms/store/user/jjhollar/PPSHLLHCTimingSimulation/PixelRun2data/pixelHistograms_Run315764_LS69to309.root");
  if(run==3)
    f = TFile::Open("/eos/cms/store/user/jjhollar/PPSHLLHCTimingSimulation/PixelRun2data/pixelHistograms_Run315790_LS700to898.root");
  if(run==4)
    //    f = TFile::Open("/eos/cms/store/user/jjhollar/PPSHLLHCTimingSimulation/PixelRun2data/pixelHistograms_Run315557_LS1to279.root");
    f = TFile::Open("pixelHistograms_Run315557_LS1to279.root");


  TH2F *h45210tr;
  TH2F *h45220tr;
  TH2F *h56210tr;
  TH2F *h56220tr;

  if(tracks==1)
    {
      h45210tr = (TH2F *)f->Get("histograms/trxy45210");
      h45220tr = (TH2F *)f->Get("histograms/trxy45220");
      h56210tr = (TH2F *)f->Get("histograms/trxy56210");
      h56220tr = (TH2F *)f->Get("histograms/trxy56220");
    }

  if(tracks==0)
    {
      h45210tr = (TH2F *)f->Get("histograms/xy45210pl3");                                                                                                           
      h45220tr = (TH2F *)f->Get("histograms/xy45220pl3");                                                                                                           
      h56210tr = (TH2F *)f->Get("histograms/xy56210pl3");                                                                                                           
      h56220tr = (TH2F *)f->Get("histograms/xy56220pl3");                                                                                                           
    }

  TH2F *hflux45210 = new TH2F("hflux45210","hflux45210",30,-5,25,30,-15,15);
  TH2F *hflux45220 = new TH2F("hflux45220","hflux45220",30,-5,25,30,-15,15);
  TH2F *hflux56210 = new TH2F("hflux56210","hflux56210",30,-5,25,30,-15,15);
  TH2F *hflux56220 = new TH2F("hflux56220","hflux56220",30,-5,25,30,-15,15);

  Float_t lumi;
  if(run==1)
    lumi = 0.092210247; // nb-1
  if(run==2)
    lumi = 0.138659399; // nb-1
  if(run==3)
    lumi = 0.044471238; // nb-1
  if(run==4)
    lumi = 0.160809171; // nb-1

  Float_t lumiscaled = 1000.0*1000.0/lumi; // 1 fb-1
  Float_t areascale = 27777.778; // 30mm/500 bins => cm2
  Float_t totalscale = lumiscaled*areascale/1E14; // p/cm2/fb-1 * 1E14

  for(Int_t x = -5; x < 25; x++)
    {
      for(Int_t y = -15; y < 15; y++)
	{
	  Float_t ntr = h45220tr->Integral(h45220tr->GetXaxis()->FindBin(x),
					   h45220tr->GetXaxis()->FindBin(x+1),
					   h45220tr->GetYaxis()->FindBin(y),
					   h45220tr->GetYaxis()->FindBin(y+1));
	  Float_t theflux = ntr*lumiscaled*100/1E15; 
	  hflux45220->SetBinContent(hflux45220->GetXaxis()->FindBin(x),hflux45220->GetYaxis()->FindBin(y),theflux);

	  // 45-210
	  ntr = h45210tr->Integral(h45210tr->GetXaxis()->FindBin(x),
				   h45210tr->GetXaxis()->FindBin(x+1),
				   h45210tr->GetYaxis()->FindBin(y),
				   h45210tr->GetYaxis()->FindBin(y+1));
          theflux = ntr*lumiscaled*100/1E15;
          hflux45210->SetBinContent(hflux45210->GetXaxis()->FindBin(x),hflux45210->GetYaxis()->FindBin(y),theflux);

          // 56-220                                                                                                                                                  
          ntr = h56220tr->Integral(h56220tr->GetXaxis()->FindBin(x),
                                   h56220tr->GetXaxis()->FindBin(x+1),
                                   h56220tr->GetYaxis()->FindBin(y),
                                   h56220tr->GetYaxis()->FindBin(y+1));
          theflux = ntr*lumiscaled*100/1E15;
          hflux56220->SetBinContent(hflux56220->GetXaxis()->FindBin(x),hflux56220->GetYaxis()->FindBin(y),theflux);

	  // 56-210                                                                                                                                                  
          ntr = h56210tr->Integral(h56210tr->GetXaxis()->FindBin(x),
                                   h56210tr->GetXaxis()->FindBin(x+1),
                                   h56210tr->GetYaxis()->FindBin(y),
                                   h56210tr->GetYaxis()->FindBin(y+1));
          theflux = ntr*lumiscaled*100/1E15;
          hflux56210->SetBinContent(hflux56210->GetXaxis()->FindBin(x),hflux56210->GetYaxis()->FindBin(y),theflux);

	}
    }

  Int_t rebinning = rebin;
  Float_t rebinscale = 1.0*rebinning*rebinning;

  TCanvas *c2 = new TCanvas("c2","c2",800,800);
  c2->SetLogz();
  c2->Divide(2,2);
  c2->cd(1);
  h45210tr->SetTitle("p/cm2/fb^{-1} *10^{14}, 45-210");
  h45210tr->Scale(totalscale/rebinscale);
  h45210tr->SetMaximum(2);
  h45210tr->SetMinimum(0.0001);
  h45210tr->Rebin2D(rebinning,rebinning)->Draw("colz");
  h45210tr->SetXTitle("x [mm]");
  h45210tr->SetYTitle("y [mm]");


  c2->cd(2);
  h45220tr->SetTitle("p/cm2/fb^{-1} *10^{14}, 45-220");
  h45220tr->Scale(totalscale/rebinscale);
  h45220tr->SetMaximum(2);
  h45220tr->SetMinimum(0.0001);
  h45220tr->Rebin2D(rebinning,rebinning)->Draw("colz");
  h45220tr->SetXTitle("x [mm]");
  h45220tr->SetYTitle("y [mm]");

  c2->cd(3);
  h56210tr->SetTitle("p/cm2/fb^{-1} *10^{14}, 56-210");
  h56210tr->Scale(totalscale/rebinscale);
  h56210tr->SetMaximum(2);
  h56210tr->SetMinimum(0.0001);
  h56210tr->Rebin2D(rebinning,rebinning)->Draw("colz");
  h56210tr->SetXTitle("x [mm]");
  h56210tr->SetYTitle("y [mm]");

  c2->cd(4);
  h56220tr->SetTitle("p/cm2/fb^{-1} *10^{14}, 56-220");
  h56220tr->Scale(totalscale/rebinscale);
  h56220tr->SetMaximum(2);
  h56220tr->SetMinimum(0.0001);
  h56220tr->Rebin2D(rebinning,rebinning)->Draw("colz");
  h56220tr->SetXTitle("x [mm]");
  h56220tr->SetYTitle("y [mm]");


}
