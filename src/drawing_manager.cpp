#include "drawing_manager.h"


DrawingManager::DrawingManager() :
   m_previewObject{ },
   m_drawnObjects{ },
   m_mouseState{ EMouseState::eMS_Up },
   m_firstPoint{ },
   m_secondPoint{ },
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
         m_firstPoint = point;
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         m_firstPoint = point;
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         m_firstPoint = point;
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
            m_secondPoint = m_firstPoint;
            m_firstPoint = point;
            addDrawnObject( m_firstPoint, m_secondPoint );
         }
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         if( m_mouseState == EMouseState::eMS_Down )
         {
            m_secondPoint = point;
            addPreviewObject( m_firstPoint, m_secondPoint );
         }
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         if( m_mouseState == EMouseState::eMS_Down )
         {
            m_secondPoint = point;
            addPreviewObject( m_firstPoint, m_secondPoint );
         }
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
         addDrawnObject( m_firstPoint, m_secondPoint );
         m_secondPoint = { };
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         addDrawnObject( m_firstPoint, m_secondPoint );
         m_secondPoint = { };
         break;
      }
   }
}

void DrawingManager::addDrawnObject( Point firstPoint, Point secondPoint )
{
   if( firstPoint == Point{} || secondPoint == Point{} )
   {
      return;
   }

   switch( m_drawingTool )
   {
      case EDrawingTool::eDT_Pencil:
      {
         m_drawnObjects.push_back( std::make_shared<Line>( Line{ m_pen,
                                                                 firstPoint,
                                                                 secondPoint } ) );
         break;
      }
      case EDrawingTool::eDT_Line:
      {
         m_drawnObjects.push_back( std::make_shared<Line>( Line{ m_pen,
                                                                 firstPoint,
                                                                 secondPoint } ) );
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         m_drawnObjects.push_back( std::make_shared<EllipseDO>( EllipseDO{ m_pen,
                                                                           firstPoint,
                                                                           secondPoint } ) );
         break;
      }
   }
}

void DrawingManager::addPreviewObject( Point firstPoint, Point secondPoint )
{
   switch( m_drawingTool )
   {
      case EDrawingTool::eDT_Line:
      {
         m_previewObject = std::make_shared<Line>( Line{ m_pen,
                                                         firstPoint, 
                                                         secondPoint } );
         break;
      }
      case EDrawingTool::eDT_Ellipse:
      {
         m_previewObject = std::make_shared<EllipseDO>( EllipseDO{ m_pen,
                                                                   firstPoint,
                                                                   secondPoint }  );
         break;
      }
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

void DrawingManager::drawPreview( HDC hdc )
{
   if( m_previewObject != nullptr )
   {
      m_previewObject->draw( hdc );
   }
}
