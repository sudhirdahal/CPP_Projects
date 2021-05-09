/*
					Milestone3	
Name: Sudhir Dahal				ID#: 144417193
Email:sdahal5@myseneca.ca		Date: November 22, 2020

I confirm that I am the only author of this file and the content was created entirely by me.
*/

#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>

class Station{
	size_t m_id;
	std::string m_itemName;
	std::string m_desc;
	unsigned m_serialNumber;
	unsigned m_stockQty;
public:
	static size_t m_widthField;
	static size_t id_generator;
	Station(const std::string&);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
	virtual ~Station();
};

#endif

