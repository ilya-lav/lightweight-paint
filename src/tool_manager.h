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

   COLORREF chooseColor();

private:

   const HWND m_window;
};

