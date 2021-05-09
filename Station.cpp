/*
					Milestone3	
Name: Sudhir Dahal				ID#: 144417193
Email:sdahal5@myseneca.ca		Date: November 22, 2020

I confirm that I am the only author of this file and the content was created entirely by me.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <memory>
#include <cstring>
#include "Station.h"
#include "Utilities.h"

size_t Station::m_widthField = 0u;
size_t Station::id_generator = 0u;

Station::Station(const std::string& record){
	id_generator++;
	m_id = id_generator;
	Utilities utility;
	unsigned tracker = 0u;
	size_t pos = 0;
	bool more = true;
	while(more){
		if(tracker == 0u){
			std::string token = utility.extractToken(record, pos, more);
			m_itemName = token;
			tracker++;
			if(token.length() > m_widthField)
				m_widthField = token.length();
		}else if(tracker == 1u){
			pos = record.find(utility.getDelimiter());
			std::string token = utility.extractToken(record, ++pos, more);
			m_serialNumber = stoi(token);
			tracker++;
			if(token.length() > m_widthField)
				m_widthField = token.length();
		} else if(tracker == 2u){
			pos = record.find(utility.getDelimiter(), pos + 1);
			std::string token = utility.extractToken(record, ++pos, more);
			m_stockQty = stoi(token);
			tracker++;
			if(token.length() > m_widthField)
				m_widthField = token.length();
		} else if(tracker == 3u){
			pos = record.find(utility.getDelimiter(), pos + 1);
			m_desc = utility.extractToken(record, ++pos, more);
		}
	}
}

const std::string& Station::getItemName() const{
	return this->m_itemName;
}

unsigned int Station::getNextSerialNumber(){
	return this->m_serialNumber++;
}

unsigned int Station::getQuantity() const{
	return this->m_stockQty;
}

void Station::updateQuantity(){
	if(this->m_stockQty)
		m_stockQty--;
}

void Station::display(std::ostream& os, bool full) const{
	if(full){
		os.fill('0');
		os << "[";
		os.setf(std::ios::right);
		os.width(3);
		os << m_id << "] Item: ";
		os.fill(' ');
		os.unsetf(std::ios::right);
		os.width(m_widthField);
		os.setf(std::ios::left);
		os << m_itemName << " [";
		os.fill('0');
		os.setf(std::ios::right);
		os.width(6);
		os << m_serialNumber << "] Quantity: ";
		os.unsetf(std::ios::right);
		os.fill(' ');
		os.width(m_widthField);
		os << m_stockQty << " Description: " << m_desc << std::endl;
	} else{
		os.fill('0');
		os << "[";
		os.setf(std::ios::right);
		os.width(3);
		os << m_id << "] Item: ";
		os.fill(' ');
		os.unsetf(std::ios::right);
		os.width(m_widthField);
		os.setf(std::ios::left);
		os << m_itemName << " [";
		os.fill('0');
		os.setf(std::ios::right);
		os.width(6);
		os << m_serialNumber << "]" << std::endl;
	}
}

Station::~Station(){}
