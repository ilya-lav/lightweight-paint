#pragma once

#include <Windows.h>
#include <assert.h>

#include <map>
#include <string_view>
#include <string>


class ToolManager
{
public:

   using Id = size_t;


   ToolManager( HWND window );

   ToolManager( ToolManager& ) = delete;
   ToolManager( ToolManager&& ) = delete;

   ToolManager operator=( ToolManager& ) = delete;
   ToolManager operator=( ToolManager&& ) = delete;

   ~ToolManager() = default;

   void validateId( Id ) const;

   HWND createComboBox( Id, int, int, int, int );
   void addItem( Id, std::wstring_view );
   int getSelectedIndex( Id );

   HWND createPushButton( Id, std::wstring_view, int, int, int, int );

   COLORREF chooseColor();

private:

   const HWND m_window;
   std::map<Id, HWND> m_controls; 
};

