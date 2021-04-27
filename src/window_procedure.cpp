#pragma once

#include "window_procedure.h"

#include <vector>


void InitializeMenu( HWND hWindow )
{
   HMENU menu = CreateMenu();
   HMENU popUpThicknessMenu = CreatePopupMenu();
   HMENU popUpModeMenu = CreatePopupMenu();


   AppendMenu( menu,
               MF_STRING,
               MenuData::saveButton.m_id,
               MenuData::saveButton.m_name.data() );

   AppendMenu( menu,
               MF_STRING | MF_POPUP,
               reinterpret_cast<UINT>( popUpThicknessMenu ),
               MenuData::thicknessSelectionButton.m_name.data() );

   for( auto item : MenuData::thicknessItems )
   {
      AppendMenu( popUpThicknessMenu,
                  MF_STRING,
                  item.m_id,
                  item.m_name.data() );
   }

   AppendMenu( menu,
               MF_STRING | MF_POPUP,
               reinterpret_cast<UINT>( popUpModeMenu ),
               MenuData::modeSelectionButton.m_name.data() );

   for( auto item : MenuData::toolItems )
   {
      AppendMenu( popUpModeMenu,
                  MF_STRING,
                  item.m_id,
                  item.m_name.data() );
   }

   AppendMenu( menu,
               MF_STRING,
               MenuData::colorSelectionButton.m_id,
               MenuData::colorSelectionButton.m_name.data() );


   SetMenu( hWindow, menu );
}


LRESULT CALLBACK MainWindowProcedure( HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam )
{
   static DrawingManager drawingManager;
   static SaveManager saveManager;
   static ToolManager toolManager{ hWindow };
 
   static int currentWidth{ }, currentHeight{ };
   HDC hdc{ };
   HDC memDC{ };
   PAINTSTRUCT paintStruct{ };
   

   switch( message )
   {
      case WM_CREATE:
      {

         break;
      }
      case WM_COMMAND:
      {
         for( auto item : MenuData::thicknessItems )
         {
            if( item.m_id == LOWORD( wParam ) )
            {
               drawingManager.setThickness( item.m_value );
            }
         }

         for( auto item : MenuData::toolItems )
         {
            if( item.m_id == LOWORD( wParam ) )
            {
               drawingManager.setDrawingTool( static_cast<EDrawingTool>( item.m_value ) );
            }
         }

         switch( LOWORD( wParam ) )
         {
            case MenuData::saveButton.m_id:
            {
               POINT point{0, 0};
               ClientToScreen( hWindow, &point );

               saveManager.requestSavePath( hWindow );

               saveManager.screenCapture( point.x,
                                          point.y,
                                          currentWidth,
                                          currentHeight,
                                          saveManager.getPath().data(),  
                                          GetDC(hWindow) );

               MessageBox( hWindow, saveManager.getPath().data(), L"Saved to:", 0 );
               break;
            }
            case MenuData::colorSelectionButton.m_id:
            {
               drawingManager.setColor( toolManager.chooseColor() );
               break;
            }
         }
         break;
      }
      case WM_LBUTTONDOWN: 
      {
         drawingManager.handleLeftButtonDown( {LOWORD( lParam ), HIWORD( lParam )} );
         break;
      }
      case WM_LBUTTONUP: 
      {
         drawingManager.handleLeftButtonUp( {LOWORD( lParam ), HIWORD( lParam )} );
         InvalidateRect( hWindow, NULL, TRUE );
         break;
      }
      case WM_MOUSEMOVE:
      {
         drawingManager.handleMouseMove( {LOWORD( lParam ), HIWORD( lParam )} );
         
         if( drawingManager.getMouseState() == EMouseState::eMS_Down )
         {
            InvalidateRect( hWindow, NULL, TRUE );
         }

         break;
      }
      case WM_PAINT:
      {
         hdc = BeginPaint( hWindow, &paintStruct );
         memDC = CreateCompatibleDC( hdc );
         HBITMAP hBitmap = CreateCompatibleBitmap( hdc, currentWidth, currentHeight );
         SelectObject( memDC, hBitmap );

         RECT rectangle;
         SetRect( &rectangle, 0, 0, currentWidth, currentHeight );
         FillRect( memDC, &rectangle, reinterpret_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ) ) );


         drawingManager.drawAll( memDC );
         drawingManager.drawPreview( memDC );


         BitBlt( hdc, 0, 0, currentWidth, currentHeight, memDC, 0, 0, SRCCOPY );

         DeleteObject( hBitmap );
         DeleteDC( memDC );
         EndPaint( hWindow, &paintStruct );
         break;
      }
      case WM_ERASEBKGND:
      {
         return TRUE;
      }
      case WM_SIZE:
      {
         currentWidth = LOWORD( lParam );
         currentHeight = HIWORD( lParam );
         break;
      }
      case WM_DESTROY:
      {
         PostQuitMessage(EXIT_SUCCESS);
         return 0;
      }
      case WM_GETMINMAXINFO:
      {
         LPMINMAXINFO minMaxInfo = reinterpret_cast<LPMINMAXINFO>( lParam );
         minMaxInfo->ptMinTrackSize.x = WindowData::minWidth;
         minMaxInfo->ptMinTrackSize.y = WindowData::minHeight;
      }
      default:
      {
         return DefWindowProc(hWindow, message, wParam, lParam);
      }
   }
}
