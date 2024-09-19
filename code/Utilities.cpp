#include <string>
#include <exception>
#include <stdexcept>
#include "Utilities.h"

using namespace std;
namespace sdds
{
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        size_t position = str.find(getDelimiter(), next_pos);

        if (next_pos >= str.length())
        {
            more = false;
            return {};
        }

        if (position == next_pos)
        {
            more = false;
            throw std::string("Failed to find the delimiter");
        }

        if (position == std::string::npos)
        {
            position = str.length();
            more = false;
        }
        else
        {
            more = true;
        }

        std::string token = str.substr(next_pos, position - next_pos);
        token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
        token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
        next_pos = position + 1;

        if (m_widthField < token.length())
        {
            setFieldWidth(token.length());
        }

        return token;
    }
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
    char Utilities::m_delimiter = '|';
}