#pragma once
#include <DBManager.h>
#include <string>
#include <tabulate.hpp>

class Response {
public:
	std::string username;
	int role;
	int id;
	friend std::ostream& operator<< (std::ostream& out, const Response& data) {
		tabulate::Table studentInfo;

		std::string temp = std::to_string(data.role);
		std::string temp2 = std::to_string(data.id);

		studentInfo.add_row({ "Username","Role", "ID" });
		for (size_t i = 0; i < 3; ++i) {
			studentInfo[0][i].format()
				.font_color(tabulate::Color::green)
				.font_align(tabulate::FontAlign::center)
				.font_style({ tabulate::FontStyle::bold });
		}
		studentInfo.add_row({ data.username , temp , temp2 });
		out << studentInfo << std::endl;

		return out;


	}
};

class AuthService
{
public:
	AuthService(std::string menu);
	AuthService(int reservationMadeC);
	AuthService();
	Response login(std::string username, std::string password);
	void createAccount(std::string username, std::string password, int role);
	void updateMenu(int id, std::string menu);
	std::string printMenu(int id);
	std::string getMenu();
	void reservationStatus(int id);
	int statusOfReservation(int id);
	int getReservationMade();
	void setReservationStatusToZero();
	void printAllStudents();
	
private:
	DBManager _dbManager;
	std::string menu;
	int reservationMade;
};

