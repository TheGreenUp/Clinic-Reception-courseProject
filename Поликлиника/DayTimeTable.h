#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "FileManager.h"
#include "User.h"
class DayTimeTable
{
private:
	SYSTEMTIME real_date;
	std::vector<std::string> date;
	bool isFree;
public:
	DayTimeTable();
	std::vector<std::string> getDateVector();// ��� ��������� ���������� ������� � ���������� �����������;
	void GetInfoFromFile(std::string nameOfChosenDoctor);// ��� ��������� ������ � ���������� �� �����;
	void BookChosenTime(int chosenDate, std::string doctorName, std::string patientName, std::string problemDescription, std::string& justDate, std::string& spec);// ��� ������ ���������� ������� � ���������� �����;
	bool checkIsFree(int tempDate, std::string doctorName);// ��� �������� �������� �� ��������� ��������� ����� � �����������;
};

