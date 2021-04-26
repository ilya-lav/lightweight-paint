#include "drawing_manager.h"


DrawingManager::DrawingManager() :
   m_drawnObjects{ },
   m_mouseState{ EMouseState::eMS_Up },
   m_currentCoordinates{ },
   m_previousCoordinates{ },
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

void DrawingManager::setCurrentCoordinates( DrawingObject::Point newCoordinates )
{
   m_previousCoordinates = m_currentCoordinates;
   m_currentCoordinates = newCoordinates;
}

DrawingObject::Point DrawingManager::getCurrentCoordinates() const
{
   return m_currentCoordinates;
}

DrawingObject::Point DrawingManager::getPreviousCoordinates() const
{
   return m_previousCoordinates;
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

void DrawingManager::handleLeftButtonUp( DrawingObject::Point point )
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
         setCurrentCoordinates( point );
         addDrawnObject();
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         setCurrentCoordinates( point );
         addDrawnObject();
         break;
      }
   }
}

void DrawingManager::handleLeftButtonDown( DrawingObject::Point point )
{
   setMouseState( EMouseState::eMS_Down );

   switch( m_drawingTool )
   {
      case EDrawingTool::eDT_Pencil:
      {
         setCurrentCoordinates( point );
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         setCurrentCoordinates( point );
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         setCurrentCoordinates( point );
         break;
      }
   }
}

void DrawingManager::handleMouseMove( DrawingObject::Point point, HDC hdc )
{
   switch( m_drawingTool )
   {
      case EDrawingTool::eDT_Pencil:
      {
         if( m_mouseState == EMouseState::eMS_Down )
         {
            setCurrentCoordinates( point );
            addDrawnObject();
         }
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
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
                                                                 m_previousCoordinates,
                                                                 m_currentCoordinates} ) );
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         m_drawnObjects.push_back( std::make_shared<Line>( Line{ m_pen,
                                                                 m_previousCoordinates,
                                                                 m_currentCoordinates } ) );
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         m_drawnObjects.push_back( std::make_shared<EllipseDO>( EllipseDO{ m_pen,
                                                                           m_previousCoordinates,
                                                                           m_currentCoordinates } ) );
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

void DrawingManager::DrawAll( HDC hdc )
{
   for( auto item : m_drawnObjects )
   {
      item->draw( hdc );
   }
}

