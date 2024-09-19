#ifndef sdds_STATION_H
#define sdds_STATION_H
#include <string>
namespace sdds
{
	class Station
	{
		size_t m_id;
		std::string m_name;
		std::string m_description;
		size_t m_serial;
		size_t m_qty;
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !sdds_STATION_H
