/******************************************************************************
 * @ingroup   Utilities
 * @file      Utilities/HexString.cpp
 * @author    Anton Tkachenko
 * @brief     Class for neat parsing lines of HEX, MOT and TI TXT files
 * @date      2022/05/07
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_Utilities
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "StringList.hpp"

static const char sLineEndings[2] = { '\r', '\n' };

bool utils::strings::StringList::loadFromFile(const std::string &filename)
{
  this->clear();
  return this->appendFromFile(filename);
}

bool utils::strings::StringList::appendFromFile(const std::string &filename)
{
  std::ifstream in(filename, std::ios_base::in);
  if(in.fail()) return false;

  std::string str;
  while (std::getline(in, str)) *this += str;

  this->cleanup();
  return true;
}

bool utils::strings::StringList::saveToFile(const std::string &filename)
{
  std::ofstream out(filename, std::ios_base::out | std::ios_base::binary);
  if (out.fail()) return false;

  const size_t szEndLine = (this->eLineEndings == utils::strings::LineEnding::crlf) ? (2) : (1);
  const char* const pEndLine = &(sLineEndings[(this->eLineEndings == utils::strings::LineEnding::lf) ? (1) : (0)]);

  for (auto const &it : *this) {
    out.write(it.c_str(), it.length());
    if (out.fail()) return false;
    out.write(pEndLine, szEndLine);
    if (out.fail()) return false;
  }

  return true;
}

/******************************************************************************
 * End-of-File Utilities/StringList.cpp
 *****************************************************************************/
