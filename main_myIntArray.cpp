#include<iostream>
#include"myIntArray.h"


int main() {
	const int size = 10;
	
	try {
		//для проверки введите отрицательное значение или 0 
		//(если ввести INT_MAX+1 сработает обрабртчик на отрицательное значение, поэтому в самом конструкторе )
		//поэтому в самом конструкторе нужно выделить память для большого кол-ва элементов чтоб сработал -catch (std::bad_array_new_length & error)-
		myIntArray arr(size);
		
		arr[0] = 1;				//для проверки введите индекс -1 или >=size
		arr.reallocate(size);	//укажите в качестве аргумента size для внутренней обработки или отрицательное значение для обработчика исключений
		arr.resize(5);			//укажите в качестве аргумента size для внутренней обработки или отрицательное значение для обработчика исключений
		arr.insertAt(5, 10);	//укажите в качестве первого параметра отрицательное или size+1 
		arr.popAt(5);		//укажите в качестве параметра отрицательное или size+1
		
		arr.pushForward(2);		//вставка элемента вперед
		arr.pushBack(3);		//вставка элемента в конец
		arr.showArray();
		
		arr.popForward();		//удаление первого элемента
		arr.popBack();			//удаление последнего элемента
		arr.showArray();

		arr.initializeWithRandValues();	//инициализация контейнера псевдо случайными числами
		arr.showArray();

		arr.findElement(19);		//поиск элемента по индексу
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
		
		//arr[0] = 15;	//убрать комментарий чтоб было неравенство или изменить размер одного из сравниваемых
		if (arr3 == arr) {
			std::cout << std::endl << "arr3 == arr" << std::endl;
		}
		else {
			std::cout << std::endl << "arr3 != arr" << std::endl;
		}

		//Сортировка контейнера
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
	catch (std::bad_array_new_length & error) {	// Добавь в конструкторе побольше элементов для выделения памяти чтоб проверить
		std::cout << error.what() << std::endl;
	}
	
	return 0;
}