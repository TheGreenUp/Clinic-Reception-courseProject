#pragma once

#include <string>


class OutPatientCard
{
private: 
	std::string conclusion;
public:
	void AddConclusion();// ��� ������ ���������� ����� � ������������ ����� ��������;
	void GetConclusionsCount();// ��� ��������� ������� ����������, ������������� � ����;
	void GetIntoFromFile();// ��� ��������� ������ �� �����;
	void PutInfoIntoFile();// ��� ������ ������ � ����;
	void ShowInfo();// ��� ��������� ����������� ���������� � ����� ��������;

};

