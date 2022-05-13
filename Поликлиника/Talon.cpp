#include "Talon.h"

std::string Talon::GetPatientName()
{
	return this->clientName;
}
std::string Talon::GetTime() {
	return this->date;
}
std::string Talon::GetDoctorName()
{
	return this->doctorName;
}
std::string Talon::GetDoctorSpec() {
	return this->doctorSpec;
}
std::string Talon::getProblemDescription() {
	return this->problemDescription;
}
//	std::string clientName, doctorName, doctorSpec, problemDescription, date;


void Talon::PutTalonIntoPatientFile()//������������ ���� �������, ����� ���� ����� (������) � �����
{
	FileManager fmanager;//��� �������� ����
	fmanager.createClientDir(this->clientName);//������� ���������� (���� ��� ����������, �� ������� ������������)
	std::string path = fmanager.getClientDir();//����� ���� ������� �������
	std::ofstream out;// ����� ��� ������
	out.open(path, std::ios::app); // �������� ���� ��� ������
	if (out.is_open())
	{
		out << this->date << this->doctorName << this->doctorSpec << this->problemDescription << std::endl;

	}
	out.close();
}


void Talon::Set(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date)
{
	this->clientName = clientName + " | ";
	this->doctorName = doctorName + " | ";
	this->doctorSpec = doctorSpec + " | ";
	this->problemDescription = problemDescription + " |";
	this->date = date;
}

void Talon::addTalonToOutPatientCard(std::string patientDate, std::string doctorName, std::string doctorSpec, std::string problemDescription) {
	this->doctorName = doctorName + " | ";
	this->doctorSpec = doctorSpec + " | ";
	this->problemDescription = problemDescription + " |";
	this->date = patientDate;
}

//==========�������������� ��������==========
void Talon::editTalonByDoctor(std::string doctorName, std::string problemDescription)//������������ ���� �������, ����� ���� ����� (������) � �����
{
	FileManager fmanager;//��� �������� ����
	std::vector<std::string> buff;
	fmanager.createClientDir(this->clientName);//������� ���������� (���� ��� ����������, �� ������� ������������)
	std::string path = fmanager.getClientDir();//����� ���� ������� �������
	std::string tempDate;
	std::string newTalon = this->date + this->doctorName + this->doctorSpec + this->problemDescription;

	bool foundDoctor = false;

	int numberOfString = 0;
	std::ifstream fout;// ����� ��� ������
	fout.open(path); // �������� ���� ��� ������

	int doctorPos;
	int probDescPos;

	for (int n; std::getline(fout, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		if (!numberOfString) {
			
			numberOfString++;
			buff.push_back(tempDate);
			continue;
		}

		doctorPos = tempDate.find(doctorName);
		probDescPos = tempDate.find(problemDescription);
		

		if (doctorPos > 0 && doctorPos < 1000) {//���� �� ����� ��� ������� �������
			foundDoctor = true;
		}
		if (probDescPos > 0 && probDescPos < 1000 && foundDoctor) {//���� �� ����� ��������
			buff.push_back(newTalon);
			numberOfString++;
			foundDoctor = false;
			continue;
		}
		buff.push_back(tempDate);
		numberOfString++;
	}
	fout.close();

	std::ofstream fin;
	fin.open(path);
	for (int i = 0; i < buff.size(); i++) {
		fin << buff[i] << std::endl;
	}

	fin.close();
}
void Talon::editedSet(std::string clientName, std::string doctorName, std::string doctorSpec, std::string problemDescription, std::string date)
{
	this->clientName = clientName + " | ";
	this->doctorName = doctorName + " | ";
	this->doctorSpec = doctorSpec + " | ";
	this->problemDescription = problemDescription + " |";
	this->date = date + " | ";
}
//===========================================
void Talon::ShowInfo(std::string patientName)//����������, ����� �� ����� �������� ������ 
{
	FileManager fm;
	std::ifstream fin;//����� ������ �� ����a

	int stringNumber = 0; //����� ������� � ����
	int dateNumber = 1; //����� ������� � ����
	int stringTalonSize = 0;
	int numberOfSymbolsInTalon = 0; //�������� ��� �������� �� ��, �������� �� �����

	std::string tempDate;
	std::string talonString;


	fm.createClientDir(patientName);
	fin.open(fm.getClientDir());

	for (int n; std::getline(fin, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		if (stringNumber != 0) {//��� ������ � ����� �������� ��������� ����� ������ �������, ������� ������ �������� ����������
			std::cout << "[" << stringNumber << "] " << tempDate << std::endl;
		}
		stringNumber++;


		if (fin.eof()) {//�������� �� ����� �����
			fin.close();//���������
			return;
		}
	}
}