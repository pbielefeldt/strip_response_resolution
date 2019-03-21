Double_t get_centre(TH1I* h)
{
  double amp_sum=0;
  double x_a_sum=0;
  
  for (Int_t bin=1; bin<=h->GetNbinsX(); bin++) // beware the ROOT numbering
  {
    Int_t    a = h->GetBinContent(bin); 
    Double_t c = h->GetXaxis()->GetBinCenter(bin); 
    
    amp_sum += a;
    x_a_sum += a*c;
  }
  
  return x_a_sum/amp_sum;
}

// number of strips with non-zero entry
Int_t num_strips(TH1I* h)
{
  Int_t n=0;
  for (Int_t bin=1; bin<=h->GetNbinsX(); bin++)
  {
    if (h->GetBinContent(bin) != 0) n++;
  }
  return n;
}

void StripResolution()
{
  const Double_t x_min = -400;
  const Double_t x_max = 400; 
  
  // number of strips from x_min to x_max (start value, is incremented)
  //NOTE: The signal has to be the same in each case; Hence, without loss of
  // generality, a standard gaus is chosen. What's varied is the strip size. 
  // The granularity hence serves as a geometric scalng factor. If the question
  // asked is "how does the resolution change with broadening avalanche width?",
  // what has to be counted here is sigma(avalanche)*granularity, where the 
  // former is set to one.
  const Int_t granularity_start = 2;
  const Int_t granularity_incre = 4;
  
  // "integrated signal" – number in FillRandom
  const Int_t amp_n = 800;
  
  // how many individual simulations?
  const int runs_n = 250;
  // how many events per run?
  const int events_n = 8;

  // the impeding signal (don't change  it)
  TF1 *mc_signal = new TF1("MCSignal", "gaus(0)", x_min, x_max); 
  
  TGraph *plot_graph = new TGraph(runs_n);
  
  for (int n=0; n<runs_n; n++)
  {
    // number of strips
    const Int_t granularity = granularity_start + (n*granularity_incre);
    
    Double_t RMS2 = 0.;
    
    for (int e=0; e<events_n; e++)
    {
        Double_t mc_mu = 0; //TODO: vary about one bin width
        mc_signal->SetParameters(4, mc_mu, 1);
        
        // fill "strip plane"
        TH1I *plane = new TH1I("p", "strip plane", granularity, x_min, x_max);
        plane->FillRandom("MCSignal", amp_n);
        
        // reconstruction of the measusrement
        const Double_t cog = get_centre(plane);
        const Double_t residual = cog-mc_mu;
        
        RMS2 += residual*residual;
        
        delete plane;
    }
    
    // error assumption
    Double_t reco_err = 0;
    const Int_t hit_strips = num_strips(plane);
    if (hit_strips<2) reco_err = ((x_max-x_min)/granularity) / TMath::Sqrt(12); // case sqrt(12)
    else reco_err = plane->GetStdDev(11) / plane->GetNbinsX();                  // the "11" should be the x-axis
    
    const Double_t sigma = TMath::Sqrt(RMS2/(events_n-1));
    
    /*
    cout << "µ: " << cog 
         << "\tsigma: " << reco_err*granularity 
         << "\thits: " << hit_strips
         << "\tn:" << granularity 
         << endl;
    */
    
    plot_graph->SetPoint(n, granularity, reco_err*granularity);
  }
  
  TCanvas *c1 = new TCanvas("c1","strip resolution",200,10,700,500);
  plot_graph->SetLineWidth(4);
  plot_graph->SetMarkerStyle(21);
  plot_graph->SetTitle("strip response resolution");
  plot_graph->GetXaxis()->SetTitle("strip number");
  plot_graph->GetYaxis()->SetTitle("sigma");
  
  c1->SetLogy();
  plot_graph->Draw("AIC*");
  c1->Update();
  
  delete mc_signal;
}
