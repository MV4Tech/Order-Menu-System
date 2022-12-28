#pragma once
#include <json.hpp>
#include <string>
#include <fstream>

class DBManager
{
public:
	nlohmann::json getJSONFromFile(std::string filename);
	bool checkIfValueExistsInField(nlohmann::json json, std::string field, std::string fieldData);
	int getLastId(nlohmann::json json);
	bool setJSONFile(nlohmann::json json, std::string filename);
};

