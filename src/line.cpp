#include "line.h"


Line::Line( HPEN pen, Point first, Point second ) :
   DrawingObject{ pen, first, second }
{
}

void Line::draw( HDC hdc )
{
   SelectObject( hdc, m_pen );

   MoveToEx( hdc, m_coordinates.first.first, m_coordinates.first.second, NULL );
   LineTo( hdc, m_coordinates.second.first, m_coordinates.second.second );
}
