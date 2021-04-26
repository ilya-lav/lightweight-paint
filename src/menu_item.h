#pragma once

#include <string_view>


struct MenuItem
{
   size_t m_id;
   std::wstring_view m_name;
   int m_value;
};