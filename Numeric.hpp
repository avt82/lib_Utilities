/******************************************************************************
 * @ingroup   Utilities
 * @file      Utilities/Numeric.hpp
 * @author    Anton Tkachenko
 * @brief     Utilities - String/Numeric manipulation
 * @date      2022/06/12
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_Utilities
 *****************************************************************************/

#if !defined(COMMONTOOLS_CMDLINE_UTILS_HPP_)
#define COMMONTOOLS_CMDLINE_UTILS_HPP_

#include <string>

namespace utils {

  namespace numeric {

    constexpr int cUpperCaseBit = 0x20;

    constexpr int getDigit(int ch) {
      if((ch >= '0') && (ch <= '9')) return (ch - '0');
      ch |= cUpperCaseBit;
      if((ch >= 'a') && (ch <= 'f')) return (ch + 10 - 'a');
      return -1;
    }

    constexpr int getDigit(const int ch, const int base) {
      const int ret = getDigit(ch);
      if(ret > base) return -1;
      return ret;
    }

//    bool updateChar(int &ch, const int min, const int max, const int diff) {
//      if ((ch >= min) && (ch <= max)) {
//        ch -= min;
//        ch += diff;
//        return true;
//      }
//      return false;
//    }

    // TODO: not yet working - required by CmdLine/Parsers/IntParser.hpp
    template<typename T>
    bool stringToInt(const std::string &str, T &val) {
      if(str.length() == 0) return false;
      unsigned char base = 10;
      T res = 0;
      if((str.rfind("0x", 0) == 0)  { base = 0x10; }
    }

  }

}

#endif // COMMONTOOLS_CMDLINE_UTILS_HPP_
