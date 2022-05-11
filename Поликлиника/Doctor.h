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
	void findFirstTalon();// ��� ������ ������� ������ � �������
	void getInfoFromFile();// ��� ��������� ���������� �� �����;
	void putInfoIntoFile();// ��� ������ ����������� ���������� � ����;
	void serveNextClient();// ��� ������������ ���������� �������, � �������� ������� �����;
	void setSpec();// ��� ��������� ������������ ��� �����������;
	void showTimeTable();// ��� ��������� ���������� �����������;
	void changeRecordDate();	// ������������� timetable
	std::string checkDateInput(); //��� �������� ��� �������� ����������� ����


};

