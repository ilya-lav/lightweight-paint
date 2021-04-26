#pragma once

#include "drawing_manager.h"
#include "save_manager.h"
#include "tool_manager.h"
#include "data.h"


void InitializeMenu( HWND hWindow );

LRESULT CALLBACK MainWindowProcedure( HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam );