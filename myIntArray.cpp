#include<iostream>
#include<cmath>
#include<ctime>	//библиотека нужна для инициализации элементов массива
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
		throw bad_length();
	}
	
	_size = length;
	_array = new int[_size];	//Добавь +INT_MAX к _size чтоб проверить catch с bad_array_new_length
		
	for (int i = 0; i < _size; i++) {
		_array[i] = 0;
	}
		
}

myIntArray::myIntArray(const myIntArray& init):_size(init._size) { //конструктор копирования
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
	if (&right != this) {				//проверка самоприсваивания
		if (_size != right._size) {
			delete[] _array;
			_size = right._size;
			_array = new int[_size];
		}
		for (int i = 0; i < _size; i++)
			_array[i] = right._array[i];
	}
	return *this;						//позволяет множественное присваивание 
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
	//проверка диапазона массива
	if (index < 0 || index >= _size) {
		throw bad_range();
	}

	return _array[index];
}

const int & myIntArray::operator[](int index) const{
	//проверка диапазона массива
	if (index < 0 || index >= _size) {
		throw bad_range();
	}

	return _array[index];
}

//операция ввода элементов контейнера
std::istream & operator>>(std::istream & input, const myIntArray & m_array) {
	for (int i = 0; i < m_array._size; i++) {
		
			if (input.fail()) {//обработка ввода нерверного значения
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

//операция вывода контейнера на экран
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
		throw bad_length();
	}
	
	//обработка изменения размера массива на тот же размер	
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
	std::cout<<"Container can\'t have 0 or less size!!!\n";
	return;
	}
	
	//обработка изменения размера массива на тот же размер
	if (length == _size) {	
		std::cout << "resize(\"Container already have size " << _size << "\")" << std::endl;
		return;
	}

	int * temp = new int[length];
	
	const int elementsToCopy = (length > _size ? _size : length);
	
	for (int i = 0; i < elementsToCopy; i++) {
		temp[i] = _array[i];
	}
	if (length > _size) {// если увеличиваем массив инициализирую 0-м новые элементы
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
		std::cout << "Container can\'t insert element at this position (Index is out of range)\n" << std::endl;
		return;
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

void myIntArray::deleteAt(int pos) {
	if (pos < 0 || pos >= _size) {
		std::cout << "Container can\'t delete element at this position (Index is out of range)\n" << std::endl;
		return;
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

void myIntArray::deleteFirst() {
	deleteAt(0);
}

void myIntArray::deleteLast() {
	deleteAt(_size-1);
}

void myIntArray::findValue(int value) const {
	int checked = 0;
	
	for (int i = 0; i < _size; i++) {
		if (value == _array[i]) {
			std::cout << "Element [" << i << "] = " << value << std::endl;
			checked++;
		}
	}
	if (checked > 0)
		return;
	else
	std::cout << "Container has no element with value = " << value << std::endl;
	
}

int myIntArray::digitCount(int pos) const{	//фун-ия определения количества цифр в числе (нужна для корректной отрисовки)
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

const char* bad_range::what() const noexcept{
	return "Error: Index is out of range";
}

const char * bad_length::what() const noexcept{
	return "Error: Size of container too small";
}