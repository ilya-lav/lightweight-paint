#include "tool_manager.h"


ToolManager::ToolManager( HWND window ) :
   m_window{ window },
   m_controls{ }
{
}

void ToolManager::validateId( Id id ) const
{
   assert( m_controls.count( id ) == 0 );
}

HWND ToolManager::createComboBox( Id id, int x, int y, int width, int height )
{
   validateId( id );

   HWND newListBox = CreateWindow( L"combobox", 
                                   NULL, 
                                   WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
	                               x, 
                                   y, 
                                   width, 
                                   height, 
                                   m_window, 
                                   reinterpret_cast<HMENU>( id ), 
                                   NULL, 
                                   NULL);

   m_controls[id] = newListBox;

   return newListBox;
}

void ToolManager::addItem( Id id, std::wstring_view item )
{
   SendMessage( m_controls[id], WM_SETREDRAW, FALSE, 0L );
   SendMessage( m_controls[id], CB_ADDSTRING, 0, (LPARAM)item.data() );
   SendMessage( m_controls[id], WM_SETREDRAW, TRUE, 0L );
   SendMessage( m_controls[id], CB_SETCURSEL, 0, 0L );
}

int ToolManager::getSelectedIndex( Id id )
{
   int itemIndex = (int)SendMessage( m_controls[id], CB_GETCURSEL, 0, 0 );
   if( itemIndex == LB_ERR )
   {
      return -1;
   }

   return itemIndex;
}

HWND ToolManager::createPushButton( Id id, std::wstring_view name, int x, int y, int width, int height )
{
   validateId( id );

   HWND newListBox = CreateWindow( L"button",
                                   name.data(),
                                   WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                   x,
                                   y,
                                   width,
                                   height,
                                   m_window,
                                   reinterpret_cast<HMENU>(id),
                                   NULL,
                                   NULL );

   m_controls[id] = newListBox;

   return newListBox;
}

COLORREF ToolManager::chooseColor( )
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
