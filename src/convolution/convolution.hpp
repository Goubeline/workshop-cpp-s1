#pragma once

#include <sil/sil.hpp>

sil::Image linear_convolution(sil::Image image, int n);
sil::Image gaussian_convolution(sil::Image image, int n);
sil::Image edge_detection(sil::Image image, char sens);
sil::Image emboss(sil::Image image);
sil::Image sharpen(sil::Image image);
sil::Image outline(sil::Image image);