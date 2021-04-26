#pragma once

#include <array>

#include "menu_item.h"


namespace WindowData
{
   constexpr size_t initialWidth = 600;
   constexpr size_t initialHeight = 600;

   constexpr size_t minHeight = 300;
   constexpr size_t minWidth = 300;
}

namespace MenuData
{
   constexpr MenuItem saveButton{ 222, L"Save...", 0 };

   constexpr std::array<MenuItem, 8> thicknessItems =
   {
      MenuItem{ 223, L"1", 1 },
      MenuItem{ 224, L"2", 2 },
      MenuItem{ 225, L"3", 3 },
      MenuItem{ 226, L"5", 5 },
      MenuItem{ 227, L"8", 8 },
      MenuItem{ 228, L"13", 13 },
      MenuItem{ 229, L"21", 21 },
      MenuItem{ 230, L"34", 34 }
   };

   constexpr std::array<MenuItem, 3> toolItems =
   {
      MenuItem{ 231, L"Pencil", 0 },
      MenuItem{ 232, L"Line", 1 },
      MenuItem{ 233, L"Ellipse", 2 }
   };

   constexpr MenuItem colorSelectionButton{ 234, L"Color", 0 };
   constexpr MenuItem thicknessSelectionButton{ 235, L"Thickness", 0 };
   constexpr MenuItem modeSelectionButton{ 236, L"Mode", 0 };
}
