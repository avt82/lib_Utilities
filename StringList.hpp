/******************************************************************************
 * @ingroup   Utilities
 * @file      Utilities/HexString.hpp
 * @author    Anton Tkachenko
 * @brief     Class for neat parsing lines of HEX, MOT and TI TXT files
 * @date      2022/05/07
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_Utilities
 *****************************************************************************/

#if !defined(UTILITIES_STRINGLIST_HPP_)
#define UTILITIES_STRINGLIST_HPP_

#include <vector>
#include <string>

namespace utils {

  namespace strings {

    enum class LineEnding { lf, crlf, cr };
    enum class TabPolicy { use, replace, indent, ignore };

    class StringList {

    public:
      // TBD: do I need copy/move constructors?
      StringList(const StringList&) = delete;
      StringList(const StringList&&) = delete;
      // Constructor
      StringList() : bSkipEmptyLines(false), eLineEndings(LineEnding::lf), eTabPolicy(TabPolicy::ignore), iIndent(4) {};

      typedef std::vector<std::string>::iterator iterator;
      typedef std::vector<std::string>::const_iterator const_iterator;

      bool getOption_skipEmptyLines() const { return this->bSkipEmptyLines; }
      void setOption_skipEmptyLines(const bool bSkipEmptyLines) { this->bSkipEmptyLines = bSkipEmptyLines; }

      LineEnding getOption_lineEndings() const { return this->eLineEndings; }
      void setOption_lineEndings(const LineEnding eLineEndings) { this->eLineEndings = eLineEndings; }

      TabPolicy getOption_tabPolicy() const { return this->eTabPolicy; }
      size_t getOption_tabIndent() const { return this->iIndent; }
      void setOption_tabPolicy(const TabPolicy eTabPolicy, const size_t iIndent = 4) { this->eTabPolicy = eTabPolicy; this->iIndent = iIndent; }

      bool loadFromFile(const std::string &filename);
      bool appendFromFile(const std::string &filename);
      bool saveToFile(const std::string &filename);

      std::vector<std::string> &getRawData() { return this->list; }

      inline void clear() { this->list.clear(); }
      inline size_t size() const { return this->list.size(); }

      inline std::string &operator[](const size_t index) { return this->list[index]; }
      inline const std::string &operator[](const size_t index) const { return this->list[index]; }
      inline StringList &operator+=(const int ch) { this->addChar(ch); return *this; }
      inline StringList &operator+=(const std::string &str) { for (const auto &it : str) this->addChar(it); this->addString(); return *this; }
      inline StringList &operator++() { this->addString(); return *this; }

      inline StringList::iterator begin() { return this->list.begin(); }
      inline StringList::iterator end() { return this->list.end(); }
      inline StringList::const_iterator cbegin() const { return this->list.cbegin(); }
      inline StringList::const_iterator cend() const { return this->list.cend(); }

      void cleanup() {
        if ((this->list.size() > 0) && (this->getLastStringRef().size() == 0)) this->list.pop_back();
      }

    protected:
      std::vector<std::string> list;
      bool bSkipEmptyLines;
      LineEnding eLineEndings;
      TabPolicy eTabPolicy;
      size_t iIndent;

      void addChar(const int ch) {
        if (ch == '\n') this->addString();
        if (ch == '\t') this->addTab();
        if (ch >= ' ') this->getLastStringRef() += ch;
      }

      void addNChar(const int ch, const size_t count) {
        std::string &str = this->getLastStringRef();
        for (size_t i = 0; i < this->iIndent; i++) str += ch;
      }

      void addToNChar(const int ch, const size_t count) {
        std::string &str = this->getLastStringRef();
        while(str.length() < count) str += ch;
      }

      void addTab(void) {
        switch (this->eTabPolicy) {

        case TabPolicy::use:
          this->getLastStringRef() += '\t';
          break;

        case TabPolicy::replace:
          this->addNChar(' ', this->iIndent);
          break;

        case TabPolicy::indent:
          if (this->iIndent > 0) {
            std::string &str = this->getLastStringRef();
            const size_t count = ((str.length() + this->iIndent) / this->iIndent) * this->iIndent;
            this->addToNChar(' ', count);
          }
          break;

        // same for ::ignore
        default:
          break;
        }
      }

      std::string &getLastStringRef()
      {
        if (this->list.size() == 0) this->addString();
        return this->list[this->list.size() - 1];
      }

      void addString(void) {
        if ((this->bSkipEmptyLines) && (this->list.size() > 0) && (this->getLastStringRef().length() == 0)) return;
        this->list.push_back("");
      }

    private:

    };

  }
}

#endif // UTILITIES_STRINGLIST_HPP_
