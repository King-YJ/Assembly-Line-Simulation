#ifndef sdds_WORKSTATION_H
#define sdds_WORKSTATION_H
#include <iostream>
#include <deque>
#include <ostream>
#include <string>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {

    enum class OrderStatus {
        OrderFilled,
        ItemFilled,
        InsufficientQuantity
    };

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_nextWorkStation = nullptr;

    public:
        Workstation(const std::string&);

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);

        // Copy operations are deleted
        Workstation(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation& operator=(Workstation&&) = delete;


    };
}
#endif // !sdds_WORKSTATION_H