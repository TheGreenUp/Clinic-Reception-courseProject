#include "FileManager.h"


std::string FileManager::getClientDir()
{
	return this->clientDir;
}
std::string FileManager::getOutPatientCardDir()
{
	return this->outPatientCardDir;
}
std::string FileManager::getDoctorDir()
{
	return this->doctorDir;
}

void FileManager::createClientDir(std::string name)
{
	setlocale(LC_ALL, "russian");
	std::string userName = name; //��� ����� = ��� ������������
	int stringLength = name.length();//����� ������
	int pos = userName.find("|"); //���� ������� ����������� ������, �� ������� ���, 

	if (pos != -1) {//��� �� ��� ����� � ���, � �.�. � ��� userName = name + " | "
		userName.resize(userName.size() - 3);//������� ��� �������
		stringLength -=3;
	}
	while (name[stringLength - 1] == ' ') {//���� ��������� ������ - ������, �� ������� ���
		userName.erase(stringLength - 1, 1);//������� ������
		stringLength--;//� ��������� ����� ������
	}

	std::string format = ".txt"; //������ ��������� ����������
	userName += format; //���������
	_mkdir("Patients"); //������� ����� ��������
	std::string path = "Patients\\"; //��������� ���� � ����� ��������
	path += userName; //��������� ������� � ��������
	this->clientDir = path;//���� � ����� - � ����� � ��������� �������
}

void FileManager::createDoctorDir(std::string name)
{
	setlocale(LC_ALL, "russian");
	std::string userName = name; //��� ����� = ��� �������
	std::string format = ".txt"; //������ ��������� ����������
	userName += format; //���������
	_mkdir("Doctors"); //������� ����� 
	std::string path = "Doctors\\"; //��������� ���� � ����� ��������
	path += userName; //��������� ������� � ��������
	this->doctorDir = path;//���� � ����� - � ����� � ��������� ������
}

void FileManager::createOutPatientCardDir(std::string name)
{
	setlocale(LC_ALL, "russian");
	std::string userName = name; //��� ����� = ��� �������
	std::string format = ".txt"; //������ ��������� ����������
	userName += format; //���������
	_mkdir("OutPatientsCard"); //������� ����� 
	std::string path = "OutPatientsCard\\"; //��������� ���� � ����� ��������
	path += userName; //��������� ������� � ��������
	this->outPatientCardDir = path;//���� � ����� - � ����� � ��������� ������
}

std::vector<std::string> FileManager::getDoctorsNames()
{
	std::vector<std::string> doctorsNames; //������ ���� ��������
	std::string tempStr;
	std::string inputPath = "Doctors";        // ���� � ����� � �������
	fs::path path;


	for (auto& p : fs::directory_iterator(inputPath)) //��� ������ ���� ������� ������ �������� ���� ������, ������� � inputPath
	{
		path = p;
		tempStr = path.fs::path::generic_string();
		tempStr.erase(0, 8); //������� ��� ����� (Doctors)
		tempStr.erase(tempStr.size() - 4);//������� ���������� (.txt)
		doctorsNames.push_back(tempStr); //���������� � ������
	}
	return doctorsNames;
}

void FileManager::showDoctorsInfo(std::vector<std::string> doctorNames) {



	std::ifstream fin;//����� ������ �� �����
	FileManager fm;//������������ ��� �������� �����
	std::string spec;//������������� �����

	int i = 0;

	{
		for (int x = 0; x < doctorNames.size(); x++) {//���������� �� ������ ���� ��������
			{
				std::cout << "[" << x + 1 << "]" << " "; //������� �����
				std::cout << std::setw(30) << std::left << doctorNames[x] << "\t" << std::setw(50) <<std::left;//������� ���

				//��������� �������������
				fm.createDoctorDir(doctorNames[x]);
				fin.open(fm.getDoctorDir());
				for (i; i < 2; i++) {//��� ���������� ������ �������, ������� ���� ������ ��������� ������
					std::getline(fin, spec);//��������� �������, �� �.�. ������ ������� - ������, �� �� ������ ������� �������
					if (i == 1) {//� ��� �� ������ �������� - ������������� - �� ��� �����
						std::cout << spec << std::endl; //������� �� 
					}
				}
					fin.close();
					i = 0;
			}
		}
	}
	fin.close();
}
