
#include <utility>
#include <algorithm>
#include "Workstation.h"

Workstation::Workstation(const std::string& record): Station(record){
	this->m_pNextStation = nullptr;
}

void Workstation::runProcess(std::ostream& os){
	if(this->m_orders.size() > 0u)
		m_orders.front().fillItem(*this, os);
}

bool Workstation::moveOrder(){
	if(m_orders.size() == 0)
		return false;
	else{
		if(m_orders.front().isItemFilled(this->getItemName())){
			if(m_pNextStation){
				*this->m_pNextStation += std::move(m_orders.front());
				m_orders.pop_front();
			}
				
			return true;
		} else
			return false;
	}
}

void Workstation::setNextStation(Station& station){
	this->m_pNextStation = dynamic_cast<Workstation*>(&station);
}

const Workstation* Workstation::getNextStation() const{
	return this->m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order){
	if(this->m_orders.size() == 0)
		return false;
	else {
		if(this->m_orders[0].isOrderFilled()){
			order = std::move(m_orders[0]);
			m_orders.pop_front();
			return true;
		} else
			return false;
	}
}

void Workstation::display(std::ostream& os)const{
	if(this->getNextStation())
		os << this->getItemName() << " --> " << m_pNextStation->getItemName();
	else
		os << this->getItemName() << " --> " << "END OF LINE";
	os << std::endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& other){
	this->m_orders.push_back(std::move(other));
	return *this;
}

