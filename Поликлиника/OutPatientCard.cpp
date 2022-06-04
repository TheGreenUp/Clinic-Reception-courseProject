#include "OutPatientCard.h"

void OutPatientCard::AddConclusion(std::string conclusion)
{
	this->conclusion = conclusion;
}

void OutPatientCard::PutInfoIntoFile(Talon talon, std::string path)
{
	std::ofstream fout;
	FileManager fm;
	fout.open(path, std::ios::app);
	fout << talon.GetTime() << talon.GetDoctorName() << talon.GetDoctorSpec() << talon.getProblemDescription() << std::endl;
	fout << "����������: " << this->conclusion << std::endl;
	//25.05.2025 | 10:00 | �������� | ������������� | ���������������� |
	fout.close();
}
