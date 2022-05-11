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
		out << this->password << std::endl;
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
		out << this->password << std::endl;//��������� ������
		out << spec << std::endl;//�������������
		for (int i = 0; i < 10; i++) {
			out << timetable[i] << std::endl; //����������� ���������
		}

	}
	out.close();
}
void User::putInfoIntoFileDoctor(std::string doctorName,std::vector<std::string> vector) {
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
std::string User::hashPassword() {
	// ���������
	return "ya gay";
}