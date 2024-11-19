#include <format>

#include "../utils/utils.hpp"
#include "disque.hpp"

void __disk(Make_circle& data, sil::Image& image)
{
    float dist;
    if (data.thickness == data.ray)
    {
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                dist = sqrt(pow(x - data.center.first, 2) + pow(y - data.center.second, 2));
                if (dist <= data.ray)
                {
                    image.pixel(x, y) = data.front_color;
                }
            }
        }
    }
    else
    {
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                dist = sqrt(pow(x - data.center.first, 2) + pow(y - data.center.second, 2));
                if (dist <= (data.ray + data.thickness/2) && dist > (data.ray - data.thickness/2))
                {
                    image.pixel(x, y) = data.front_color;
                }
            }
        }
    }
}

void check_val(Make_circle& data)
{
    if (data.center.first < 0)
    {
        data.center.first = 0;
    }
    else if (data.center.first > 499)
    {
        data.center.first = 499;
    }
    if (data.center.second < 0)
    {
        data.center.second = 0;
    }
    else if (data.center.second > 499)
    {
        data.center.second = 499;
    }    
    if (data.ray < 20)
    {
        data.ray = 20;
    }
    else if (data.ray > 250)
    {
        data.ray = 250;
    }
}

sil::Image disk(Make_circle data)
{
    check_val(data);
    data.thickness = data.ray;

    sil::Image image(500, 500);
    colorize(image, data.background_color);

    __disk(data, image);
    return image;
}

sil::Image circle(Make_circle data)
{
    check_val(data);

    int quatre_cinquième = 4 * (data.ray / 5.f);
    if (data.thickness < 2)
    {
        data.thickness = 2;
    }
    else if (data.thickness > quatre_cinquième)
    {
        data.thickness = quatre_cinquième;
    }
    data.ray -= data.thickness/2;

    sil::Image image(500, 500);
    colorize(image, data.background_color);

    __disk(data, image);
    return image;
}

void anim(Make_circle data, int nb_frames)
{
    if (nb_frames < 10)
    {
        nb_frames = 10;
    }
    else if (nb_frames > 100)
    {
        nb_frames = 100;
    }

    check_val(data);
    data.thickness = data.ray;
    data.center.first = 0 + data.ray/2;

    int dist = 499 - data.ray;
    float new_center = dist/(nb_frames - 1.f);
    for (int i = 0; i < nb_frames; i++)
    {
        sil::Image image(500, 500);
        colorize(image, data.background_color);

        __disk(data, image);

        image.save(std::format("output/animation/anim{}.jpg",  i+1));
        data.center.first += new_center;
    }
}

sil::Image rosace(Make_circle data)
{
    data.ray = 100;
    data.thickness = 5;

    sil::Image image(500, 500);
    colorize(image, data.background_color);

    data.center.first = 249;
    data.center.second = 249;
    __disk(data, image);
    data.center.first -= data.ray; 
    __disk(data, image);
    data.center.first += 2 * data.ray; 
    __disk(data, image);

    int haut_y = sqrt(pow(data.ray, 2) - pow(data.ray/ 2, 2));
    data.center.second += haut_y;
    data.center.first -= data.ray/2;
    __disk(data, image);
    data.center.first -= data.ray;
    __disk(data, image);

    data.center.second -= 2 * haut_y;
    __disk(data, image);
    data.center.first += data.ray;    
    __disk(data, image);

    return image;
}