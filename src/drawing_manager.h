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

   using Point = DrawingObject::Point;

   explicit DrawingManager();

   DrawingManager( DrawingManager& ) = delete;
   DrawingManager( DrawingManager&& ) = delete;

   DrawingManager operator=( DrawingManager& ) = delete;
   DrawingManager operator=( DrawingManager&& ) = delete;

   ~DrawingManager() = default;

public:

   void setMouseState( EMouseState newState );
   EMouseState getMouseState() const;

   void setDrawingTool( EDrawingTool newDrawingMode );
   EDrawingTool getDrawingTool() const;
   
   void setColor( COLORREF newColor );
   void setThickness( int newThickness );


   void handleLeftButtonUp( Point point );
   void handleLeftButtonDown( Point point );
   void handleMouseMove( Point point );


   void addDrawnObject( Point firstPoint, Point secondPoint );
   void addPreviewObject( Point firstPoint, Point secondPoint );

   void drawAll( HDC hdc );
   void drawNew( HDC hdc );
   void drawPreview( HDC hdc );

private:

   std::shared_ptr<DrawingObject> m_previewObject;
   std::vector<std::shared_ptr<DrawingObject>> m_drawnObjects;

   EMouseState m_mouseState;
   DrawingObject::Point m_firstPoint;
   DrawingObject::Point m_secondPoint;

   EDrawingTool m_drawingTool;

   COLORREF m_color;
   int m_thickness;
   HPEN m_pen;
};
