#ifndef sdds_UTILITIES_H
#define sdds_UTILITIES_H
#include <string>
namespace sdds
{
	class Utilities
	{
		size_t m_widthField = 1;
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}
#endif // !sdds_UTILITIES_H
