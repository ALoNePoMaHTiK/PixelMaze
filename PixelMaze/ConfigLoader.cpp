#include "ConfigLoader.h"

int getMazeHeight()
{
	fstream file("config.ini", fstream::in);
	if (!file.is_open()) {
		return 10;	//Стандартное значение
	}
	while (!file.eof()) {
		string str;
		file >> str;
		string temp;
		string result;
		for (int i = 0; i < str.size(); i++) {
			temp.push_back(str[i]);
			if (temp == "#MazeHeight=") {
				for (int j = i + 1; j < str.size(); j++)
					result.push_back(str[j]);
				int MazeHeight = atoi(result.c_str());
				return (MazeHeight%61 > 7) ? MazeHeight%61 : 10;
			}
		}
	}
	return 10;
}

int getMazeWidth()
{
	fstream file("config.ini", fstream::in);
	if (!file.is_open()) {
		return 10;	//Стандартное значение
	}
	while (!file.eof()) {
		string str;
		file >> str;
		string temp;
		string result;
		for (int i = 0; i < str.size(); i++) {
			temp.push_back(str[i]);
			if (temp == "#MazeWidth=") {
				for (int j = i + 1; j < str.size(); j++)
					result.push_back(str[j]);
				int MazeWidth = atoi(result.c_str());
				return (MazeWidth%61 > 7) ? MazeWidth%61 : 10;
			}
		}
	}
	return 10;
}

int getCellSize()
{
	fstream file("config.ini", fstream::in);
	if (!file.is_open()) {
		return 10;	//Стандартное значение
	}
	while (!file.eof()) {
		string str;
		file >> str;
		string temp;
		string result;
		for (int i = 0; i < str.size(); i++) {
			temp.push_back(str[i]);
			if (temp == "#CellSize=") {
				for (int j = i + 1; j < str.size(); j++)
					result.push_back(str[j]);
				int CellSize = atoi(result.c_str());
				return (CellSize%61 > 0) ? CellSize%61 : 10;
			}
		}
	}
	return 10;
}

int getWallWidth()
{
	fstream file("config.ini", fstream::in);
	if (!file.is_open()) {
		return 3;	//Стандартное значение
	}
	while (!file.eof()) {
		string str;
		file >> str;
		string temp;
		string result;
		for (int i = 0; i < str.size(); i++) {
			temp.push_back(str[i]);
			if (temp == "#WallWidth=") {
				for (int j = i + 1; j < str.size(); j++)
					result.push_back(str[j]);
				int PathWidth = atoi(result.c_str());
				return (PathWidth%61 > 0) ? PathWidth%61 : 3;
			}
		}
	}
	return 3;
}

int getColorStyle() {
	fstream file("config.ini", fstream::in);
	if (!file.is_open()) {
		return ColorStyle::STANDART;	//Стандартное значение
	}
	while (!file.eof()) {
		string str;
		file >> str;
		string temp;
		string result;
		for (int i = 0; i < str.size(); i++) {
			temp.push_back(str[i]);
			if (temp == "#ColorStyle=") {
				for (int j = i + 1; j < str.size(); j++)
					result.push_back(str[j]);
				if (result == "Blue" || result == "BLUE" || result == "blue")
					return ColorStyle::BLUE;
				else if (result == "Red" || result == "RED" || result == "red")
					return ColorStyle::RED;
				else if (result == "Green" || result == "GREEN" || result == "green")
					return ColorStyle::GREEN;
				else 
					return ColorStyle::STANDART;
			}
		}
	}
	return ColorStyle::STANDART;
}