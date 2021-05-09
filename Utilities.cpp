/*
					Milestone3	
Name: Sudhir Dahal				ID#: 144417193
Email:sdahal5@myseneca.ca		Date: November 22, 2020

I confirm that I am the only author of this file and the content was created entirely by me.
*/

#include "Utilities.h"

char Utilities::m_delimiter{};

void Utilities::setDelimiter(char newDelimiter){
	m_delimiter = newDelimiter;
}

char Utilities::getDelimiter(){
	return m_delimiter;
}

void Utilities::setFieldWidth(size_t newWidth){
	this->m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const{
	return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
	int pos1 = str.find(m_delimiter, next_pos);
	std::string token{};
	if(pos1 != -1){
		token = str.substr(next_pos, pos1 - next_pos);
		if(token.length() > this->m_widthField)
			m_widthField = token.length();
	} else{
		more = false;
		token = str.substr(next_pos);
	}
	if(token.length() == 0)
		throw;
	return token;	
}
