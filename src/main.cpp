#include <sil/sil.hpp>

#include "une_etoile/une_etoile.hpp"
#include "deux_etoile/deux_etoile.hpp"
#include "disque/disque.hpp"
#include "mosaique/mosaique.hpp"
#include "trois_etoile/trois_etoile.hpp"
#include "quatre_etoile/quatre_etoile.hpp"
#include "convolution/convolution.hpp"

#include <iostream>
#include "random.hpp"
int main()
{
    sil::Image photo{"images/photo.jpg"};
    sil::Image faible_contraste{"images/photo_faible_contraste.jpg"};
    sil::Image logo{"images/logo.png"};

    // une étoile
    // green_only(logo).save("output/green_only.png");
    // canal_swap(logo).save("output/canal_swap.png");
    // black_white(photo).save("output/black_white.png");
    // negativ(logo).save("output/negativ.png");
    // degrade().save("output/degrade.png");

    // deux étoiles
    // mirror(logo).save("output/mirror.png");
    // noise(logo).save("output/noise.png");
    // rotate90(logo).save("output/rotate90.png");
    // luminosityup(photo).save("output/luminosityup.jpg");
    // luminositydown(photo).save("output/luminositydown.jpg");

    // disque
    // disk({}).save("output/disk.jpg");
    // circle({}).save("output/circle.jpg");
    // circle({.ray = 175, .center = std::make_pair(270, 190), .thickness = 6, .background_color = glm::vec3(0.f, 0.80f, 1.f), .front_color = glm::vec3(0.88f, 0.80f, 0.66f)}).save("output/fancycircle.jpg");
    //anim({}, 50);
    //rosace({}).save("output/rosace.jpg");

    // mosaique
    // mosaic(logo, 7).save("output/mosaic.png");
    // mosaic_mirror(logo, 5).save("output/mosaic_mirror.png");

    // trois étoiles
    // glitch(logo).save("output/glitch.png");
    // sort_pixels(logo).save("output/sort_pixels.png");
    // degrade_color(glm::vec3{1, 0, 0}, glm::vec3{0, 1, 0}).save("output/degrade_Lab.png");

    // quatre étoiles
    // mandelbrot().save("output/mandelbrot.png");
    // dithering(black_white(photo)).save("output/dithering_b&w.png");
    // dithering(photo).save("output/dithering_color.png");
    // normalize_histogram(faible_contraste).save("output/normalize_histogram.png");
    // vortex(logo).save("output/vortex.png");
    
    // convolution
    // linear_convolution(logo, 100).save("output/test.png");
    return 1;
}