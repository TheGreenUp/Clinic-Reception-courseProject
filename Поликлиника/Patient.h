#pragma once
#include "User.h"
#include "OutPatientCard.h"
#include "FileManager.h"
#include "Talon.h"

#include <vector>



class Patient : public User
{
private:
	std::vector<Talon> talons;
	OutPatientCard card;
public:
	void createTalon();//������� �����
	
	//====
	void createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);	//������� ����� c ������� ���������� �����������
	void editTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date); //���������� ������ � ��������
	//===
	void deleteTalonFromFile();
	void showOutPatientCard();
	//������� ����� �� �����
	void SortTalonByClientName();// ��� ���������� ������� �� �������� �� ����� �������;
	void SortTalonByDoctorName();// ��� ���������� ������� �� �������� �� ����� �������;

	void showTalonInfoByClientName();// ��� ������ ������ �� ����� �������;
	void showTalonInfoByDocName();// ��� ������ ������ �� ����� �������;

	void getInfoFromFile();//��� ��������� ������ ������� ������ �� �����;
	void getOutPatientCard();//��� ��������� ������ ������� ������ �� �����;
	void showTalons();

	
	//===
	void signUp();//��� ����������� ��������
	bool Login();//��� ����� ���������
	//===

};

