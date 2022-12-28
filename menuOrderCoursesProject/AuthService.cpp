#include "AuthService.h"
#include <json.hpp>
#include "DBManager.h"
#include<iostream>
#include <tabulate.hpp>



std::string AuthService::getMenu()
{
	return menu;
}

void AuthService::reservationStatus(int id)
{
	nlohmann::json userJSON;

	// Get the JSON from the file
	try
	{
		userJSON = _dbManager.getJSONFromFile("users.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open users.json file");
	}

	// Check if json is []
	if (userJSON.is_array())
	{
		if (userJSON.empty())
		{
			userJSON = nullptr;
		}
	}

	for (auto it = userJSON.begin(); it != userJSON.end(); ++it)
	{
		if (it.value()["ID"] == id)
		{
			int status = 1;

			it.value()["ReservationMade"] = status;


			if (!_dbManager.setJSONFile(userJSON, "users.json"))
			{
				throw ("Could'n open users.json file");
			}

			return;
		}

	}


	throw std::string("Could'n open users.json file");




	
}

int AuthService::statusOfReservation(int id)
{

	// vector with all menus
	std::vector<AuthService> vec;
	nlohmann::json userJSON;
	// Get the JSON from the file
	try
	{
		userJSON = _dbManager.getJSONFromFile("users.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open users.json file");
	}

	// Iterate over JSONFile
	for (auto it = userJSON.begin(); it != userJSON.end(); ++it) {
		if (it.value()["ID"] == id) {
			int stat = it.value()["ReservationMade"];
			AuthService as(stat);
			vec.push_back(as);
		}

	}



	//print all menus and ID 
	return vec[0].getReservationMade();
}

int AuthService::getReservationMade()
{
	return reservationMade;
}

void AuthService::setReservationStatusToZero()
{
	nlohmann::json userJSON;

	// Get the JSON from the file
	try
	{
		userJSON = _dbManager.getJSONFromFile("users.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open users.json file");
	}

	// Check if json is []
	if (userJSON.is_array())
	{
		if (userJSON.empty())
		{
			userJSON = nullptr;
		}
	}

	for (auto it = userJSON.begin(); it != userJSON.end(); ++it)
	{
		if (it.value()["ReservationMade"] == 1)
		{
			int status = 0;

			it.value()["ReservationMade"] = status;


			if (!_dbManager.setJSONFile(userJSON, "users.json"))
			{
				throw ("Could'n open users.json file");
			}

			return;
		}

	}


	throw std::string("Could'n open users.json file");



}

void AuthService::printAllStudents()
{
	// vector with all menus
	std::vector<Response> vec;
	nlohmann::json userJSON;
	// Get the JSON from the file
	try
	{
		userJSON = _dbManager.getJSONFromFile("users.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open users.json file");
	}

	// Iterate over JSONFile
	for (auto it = userJSON.begin(); it != userJSON.end(); ++it) {
		vec.push_back({ it.value()["Username"], it.value()["Role"], it.value()["ID"] });
	}



	//print all menus and ID 
	for (Response i : vec) {
		std::cout << i << std::endl;
	}


}


Response AuthService::login(std::string username, std::string password)
{
	nlohmann::json userJSON;

	try
	{
		userJSON = _dbManager.getJSONFromFile("users.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open user.json file");
	}

	for (auto it = userJSON.begin(); it != userJSON.end(); ++it)
	{
		// Authtenticate user
		if (it.value()["Username"] == username && password == it.value()["Password"])
		{
			return {
				username,it.value()["Role"], it.value()["ID"]
			};
		}
	}

	// Login failure
	throw std::string("There is not a user with this username: " + username + " or password is invalid.");
}

AuthService::AuthService(std::string menuC)
{
	menu = menuC;
}

AuthService::AuthService(int reservationMadeC)
{
	reservationMade = reservationMadeC;
}

AuthService::AuthService()
{

}

void AuthService::createAccount(std::string username, std::string password, int role)
{
	nlohmann::json userJSON;
	//std::string menu;
	// Get the JSON from the file
	try
	{
		userJSON = _dbManager.getJSONFromFile("users.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open user.json file");
	}

	// Check for duplicate username
	if (_dbManager.checkIfValueExistsInField(userJSON, "Username", username))
	{
		throw std::string("There is already a user with this username: " + username);
	}

	// Check if json is []
	if (userJSON.is_array())
	{
		if (userJSON.empty())
		{
			userJSON = nullptr;
		}
	}

	// Add the user to the JSON
	
	userJSON.push_back(
		{
		{ "ID", _dbManager.getLastId(userJSON) + 1},
		{ "Username", username },
		{ "Password", password },
		{ "Role", role },
		{"Menu", "//"},
		{"ReservationMade", 0}
		}
	);

	// Save the json to the file
	if (!_dbManager.setJSONFile(userJSON, "users.json"))
	{
		throw std::string("Could'n open user.json file");
	}
}



void AuthService::updateMenu(int id, std::string menu)
{
	nlohmann::json userJSON;

	// Get the JSON from the file
	try
	{
		userJSON = _dbManager.getJSONFromFile("users.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open users.json file");
	}

	// Check if json is []
	if (userJSON.is_array())
	{
		if (userJSON.empty())
		{
			userJSON = nullptr;
		}
	}

	for (auto it = userJSON.begin(); it != userJSON.end(); ++it)
	{
		if (it.value()["ID"] == id)
		{
			std::string menu1 = menu;

			it.value()["Menu"] = menu1;


			if (!_dbManager.setJSONFile(userJSON, "users.json"))
			{
				throw ("Could'n open users.json file");
			}

			return;
		}

	}


	throw std::string("Could'n open users.json file");




}



std::string AuthService::printMenu(int id)
{
	// vector with all menus
	std::vector<AuthService> vec;
	nlohmann::json userJSON;
	// Get the JSON from the file
	try
	{
		userJSON = _dbManager.getJSONFromFile("users.json");
	}
	catch (std::string ex)
	{
		throw std::string("Could'n open users.json file");
	}

	// Iterate over JSONFile
	for (auto it = userJSON.begin(); it != userJSON.end(); ++it) {
		if (it.value()["ID"] == id) {
			std::string asd = it.value()["Menu"];
			AuthService as(asd);
			vec.push_back(as);
		}

	}



	//print all menus and ID 
	return vec[0].getMenu();


}


