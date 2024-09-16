#include <iostream>
#include <cmath> //for fmod
#include "Image.h"
#include "cs225/PNG.h" //diff folder
#include "cs225/HSLAPixel.h" //diff folder

using cs225::PNG;
using cs225::HSLAPixel;
using namespace std;

/*Image::Image(unsigned int width, unsigned int height) : PNG(width, height)
{
    resize(width, height);
}*/

void Image::darken() //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            if((p.l - 0.1) >= 0) //ensure range of [0,1]
            {
                p.l = p.l - 0.1; //subtract 0.1 from luminance (.l) as specified
            }
            else
            {
                p.l = 0.0;
            }
        }
    }
}

void Image::darken(double amount) //needs to be tested again
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            p.l = max(0.0, p.l - amount);
        }
    }
}

void Image::desaturate() //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            if((p.s - 0.1) >= 0 && (p.s - 0.1) <= 1) //ensure range of [0,1]
            {
                p.s = p.s - 0.1; //subtract 0.1 from saturation (.s) as specified
            }
        }
    }
}

void Image::desaturate(double amount) //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            if((p.s - amount) >= 0 && (p.s - amount) <= 1) //ensure range of [0,1]
            {
                p.s = p.s - amount; //subtract amount from saturation (.s) as specified
            }
        }
    }
}

void Image::grayscale() //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            p.s = 0; //to make an image grayscale, set its saturation to 0
        }
    }
}

void Image::illinify() //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            double hue11 = abs(p.h - 11); //calc hue difference from 11, store in a temp var
            double hue216 = abs(p.h - 216); //calc hue difference from 216, store in a temp var
            if (hue11 > 180)
            {
                hue11 = 360 - hue11; 
            }
            if (hue216 > 180) 
            {
                hue216 = 360 - hue216;
            }
            if (hue11 < hue216) 
            {
                p.h = 11;
            }
            else 
            {
                p.h = 216;
            }
        }
    }
}

void Image::lighten() //needs to be tested again
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            if((p.l + 0.1) >= 0 && (p.l + 0.1) <= 1) //ensure range of [0,1]
            {
                p.l = p.l + 0.1; //add 0.1 from luminance (.l) as specified
            }
            else
            {
                p.l = 1.0;
            }
        }
    }
}

void Image::lighten(double amount) //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            double changedL = p.l + amount;
            if(changedL < 0)
            {
                changedL = 0;
            }
            else if(changedL > 1)
            {
                changedL = 1;
            }
            p.l = changedL;
        }
    }
}

void Image::rotateColor(double degrees) //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            p.h = fmod((p.h + degrees), 360.0);
            if(p.h < 0)
            {
                p.h += 360.0;
            }        
        }
    }
}

void Image::saturate() //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            if((p.s + 0.1) >= 0 && (p.s + 0.1) <= 1) //ensure range of [0,1]
            {
                p.s = p.s + 0.1; //add 0.1 from saturation (.s) as specified
            }
        }
    }
}

void Image::saturate(double amount) //checked
{
    for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
    {
        for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
        {
            HSLAPixel &p = getPixel(w, h); //create ref to pixel using width, height dimensions
            if((p.s + amount) >= 0 && (p.s + amount) <= 1) //ensure range of [0,1]
            {
                p.s = p.s + amount; //add amount from saturation (.s) as specified
            }
        }
    }
}

void Image::scale(double factor) //checked
{
    PNG *original = new PNG(*this);
    this->resize(width() * factor, height() * factor);
    if(factor > 0 && factor < 1)
    {
        for(unsigned w = 0; w < width(); w++) //traverse thru width() <-- from PNG
        {
            for(unsigned h = 0; h < height(); h++) //traverse thru length() <-- from PNG
            {
                const HSLAPixel &p = original->getPixel(w / factor, h / factor); //create ref to pixel using width, height dimensions
                HSLAPixel &scaled = this->getPixel(w, h);
                scaled = p;
            }
        }
    }
    else if(factor > 1)
    {
        for(unsigned w = 0; w < (this->width() / factor); w++)
        {
            for(unsigned h = 0; h < (this->height() / factor); h++)
            {
                HSLAPixel &p = original->getPixel(w, h);
                for(unsigned x = 0; x < factor; x++)
                {
                    for(unsigned y = 0; y < factor; y++)
                    {
                        HSLAPixel &scaled = this->getPixel(w*factor+x, h*factor+y);
                        scaled = p;
                    }
                }
            }
        }
    }
    delete original;
}

void Image::scale(unsigned width, unsigned height) //needs to be fixed
{
        //resize(width, height);
        double newWidth = ((double)width)/(this->width());
        double newHeight = ((double)height)/(this->height());
        if(newWidth < newHeight)
        {
            this->scale(newWidth);
        }
        else
        {
            this->scale(newHeight);
        }
}