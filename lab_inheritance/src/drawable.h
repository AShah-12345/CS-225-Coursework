/**
 * @file drawable.h
 * Declaration of the Drawable class.
 */

#pragma once

#include "cs225/PNG.h"

/**
 * A pure virtual interface class that can draw itself to a canvas
 */
class Drawable
{
  public:
<<<<<<< HEAD
    virtual ~Drawable()
=======
    ~Drawable()
>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d
    { /* Nothing */
    }

    /**
     * This method will draw the object onto the canvas.
     *
     * @param canvas to draw onto.
     */
    virtual void draw(cs225::PNG* canvas) const = 0;
};

