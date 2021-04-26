#pragma once

#include "drawing_object.h"


class Line : public DrawingObject
{
public:
   Line() = delete;
   explicit Line( HPEN pen, Point first, Point second );

   void draw( HDC hdc ) override;
};

