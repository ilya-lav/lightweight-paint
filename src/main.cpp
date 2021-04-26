#include "window_procedure.h"


int CALLBACK wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow )
{
   MSG message{ };
   HWND hWindow{ };
   
   Gdiplus::GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR gdiplusToken;
   Gdiplus::GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );

   WNDCLASSEX windowClass{ sizeof( WNDCLASSEX ) };
   windowClass.cbClsExtra = 0;
   windowClass.cbWndExtra = 0;
   windowClass.hbrBackground = reinterpret_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ) );
   windowClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
   windowClass.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
   windowClass.hIconSm = LoadIcon( nullptr, IDI_APPLICATION );
   windowClass.hInstance = hInstance;
   windowClass.lpfnWndProc = MainWindowProcedure;
   windowClass.lpszClassName = L"Name";
   windowClass.lpszMenuName = nullptr;
   windowClass.style = CS_VREDRAW | CS_HREDRAW;


   if( !RegisterClassEx( &windowClass ) )
      return EXIT_FAILURE;

   hWindow = CreateWindow( windowClass.lpszClassName,
                           L"Title",
                           WS_OVERLAPPEDWINDOW,
                           0,
                           0,
                           WindowData::initialWidth,
                           WindowData::initialHeight,
                           nullptr,
                           nullptr,
                           windowClass.hInstance,
                           nullptr );

   if( hWindow == INVALID_HANDLE_VALUE )
   {
      return EXIT_FAILURE;
   }


   InitializeMenu( hWindow );


   ShowWindow( hWindow, nCmdShow );
   UpdateWindow( hWindow );

   while( GetMessage( &message, nullptr, 0, 0) )
   {
      TranslateMessage( &message );
      DispatchMessage( &message );
   }
   Gdiplus::GdiplusShutdown( gdiplusToken );
   return static_cast<int>( message.wParam );
}
