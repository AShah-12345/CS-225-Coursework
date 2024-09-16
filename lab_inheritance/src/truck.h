/**
 * @file truck.h
 * Declaration of the Truck class.
 */

#pragma once

#include "circle.h"
#include "drawable.h"
#include "rectangle.h"
#include "vector2.h"

<<<<<<< HEAD

=======
>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d
/**
 * A subclass of Drawable that can draw a truck
 */
class Truck : public Drawable
{
  private:
    Vector2 center_;
    Circle** wheels;
    Rectangle* trailer;
    Rectangle* cabin;
    Rectangle* window;
    Rectangle* engine;

    void copy(const Truck& other);
    void clear();

  public:
    Truck(const Vector2& center);
    Truck(const Truck& other);
<<<<<<< HEAD
    virtual ~Truck();
    Truck& operator=(const Truck& rhs);
    Vector2 center() const;
    void set_center(const Vector2& center);
    void draw(cs225::PNG* png) const;
=======
    ~Truck();
    Truck& operator=(const Truck& rhs);
    Vector2 center() const;
    void set_center(const Vector2& center);
>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d
};

