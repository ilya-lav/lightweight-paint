#include "drawing_object.h"

DrawingObject::DrawingObject( HPEN pen, DrawingObject::Point first, DrawingObject::Point second ) :
   m_pen{ pen },
   m_coordinates{ first, second }
{
}
