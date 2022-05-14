#include "DayTimeTable.h"



DayTimeTable::DayTimeTable() {
	std::vector<std::string> date;
	date.push_back("25.05.2022 | 08:00 | �������� |");
	date.push_back("25.05.2022 | 08:30 | �������� |");
	date.push_back("25.05.2022 | 09:00 | �������� |");
	date.push_back("25.05.2022 | 09:30 | �������� |");
	date.push_back("25.05.2022 | 10:00 | �������� |");
	date.push_back("25.05.2022 | 10:30 | �������� |");
	date.push_back("25.05.2022 | 11:00 | �������� |");
	date.push_back("25.05.2022 | 11:30 | �������� |");
	date.push_back("25.05.2022 | 12:00 | �������� |");
	date.push_back("25.05.2022 | 12:30 | �������� |");
	this->date = date;
}

std::vector<std::string> DayTimeTable::getDateVector()
{
	return this->date;
}

void DayTimeTable::GetInfoFromFile(std::string nameOfChosenDoctor)
{
	FileManager fm;
	std::ifstream fin;//����� ������ �� ����a

	int stringNumber = 0; //����� ������� � ����
	int dateNumber = 1; //����� ������� � ����
	std::string tempDate;

	fm.createDoctorDir(nameOfChosenDoctor);
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		if (stringNumber > 1) {//� ��� �� ������� � ���� ���������� �������� - ���������� - �� ��� �����
			std::cout << "[" << dateNumber << "]" << " "; //������� ����� [1] [2] � �.�.
			std::cout << tempDate << std::endl; //������� ���� 12.12.2022
			dateNumber++;
		}
		stringNumber++;

		if (fin.eof()) {//�������� �� ����� �����
			fin.close();//���������
			return;
		}
	}
}

void DayTimeTable::BookChosenTime(int chosenDate, std::string doctorName,std::string patientName, std::string problemDescription, std::string &justDate, std::string& spec)
{

	std::vector<std::string> buff; //���������� ���� ���� ����
	FileManager fm; User user; //user ����� ������ ��� ������ � ����
	std::ifstream fin;//����� ������ �� ����a

	int stringNumber = 0; //����� ������� � ����
	std::string tempDate;
	std::string changedDate;

	fm.createDoctorDir(doctorName);
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) {//��� �� ��� � � �������� � ������� �� ����� ���������� - � for �� � ���������, � ������ �� ����� ����� ����� �����
		buff.insert(buff.begin()+stringNumber, tempDate);//���������� ��� ������ � �������� ����������
		if (stringNumber == 1) spec = tempDate; //����������� �������������
		if (stringNumber > 1) {//� ��� �� ������� � ���� ���������� �������� - ���������� - �� ��� �����
			if (stringNumber - 1 == chosenDate) { // � ����� ����� ��������� 1. ������ 2. ������������� 3 � ����� - ����������, ������� �������� ���
				tempDate.erase(21, 100); //������� "��������"
				justDate = tempDate;
				tempDate +=  "������ | " + patientName + " | " + problemDescription + " |"; //������ �� "������ + ��� + ��������"
				changedDate = tempDate;
			}
		}
		stringNumber++;
	}
	buff[chosenDate + 1] = changedDate;
	fin.close();//���������
	user.putInfoIntoFileDoctor(doctorName, buff);//��������������

}

bool DayTimeTable::checkIsFree(int chosenDate, std::string doctorName) {
	FileManager fm;
	std::ifstream fin;//����� ������ �� ����a

	int stringNumber = 0; //����� ������� �� ������� �� ������ ���������
	std::string tempDate;

	fm.createDoctorDir(doctorName);
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) {//��� �� ��� � � �������� � ������� �� ����� ���������� - � for �� � ���������, � ������ �� ����� ����� ����� �����
		stringNumber++;
		if (stringNumber > 1) {//� ��� �� ������� � ���� ���������� �������� - ���������� - �� ��� �����
			if (stringNumber - 2 == chosenDate) { // � ����� ����� ���������: 1. ������ 2. ������������� 3 � ����� - ����������, ������� �������� ���
				int pos = tempDate.find("������"); //������� ������� � �����
			if (pos != -1) {//���� ������� ����� "������", �� �������� false
					fin.close();
					return false;
				}
			}
		}
	}
	fin.close();
	return true;
}

