#include "ellipse.h"

EllipseDO::EllipseDO( HPEN pen, Point first, Point second ) :
   DrawingObject{ pen, first, second }
{
}

void EllipseDO::draw( HDC hdc )
{
   SelectObject( hdc, GetStockObject( HOLLOW_BRUSH ) );
   SelectObject( hdc, m_pen );
   ::Ellipse( hdc, 
              m_coordinates.first.first, 
              m_coordinates.first.second,
              m_coordinates.second.first, 
              m_coordinates.second.second );
}
