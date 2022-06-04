#pragma once
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>

#include "FileManager.h"


class User
{
private:
	std::string fullName;
	int password;
public:
	User();
	std::string getName();//������� ��� ������������
	int getPassword();//�������� ������ ������������
	void setName(std::string);//�������� ��� ������������
	void setPassword(int);//�������� ������ ������������
	void putInfoIntoFileDoctor(std::string spec);//�������� ������ ������� � ����
	void putInfoIntoFileDoctor(std::string doctorName,std::vector<std::string> vector);//�������� ������ ������� � ����
	void putInfoIntoFilePatient();//�������� ������ �������� � ����
	void checkUserInput(int& user_option);//�������� �� �������� ����
	std::string encryptPassword(std::string password); //���������� ������ � �����
	int decryptPassword(std::string password);//������������ ������ (����� � ��� ����)
	int hidePasswordInput();//��������� ������ ���� ��� ����� ������
};

