#include <cmath>
#include <sil/sil.hpp>

#include "utils/utils.hpp"

std::vector<std::vector<float>> kernel_maker(int taille, char type)
{
    switch (type)
    {
    case 'l': 
        /* code */
        break;
    case 'g': 
        /* code */
        break;
    case 's': 
        /* code */
        break;
    case 'h': 
        /* code */
        break;
    case 'w': 
        /* code */
        break;
    case 'b': 
        /* code */
        break;
    default:
        break;
    }
}
// linear   gaussian    sharpen     edge_detection(height, width, both)

sil::Image convolution(sil::Image& image, std::vector<std::vector<float>> kernel)
{
    sil::Image copie(image.width(), image.height());
    glm::vec3 pixel;
    int kernel_center = kernel.size() / 2;
    for (int x{kernel_center}; x < image.width() - kernel_center; x++)
    {
        for (int y{kernel_center}; y < image.height() - kernel_center; y++)
        {
            for (int i = 0; i < kernel.size(); i++)
            {
                for (int j = 0; j < kernel.size(); j++)
                {
                    pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                    copie.pixel(x,y).r += kernel[i][j] * pixel.r;
                    copie.pixel(x,y).g += kernel[i][j] * pixel.g;
                    copie.pixel(x,y).b += kernel[i][j] * pixel.b;
                }
            }
        }
    }

    int in_image;
    for (int x{0}; x < kernel_center; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int i = kernel_center - x; i < kernel.size(); i++)
            {
                for (int j = 0; j < kernel.size(); j++)
                {
                    in_image = (y + j - kernel_center);
                    if (in_image >= 0 && in_image < image.height())
                    {
                        pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                        copie.pixel(x,y).r += kernel[i][j] * pixel.r;
                        copie.pixel(x,y).g += kernel[i][j] * pixel.g;
                        copie.pixel(x,y).b += kernel[i][j] * pixel.b;
                    }
                }
            }
        }
    }
    for (int x{image.width() - kernel_center}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int i = 0; i < kernel_center + (image.width() - x); i++)
            {
                for (int j = 0; j < kernel.size(); j++)
                {
                    in_image = (y + j - kernel_center);
                    if (in_image >= 0 && in_image < image.height())
                    {
                        pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                        copie.pixel(x,y).r += kernel[i][j] * pixel.r;
                        copie.pixel(x,y).g += kernel[i][j] * pixel.g;
                        copie.pixel(x,y).b += kernel[i][j] * pixel.b;
                    }
                }    
            }
        }
    }

    for (int x{kernel_center}; x < image.width() - kernel_center; x++)
    {
        for (int y{0}; y < kernel_center; y++)
        {
            for (int i = 0; i < kernel.size(); i++)
            {
                for (int j = kernel_center - y; j < kernel.size(); j++)
                {
                    pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                    copie.pixel(x,y).r += kernel[i][j] * pixel.r;
                    copie.pixel(x,y).g += kernel[i][j] * pixel.g;
                    copie.pixel(x,y).b += kernel[i][j] * pixel.b;
                }  
            }
        }
    }
    for (int x{kernel_center}; x < image.width() - kernel_center; x++)
    {
        for (int y{image.height() - kernel_center}; y < image.height(); y++)
        {
            for (int i = 0; i < kernel.size(); i++)
            {
                for (int j = 0; j < kernel_center + (image.height() - y); j++)
                {
                    pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                    copie.pixel(x,y).r += kernel[i][j] * pixel.r;
                    copie.pixel(x,y).g += kernel[i][j] * pixel.g;
                    copie.pixel(x,y).b += kernel[i][j] * pixel.b;
                }  
            }
        }
    }
    return copie;
}

sil::Image linear_convolution(sil::Image image, int n)
{
    sil::Image copie(image.width(), image.height());
    glm::vec3 pixel;
    float div = 1.f / (n * n);
    int kernel_center = n / 2;
    for (int x{kernel_center}; x < image.width() - kernel_center; x++)
    {
        for (int y{kernel_center}; y < image.height() - kernel_center; y++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                    copie.pixel(x,y).r += div * pixel.r;
                    copie.pixel(x,y).g += div * pixel.g;
                    copie.pixel(x,y).b += div * pixel.b;
                }
            }
        }
    }

    int in_image;
    for (int x{0}; x < kernel_center; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int i = kernel_center - x; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    in_image = (y + j - kernel_center);
                    if (in_image >= 0 && in_image < image.height())
                    {
                    pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                    copie.pixel(x,y).r += div * pixel.r;
                    copie.pixel(x,y).g += div * pixel.g;
                    copie.pixel(x,y).b += div * pixel.b;
                    }
                }
            }
        }
    }
    for (int x{image.width() - kernel_center}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int i = 0; i < kernel_center + (image.width() - x); i++)
            {
                for (int j = 0; j < n; j++)
                {
                    in_image = (y + j - kernel_center);
                    if (in_image >= 0 && in_image < image.height())
                    {
                    pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                    copie.pixel(x,y).r += div * pixel.r;
                    copie.pixel(x,y).g += div * pixel.g;
                    copie.pixel(x,y).b += div * pixel.b;
                    }
                }    
            }
        }
    }

    for (int x{kernel_center}; x < image.width() - kernel_center; x++)
    {
        for (int y{0}; y < kernel_center; y++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = kernel_center - y; j < n; j++)
                {
                    pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                    copie.pixel(x,y).r += div * pixel.r;
                    copie.pixel(x,y).g += div * pixel.g;
                    copie.pixel(x,y).b += div * pixel.b;
                }  
            }
        }
    }
    for (int x{kernel_center}; x < image.width() - kernel_center; x++)
    {
        for (int y{image.height() - kernel_center}; y < image.height(); y++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < kernel_center + (image.height() - y); j++)
                {
                    pixel = image.pixel(x + i - kernel_center, y + j - kernel_center);
                    copie.pixel(x,y).r += div * pixel.r;
                    copie.pixel(x,y).g += div * pixel.g;
                    copie.pixel(x,y).b += div * pixel.b;
                }  
            }
        }
    }
    return copie;
}