#pragma once

class myIntArray{
	friend std::ostream & operator<<(std::ostream & output, const myIntArray & m_array);
	friend std::istream & operator>>(std::istream & input, const myIntArray & m_array);

public:
	myIntArray();					//�� ��������� ������ ��������� �� 10 ���������
	myIntArray(int length);			//����������� �������� ���������� ������������� �������
	myIntArray(const myIntArray &);	//����������� �����������
	~myIntArray();

	const myIntArray& operator=(const myIntArray& right);	//�������� ������������
	bool operator==(const myIntArray & right) const;		//�������� ���������
	bool operator!=(const myIntArray & right) const;		//�������� ���������
	int & operator[](int index);							//�������� ����������
	const int & operator[](int index) const;				//�������� ���������� ��� ������������
	
	int getSize() const;
	void reallocate(int length);	//��������������� ����������
	void resize(int length);		//������� ������ ����������

	void insertAt(int pos, int value);	//������� � �������
	void pushForward(int value);		//������� � ������
	void pushBack(int value);			//������� � �����
	void popAt(int pos);				//�������� ��������
	void popForward();					//������� ������� � ������
	void popBack();						//������� ������� � �����
	
	int digitCount(int pos) const;
	void findElement(int index) const;
	void showArray() const;				//������� ������ �������
	void initializeWithRandValues();	//������������� ��������� ������� ������� �������
	void sortArrayAsc();
	void sortArrayDesc();
private:
	void erase();	//������� �������� �������
	
	int _size;
	int * _array;
};

