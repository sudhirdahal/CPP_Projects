
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

