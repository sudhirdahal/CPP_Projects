/*
					Milestone3
Name: Sudhir Dahal				ID#: 144417193
Email:sdahal5@myseneca.ca		Date: November 22, 2020

I confirm that I am the only author of this file and the content was created entirely by me.
*/

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <string>
#include"Workstation.h"

class LineManager{
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
	Workstation* findStart()const;
public:
	LineManager(const std::string& filename, std::vector<Workstation*>& wstation, std::vector<CustomerOrder>& corder);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif