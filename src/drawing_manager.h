#pragma once

#include <Windows.h>
#include <assert.h>

#include <vector>
#include <utility>
#include <memory>

#include "drawing_object.h"
#include "line.h"
#include "ellipse.h"


enum class EMouseState
{
   eMS_Up,
   eMS_Down,
};

enum class EDrawingTool : size_t
{
   eDT_Pencil = 0,
   eDT_Line = 1,
   eDT_Ellipse = 2,
};


class DrawingManager final
{
public:

   explicit DrawingManager();

   DrawingManager( DrawingManager& ) = delete;
   DrawingManager( DrawingManager&& ) = delete;

   DrawingManager operator=( DrawingManager& ) = delete;
   DrawingManager operator=( DrawingManager&& ) = delete;

   ~DrawingManager() = default;

public:

   void setMouseState( EMouseState newState );
   EMouseState getMouseState() const;

   void setCurrentCoordinates( DrawingObject::Point newCoordinates );
   DrawingObject::Point getCurrentCoordinates() const;

   DrawingObject::Point getPreviousCoordinates() const;

   void setDrawingTool( EDrawingTool newDrawingMode );
   EDrawingTool getDrawingTool() const;
   
   void setColor( COLORREF newColor );
   void setThickness( int newThickness );

   void handleLeftButtonUp( DrawingObject::Point point );
   void handleLeftButtonDown( DrawingObject::Point point );
   void handleMouseMove( DrawingObject::Point point, HDC hdc );

   void addDrawnObject();
   void removeLastObject();
   void DrawAll( HDC hdc );

   void drawPreviewLine();

private:

   std::vector<std::shared_ptr<DrawingObject>> m_drawnObjects;

   EMouseState m_mouseState;
   DrawingObject::Point m_currentCoordinates;
   DrawingObject::Point m_previousCoordinates;

   EDrawingTool m_drawingTool;

   COLORREF m_color;
   int m_thickness;
   HPEN m_pen;
};
