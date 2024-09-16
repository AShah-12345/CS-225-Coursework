/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
<<<<<<< HEAD
#include "cs225/PNG.h"

using namespace cs225;

namespace cs225
{
    class Image : public cs225::PNG
    {
        private: //none
        public: //from doxygen, constructors left out since they will be derived from PNG
            void lighten();
            void lighten(double amount);
            void darken();
            void darken(double amount);
            void saturate();
            void saturate(double amount);
            void desaturate();
            void desaturate(double amount);
            void grayscale();
            void rotateColor(double degrees);
            void illinify();
            void scale(double factor);
            void scale(unsigned w, unsigned h);
            //Image(unsigned int width, unsigned int height);
    };
}
=======

>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d
