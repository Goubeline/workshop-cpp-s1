#pragma once

#include <sil/sil.hpp>

sil::Image mandelbrot();
sil::Image normalize_histogram(sil::Image image);
sil::Image dithering(sil::Image image);
sil::Image vortex(sil::Image image);