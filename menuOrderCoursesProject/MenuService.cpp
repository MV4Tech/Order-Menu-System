#include "MenuService.h"
#include <iostream>
#include <tabulate.hpp>

// contstructor 1
MenuService::MenuService(int menuIDC, std::string addedByC, std::string menuC, int votesC)
{
	menuID = menuIDC;
	menu = menuC;
	addedBy = addedByC;
	votes = votesC;
}

MenuService::MenuService(std::string menuC)
{
	menu = menuC;
}


// constructor 2
MenuService::MenuService()
{

}


// add menu
void MenuService::addMenu(std::string menu, std::string addedBy)
{
	nlohmann::json menuJSON;

	// Get the JSON from the file
	try
	{
		menuJSON = _dbManager.getJSONFromFile("menu.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open menu.json file");
	}

	// Check for duplicate menu
	if (_dbManager.checkIfValueExistsInField(menuJSON, "Menu", menu))
	{
		throw std::string("This menu already exist in menues: " + menu);
	}

	// Check if json is []
	if (menuJSON.is_array())
	{
		if (menuJSON.empty())
		{
			menuJSON = nullptr;
		}
	}

	// Add the user to the JSON
	menuJSON.push_back(
		{
		{ "ID", _dbManager.getLastId(menuJSON) + 1},
		{ "Menu", menu},
		{"Added By", addedBy},
		{"Votes", 0}
		}
	);

	// Save the json to the file
	if (!_dbManager.setJSONFile(menuJSON, "menu.json"))
	{
		throw std::string("Could'n open menu.json file");
	}


}


// remove menu
void MenuService::removeMenu(int menuID)
{
	nlohmann::json menuJSON;

	// Get the JSON from the file
	try
	{
		menuJSON = _dbManager.getJSONFromFile("menu.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open menu.json file");
	}

	// Check if json is []
	if (menuJSON.is_array())
	{
		if (menuJSON.empty())
		{
			menuJSON = nullptr;
		}
	}

	// Remove menu
	auto it = menuJSON.cbegin();
	for (; it != menuJSON.cend();)
	{
		if (it.value()["ID"] == menuID)
		{
			it = menuJSON.erase(it);

			if (!_dbManager.setJSONFile(menuJSON, "menu.json"))
			{
				throw ("Could'n open menu.json file");
			}

			return;
		}
		else
		{
			++it;
		}
	}


	throw std::string("Could'n open menu.json file");
}


// show all menus
void MenuService::showMenu()
{
	
	// vector with all menus
	std::vector<MenuService> allMenusVector;

	nlohmann::json menuJSON;
	// Get the JSON from the file
	try
	{
		menuJSON = _dbManager.getJSONFromFile("menu.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open menu.json file");
	}

	// Iterate over JSONFile
	for (auto it = menuJSON.begin(); it != menuJSON.end(); ++it) {
		allMenusVector.push_back({ it.value()["ID"], it.value()["Added By"], it.value()["Menu"], it.value()["Votes"]});
	}



	//print all menus and ID 
	for (MenuService i : allMenusVector) {
		std::cout << i;
	}
	
	
}


// get menu id
int MenuService::getMenuID()
{
	return menuID;
	
}

// get menu 
std::string MenuService::getMenu()
{
	return menu;
}

// get Added by method
std::string MenuService::getAddedBy()
{
	return addedBy;
}

// CHANGE VOTE POLE
void MenuService::changeVotePole(int menuID)
{
	nlohmann::json menuJSON;

	// Get the JSON from the file
	try
	{
		menuJSON = _dbManager.getJSONFromFile("menu.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open menu.json file");
	}

	// Check if json is []
	if (menuJSON.is_array())
	{
		if (menuJSON.empty())
		{
			menuJSON = nullptr;
		}
	}

	for (auto it = menuJSON.begin(); it != menuJSON.end(); ++it)
	{
		if (it.value()["ID"] == menuID)
		{
			int vote = it.value()["Votes"];

			it.value()["Votes"] = vote+1;
		

			if (!_dbManager.setJSONFile(menuJSON, "menu.json"))
			{
				throw ("Could'n open menu.json file");
			}

			return;
		}
	
	}


	throw std::string("Could'n open menu.json file");


}


std::string MenuService::printMenu(int menuID)
{
	// vector with all menus
	std::vector<MenuService> vec;
	nlohmann::json menuJSON;
	// Get the JSON from the file
	try
	{
		menuJSON = _dbManager.getJSONFromFile("menu.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open menu.json file");
	}
	
	// Iterate over JSONFile
	for (auto it = menuJSON.begin(); it != menuJSON.end(); ++it) {
		if (it.value()["ID"] == menuID) {
			std::string asd = it.value()["Menu"];
			MenuService m(asd);
			vec.push_back(m);
		}

	}

	//print all menus and ID 
	return vec[0].getMenu();

}

// minus one vote for changing reservation
void MenuService::minusOneVote(int menuID)
{
	nlohmann::json menuJSON;

	// Get the JSON from the file
	try
	{
		menuJSON = _dbManager.getJSONFromFile("menu.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open menu.json file");
	}

	// Check if json is []
	if (menuJSON.is_array())
	{
		if (menuJSON.empty())
		{
			menuJSON = nullptr;
		}
	}

	for (auto it = menuJSON.begin(); it != menuJSON.end(); ++it)
	{
		if (it.value()["ID"] == menuID)
		{
			int vote = it.value()["Votes"];

			it.value()["Votes"] = vote - 1;


			if (!_dbManager.setJSONFile(menuJSON, "menu.json"))
			{
				throw ("Could'n open menu.json file");
			}

			return;
		}

	}


	throw std::string("Could'n open menu.json file");


}




int MenuService::numberOfMenus()
{
	nlohmann::json menuJSON;

	// Get the JSON from the file
	try
	{
		menuJSON = _dbManager.getJSONFromFile("menu.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open menu.json file");
	}

	// Check if json is []
	if (menuJSON.is_array())
	{
		if (menuJSON.empty())
		{
			menuJSON = nullptr;
		}
	}
	int numberOfMenu;
	numberOfMenu = 0;
	for (auto it = menuJSON.begin(); it != menuJSON.end(); ++it)
	{
		numberOfMenu = it.value()["ID"];
	}

	
	return numberOfMenu;
	//std::cout << numberOfMenu;
}




// override operator cout
std::ostream& operator<<(std::ostream& out, MenuService const& data)
{
	
	std::string votes = std::to_string(data.votes);
	std::string menuID = std::to_string(data.menuID);
	tabulate::Table menuInfo;
	
	menuInfo.add_row({ "Menu","Added By", "Votes", "Menu ID" });
	for (size_t i = 0; i < 4; ++i) {
		menuInfo[0][i].format()
			.font_color(tabulate::Color::green)
			.font_align(tabulate::FontAlign::center)
			.font_style({ tabulate::FontStyle::bold });
	}
	menuInfo.add_row({ data.menu ,data.addedBy, votes, menuID });


	
	out << menuInfo << std::endl;
	/*

	out << data.menu << " " << '/' << " ";
	out << data.addedBy << " " << '/' << " ";
	out << data.votes << " " << '/' << " ";
	out << data.menuID << ';';
	*/
	return out;
}
