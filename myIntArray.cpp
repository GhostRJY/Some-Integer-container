#include<exception>
#include<iostream>
#include<cmath>
#include<ctime>	//���������� ����� ��� ������������� ��������� �������

#include "myIntArray.h"

myIntArray::myIntArray() {
	_size = 10;
	_array = new int[_size];

	for (int i = 0; i < _size; i++) {
		_array[i] = 0;
	}
}

myIntArray::myIntArray(int length) {
	if (length <= 0) {
		throw std::length_error("Object not created (size must be bigger than 0)\n");
	}
	
	_size = length;
	_array = new int[_size];	//������ +INT_MAX � _size ���� ��������� catch � bad_array_new_length
	
	
	for (int i = 0; i < _size; i++) {
		_array[i] = 0;
	}
		
}

myIntArray::myIntArray(const myIntArray& init):_size(init._size) { //����������� �����������
	_array = new int[_size];
		
	for (int i = 0; i < _size; i++) {
		_array[i] = init._array[i];
	}
}

myIntArray::~myIntArray() {
	delete[] _array;
}

void myIntArray::erase() {
	delete[] _array;

	_array = nullptr;
	_size = 0;
}

const myIntArray & myIntArray::operator=(const myIntArray & right) {
	if (&right != this) {				//�������� ����������������
		if (_size != right._size) {
			delete[] _array;
			_size = right._size;
			_array = new int[_size];
		}
		for (int i = 0; i < _size; i++)
			_array[i] = right._array[i];
	}
	return *this;						//��������� ������������� ������������ 
}

bool myIntArray::operator==(const myIntArray & right) const {
	if (_size != right._size)
		return false;

	for (int i = 0; i < _size; i++) {
		if (_array[i] != right._array[i])
			return false;
	}

	return true;
}

bool myIntArray::operator!=(const myIntArray & right) const {
	return !(*this == right);
}

int & myIntArray::operator[](int index) {
	//�������� ��������� �������
	if (index < 0 || index >= _size) {
		throw std::out_of_range("Index is out of range\n");
	}

	return _array[index];
}

const int & myIntArray::operator[](int index) const{
	//�������� ��������� �������
	if (index < 0 || index >= _size) {
		throw std::out_of_range("Index is out of range\n");
	}

	return _array[index];
}

//�������� ����� ��������� ����������
std::istream & operator>>(std::istream & input, const myIntArray & m_array) {
	for (int i = 0; i < m_array._size; i++) {
		
			if (input.fail()) {//��������� ����� ���������� ��������
				input.clear();
				input.ignore();
				std::cout << "Please enter integer value. Once again" << std::endl;
				i -= 2;
			}
			else {
			input >> m_array._array[i];
			}
					
	}

	return input;
}

//�������� ������ ���������� �� �����
std::ostream & operator<<(std::ostream & output, const myIntArray & m_array) {
	
	output << "Container[" << m_array._size << "]{";
	for (int i = 0; i < m_array._size; i++) {
		
		if (i == (m_array._size - 1)) {
			output << m_array._array[i];
		}
		else {
			output << m_array._array[i] << ", ";
		}

	}
	output <<"}";
	return output;
}

int myIntArray::getSize() const {
	return _size;
}

void myIntArray::reallocate(int length) {
	if (length <= 0) {
		throw std::length_error("Function \'reallocate\': Size must be bigger than 0\n");
	}
	
	//��������� ��������� ������� ������� �� ��� �� ������	
	if (length == _size) {
		std::cout << "reallocate(\"Container already have size " << _size<<"\")" << std::endl;
		return;
	}

	erase();
	_size = length;
	_array = new int[_size];
	
	for (int i = 0; i < _size; i++) {
		_array[i] = 0;
	}
}

void myIntArray::resize(int length) {
	if (length <= 0) {
		throw std::length_error("Function \'resize\': Size must be bigger than 0\n");
	}
	
	//��������� ��������� ������� ������� �� ��� �� ������
	if (length == _size) {	
		std::cout << "resize(\"Container already have size " << _size << "\")" << std::endl;
		return;
	}

	int * temp = new int[length];
	
	//����� ������ ������� �������� �� ������ ������ ��� ��� � ��� ������������ �������� ��� ��������� �� ����� ���� 0-�� �������
	//if (_length > 0) {} (���� � ��������� ������� �� ���������)

	const int elementsToCopy = (length > _size ? _size : length);
	
	for (int i = 0; i < elementsToCopy; i++) {
		temp[i] = _array[i];
	}
	if (length > _size) {// ���� ����������� ������ ������������� 0-� ����� ��������
		for (int i = elementsToCopy; i < length; i++) {
			temp[i] = 0;
		}
	}

	delete[] _array;
	_size = length;
	_array = temp;
}

void myIntArray::insertAt(int pos, int value) {
	if (pos < 0 || pos > _size) {
		throw std::out_of_range("Container can\'t insert element at this position (Index is out of range)\n");
	}
			
	int * temp = new int[_size+1];
	for (int i = 0; i < pos; i++) {
		temp[i] = _array[i];
	}

	temp[pos] = value;
	
	for (int i = pos; i < _size; i++) {
		temp[i+1] = _array[i];
	}

	delete[] _array;
	_array = temp;
	++_size;
}

void myIntArray::pushForward(int value) {
	insertAt(0, value);
}

void myIntArray::pushBack(int value) {
	insertAt(_size, value);
}

void myIntArray::popAt(int pos) {
	if (pos < 0 || pos >= _size) {
		throw std::out_of_range("Container can\'t delete element at this position (Index is out of range)\n");
	}

	if (_size == 1) {
		erase();
		return;
	}
	
	int * temp = new int[_size-1];
	for (int i = 0; i < pos; i++) {
		temp[i] = _array[i];
	}

	for (int i = pos+1; i < _size; i++) {
		temp[i - 1] = _array[i];
	}

	delete[] _array;
	_array = temp;
	--_size;
}

void myIntArray::popForward() {
	popAt(0);
}

void myIntArray::popBack() {
	popAt(_size-1);
}

void myIntArray::findElement(int index) const {
	if (index >= 0 && index < _size) {
		std::cout << "Container have element with index ["<< index <<"] = " << _array[index] << std::endl;
	}
	else {
		std::cout << "Container has no element with index [" << index << "]" << std::endl;
	}
}

int myIntArray::digitCount(int pos) const{	//���-�� ����������� ���������� ���� � ����� (����� ��� ���������� ���������)
	return std::log10(abs(_array[pos] + 1)) + 1;
}

void myIntArray::showArray() const{
	std::cout << "Container with ["<<_size<<"] elements:" << std::endl;
	
	for (int i = 0; i < _size; ++i) {
		
		int g = digitCount(i);
		
		for (int j = 0; j <= g; ++j) {
			std::cout << (char)205;
		}
	}

	std::cout << std::endl;
	
	for (int i = 0; i < _size; i++) {
		std::cout << _array[i] << (char)179;
	}
	
	std::cout << std::endl;
	
	for (int i = 0; i < _size; ++i) {

		int g = digitCount(i);

		for (int j = 0; j <= g; ++j) {
			std::cout << (char)205;
		}
	}

	std::cout << std::endl<<std::endl;
	
}

void myIntArray::initializeWithRandValues() {
	srand(time(NULL));
	for (int i = 0; i < _size; i++) {
		_array[i] = 1 + rand() % 1000;
	}
}

void myIntArray::sortArrayAsc() {
	int var = 0;

	for (int i = 0; i < _size - 1; i++) {
		for (int j = 0; j < _size - 1; j++) {
			if (_array[j] > _array[j + 1]) {
				var = _array[j];
				_array[j] = _array[j + 1];
				_array[j + 1] = var;
			}
		}
	}
}

void myIntArray::sortArrayDesc() {
	
	int var = 0;

	for (int i = 0; i < _size - 1; i++) {
		for (int j = 0; j < _size - 1; j++) {
			if (_array[j] < _array[j + 1]) {
				var = _array[j];
				_array[j] = _array[j + 1];
				_array[j + 1] = var;
			}
		}
	}
}