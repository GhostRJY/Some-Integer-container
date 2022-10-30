#include<iostream>
#include"myIntArray.h"


int main() {
	const int size = 10;
	
	try {
		//��� �������� ������� ������������� �������� ��� 0 
		//(���� ������ INT_MAX+1 ��������� ���������� �� ������������� ��������, ������� � ����� ������������ )
		//������� � ����� ������������ ����� �������� ������ ��� �������� ���-�� ��������� ���� �������� -catch (std::bad_array_new_length & error)-
		myIntArray arr(size);
		
		arr[0] = 1;				//��� �������� ������� ������ -1 ��� >=size
		arr.reallocate(size);	//������� � �������� ��������� size ��� ���������� ��������� ��� ������������� �������� ��� ����������� ����������
		arr.resize(5);			//������� � �������� ��������� size ��� ���������� ��������� ��� ������������� �������� ��� ����������� ����������
		arr.insertAt(5, 10);	//������� � �������� ������� ��������� ������������� ��� size+1 
		arr.popAt(5);		//������� � �������� ��������� ������������� ��� size+1
		
		arr.pushForward(2);		//������� �������� ������
		arr.pushBack(3);		//������� �������� � �����
		arr.showArray();
		
		arr.popForward();		//�������� ������� ��������
		arr.popBack();			//�������� ���������� ��������
		arr.showArray();

		arr.initializeWithRandValues();	//������������� ���������� ������ ���������� �������
		arr.showArray();

		arr.findElement(19);		//����� �������� �� �������
		arr.findElement(100);

		myIntArray arr2(arr);
		std::cout << std::endl << "Next ARRAY after copy constructor" << std::endl;
		arr2.showArray();

		std::cout << std::endl << "New ARRAY by default" << std::endl;
		myIntArray arr3;
		arr3.showArray();
		std::cout << std::endl << "New ARRAY by default after operator =" << std::endl;
		arr3 = arr2;
		arr3.showArray();

		std::cout << std::endl << "Compare arr and arr3" << std::endl;
		
		//arr[0] = 15;	//������ ����������� ���� ���� ����������� ��� �������� ������ ������ �� ������������
		if (arr3 == arr) {
			std::cout << std::endl << "arr3 == arr" << std::endl;
		}
		else {
			std::cout << std::endl << "arr3 != arr" << std::endl;
		}

		//���������� ����������
		std::cout << std::endl << "\nLets sort our array\nAscending" << std::endl;
		arr.sortArrayAsc();
		arr.showArray();
		std::cout << std::endl << "Descending" << std::endl;
		arr.sortArrayDesc();
		arr.showArray();

		std::cout << std::endl << "Input "<<arr.getSize()<<" values for elements of container: ";
		std::cin >> arr;
		std::cout << std::endl<<arr<<std::endl;


	}
	catch (std::out_of_range & error) {
		std::cout << error.what() << std::endl;
	}
	catch (std::length_error & error) {
		std::cout << error.what() << std::endl;
	}
	catch (std::bad_array_new_length & error) {	// ������ � ������������ �������� ��������� ��� ��������� ������ ���� ���������
		std::cout << error.what() << std::endl;
	}
	
	return 0;
}