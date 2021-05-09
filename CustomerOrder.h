/*
					Milestone3	
Name: Sudhir Dahal				ID#: 144417193
Email:sdahal5@myseneca.ca		Date: November 22, 2020

I confirm that I am the only author of this file and the content was created entirely by me.
*/

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"

struct Item{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;

	Item(const std::string& src): m_itemName(src){
	};
};

class CustomerOrder{
	std::string m_name{};
	std::string m_product{};
	unsigned int m_cntItem{};
	Item** m_lstItem{};
public:
	static size_t m_widthField;
	CustomerOrder(){};
	CustomerOrder(std::string& record);
	CustomerOrder(const CustomerOrder& other);
	CustomerOrder& operator = (const CustomerOrder& other) = delete;
	CustomerOrder(CustomerOrder&& other) noexcept;
	CustomerOrder& operator = (CustomerOrder&& other) noexcept;
	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
	~CustomerOrder();
};

#endif
