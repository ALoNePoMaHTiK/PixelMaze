#pragma once
#ifndef CONFIG_LOADER_H

#define CONFIG_LOADER_H

#include <fstream>
#include <string>

using namespace std;

enum ColorStyle {STANDART, BLUE, RED, GREEN};

//Получение из файла конфигурации значение высоты лабиринта	[8-60]
int getMazeHeight();

//Получение из файла конфигурации значение ширины лабиринта	[8-60]
int getMazeWidth();

//Получение из файла конфигурации значение размера клетки	[1-60]
int getCellSize();

//Получение из файла конфигурации значение ширины стены		[1-60]
int getWallWidth();

//Получение из файла конфигурации значение цветового стиля	[STANDART,BLUE,RED,GREEN]
int getColorStyle();

#endif // !CONFIG_LOADER_H