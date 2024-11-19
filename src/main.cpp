#include <sil/sil.hpp>

#include "une_etoile/une_etoile.hpp"
#include "deux_etoile/deux_etoile.hpp"
#include "disque/disque.hpp"
#include "mosaique/mosaique.hpp"

int main()
{
    sil::Image image{"images/logo.png"};

    // une étoile
    // green_only(image).save("output/green_only.png");
    // canal_swap(image).save("output/canal_swap.png");
    // black_white(image).save("output/black_white.png");
    // negativ(image).save("output/negativ.png");
    // degrade().save("output/degrade.png");

    // deux étoiles
    // mirror(image).save("output/mirror.png");
    // noise(image).save("output/noise.png");
    // rotate90(image).save("output/rotate90.png");
    //luminosityup(image).save("output/luminosityup.jpg");
    //luminositydown(image).save("output/luminositydown.jpg");

    // disque
    // disk({}).save("output/disk.jpg");
    // circle({}).save("output/circle.jpg");
    // circle({.ray = 175, .center = std::make_pair(270, 190), .thickness = 6, .background_color = glm::vec3(0.f, 0.80f, 1.f), .front_color = glm::vec3(0.88f, 0.80f, 0.66f)}).save("output/fancycircle.jpg");
    //anim({}, 50);
    //rosace({}).save("output/rosace.jpg");

    // mosaique
    // mosaic(image, 7).save("output/mosaic.png");
    // mosaic_mirror(image, 5).save("output/mosaic_mirror.png");
}