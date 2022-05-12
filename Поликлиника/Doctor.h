#pragma once
#include "User.h"
#include "MyException.h"
#include "DayTimeTable.h"

class Doctor : public User {
private:
	std::string speciality;
public:
	void signUp();//�����������
	bool Login();//���� � �������
	void setSpeciality(std::string spec);// ��� ��������� ������������ ��� �����������;
	std::string getSpeciality();// ��� ���������
	void serveNextClient();// ��� ������������ ���������� �������, � �������� ������� �����;
	void showTimeTable();// ��� ��������� ���������� �����������;
	void changeRecordDate();	// ������������� timetable
	void changeRecordByPatient(std::string date, std::string time, std::string name);
	std::string checkDateInput(); //��� �������� ��� �������� ����������� ����


};

