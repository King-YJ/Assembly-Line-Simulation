#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;
namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities temp;
		bool more = false;
		size_t pos = 0u;
		//If the string str is empty ---> set to empty state
		if (str.empty())
		{
			m_name = "";
			m_product = "";
			m_cntItem = 0;
			m_lstItem = nullptr;
		}
		else
		{
			//Otherwise, the m_name is extracted from the string str
			m_name = temp.extractToken(str, pos, more);
			if (more)
			{
				m_product = temp.extractToken(str, pos, more);
			}
			std::string newItems = str.substr(pos, str.length() - pos);
			m_cntItem = (count(newItems.begin(), newItems.end(), temp.getDelimiter())) + 1;
			//DMA for the list of Items
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0u; i < m_cntItem && more; i++)
				m_lstItem[i] = new Item(temp.extractToken(str, pos, more));  //DMA
			if (m_widthField < temp.getFieldWidth())
				m_widthField = temp.getFieldWidth();
		}
	}
	
	CustomerOrder::CustomerOrder(CustomerOrder& co)
	{
		throw string("No copy allowed");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept
	{
		*this = move(co);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept
	{
		if (this != &co)
		{
			for (auto i = 0u; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = co.m_name;
			m_product = co.m_product;
			m_widthField = co.m_widthField;
			m_cntItem = co.m_cntItem;
			m_lstItem = co.m_lstItem;
			co.m_name = {};
			co.m_product = {};
			co.m_cntItem = 0;
			co.m_lstItem = nullptr;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		for (auto i = 0u; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				filled = false;
			}
		}
		return filled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (!m_lstItem[i]->m_isFilled)
				{
					filled = false;
				}
			}
		}
		return filled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool filled = false;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == filled && m_lstItem[i]->m_itemName == station.getItemName()) {

				if (station.getQuantity() >= 1) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << std::setw(11) << std::right;
					os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					filled = true;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << '[' << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] " << setfill(' ') << setw(m_widthField)
				<< left << m_lstItem[i]->m_itemName << right << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}
}
