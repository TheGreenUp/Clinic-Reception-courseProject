#pragma once
#include "User.h"
#include "MyException.h"
#include "DayTimeTable.h"
#include "Talon.h"

class Doctor : public User {
private:
	std::string speciality;
public:
	void signUp();//�����������
	bool Login();//���� � �������
	void setSpeciality(std::string spec);// ��� ��������� ������������ ��� �����������;
	std::string getSpeciality();// ��� ���������
	void serveNextClient();// ��� ������������ ���������� �������, � �������� �����;
	void showTimeTable();// ��� ��������� ���������� �����������;
	void changeRecordDate();	// ������������� timetable
	void changeRecordByPatient(std::string date, std::string time, std::string name);
	std::string checkDateInput(); //��� �������� ��� �������� ����������� ����
	void showByName(std::string name);//������� �� �����
	Talon addRecordToOutPatientCard(std::string patientName, std::string patientDate, std::string doctorName, std::string doctorSpec);//�� ������ �� ������� ������� ������� �����, � ������� ����� ��������
	int checkRecordDataInput();//��������� ����
};

