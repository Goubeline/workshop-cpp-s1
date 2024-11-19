#include <sil/sil.hpp>

sil::Image carreaux(sil::Image& image, int nb_mosaic)
{
    sil::Image petit(image.width() / nb_mosaic, image.height() / nb_mosaic);
    for (int x = 0; x < petit.width() * nb_mosaic; x+=nb_mosaic)
    {
        for (int y = 0; y < petit.height() * nb_mosaic; y+=nb_mosaic)
        {
            petit.pixel(x/nb_mosaic, y/nb_mosaic) = image.pixel(x, y);
        }
    }
    return petit;
}

sil::Image mosaic(sil::Image image, int nb_mosaic)
{
    sil::Image petit = carreaux(image, nb_mosaic);
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, image.height() - y - 1) = petit.pixel(x % petit.width(), petit.height() - (y % petit.height()) - 1);
        }
    }
    return image;
}

void last_row_column(sil::Image& image, int nb_mosaic, sil::Image& petit)
{
    for (int i = 2; i < nb_mosaic; i+=2)
    {
        for (int x{(i - 2) * petit.width()}; x < ((i - 2) + 1) * petit.width(); x++)
        {
            for (int y{(nb_mosaic - 1) * petit.height()}; y < image.height(); y++)
            {
                image.pixel(x, image.height() - y - 1) =
                        petit.pixel(x % petit.width(), petit.height() - (y % petit.height()) - 1);
                image.pixel(x + petit.width(), image.height() - y - 1) =
                        petit.pixel(petit.width() - (x % petit.width()) - 1, petit.height() - (y % petit.height()) - 1);
            }
        }
    }
    for (int j = 2; j < nb_mosaic; j+=2)
    {
        for (int x{(nb_mosaic - 1) * petit.width()}; x < image.width(); x++)
        {
            for (int y{(j - 2) * petit.height()}; y < ((j - 2) + 1) * petit.height(); y++)
            {
                image.pixel(x, image.height() - y - 1) =
                        petit.pixel(x % petit.width(), petit.height() - (y % petit.height()) - 1);
                image.pixel(x, image.height() - y - 1 - petit.height()) =
                        petit.pixel(x % (image.width()/nb_mosaic), y % petit.height());
            }
        }
    }
    for (int x{(nb_mosaic - 1) * petit.width()}; x < image.width(); x++)
    {
        for (int y{(nb_mosaic - 1) * petit.height()}; y < image.height(); y++)
        {
            image.pixel(x, image.height() - y - 1) =
                    petit.pixel(x % petit.width(), petit.height() - (y % petit.height()) - 1);
        }
    }
}

sil::Image mosaic_mirror(sil::Image image, int nb_mosaic)
{
    sil::Image petit = carreaux(image, nb_mosaic);

    for (int i = 2; i < nb_mosaic; i+=2)
    {
        for (int j = 2; j < nb_mosaic; j+=2)
        {
            for (int x{(i - 2) * petit.width()}; x < ((i - 2) + 1) * petit.width(); x++)
            {
                for (int y{(j - 2) * petit.height()}; y < ((j - 2) + 1) * petit.height(); y++)
                {
                    image.pixel(x, image.height() - y - 1) =
                            petit.pixel(x % petit.width(), petit.height() - (y % petit.height()) - 1);
                    image.pixel(x + petit.width(), image.height() - y - 1) =
                            petit.pixel(petit.width() - (x % petit.width()) - 1, petit.height() - (y % petit.height()) - 1);
                    image.pixel(x, image.height() - y - 1 - petit.height()) =
                            petit.pixel(x % (image.width()/nb_mosaic), y % petit.height());
                    image.pixel(x + petit.width(), image.height() - y - 1 - petit.height()) = 
                            petit.pixel(petit.width() - (x % petit.width()) - 1, y % petit.height());
                }
            }
        }

    }
    if (nb_mosaic % 2 == 1)
    {
        last_row_column(image, nb_mosaic, petit);
    }
    return image;
}