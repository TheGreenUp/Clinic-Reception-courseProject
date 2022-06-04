#pragma once
template <class T>
struct Status {
	T* ptr; // ��������� �� ������
	int counter; // ������� ����� ������ �� ������ 
};


//����� ������ ���������. ���� ������ ��������� ������� � ��������  ���������� ������
//����� ��������� ����� ���������� �� ���� ������
template <class T>
class SmartPointer {
	Status<T>* smartPtr;
public:
	SmartPointer(T* ptr = 0);
	SmartPointer(const SmartPointer&);
	~SmartPointer();
	SmartPointer& operator=(const SmartPointer&); //���������� ��������� =
	T* operator->() const; // ���������� ��������� ->
};
