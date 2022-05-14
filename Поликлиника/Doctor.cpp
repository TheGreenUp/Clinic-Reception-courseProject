#define NOMINMAX //���������� ��� ������� ��������� �������� std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), �.�. max ��������� � windows.h

#include "Talon.h"
#include "Patient.h"
#include "Doctor.h"
#include <Windows.h>




std::string Doctor::getSpeciality() {
	return this->speciality;
}
void Doctor::setSpeciality(std::string name) {
	this->speciality = name;
}

void Doctor::signUp()
{
	FileManager file_manager; //������� ������ ������ ����_��������
	std::string name, spec; //�������������� ���
	int password = 0, password_repeat = 0, quit = 1;
	std::cout << "====================================";
	std::cout << "\n������� ���� ���: ";
	std::getline(std::cin, name);
	User::setName(name);//������ ��������� ��� ������������	
	std::cout << "���������� ������ [�� 8 ��������, ������ �����]: ";
	password = User::hidePasswordInput();//������ �� (*)
	User::setPassword(password);//������ ������
	//User::checkUserInput(password);//��������� ���� ������
	system("cls");//������ �����, ����� ������ ������
	while (quit)//���������� ������, � ����� ����� 1
	{
		std::cout << "��������� ������ [�������� 8 ��������]: ";
		password_repeat = User::hidePasswordInput();//������ �� (*)
		//User::checkUserInput(password);//��������� ���� ������

		if (password == password_repeat) {//���� ����� ���������� ����� ������ �������, �� ������ ������������� � ���������� � ����
			std::cout << "������� ���� �������������: ";
			std::getline(std::cin, spec);
			Doctor::setSpeciality(spec);
			std::cout << "����������� ������� ���������!\n";
			User::putInfoIntoFileDoctor(spec);//���������� � ���� ������
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
				return;
			}

		}
	}
}
bool Doctor::Login()
{
	FileManager fmanager;//��� �������� ����
	std::string real_password_int;
	int enetered_password = 0, try_repeat = 0, quit = 1;
	int successLogin = 0;//��������� ���� ������������� ������
	std::string entered_name, real_password_string;
	std::ifstream fin;

	while (quit)//�������� �� ������������� ������ ��������
	{
		while (!successLogin) {
			std::cout << "====================================";
			std::cout << "\n������� ���� ���: ";
			std::getline(std::cin, entered_name);
			fmanager.createDoctorDir(entered_name);
			fin.open(fmanager.getDoctorDir());
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
		quit = 1;
		std::getline(fin, real_password_string); //���������� ������ ������ �� �����, ������� �������� �������
		//real_password_int = atoi(real_password_string.c_str());//�������������� �� ���� string � Int
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
				case 1: continue;
				case 2: return false;
				}
			}
		}
	}
}

void Doctor::showTimeTable()
{
	FileManager fm;
	std::ifstream fin;
	int stringNumber = 0; //����� ������� � ����
	int dateNumber = 1; //����� ������� � ����
	std::string tempDate;

	fm.createDoctorDir(this->getName());
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
	fin.close();
}

void Doctor::changeRecordDate()
{
	showTimeTable();//������� ������� ����������
	int chosenDate;
	std::cout << "�������� �����, ������� ������ ��������:\n";	std::cin >> chosenDate;

	FileManager fm; User user;//���� ������ ��� ������ � ����
	std::ifstream fin;//����� ������
	std::vector<std::string> buff; //���������� ���� ���� ����

	//====================
	int stringNumber = 0; //����� ������� � ����
	int stringRecordSize = 0; //����� ������� � ����
	int currentSymbolsInString = 0; //���������� ����������� ��������

	int wordsIterator = 0; //���������� ����������� ����
	int specSymbolIterator = 0; //���������� ����������� ����������� �������� (����� 5) [� ������ �������� �� Enum]

	int numberOfWordsInPatientName = 0; //���������� ���� � ����� �������� (���������� ��� ���������� ��������)
	int numberOfWordInPatientPB = 0; //���������� ���� � �������� �������� �������� (���������� ��� ���������� ��������)

	std::string tempDate;   //��� ������ ������
	std::string wordInRecord;   //�����, ����������� �� ������

	//==========
	std::string chDate; //���������� ����

	bool isSpecSymbol = false;//�������� �� ����������� ������ � ����������� ������
	bool shouldEditPatientFile = false;//�������� �� ����������� ������ � ����������� ������

	//===========��� ��������===============
	std::string patientTalonDate;					//����������� �� ����� ������� ����
	std::string patientTalonName;					//� ��� ���� ��
	std::string patientTalonDoctorSpec;				//�������������
	std::string patientTalonProblemDescription;		//�������� �������� �� ��������
	std::string patientTalonDoctorName = this->getName(); //� ������ �������
	//======================================


	fm.createDoctorDir(this->getName());
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		if (stringNumber - 1 != chosenDate) {//��� ��������, �.�. �� ������ ����, �� ����, ����� ���� ��� �� ���������� ���� �hosen date �������� ������ � ������� ������, �.�. ���� ������
			buff.insert(buff.begin() + stringNumber, tempDate);//���������� ��� ������ � �������� ����������
		}
		if (stringNumber == 1) patientTalonDoctorSpec = tempDate;
		if (stringNumber > 1) {//� ��� �� ������� � ���� ���������� �������� - ���������� - �� ��� �����
			if (stringNumber - 1 == chosenDate) {

				//===============������ � ������� � �����==============
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				chDate = checkDateInput();
				tempDate.erase(0, 18); //������� ���� (������ 18 ��������) 12.12.2022 | 15:30
				tempDate = chDate + tempDate;//���������� ��
				patientTalonDate = chDate;//��������� ���� ����
				buff.push_back(tempDate);//��� ���� ��� ������ �������� ��������, ������� ������
				//====================================================


				if (tempDate.find("������") > 0 && tempDate.find("������") < 1000) {//���� � ������ ���� ����� ������, ����� ������ ���� ��������
					//==============������ � �������� � �����==============
					std::stringstream ss(tempDate);// ���������� ��������� �����
					stringRecordSize = tempDate.size();//������ ������

					for (currentSymbolsInString; currentSymbolsInString <= stringRecordSize;) {//������ �� ��� ���, ���� �� �������� �����
						ss >> wordInRecord;// ������� �����, ��������� � �����, ���� ����� �� ��������
						if (wordInRecord == "|") { specSymbolIterator++; isSpecSymbol = true; } //���� ����� ����.������, �� ����������� �� ���������� � ������� ���������, ��� ��� ������� - ������ �����������
						if (isSpecSymbol == false) {//���� � ������ ������ �� ����������� ������, ��
							switch (specSymbolIterator)//� ����������� �� ���������� ����������� ��������, ������� ��������� ������ ���������, ���������� ������ �����
							{
							case 3: {//����������  0, 1 � 2, �.�. ��� �������� �� ������ ��� ����������
								if (numberOfWordsInPatientName == 0)//���� ���� ����� � �����, ����� ������� � ���� ����
									patientTalonName = wordInRecord;
								else patientTalonName += " " + wordInRecord;//� ��� ���� ���� ������, ��� ����, ����� ����� �����, ������� ������� ������ � ��������� �������
								numberOfWordsInPatientName++;//� ����������� ����������� ��������� ���� � ����� ��������
								break;
							}
							case 4: {
								if (numberOfWordInPatientPB == 0)									//====================//
									patientTalonProblemDescription = wordInRecord;					//====================//
								else patientTalonProblemDescription += " " + wordInRecord;			//������ �������� ����//
								numberOfWordInPatientPB++;											//====================//
								break;																//====================//
							}
							}
						}

						if (currentSymbolsInString == 0) currentSymbolsInString++; //� ����� � ���, ��� � ������ ���� �������, ������ ������� ������������, � ��� ����� ������ �������� �� ��� ������ =)
						currentSymbolsInString += wordInRecord.size();//�������� � ��������� ����� �����, ������� ������
						currentSymbolsInString += 1; //������
						wordsIterator++;
						isSpecSymbol = false;
						if (currentSymbolsInString >= stringRecordSize) {
							std::cout << std::endl; //���� ���������� �����, ������ ������� �� ��������� �������
							shouldEditPatientFile = true;
						}
					}
				}
				currentSymbolsInString = 0; //�������� ���������� ����������� �������� � ������ 
			}
		}
		stringNumber++;//������� ����� ���������
	}
	user.putInfoIntoFileDoctor(this->getName(), buff);//���������� ���������� ���������� � ���� �������
	if (shouldEditPatientFile) {//���� �� �������� ���� ��������, ���� �������� ���� ����
		Patient patient; //��������� �������� ������� ��� �������� ��� ������
		patient.createTalon(patientTalonName, patientTalonDoctorName, patientTalonDoctorSpec, patientTalonProblemDescription, patientTalonDate); //� �������� � �����
	}
	fin.close();//���������
}
void Doctor::changeRecordByPatient(std::string date, std::string time, std::string name) {
	FileManager fm; User user;//���� ������ ��� ������ � ����
	std::ifstream fin;//����� ������
	std::vector<std::string> buff; //���������� ���� ���� ����

	//====================
	int stringNumber = 0; //����� ������� � ����

	std::string tempDate;   //��� ������ ������


	fm.createDoctorDir(name);
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		if (!(stringNumber > 1)) {//� ��� �� ������� � ���� ���������� �������� - ���������� - �� ��� �����
			buff.push_back(tempDate);//���������� ��� ������ � �������� ����������
			stringNumber++;
			continue;
		}
		if (!(tempDate.find(date) > 0) && !(tempDate.find(date) < 1000)) {//���� �� ����� ������� ���� 
			buff.push_back(tempDate);//������ � ������
			stringNumber++;
			continue;
		}
		if (!(tempDate.find(time) > 0) && !(tempDate.find(time) < 1000)) {//���� �� ����� ������ �����
			buff.push_back(tempDate);//���� ���
			stringNumber++;
			continue;
		}
		tempDate.erase(21, 100); //������� ������ � ��� ��� ������
		tempDate += "�������� |";
		buff.push_back(tempDate);//��� ���� ��� ������ �������� ��������, ������� ������
	}
	user.putInfoIntoFileDoctor(name, buff);
}
std::string Doctor::checkDateInput() {
	int day = 0, month = 0, year = 0, hour = 0, minute = 0;
	std::string dayS, monthS, yearS, hourS, minuteS;
	std::string tmp;
	std::string changedDate;

	int maxDays = 0;

	std::cout << "������� ����� �����: ";
	while (!(std::cin >> month) || (month <= 0 || month > 12)) {
		std::cout << "������� �������� �������� [1;12]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	monthS = std::to_string(month);//��������� int � std::string
	if (month < 10) monthS = "0" + monthS;//���� ����� ������ 10, �� ��������� ����, ����� ���������� 04

	switch (month) //������ �� ������ ���������� ����
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: {
		maxDays = 31;
		break;
	}
	case 4: case 6: case 9: case 11: {
		maxDays = 30;
		break;
	}
	default:
		maxDays = 28;
		break;
	}

	std::cout << "������� ����� ����: ";
	while (!(std::cin >> day) || (day <= 0 || day > 31) || day > maxDays) {
		std::cout << "������� �������������� �������� ��������: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	dayS = std::to_string(day);//��������� int � std::string
	if (day < 10) dayS = "0" + dayS;//���� ���� ������ 10, �� ��������� ����, ����� ���������� 04

	std::cout << "������� ����� ���: ";
	while (!(std::cin >> year) || (year < 2022 || year > 2030)) {
		std::cout << "������� �������� �������� [2022;2030]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	yearS = std::to_string(year);

	std::cout << "������� ����� ����� (���): ";
	while (!(std::cin >> hour) || (hour <= 7 || hour > 22)) {
		std::cout << "������� �������� �������� [8;22]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	hourS = std::to_string(hour);//��������� int � std::string
	if (hour < 10) hourS = "0" + hourS;//���� ��� ������ 10, �� ��������� ����, ����� ���������� 04

	std::cout << "������� ����� ����� (������): ";
	while (!(std::cin >> minute) || (minute < 0 || minute > 60)) {
		std::cout << "������� �������� �������� [1;59]: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	minuteS = std::to_string(minute);//��������� int � std::string
	if (minute < 10) minuteS = "0" + minuteS;//���� ������ ������ 10, �� ��������� ����, ����� ���������� 04


	changedDate = dayS + "." + monthS + "." + yearS + " | " + hourS + ":" + minuteS;
	return changedDate;
}


void Doctor::serveNextClient()
{
	FileManager fm;
	std::ifstream fin;
	std::vector<std::string> buff;
	//======================
	int stringNumber = 0; //����� ������� � ����
	int chosenTalon = 0; //����� ������� � ����
	int specSymbolIterator = 0; //���������� ����������� ����������� �������� (����� 5) [� ������ �������� �� Enum]
	//======================
	bool shoudEdit = true;
	bool isSpecSymbol = false;
	//======================
	int busyPos = 0;
	int numberOfWordsInPatientName = 0;
	int numberOfWordInPatientPB = 0;
	//======================
	//===========������ �� �����===========
	std::string fileDate;
	std::string fileTime;
	std::string filePatientName;
	std::string fileDoctorName = this->getName();
	std::string fileSpec;
	std::string fileProblemDescription;
	//=====================================
	std::string wordInRecord;
	std::string tempDate;


	fm.createDoctorDir(this->getName());
	fin.open(fm.getDoctorDir());

	for (int n; std::getline(fin, tempDate); ) { //����� ����� �������, ���� ������ ����� while (fin.eof()) - �����
		busyPos = tempDate.find("������");
		if (!(busyPos > 0 && busyPos < 100) || shoudEdit == false) buff.push_back(tempDate);
		if (stringNumber == 1) fileSpec = tempDate;
		if (stringNumber > 1) {//� ��� �� ������� � ���� ���������� �������� - ���������� - �� ��� �����
			if (busyPos > 0 && busyPos < 100 && shoudEdit) {//12.12.2022 | 15:30 | ������ |
				chosenTalon = stringNumber-2;
				std::stringstream ss(tempDate);
				while (specSymbolIterator < 5) {
					ss >> wordInRecord;
					if (wordInRecord == "|") { isSpecSymbol = true; specSymbolIterator++; }
					if (isSpecSymbol == false) {
						switch (specSymbolIterator)
						{
						case 0: {
							fileDate = wordInRecord;
							break;
						}
						case 1: {
							fileTime = wordInRecord;
							break;
						}
						case 3: {//����������  0, 1 � 2, �.�. ��� �������� �� ������ ��� ����������
							if (numberOfWordsInPatientName == 0)//���� ���� ����� � �����, ����� ������� � ���� ����
								filePatientName = wordInRecord;
							else filePatientName += " " + wordInRecord;//� ��� ���� ���� ������, ��� ����, ����� ����� �����, ������� ������� ������ � ��������� �������
							numberOfWordsInPatientName++;//� ����������� ����������� ��������� ���� � ����� ��������
							break;
						}
						case 4: {
							if (numberOfWordInPatientPB == 0)									//====================//
								fileProblemDescription = wordInRecord;							//====================//
							else fileProblemDescription += " " + wordInRecord;					//������ �������� ����//
							numberOfWordInPatientPB++;											//====================//
							break;																//====================//
						}
						default:
							break;
						}					
					}
					isSpecSymbol = false;
				}
				tempDate.erase(21, 6);
				tempDate.insert(21, "��������");//12.12.2023 | 16:30 | �������� | 
				tempDate.erase(32, 1000);
				buff.push_back(tempDate);
				shoudEdit = false;
			}
	
		}
		stringNumber++;
	}
	fin.close();
	if (!shoudEdit) {
		User user;
		Talon talon;
		std::ofstream fout;
		std::string pathOPCD;
		std::string conclusion;

		Patient patient;
		patient.setName(filePatientName);
		user.putInfoIntoFileDoctor(this->getName(), buff);//���������� ���������� ���������� �������

		fileDate = fileDate + " | " + fileTime + " | ";//�������� ���� � ������������ �������
		talon = addRecordToOutPatientCard(fileDate, fileDoctorName, fileSpec, fileProblemDescription);//�������� ����� ������� �������

		fm.createOutPatientCardDir(filePatientName);
		fm.createClientDir(filePatientName);
		pathOPCD = fm.getOutPatientCardDir();
		patient.deleteTalonFromFile(chosenTalon);
		std::cout << "������� ����������: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, conclusion);
		OutPatientCard opc;
		opc.AddConclusion(conclusion);
		opc.PutInfoIntoFile(talon, pathOPCD);
		std::cout << "������� ������� ��������!\n";
	}
	else std::cout << "��� ��������� � �������!\n";
	system("pause");



	//case 0: case 1: + doctor->getName() case 3: case 4: \n
	// conclusion
	// 
	//doctor: 25.05.2022 | 09:30 | ������ | ����� | ���� ���� |
	//patient: 25.05.2022 | 09:30 | ���� | ���������� ������� | ���� ���� |
	// 
	//25.05.2025 | 10:00 | �������� | ������������� | ���������������� |
}
Talon Doctor::addRecordToOutPatientCard(std::string patientDate, std::string doctorName, std::string doctorSpec, std::string problemDescription) {
	Talon talon;
	talon.addTalonToOutPatientCard(patientDate, doctorName, doctorSpec, problemDescription);
	return talon;

}