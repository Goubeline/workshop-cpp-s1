#include <cmath>
#include <sil/sil.hpp>
#include<iostream>

#include "une_etoile/une_etoile.hpp"
#include "utils/utils.hpp"

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

sil::Image gaussian_convolution(sil::Image image, int n)
{
    std::vector<std::vector<float>> kernel(n);
    double val;
    double sum = 0;   
    for (float i = 0; i < n; i++)
    {
        kernel[i] = std::vector<float>(n);
        for (float j = 0; j < n; j++)
        {
            float r = std::sqrt((i - n / 2) * (i - n / 2) + (j - n / 2) * (j - n / 2));
            val = (std::exp(-(r * r) / 2)) / 2;
            kernel[i][j] = val;
            sum += val;

        }
    }
    for (float i = 0; i < n; i++)
    {
        for (float j = 0; j < n; j++)
        {
            kernel[i][j] /= sum;
        }
    }   
    return convolution(image, kernel);
}

sil::Image emboss(sil::Image image)
{
    std::vector<std::vector<float>> kernel = {{-2, -1, 0},
                                            {-1, 1, 1},
                                            {0, 1, 2}};
    image = convolution(image, kernel);
    return image;
}

sil::Image outline(sil::Image image)
{
    std::vector<std::vector<float>> kernel = {{-1, -1, -1},
                                            {-1, 8, -1},
                                            {-1, -1, -1}};
    image = convolution(image, kernel);
    return image;
}

sil::Image sharpen(sil::Image image)
{
    std::vector<std::vector<float>> kernel = {{-0.5, -1, -0.5},
                                            {-1, 7, -1},
                                            {-0.5, -1, -0.5}};
    image = convolution(image, kernel);
    return image;
}

sil::Image edge_detection(sil::Image image, char sens)
{
    std::vector<std::vector<float>> kernel;
    switch (sens)
    {
    case 'h':
        kernel = {{-0.25, 0, 0.25},
                    {-0.5, 0, 0.5},
                    {-0.25, 0, 0.25}};

        break;

    case 'v':
        kernel = {{-0.25, -0.5, -0.25},
                    {0, 0, 0},
                    {0.25, 0.5, 0.25}};
        break; 

    default:
        kernel = {{-0.5, -0.25, 0},
                    {-0.25, 0, 0.25},
                    {0, 0.25, 0.5}};
        break;
    }  
    image = black_white(image);
    image = convolution(image, kernel);
    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            image.pixel(i, j).r = std::abs(image.pixel(i, j).r);
            image.pixel(i, j).g = std::abs(image.pixel(i, j).g);
            image.pixel(i, j).b = std::abs(image.pixel(i, j).b);
        }
        
    }
    return image;
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