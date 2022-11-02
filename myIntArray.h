#pragma once
#include<exception>

class bad_range: public std::exception{
public:
	bad_range() = default;
	~bad_range() = default;

	virtual const char * what() const noexcept override;
};

class bad_length: public std::exception{
public:
	bad_length() = default;
	~bad_length() = default;

	virtual const char * what() const noexcept override;
};

class myIntArray{
	friend std::ostream & operator<<(std::ostream & output, const myIntArray & m_array);
	friend std::istream & operator>>(std::istream & input, const myIntArray & m_array);

public:
	myIntArray();					//по умолчанию создаю контейнер на 10 элементов
	myIntArray(int length);			//конструктор создания контейнера определенного размера
	myIntArray(const myIntArray &);	//конструктор копирования
	~myIntArray();

	const myIntArray& operator=(const myIntArray& right);	//оператор присваивания
	bool operator==(const myIntArray & right) const;		//оператор сравнения
	bool operator!=(const myIntArray & right) const;		//оператор сравнения
	int & operator[](int index);							//оператор индексации
	const int & operator[](int index) const;				//оператор индексации для константного
	
	int getSize() const;
	void reallocate(int length);	//переопределение контейнера
	void resize(int length);		//изменяю размер контейнера

	void insertAt(int pos, int value);	//вставка в позицию
	void pushForward(int value);		//вставка в начало
	void pushBack(int value);			//вставка в конец
	void deleteAt(int pos);				//удаление элемента
	void deleteFirst();					//удалить элемент в начале
	void deleteLast();						//удалить элемент в конце
	
	int digitCount(int pos) const;
	void findValue(int value) const;
	void showArray() const;				//функция показа массива
	void initializeWithRandValues();	//инициализация элементов массива разными числами
	void sortArrayAsc();
	void sortArrayDesc();
private:
	void erase();	//функция удаления массива
	
	int _size;
	int * _array;
};

