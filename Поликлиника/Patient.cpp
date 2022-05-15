#define NOMINMAX //���������� ��� ������� ��������� �������� std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), �.�. max ��������� � windows.h
#include "Patient.h"
#include "MyException.h"
#include "Doctor.h"

#include <string>
#include <iostream>
#include <Windows.h>


bool Patient::showTalons()
{

	Talon talon;
	if (talon.ShowInfo(this->getName())) return true;
	else return false;

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
	std::cout << "���������� ������ [�� 8 ��������, ������ �����]: ";
	password = User::hidePasswordInput();//������ �� (*)
	User::setPassword(password);
	system("cls");
	while (quit)//���������� ������, � ����� ����� 1
	{
		std::cout << "��������� ������: ";
		password_repeat = User::hidePasswordInput();//������ �� (*)
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
	int enetered_password = 0, try_repeat = 0, quit = 1;
	int successLogin = 0;//��������� ���� ������������� ������
	std::string entered_name, real_password_string;
	std::ifstream fin;

	while (quit)//�������� �� ������������� ������ ��������
	{
		while (!successLogin) {

			std::cout << "====================================";
			std::cout << "\n������� ���: ";
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
	while (quit)
	{
		std::cout << "������� ������ [�������� 8 ��������]: ";
		enetered_password = User::hidePasswordInput();
		//User::checkUserInput(enetered_password); //���� ������
		if (enetered_password == User::decryptPassword(real_password_string)) {
			this->setName(entered_name);
			this->setPassword(enetered_password);
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

int Patient::checkDataInput()
{
	int chosenDate;
	std::cout << "�������� ������� ����: ";
		while (!(std::cin >> chosenDate) || std::cin.get() != '\n' || chosenDate < 1 || chosenDate > 10)
	{
		std::cout << "������� �������� �������� [1;10]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');

	}
	return chosenDate;
}

int Patient::checkChosenDoctorInput(std::vector<std::string> doctorVector) {
	int chosenDate;
	int vectorSize = doctorVector.size();
	std::cout << "� ������ ����� ������ ���������� �� �����: ";
	while (!(std::cin >> chosenDate) || std::cin.get() != '\n' || chosenDate < 1 || chosenDate > vectorSize)
	{
		std::cout << "�������� ����! ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	return chosenDate;
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
	doctorNames = fm.getDoctorsNames();//���������� � ������ ����� ���� ������ //������� ��� + �������������

	if (doctorNames.size() == 0) {
		std::cout << "������ ���! ���� ��������...\n";
		return;
	}

	fm.showDoctorsInfo(doctorNames); //��� ���� ������
	//===========����� ����������======
	chosenDoctor = checkChosenDoctorInput(doctorNames);
	nameOfChosenDoctor = doctorNames[chosenDoctor - 1];
	dtt.GetInfoFromFile(nameOfChosenDoctor);
	//===============�����=============
	chosenDate = checkDataInput();
	while (!dtt.checkIsFree(chosenDate, nameOfChosenDoctor)) {//���� ������ //��������
		std::cout << "��������� ����� ������, �������� ������:\n";
		std::cin >> chosenDate;
	};
	std::cout << "������� ��������: ";
	//std::getline(std::cin, problemDescription);
	std::getline(std::cin, problemDescription);
	dtt.BookChosenTime(chosenDate, nameOfChosenDoctor, patientName, problemDescription, date, spec); //��������� ��� ��������� � ������� ������� ���� ��������, �.�. ���������� �� ������
	Talon talon;
	talon.Set(patientName, nameOfChosenDoctor, spec, problemDescription, date);//�������-�� ������� �����
	this->talons.push_back(talon);
	talon.PutTalonIntoPatientFile();
}

void Patient::createTalon(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date) {
	Talon talon;
	talon.editedSet(clientName, doctorName, doctorSpec, problemDescription, date);//�������-�� ������� �����
	this->talons.push_back(talon);
	talon.editTalonByDoctor(doctorName, problemDescription);
}

void Patient::deleteTalonFromFile() {
	std::ifstream fout;
	if (!showTalons()) return;//���� ������� ���, �� �������
	int chosenTalon = 0;
	std::cout << "������� ����� ������, ������� ������ �������: ";
	std::cin >> chosenTalon;

	FileManager fm;
	Doctor doctor;

	std::string tempDate, wordInRecord;
	std::string date, time, doctorName;
	std::vector<std::string> buff;

	int stringNumber = 0;
	int specSymbolIterator = 0;
	int numberOfWordsInDoctorName = 0;

	bool isSpecSymbol = false;

	fm.createClientDir(this->getName());
	fout.open(fm.getClientDir());

	for (int n; std::getline(fout, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		if (!stringNumber) {//������ ������ (������) ���������� �����
			stringNumber++;
			buff.push_back(tempDate);
			continue;
		}
		if (stringNumber == chosenTalon) {//���� �����, ��
			std::stringstream ss(tempDate);// ���������� ��������� �����

			while (specSymbolIterator < 3) {
				ss >> wordInRecord;// ������� �����, ��������� � �����, ���� ����� �� ��������
				if (wordInRecord == "|") { specSymbolIterator++; isSpecSymbol = true; } //���� ����� ����.������, �� ����������� �� ���������� � ������� ���������, ��� ��� ������� - ������ �����������
				if (isSpecSymbol == false) {//���� � ������ ������ �� ����������� ������, ��
					switch (specSymbolIterator)//� ����������� �� ���������� ����������� ��������, ������� ��������� ������ ���������, ���������� ������ �����
					{
					case 0: {//����������� ����
						date = wordInRecord;
						break;
					}
					case 1: {//����������� �����
						time = wordInRecord;
						break;
					}
					case 2: {//����������� ������
						if (numberOfWordsInDoctorName == 0)//���� ���� ����� � �����, ����� ������� � ���� ����
							doctorName = wordInRecord;
						else doctorName += " " + wordInRecord;//� ��� ���� ���� ������, ��� ����, ����� ����� �����, ������� ������� ������ � ��������� �������
						numberOfWordsInDoctorName++;//� ����������� ����������� ��������� ���� � ����� ��������
						break;
					}
					}
				}
					isSpecSymbol = false;
			}
				doctor.changeRecordByPatient(date, time, doctorName);
				stringNumber++;
				continue;
			}
			else {
				buff.push_back(tempDate);
				stringNumber++;

			}
		}
		fout.close();
		std::ofstream fin;
		fin.open(fm.getClientDir());
		for (int i = 0; i < buff.size(); i++) {
			fin << buff[i] << std::endl;
		}
		fin.close();
	}

void Patient::deleteTalonFromFile(int chosenTalon) {
	std::ifstream fout;

	FileManager fm;
	Doctor doctor;

	std::string tempDate, wordInRecord;
	std::string date, time, doctorName;
	std::vector<std::string> buff;

	int stringNumber = 0;
	int specSymbolIterator = 0;
	int numberOfWordsInDoctorName = 0;

	bool isSpecSymbol = false;

	fm.createClientDir(this->getName());
	fout.open(fm.getClientDir());

	for (int n; std::getline(fout, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		if (!stringNumber) {
			stringNumber++;
			buff.push_back(tempDate);
			continue;
		}
		if (stringNumber == chosenTalon) {
			stringNumber++;
			continue;
		}
		else {
			buff.push_back(tempDate);
			stringNumber++;

		}
	}
	fout.close();
	std::ofstream fin;
	fin.open(fm.getClientDir());
	for (int i = 0; i < buff.size(); i++) {
		fin << buff[i] << std::endl;
	}
	fin.close();
}

void Patient::showOutPatientCard() {
	FileManager fm;
	std::string path;
	std::string tempDate;
	std::ifstream fin;

	bool isData = false;

	fm.createOutPatientCardDir(this->getName());
	path = fm.getOutPatientCardDir();
	fin.open(path); 

	for (int n; std::getline(fin, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - ����� 
		std::cout << tempDate << std::endl;
		isData = true;
	}
	fin.close();
	if (!isData) std::cout << "��� �������!\n";	
}

void Patient::SortTalonByDate()
{

	FileManager fm;
	std::ifstream fin;//����� ������ �� ����a

	int stringNumber = 0; //����� ������� � ����
	int dateNumber = 1; //����� ������� � ����
	int stringTalonSize = 0;
	int numberOfSymbolsInTalon = 0; //�������� ��� �������� �� ��, �������� �� �����

	std::string tempDate;
	std::string talonString;

	std::vector<std::string> buff;

	bool areRecordsInFile = false;


	fm.createClientDir(this->getName());
	fin.open(fm.getClientDir());

	for (int n; std::getline(fin, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		buff.push_back(tempDate);
		}
	
}

