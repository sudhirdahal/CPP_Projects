/*
					Milestone3	
Name: Sudhir Dahal				ID#: 144417193
Email:sdahal5@myseneca.ca		Date: November 22, 2020

I confirm that I am the only author of this file and the content was created entirely by me.
*/

#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField{};

CustomerOrder::CustomerOrder(std::string& record){
	Utilities utility;
	unsigned tracker = 0u;
	size_t pos = 0;
	bool more = true;

	std::vector<std::string> items;

	while(more){
		if(tracker == 0u){
			std::string token = utility.extractToken(record, pos, more);
			m_name = token;
			tracker++;
			if(token.length() > m_widthField)
				m_widthField = token.length();
		} else if(tracker == 1u){
			pos = record.find(utility.getDelimiter());
			std::string token = utility.extractToken(record, ++pos, more);
			m_product = token;
			tracker++;
			if(token.length() > m_widthField)
				m_widthField = token.length();
		} else {
			pos = record.find(utility.getDelimiter(), pos + 1);
			std::string token = utility.extractToken(record, ++pos, more);
			items.push_back(token);
			m_cntItem++;
			if(token.length() > m_widthField)
				m_widthField = token.length();
		}
	}

	this->m_lstItem = new Item*[m_cntItem];
	for(auto i = 0u; i < m_cntItem; i++){
		this->m_lstItem[i] = new Item(items[i]);
	}
		

	if(m_widthField < utility.getFieldWidth())
		m_widthField = utility.getFieldWidth();
}

CustomerOrder::CustomerOrder(const CustomerOrder& other){
	const char* msg{"error"};
	throw msg;
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept{
	*this = std::move(other);
}

CustomerOrder& CustomerOrder::operator = (CustomerOrder&& other) noexcept{
	if(this != &other){
		for(auto i = 0u; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[] this->m_lstItem;
		this->m_name = other.m_name;
		this->m_product = other.m_product;
		this->m_widthField = other.m_widthField;
		this->m_cntItem = other.m_cntItem;
		this->m_lstItem = other.m_lstItem;
		other.m_lstItem = nullptr;
		other.m_cntItem = 0;
	}
	return *this;
}

bool CustomerOrder::isOrderFilled() const{
	for(auto i = 0u; i < m_cntItem; i++){
		if(!m_lstItem[i]->m_isFilled)
			return false;
	}
	return true;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const{
	auto iter = std::find_if(m_lstItem, m_lstItem + m_cntItem, [itemName] (Item* it)->bool{
		if(it->m_itemName == itemName)
			return true;
		return false;
		});

	if(iter == m_lstItem + m_cntItem){
		return true;
	} else
		return (*iter)->m_isFilled;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os){
	auto iter = std::find_if(m_lstItem, m_lstItem + m_cntItem, [&station] (Item* it)->bool{
		if(it->m_itemName == station.getItemName())
			return true;
		return false;
		});

	auto num = std::count_if(m_lstItem, m_lstItem + m_cntItem, [&station] (Item* it)->bool{
		if(it->m_itemName == station.getItemName())
			return true;
		return false;
		});

	while(num--){
		if(iter != m_lstItem + m_cntItem){
			if((*iter)->m_itemName != station.getItemName()){
				num++;
				iter++;
			}
			else{
				if(station.getQuantity()){
					station.updateQuantity();
					(*iter)->m_serialNumber = station.getNextSerialNumber();
					(*iter)->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << (*iter)->m_itemName << "]\n";
				} else{
					os << "    Unable to fill" << m_name << ", " << m_product << " [" << (*iter)->m_itemName << "]\n";
				}
				iter++;
			}		
		}
	}
}

void CustomerOrder::display(std::ostream& os) const{
	os << m_name << " - " << m_product << "\n";
	for(auto i = 0u; i < m_cntItem; i++){
		os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] ";
		os << std::setfill(' ');
		os << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName << " - ";
		os << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING");
		os << std::endl;
	}	
}

CustomerOrder::~CustomerOrder(){
	for(auto i = 0u; i < m_cntItem; i++)
		delete m_lstItem[i];
	delete[] m_lstItem;
}
