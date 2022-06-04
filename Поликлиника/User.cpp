#include "User.h"
#include "FileManager.h"
#include "DayTimeTable.h"

User::User()
{
	this->fullName = "����������";
	this->password = 1234;
}

void User::setName(std::string name) {
	this->fullName = name;
}
void User::setPassword(int password) {
	this->password = password;
}

std::string User::getName()
{
	return this->fullName;
}
int User::getPassword()
{
	return this->password;
}


void User::checkUserInput(int& user_option) {//�������� ��������� ����� �� [1;5]
	while (!(std::cin >> user_option) || std::cin.get() != '\n')
	{
		std::cout << "������� �������� ��������: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}

void User::putInfoIntoFilePatient() {
	FileManager fmanager;
	fmanager.createClientDir(this->fullName);
	std::string path = fmanager.getClientDir();
	std::ofstream out;// ����� ��� ������
	out.open(path); // �������� ���� ��� ������
	if (out.is_open())
	{
		out << encryptPassword(std::to_string(this->password)) << std::endl;
	}
	out.close();
}

void User::putInfoIntoFileDoctor(std::string spec) {
	FileManager fmanager;
	//��� ����������
	DayTimeTable daytimetable;
	std::vector<std::string> timetable = daytimetable.getDateVector();
	//
	fmanager.createDoctorDir(this->fullName);//������� ���������� (���� ��� ����������, �� ������� ������������)
	std::string path = fmanager.getDoctorDir();//����� ���� ������� �������
	std::ofstream out;// ����� ��� ������
	out.open(path); // �������� ���� ��� ������
	if (out.is_open())
	{
		out << encryptPassword(std::to_string(this->password)) << std::endl;//��������� ������
		out << spec << std::endl;//�������������
		for (int i = 0; i < 10; i++) {
			out << timetable[i] << std::endl; //����������� ���������
		}

	}
	out.close();
}
void User::putInfoIntoFileDoctor(std::string doctorName, std::vector<std::string> vector) {
	FileManager fmanager;

	fmanager.createDoctorDir(doctorName);//������� ���������� (���� ��� ����������, �� ������� ������������)
	std::string path = fmanager.getDoctorDir();//����� ���� ������� �������
	std::ofstream out;// ����� ��� ������
	out.open(path); // �������� ���� ��� ������
	if (out.is_open())
	{
		for (int x = 0; x < vector.size(); x++) {
			out << vector[x] << std::endl;

		}
	}
	out.close();
}


std::string User::encryptPassword(std::string password) {
	for (int i = 0; (i < password.size() && password[i] != '\0'); i++)
	{
		password[i] = password[i] + 2;
	}
	return password;

}
int User::hidePasswordInput()
{
	while (true) {
		std::string password = "";
		char ch = 0;
		while (ch != 13 && password.size() < 9) {//character 13 is enter && ������������ ����� ������ - 8 ��������
			ch = _getch();
			if (ch > 47 && ch < 58) {//� 48 �� 57 ��������� ASCII ���� ����
				password.push_back(ch);
				std::cout << '*';
			}
		}
		try {
			std::cout << std::endl;
			return std::stol(password);
		}
		catch (std::exception& ex) {
			std::cout << "����� ������ ������ ����! ��������� ����: ";
		}
	}
}
int User::decryptPassword(std::string password) {
	for (int i = 0; (i < password.size() && password[i] != '\0'); i++) {
		password[i] = password[i] - 2; //the key for encryption is 3 that is subtracted to ASCII value
	}
	int passwordEnc;
	passwordEnc = atoi(password.c_str());
	return passwordEnc;
}

