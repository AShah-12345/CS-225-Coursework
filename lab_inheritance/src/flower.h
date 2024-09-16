/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once

#include "shape.h"
<<<<<<< HEAD
#include "circle.h"
#include "color.h"
#include "rectangle.h"
#include "triangle.h"
=======
>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d

/**
 * A subclass of Drawable that can draw a flower
 */
class Flower : public Drawable
{
  private:
<<<<<<< HEAD
    Shape *stem;
    Shape *pistil; // center piece of flower
    Shape *leaf;
=======
    Shape stem;
    Shape pistil; // center piece of flower
    Shape leaf;
>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d

    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);
<<<<<<< HEAD
    ~Flower();
=======
>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d
    void draw(cs225::PNG* canvas) const;
};
