#include <iostream>
#include "Station.h"
#include <iomanip>
#include <string>
#include "Utilities.h"
using namespace std;
namespace sdds
{
	Station::Station(const std::string& str)
	{
			Utilities ut;
			size_t next_pos = 0;
			bool more = true;
			m_id = ++id_generator;
			try
			{
				m_name = ut.extractToken(str, next_pos, more);
				m_serial = std::stoi(ut.extractToken(str, next_pos, more));
				m_qty = std::stoi(ut.extractToken(str, next_pos, more));
				if (m_widthField < ut.getFieldWidth())
					m_widthField = ut.getFieldWidth();
				m_description = ut.extractToken(str, next_pos, more);
			}
			catch (const std::runtime_error& e)
			{
				cerr << "Error: " << e.what() << std::endl;
			}
	}
	const std::string& Station::getItemName() const
	{
		return m_name;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serial++;
	}
	size_t Station::getQuantity() const
	{
		return m_qty;
	}
	void Station::updateQuantity()
	{
		if (m_qty > 0)
			m_qty--;
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setw(3) << std::setfill('0') << m_id << " | "
			<< left << std::setw(m_widthField) << std::setfill(' ') << m_name << " | "
			<< right << std::setw(6) << std::setfill('0') << m_serial << " | ";
		if (full)
			os << setw(4) << setfill(' ') << m_qty << " | " << left << m_description << right;
		os << endl;
	}
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
}