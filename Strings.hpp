/******************************************************************************
 * @ingroup   Utilities
 * @file      Utilities/Strings.hpp
 * @author    Anton Tkachenko
 * @brief     Utilities - String/characters manipulation
 * @date      2022/06/12
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_Utilities
 *****************************************************************************/

#if !defined(COMMONTOOLS_UTILS_STRINGS_HPP_)
#define COMMONTOOLS_UTILS_STRINGS_HPP_

namespace utils {

  namespace strings {

    // helper constants
    constexpr int cUpperCaseBit = 0x20;

    // helper functions - check if [ min <= ch <= max ]
    constexpr bool isBetween(const int ch, const int min, const int max)
    { return (ch >= min) && (ch <= max); }

    // helper functions - check if ch is either one or two
    constexpr bool isOneOfTwo(const int ch, const int one, const int two)
    { return (ch == one) || (ch == two); }

    // some special characters
    constexpr bool isUnderscore(const int ch)     { return (ch == '_'); }
    constexpr bool isSemicolon(const int ch)      { return (ch == ';'); }
    constexpr bool isNumberSign(const int ch)     { return (ch == '#'); }

    // string manipulation routines
    constexpr bool isEscape(const int ch)         { return (ch =='\\'); }
    constexpr bool isSingleQuote(const int ch)    { return (ch =='\''); }
    constexpr bool isDoubleQuote(const int ch)    { return (ch == '"'); }
    constexpr bool isAnyQuote(const int ch)       { return isOneOfTwo(ch,'\'', '"'); }

    // numeric and alphabetical
    constexpr bool isDigit(const int ch)          { return isBetween(ch, '0', '9'); }
    constexpr bool isSmallLetter(const int ch)    { return isBetween(ch, 'a', 'z'); }
    constexpr bool isCapitalLetter(const int ch)  { return isBetween(ch, 'A', 'Z'); }
    constexpr bool isLetter(const int ch)         { return isBetween((ch | cUpperCaseBit), 'A', 'Z'); }
    constexpr bool isAlphaNumeric(const int ch)   { return isLetter(ch) || isDigit(ch); }

    constexpr bool isIdentifier(const int ch)     { return isAlphaNumeric(ch) || isUnderscore(ch); }

    constexpr bool isTab(const int ch)            { return (ch =='\t'); }
    constexpr bool isSpace(const int ch)          { return (ch == ' '); }
    constexpr bool isWhitespace(const int ch)     { return isOneOfTwo(ch,'\t', ' ');  }
    constexpr bool isNewline(const int ch)        { return isOneOfTwo(ch,'\n','\r');  }

    constexpr bool isOpeningBracket(const int ch) { return (ch == '(') || (ch == '[') || (ch == '{'); }

    constexpr int upperCase(int ch) {
      if(isSmallLetter(ch))
        ch &= ~cUpperCaseBit;
      return ch;
    }

    constexpr int lowerCase(int ch) {
      if(isCapitalLetter(ch))
        ch |= cUpperCaseBit;
      return ch;
    }

  }

}

#endif // COMMONTOOLS_UTILS_STRINGS_HPP_
