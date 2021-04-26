#pragma once

#include "Windows.h"

#include <utility>


class DrawingObject
{
public:

   using Point = std::pair<int, int>;

   DrawingObject() = delete;
   explicit DrawingObject( HPEN pen, Point first, Point second );

   virtual void draw( HDC hdc ) = 0;

protected:

   HPEN m_pen;

   std::pair<Point, Point> m_coordinates;

};

