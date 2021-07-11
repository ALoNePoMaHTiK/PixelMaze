#pragma once
#ifndef CONFIG_LOADER_H

#define CONFIG_LOADER_H

#include <fstream>
#include <string>

using namespace std;

enum ColorStyle {STANDART, BLUE, RED, GREEN};

//��������� �� ����� ������������ �������� ������ ���������	[8-60]
int getMazeHeight();

//��������� �� ����� ������������ �������� ������ ���������	[8-60]
int getMazeWidth();

//��������� �� ����� ������������ �������� ������� ������	[1-60]
int getCellSize();

//��������� �� ����� ������������ �������� ������ �����		[1-60]
int getWallWidth();

//��������� �� ����� ������������ �������� ��������� �����	[STANDART,BLUE,RED,GREEN]
int getColorStyle();

#endif // !CONFIG_LOADER_H