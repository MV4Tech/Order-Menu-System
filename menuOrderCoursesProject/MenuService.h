#pragma once
#include <DBManager.h>
#include <vector>
#include <string>
#include <tabulate.hpp>
class MenuService
{
public:
	// constructor 1
	MenuService(int menuIDC, std::string addedByC, std::string menuC, int votesC);

	// constructor 2
	MenuService(std::string menu);

	//constructor 3
	MenuService();
	
	// add menu
	void addMenu(std::string menu, std::string addedBy);

	// remove menu
	void removeMenu(int menuID);

	// show all menus
	void showMenu();

	//get method
	int getMenuID();
	std::string getMenu();

	// getAdded By
	std::string getAddedBy();
	
	//Overridding method
	friend std::ostream& operator<< (std::ostream& out, MenuService const& data);

	// changeVotePole
	void changeVotePole(int menuID);

	//print only menu
	std::string printMenu(int menuID);

	// minus one vote
	void minusOneVote(int menuID);

	//return number of menus
	int numberOfMenus();


private:
	DBManager _dbManager;
	int menuID{};
	std::string menu;
	std::string addedBy;
	int votes{};
};

	