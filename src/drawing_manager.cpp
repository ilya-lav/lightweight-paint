#include "drawing_manager.h"


DrawingManager::DrawingManager() :
   m_drawnObjects{ },
   m_mouseState{ EMouseState::eMS_Up },
   m_currentPoint{ },
   m_previousPoint{ },
   m_drawingTool{ EDrawingTool::eDT_Pencil },
   m_color{ RGB( 0, 0, 0 ) },
   m_thickness{ 1 },
   m_pen{ CreatePen( PS_SOLID, m_thickness, m_color ) }
{
}

void DrawingManager::setMouseState( EMouseState newState )
{
   m_mouseState = newState;
}

EMouseState DrawingManager::getMouseState() const
{
   return m_mouseState;
}

void DrawingManager::setCurrentPoint( Point newPoint )
{
   m_previousPoint = m_currentPoint;
   m_currentPoint = newPoint;
}

DrawingObject::Point DrawingManager::getCurrentPoint() const
{
   return m_currentPoint;
}

DrawingObject::Point DrawingManager::getPreviousPoint() const
{
   return m_previousPoint;
}

void DrawingManager::setDrawingTool( EDrawingTool newDrawingMode )
{
   m_drawingTool = newDrawingMode;
}

EDrawingTool DrawingManager::getDrawingTool() const
{
   return m_drawingTool;
}

void DrawingManager::setColor( COLORREF newColor )
{
   m_color = newColor;
   m_pen = CreatePen( PS_SOLID, m_thickness, m_color );
}

void DrawingManager::setThickness( int newThickness )
{
   assert( newThickness > 0 );

   m_thickness = newThickness;
   m_pen = CreatePen( PS_SOLID, m_thickness, m_color );
}

void DrawingManager::handleLeftButtonDown( Point point )
{
   setMouseState( EMouseState::eMS_Down );

   switch( m_drawingTool )
   {
      case EDrawingTool::eDT_Pencil:
      {
         setCurrentPoint( point );
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         setCurrentPoint( point );
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         setCurrentPoint( point );
         break;
      }
   }
}

void DrawingManager::handleMouseMove( Point point, HDC hdc )
{
   switch( m_drawingTool )
   {
      case EDrawingTool::eDT_Pencil:
      {
         if( m_mouseState == EMouseState::eMS_Down )
         {
            setCurrentPoint( point );
            addDrawnObject();
         }
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         if( m_mouseState == EMouseState::eMS_Down )
         {
            setCurrentPoint( point );
         }

         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         break;
      }
   }
}

void DrawingManager::handleLeftButtonUp( Point point )
{
   setMouseState( EMouseState::eMS_Up );

   switch( m_drawingTool )
   {
      case EDrawingTool::eDT_Pencil:
      {

         break;
      }
      case EDrawingTool::eDT_Line:
      {
         addDrawnObject();
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         setCurrentPoint( point );
         addDrawnObject();
         break;
      }
   }
}

void DrawingManager::addDrawnObject()
{
   switch( m_drawingTool )
   {
      case EDrawingTool::eDT_Pencil:
      {
         m_drawnObjects.push_back( std::make_shared<Line>( Line{ m_pen,
                                                                 m_previousPoint,
                                                                 m_currentPoint} ) );
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         m_drawnObjects.push_back( std::make_shared<Line>( Line{ m_pen,
                                                                 m_previousPoint,
                                                                 m_currentPoint } ) );
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         m_drawnObjects.push_back( std::make_shared<EllipseDO>( EllipseDO{ m_pen,
                                                                           m_previousPoint,
                                                                           m_currentPoint } ) );
         break;
      }
   }
}

void DrawingManager::removeLastObject()
{
   if( !m_drawnObjects.empty() )
   {
      m_drawnObjects.pop_back();
   }
}

void DrawingManager::drawAll( HDC hdc )
{
   for( auto item : m_drawnObjects )
   {
      item->draw( hdc );
   }
}

void DrawingManager::drawNew( HDC hdc )
{
   if( !m_drawnObjects.empty() )
   {
      m_drawnObjects[m_drawnObjects.size() - 1]->draw( hdc );
   }
}

