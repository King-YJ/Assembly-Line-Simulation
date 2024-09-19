#ifndef sdds_CUSTOMERORDER_H
#define sdds_CUSTOMERORDER_H
#include <string>
#include "Station.h"
namespace sdds
{
	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};
		std::string m_name;
		std::string m_product;
		size_t m_cntItem = 0;
		Item** m_lstItem = nullptr;
		static size_t m_widthField;
	public:
		CustomerOrder() {};
		CustomerOrder(const std::string& str);
		CustomerOrder(CustomerOrder& co);
		CustomerOrder(CustomerOrder&& co) noexcept;
		CustomerOrder& operator=(CustomerOrder&& co) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !sdds_CUSTOMERORDER_H
