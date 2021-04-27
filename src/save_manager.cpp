#include "save_manager.h"


SaveManager::SaveManager() :
   m_path{ }
{
}

void SaveManager::requestSavePath( HWND hWindow )
{
   OPENFILENAME openFileName;
   WCHAR path[MAX_PATH];

   ZeroMemory( &openFileName, sizeof( openFileName ) );
   ZeroMemory( path, sizeof( WCHAR ) * MAX_PATH );
   openFileName.lStructSize = sizeof( openFileName );
   openFileName.hwndOwner = NULL;
   openFileName.lpstrFile = path;
   openFileName.nMaxFile = MAX_PATH;
   openFileName.lpstrFilter = L"*.bmp\0";

   GetSaveFileName( &openFileName );

   m_path = path;
}

bool SaveManager::screenCapture( int x, int y, int width, int height, const std::wstring& path, HDC hdc )
{
   const GUID guid = { 0x557cf406, 0x1a04, 0x11d3, { 0x9a, 0x73, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e } };
   int initialX{ }, initialY{ };

   HDC memdc = CreateCompatibleDC( hdc );
   HBITMAP membit = CreateCompatibleBitmap( hdc, width, height );
   SelectObject( memdc, membit );
   bool flag = BitBlt( memdc, 0, 0, width, height, hdc, initialX, initialY, SRCCOPY );
   HBITMAP hBitmap = (HBITMAP)SelectObject( memdc, membit );
   Gdiplus::Bitmap bitmap( hBitmap, NULL );

   if( path.empty() )
   {
      return false;
   }

   bitmap.Save( adjustPath( path ).data(), &guid );
   DeleteObject( hBitmap );

   return true;
}

std::wstring SaveManager::getPath()
{
   return m_path;
}

std::wstring SaveManager::adjustPath( const std::wstring& path )
{
   std::wstring result = path;
   
   auto delimeter = result.find( L"." );
   result = result.substr( 0, delimeter );
   result += L".bmp";
   
   return result;
}
