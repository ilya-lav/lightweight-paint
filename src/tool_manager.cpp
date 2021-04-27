#include "tool_manager.h"


ToolManager::ToolManager( HWND window ) :
   m_window{ window }
{
}

COLORREF ToolManager::chooseColor()
{
   COLORREF result;
   CHOOSECOLOR chooseColorData;
   static COLORREF customColors[16];
   static DWORD rgbCurrent;

   ZeroMemory( &chooseColorData, sizeof( chooseColorData ) );
   chooseColorData.lStructSize = sizeof( chooseColorData );
   chooseColorData.hwndOwner = m_window;
   chooseColorData.lpCustColors = (LPDWORD)customColors;
   chooseColorData.rgbResult = rgbCurrent;
   chooseColorData.Flags = CC_FULLOPEN | CC_RGBINIT;

   if( ChooseColor( &chooseColorData ) == TRUE )
   {
      return chooseColorData.rgbResult;
   }
}
