#pragma once

#include <Windows.h>
#include <gdiplus.h>

#pragma comment (lib,"Gdiplus.lib")

#include <string>
#include <string_view>


class SaveManager final
{
public:

   SaveManager();

   SaveManager( SaveManager& ) = delete;
   SaveManager( SaveManager&& ) = delete;

   SaveManager operator=( SaveManager& ) = delete;
   SaveManager operator=( SaveManager&& ) = delete;

   ~SaveManager() = default;


   void requestSavePath( HWND hWindow );
   bool screenCapture( int x, int y, int width, int height, const std::wstring& path, HDC hdc );

   std::wstring getPath();

private:

   std::wstring m_path;

   std::wstring adjustPath( const std::wstring& path );

};

