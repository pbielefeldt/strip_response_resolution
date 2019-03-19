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

void StripResolution()
{
  const Double_t x_min = -40;
  const Double_t x_max = 40; 
  
  // number of strips from x_min to x_max
  //NOTE: The signal has to be the same in each case; Hence, without loss of
  // generality, a standard gaus is chosen. What's varied is the strip size.
  const Int_t granularity = 80;
  
  // "integrated signal" – number in FillRandom
  const Int_t amp_n = 800;

  // the impeding signal (don't change  it)
  TF1 *mc_signal = new TF1("MCSignal", "gaus(0)", x_min, x_max); 
  Double_t mc_mu = 0; //TODO: vary about one bin width
  mc_signal->SetParameters(4, mc_mu, 1);

  // fill "strip plane"
  TH1I *plane = new TH1I("p", "strip plane", granularity, x_min, x_max);
  plane->FillRandom("MCSignal", amp_n);
  
  // reconstruction of the measusrement
  const Double_t cog =  get_centre(plane);
}
