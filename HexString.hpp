/******************************************************************************
 * @ingroup   Utilities
 * @file      Utilities/HexString.hpp
 * @author    Anton Tkachenko
 * @brief     Class for neat parsing lines of HEX, MOT and TI TXT files
 * @date      2022/02/05
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_Utilities
 *****************************************************************************/

#if !defined(COMMONTOOLS_UTILITIES_HEXSTRING_HPP_)
#define UTILITIES_HEXSTRING_HPP_

#include <string>
#include "Utilities/Numeric.hpp"

namespace utils {

  constexpr int cBitsInNibble = 4;
  constexpr int cNibblesInByte = 2;

  class HexLine {
  public:
    // TODO: implement copy and move constructors
    HexLine() = delete;
    HexLine(const HexLine&) = delete;
    HexLine(const HexLine&&) = delete;
    HexLine(const std::string &data) : data(data), ptr(0), length(data.length()) { }

    inline size_t getLength() const { return this->length; }
    inline size_t getProcessed() const { return this->ptr; }
    inline size_t getLeft() const { return this->getLength() - this->getProcessed(); }
    inline size_t isProcessed() const { return this->getLeft() == 0; }

    void set(const std::string &str) {
      this->data = std::string(str);
      this->ptr = 0;
      this->length = this->data.length();
    }

    bool inline skipWhitespaces() {
      while (!this->isProcessed()) {
        if (!this->isWhitespace()) return true;
        if (!this->skipChar()) return false;
      }
      return false;
    }

    // check that next char is corresponding
    inline bool expect(const int ch) {
      int theChar;
      if (!this->getChar(theChar)) return false;
      return (ch == theChar);
    }

    // check that next substring is corresponding
    inline bool expect(const std::string &str) {
      for (const auto &it : str) if(!this->expect(it)) return false;
      return true;
    }

    // get single Hex digit
    bool inline getHexDigit(int &ch) {
      if (!this->getChar(ch)) return false;
      ch = utils::numeric::getDigit(ch);
      return (ch >= 0);
    }

    // get Hex integer of specified type
    // works fine with unsigned; could be issues with signed.
    template <typename T>
    bool inline getHex(T &value) {
      for (size_t i = 0; i < (sizeof(T) * cNibblesInByte); ++i) {
        int digit;
        if (!this->getHexDigit(digit)) return false;
        value <<= cBitsInNibble;
        value |= digit;
      }
      return true;
    }

  protected:
    std::string data;
    size_t ptr;
    size_t length;

    bool inline getChar(int &ch) {
      if (this->isProcessed()) return false;
      ch = this->data[this->ptr++];
      return true;
    }

    bool inline isWhitespace(void) {
      const int ch = this->checkChar_unsafe();
      return (ch == ' ') || (ch == '\t');
    }

    int inline checkChar_unsafe(void) {
      return this->data[this->ptr];
    }

    bool inline skipChar(void) {
      ++this->ptr;
      return (!this->isProcessed());
    }

  private:
  };

}

#endif // UTILITIES_HEXSTRING_HPP_
