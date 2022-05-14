#pragma once

#include <windows.h>
#include <string>
#include <iostream>

#include "FileManager.h"

class Talon
{
private:
	std::string clientName, doctorName, doctorSpec, problemDescription, date;
public:
	std::string GetPatientName();// ��� ��������� ��� �������;
	std::string GetDoctorName();
	std::string GetDoctorSpec();
	std::string getProblemDescription();
	// ��� ��������� ��� �����������;


	void EditTalon(std::string problemDescription, std::string doctorName, std::string patientName);
	void editTalonByDoctor(std::string doctorName, std::string problemDescription);
	void editedSet(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);

	// ��� ��������� ������ �� �����;
	std::string GetTime();// ��� ��������� ���� �����;
	void PutTalonIntoPatientFile();
	// ��� ������ ���������� � ����;
	void Set(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date);
	void addTalonToOutPatientCard(std::string patientDate, std::string doctorName, std::string doctorSpec, std::string problemDescription);
	// ��� �������� ����������� ������ ��� �������� ������ ������;
	bool ShowInfo(std::string patientName);// ��� ��������� ������;
	
};

