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
  mc_signal->SetParameters(4, 0, 1);

  // "strip plane"
  TH1I *plane = new TH1I("p", "strip plane", granularity, x_min, x_max);
  plane->FillRandom("MCSignal", amp_n);
  
}
