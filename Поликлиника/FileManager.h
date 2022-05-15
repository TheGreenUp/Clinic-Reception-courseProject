#pragma once
#include <direct.h>
#include <string>	
#include <vector>	
#include <iostream>
#include <iomanip>

#include <filesystem>
#include <fstream>


namespace fs = std::filesystem;
class FileManager
{
private:
	std::string clientDir;
	std::string doctorDir;
	std::string outPatientCardDir;
public:
	std::string getDoctorDir();//������� ���� � ������
	std::string getClientDir();//������� ���� � ��������
	std::string getOutPatientCardDir();//������� ���� � ��������

	void createClientDir(std::string name);//������� ���� � ��������
	void createDoctorDir(std::string name);//������� ���� � ��������
	void createOutPatientCardDir(std::string name);//������� ���� � ��������

	std::vector<std::string> getDoctorsNames();//�������� ���� � ������
	void showDoctorsInfo(std::vector<std::string> doctorNames);//������� ���� � ������

};

