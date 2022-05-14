#pragma once
#include "User.h"
#include "OutPatientCard.h"
#include "FileManager.h"
#include "Talon.h"

#include <vector>



class Patient : public User
{
	std::vector<Talon> talons;
	OutPatientCard card;
public:
	void createTalon();//������� �����
	
	//====
	void createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);	//������� ����� c ������� ���������� �����������
	//===
	void deleteTalonFromFile();
	void deleteTalonFromFile(int chosenTalon);
	void showOutPatientCard();
	//������� ����� �� �����
	void SortTalonByDate();// ��� ���������� ������� �� �������� �� ����� �������;

	bool showTalons();

	
	//===
	void signUp();//��� ����������� ��������
	bool Login();//��� ����� ���������
	//===
	int checkDataInput();
	int checkChosenDoctorInput(std::vector<std::string> doctorVector);
};

