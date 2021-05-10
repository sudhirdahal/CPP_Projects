
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(const std::string& filename, std::vector<Workstation*>& wstation, std::vector<CustomerOrder>& corder){

	AssemblyLine = wstation;
	for (auto i = 0u; i < corder.size(); i++)
		this->ToBeFilled.push_back(std::move(corder[i])); 

	m_cntCustomerOrder = ToBeFilled.size();

	std::string record;
	std::ifstream file(filename);
	bool more = true;
	Utilities utils;
	while(std::getline(file, record)){
		size_t pos = 0u;
		std::string station = utils.extractToken(record, pos, more);
		std::string nxtStation{};
		if((pos = record.find(utils.getDelimiter())) != std::string::npos)
			nxtStation = utils.extractToken(record, ++pos, more);			

		auto itr = std::find_if(AssemblyLine.begin(), AssemblyLine.end(), [station] (Workstation* it){
			if(it->getItemName() == station)
				return true;
			else return false; });

		auto it = std::find_if(AssemblyLine.begin(), AssemblyLine.end(), [nxtStation] (Workstation* it){
			if(it->getItemName() == nxtStation)
				return true;
			else return false; });
		if(itr != AssemblyLine.end() && it != AssemblyLine.end())
			(*itr)->setNextStation(**it);   
	}
	file.close();
}


bool LineManager::run(std::ostream& os){
	static size_t count;
	os << "Line Manager Iteration: " << ++count << std::endl;
	Workstation* assemblyStart = this->findStart();
	if(ToBeFilled.size() > 0){
		*assemblyStart += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}
	for(auto i = 0u; i < AssemblyLine.size(); i++)
		AssemblyLine[i]->runProcess(os);
	for(auto i = 0u; i < AssemblyLine.size(); i++){
		if(AssemblyLine[i]->getNextStation())
			AssemblyLine[i]->moveOrder();
		CustomerOrder done;
		if(AssemblyLine[i]->getIfCompleted(done)){
			Completed.push_back(std::move(done));
		}
	}
	return m_cntCustomerOrder == Completed.size();
	return true;
}

Workstation* LineManager::findStart()const{
	bool done = false;
	bool found = false;
	size_t i = 0u;
	for(; i < AssemblyLine.size() && !done; i++){
		for(auto j = 0u; j < AssemblyLine.size() && !found; j++){
			if(!AssemblyLine[j]->getNextStation());
			else if(AssemblyLine[i]->getItemName() == AssemblyLine[j]->getNextStation()->getItemName())
				found = true;
		}
		if(!found)
			done = true;
		else
			found = false;
	}
	return AssemblyLine[i - 1];
}	
	
void LineManager::displayCompletedOrders(std::ostream& os) const{
	for(auto& item : Completed)
		item.display(os);
}

void LineManager::displayStations() const{
	for(auto& item : AssemblyLine)
		item->display(std::cout);
}

void LineManager::displayStationsSorted() const{
	const Workstation* theStation = this->findStart();
	std::vector<const Workstation*> list(AssemblyLine.size());
	list[0] = theStation;
	for(auto i = 1u; i < AssemblyLine.size(); i++)
		list[i] = list[i - 1]->getNextStation();
	for(auto& item : list)
		item->display(std::cout);
}

