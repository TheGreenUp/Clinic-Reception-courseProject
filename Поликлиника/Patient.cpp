#define NOMINMAX //���������� ��� ������� ��������� �������� std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), �.�. max ��������� � windows.h
#include "Patient.h"
#include "MyException.h"
#include "Doctor.h"

#include <string>
#include <iostream>
#include <Windows.h>


void Patient::showTalons()
{
	
	Talon talon;
	talon.ShowInfo(this->getName());

}

void Patient::signUp()
{
	FileManager file_manager; //������� ������ ������ ����_��������
	std::string name; //�������������� ���
	int password = 0, password_repeat = 0, quit = 1;
	std::cout << "====================================";
	std::cout << "\n������� ���� ���: ";
	std::getline(std::cin, name);
	User::setName(name);
	std::cout << "���������� ������ [�� 10 ��������]: ";
	User::checkUserInput(password);
	User::setPassword(password);
	system("cls");
	while (quit)//���������� ������, � ����� ����� 1
	{
		std::cout << "��������� ������: ";
		User::checkUserInput(password_repeat);

		if (password == password_repeat) {
			std::cout << "����������� ������� ���������!\n";
			User::putInfoIntoFilePatient();//���������� � ���� ������
			Sleep(1000);//���� ������������ �������, ��� ��� ������
			return;
		}
		else
		{
			int chosen_option = 0;
			std::cout << "��������� ������ �� ��������� � �����������!\n������ ��������� �������?\n[1] ��\n[2] ���\n";
			std::cin >> chosen_option;
			switch (chosen_option)
			{
			case 1: {
				//������ �� ������
				break;
			}
			case 2:
				quit = 0; //�������
			}

		}
	}
}

bool Patient::Login()
{
	FileManager fmanager;//��� �������� ����
	int real_password_int = 0, enetered_password = 0, try_repeat = 0, quit = 1;
	int successLogin = 0;//��������� ���� ������������� ������
	std::string entered_name, real_password_string;
	std::ifstream fin;

	while (quit)//�������� �� ������������� ������ ��������
	{
		while (!successLogin) {

			std::cout << "====================================";
			std::cout << "\n������� ���� ���: ";
			std::getline(std::cin, entered_name);
			fmanager.createClientDir(entered_name);
			fin.open(fmanager.getClientDir());
			try
			{
				if (!fin) throw MyException("�������� �����! ", 0);//���� �� ���������� ����� � ������ ��������, ����� exception
				else quit = 0;
			}
			catch (MyException& ex)
			{
				std::cout << ex.what();
				std::cout << "������� ��������� �������?\n[1] ��\n[2] ���\n";
				std::cin >> try_repeat;
				switch (try_repeat)
				{
				case 1: {
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.clear();
					continue;
				}
				case 2: return false;
				}
			}
			successLogin = 1;
		}
	}
	quit = 1;
	std::getline(fin, real_password_string); //���������� ������ ������ �� �����, ������� �������� �������
	real_password_int = atoi(real_password_string.c_str());//�������������� �� ���� string � Int
	while (quit)
	{
	std::cout << "������� ������: ";
	User::checkUserInput(enetered_password); //���� ������

	if (enetered_password == real_password_int) {
		this->setName(entered_name);
		this->setPassword(real_password_int);
		return true;
	}
	else {
		std::cout << "������� ��������� �������?\n[1] ��\n[2] ���\n";
		std::cin >> try_repeat;
		switch (try_repeat)
		{
		case 1: break;
		case 2: return false;
		}
	}
	}
}

void Patient::createTalon()
{
	int chosenDoctor = 0, chosenDate;

	std::ifstream fin;//����� ������ �� �����

	DayTimeTable dtt;
	FileManager fm;//������������ ��� �������� �����

	std::vector<std::string> doctorNames; //������ ���� ������
	std::string problemDescription, date;
	std::string spec, nameOfChosenDoctor, tempDate;//������������� ����� � ��� ���������� �������, �������� ���������� ��� �������
	
	std::string patientName = this->getName();

	//=====�������� ���� � ������======
	doctorNames = fm.getDoctorsNames();//���������� � ������ ����� ���� ������
	//������� ��� + �������������
	fm.showDoctorsInfo(doctorNames); //��� ���� ������
	//===========����� ����������======
	std::cout << "� ������ ����� ������ ���������� �� �����?\n";
	std::cin >> chosenDoctor;
	nameOfChosenDoctor = doctorNames[chosenDoctor - 1];
	dtt.GetInfoFromFile(nameOfChosenDoctor);
	//===============�����=============
	std::cout << "�������� ������� �����:\n";
	std::cin >> chosenDate;
	while (!dtt.checkIsFree(chosenDate, nameOfChosenDoctor)) {//���� ������ //��������
		std::cout << "��������� ����� ������, �������� ������:\n";
		std::cin >> chosenDate;
	};
	std::cout << "������� ��������:";
	std::getline(std::cin.ignore(), problemDescription); //��� �������� (����� �����)
	dtt.BookChosenTime(chosenDate, nameOfChosenDoctor, patientName, problemDescription, date, spec); //��������� ��� ��������� � ������� ������� ���� ��������, �.�. ���������� �� ������
	Talon talon;
	talon.Set(patientName,nameOfChosenDoctor, spec, problemDescription, date);//�������-�� ������� �����
	this->talons.push_back(talon);
	talon.PutTalonIntoPatientFile();
}

void Patient::createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date) {
	Talon talon;
	talon.editedSet(clientName, doctorName, doctorSpec, problemDescription, date);//�������-�� ������� �����
	this->talons.push_back(talon);
	talon.editTalonByDoctor(doctorName, problemDescription);
}

void Patient::editTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date) {
	Talon talon;

}