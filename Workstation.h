
#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include <string>
#include "Station.h"
#include "CustomerOrder.h"

class Workstation: public Station{
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation{};
public:
	Workstation(const std::string& record);
	Workstation(const Workstation&) = delete;
	Workstation& operator = (const Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator = (Workstation&&) = delete;
	void runProcess(std::ostream&);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream&)const;
	Workstation& operator+=(CustomerOrder&&);
};

#endif
