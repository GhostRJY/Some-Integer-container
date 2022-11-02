#include<iostream>
#include"myIntArray.h"


int main() {
	const int size = 10;
	
	try {
		//для проверки введите отрицательное значение или 0 
		//(если ввести INT_MAX+1 сработает обрабртчик на отрицательное значение, поэтому в самом конструкторе )
		//поэтому в самом конструкторе нужно выделить память для большого кол-ва элементов чтоб сработал -catch (std::bad_array_new_length & error)-
		myIntArray arr(1);
		arr[0] = 1;				//для проверки введите индекс -1 или >=size
		arr.reallocate(size);	//укажите в качестве аргумента size для внутренней обработки или отрицательное значение для обработчика исключений
		
		arr.resize(3);			//укажите в качестве аргумента size для внутренней обработки или отрицательное значение для обработчика исключений
		arr.insertAt(3, 10);	//укажите в качестве первого параметра отрицательное или size +1
		arr.pushBack(7);
				
		arr.deleteAt(4);		//укажите в качестве параметра отрицательное или size
		arr.showArray();
		
		arr.pushForward(2);		//вставка элемента вперед
		arr.pushBack(3);		//вставка элемента в конец
		arr.showArray();
		
		arr.deleteFirst();		//удаление первого элемента
		arr.deleteLast();			//удаление последнего элемента
		arr.showArray();
		
		arr.findValue(3);		//поиск элемента со значением
		arr.findValue(0);

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
		//arr[0] = 15;	//убрать комментарий чтоб было неравенство или изменить размер одного из сравниваемых
		if (arr3 == arr) {
		std::cout << std::endl << "arr3 == arr" << std::endl;
		}
		else {
		std::cout << std::endl << "arr3 != arr" << std::endl;
		}

		//инициализация контейнера псевдо случайными числами
		arr.initializeWithRandValues();	
		arr.showArray();

		//Сортировка контейнера
		std::cout << std::endl << "\nLets sort our array\nAscending" << std::endl;
		arr.sortArrayAsc();
		arr.showArray();
		std::cout << std::endl << "Descending" << std::endl;
		arr.sortArrayDesc();
		arr.showArray();
		
		//ввод значений элементам контейнера
		std::cout << std::endl << "Input "<<arr.getSize()<<" values for elements of container: ";
		std::cin >> arr;
		std::cout << std::endl<<arr<<std::endl;
	}
	catch (bad_range & error) {
		std::cout << error.what() << std::endl;
	}
	catch (bad_length & error) {
		std::cout << error.what() << std::endl;
	}
	catch (std::bad_array_new_length & error) {	// Добавь в конструкторе побольше элементов для выделения памяти чтоб проверить
		std::cout << error.what() << std::endl;
	}
	catch (...) {
		std::cout << "Uknown error!!!" << std::endl;
	}
	
	return 0;
}