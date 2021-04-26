#pragma once

#include "drawing_object.h"


class EllipseDO : public DrawingObject
{
public:
   EllipseDO() = delete;
   explicit EllipseDO( HPEN pen, Point first, Point second );

   void draw( HDC hdc ) override;
};

