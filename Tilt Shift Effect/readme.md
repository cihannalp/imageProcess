For Part A, apply a 5x5 Gaussian filter (implemented as cascaded 5x1 and 1x5 filters) iteratively. At first iteration,
Gaussian filter is applied to the image except for the band (i.e. K  d) defined by a row number K (e.g. 200) and a
distance d (e.g. 20). At the next iteration, the unaltered band is extended to K  2d. Iterations end when the band contains
the whole image.
