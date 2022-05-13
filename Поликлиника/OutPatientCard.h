#pragma once
#include "FileManager.h"
#include "Talon.h"
#include <string>


class OutPatientCard
{
private: 
	std::string conclusion;
public:
	void AddConclusion(std::string conclusion);// ��� ������ ���������� ����� � ������������ ����� ��������;
	void GetConclusionsCount();// ��� ��������� ������� ����������, ������������� � ����;
	void getInfoFromFile();
	void PutInfoIntoFile(Talon talon, std::string path);
	// ��� ��������� ������ �� �����;
	void ShowInfo();// ��� ��������� ����������� ���������� � ����� ��������;

};

