# Toy Simulation on Resolution Dependency of Strip Width

## Goal
*What is the ideal width of an anode strip in a gaseous detector?*

The ideal strip width of a detector depends on the width of the avalanche.
It is obvious that an avalanche too broad yields uncertainties in position reconstruction.

On the other hand, an avalanche too narrow can reduce spatial resolution, too.
That is because (given a fixed size of anode strips) the number of strips covered reduces with smaller avalanches.
In an extreme case, one *one* strip is covered, yielding a resolution of
![sqrt12].

Hence, an __ideal__ avalanche width (i.e. a minimum in the avalanche-width vs. resolution distribution) should exist.
This small simulation is intended to give a handle on this minimum.
N.B.: It could equivalently be interpreted as a search for the ideal strip width in a 2D readout.

[sqrtqw]: http://chart.apis.google.com/chart?cht=tx&chl=\frac{\mathrm{strip-width}}{\sqrt{12}}
