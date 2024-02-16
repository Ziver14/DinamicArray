#include<iostream>
/*!
\brief Шаблонный класс динамической коллекции представляющий собой динамический 
массив, которая имеет возможность работать через std::size и range based for
*/

template<typename T>

class DynamicArray {
public:
	DynamicArray() :data_(nullptr), size_(0), capacity_(0) {};//\details Конструктор по умолчанию который заолняет все поля нулями,
															  //а указатель data_ переводит на позицию nullptr

	DynamicArray(const DynamicArray<T>& other) //! Конструктор копирования который выполняет копирование
											   //!элементов из объекта DynamicArray в текущий объект
	{
		size_ = other.size_;          //!присваивает текущему объекту размер другого объекта 'other'
		capacity_ = size_;			  //!устанавливает емкость текущего объекта равной размеру
		data_ = nullptr;              //!инициализирует указатель на массив элементов значением nullptr
		if (size_ != 0)				  //!если размер не равен 0, то выделяет память для массива размером 'size_'
			data_ = new T[size_];	
		else						  //!иначе, устанавливает указатель на массив в значение '0'
			data_ = 0;				
		for (int i = 0; i < size_;i++)//! копирует элементы из массива 'other.data_' в 
			data_[i] = other.data_[i];//! массив 'data_'
	}

	DynamicArray(size_t size)		  //! создает массив с указанным размером 'size'
	{
		size_ = size;				  //!переданное значение  'size' в конструктор присваивается переменной 'size_' котрая 
									  //!является текущим размером массива
		capacity_ = size;			  //! так же переданное значение 'size' присваивается переменной 'capacity_',
									  //!которая представляет текущую емкость массива
		if (size != 0)				  //! если массив имеет размер больше 0, то выделяется память для 
									  //!массива data_ размером size
			data_ = new T[size];
		else                          //!если размер массива равен 0, то 'data'
			data_ = 0;				  //!устанавливается в nullptr

	}
	/*!\brief
	Указатель на начало массива нужен чтобы использовать цикл 'for'
	с использованием оператора range
	\return возвращает указатель на начало массива 'data_'
	*/
	T* begin()  {					
		return data_;
	 }
	/*!\brief
	Указатель на конец массива нужен чтобы использовать цикл 'for'
	с использованием оператора range
	\return возвращает указатель на конец массива 'data_'
	*/
	T* end() const {
		return (size_ + data_);
	}
	/*!\brief Метод вставляет передаваемое значение в конец массива
	
	Если размер массива равен вместимости, то увелмчивает вместимость в два раза(в два раза
	чтобы очень часто не увеличивать размер вместимости)*/
	void push_back(T value) 
	{
		if (size_ == capacity_) {
			capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
			T* new_data = new T[capacity_];
			for (int i = 0; i < size_; i++) {
				new_data[i] = data_[i];
			}
			delete[] data_;
			data_ = new_data;
		}
		data_[size_++] = value;
	}

	/*!\brief Удаляет последний элемент из массива
	Если массив не пустой то уменьшает его размер на единицу
	*/
	void pop_back() {
		if (size_ > 0) {
			size_--;
		}
	}
	/*!\brief
	Метод добавляет элемент в указанную позицию
	
	Если указанная позиция больше размера массива кидает исключение
	
	Если вместимость заполненна, то увеличивет ее в два раза
	
	*/
	void Insert(size_t index, const T& value)
	{
		if (index > size_) {
			throw - 1; 
		}
		if (size_ == capacity_) {
			capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
			T* new_data = new T[capacity_];
			for (int i = 0; i < size_; i++) {
				new_data[i] = data_[i];
			}

			new_data[index] = value;
			for (size_t i = index; i < size_; i++) {
				new_data[i + 1] = data_[i];
			}
			delete[]data_;
			data_ = new_data;
		}
		else {
			for (size_t i = size_; i > index; i--) {
				data_[i] = data_[i - 1];
			}
			data_[index] = value;
		}
		size_++;
			
		
	}
	/*!\brief
	Возвращает размер массива так же аозваляет работать через std::size

	\return Размер массива
	*/
	int size() const 
	{
		return size_;
	}



	/*!\brief Перегруженный оператор для доступа к элементам массива
	
	\return Ссылка на элемент массива с указанным индексом
	*/
	T& operator [](size_t index) {
		return data_[index];
	}

	/*!\brief Перегруженный оператор для доступа к элементам массива

	\return Константная ссылка на элемент массива с указанным индексом
	*/
	const T& operator[](size_t index) const {
		return data_[index];
	}

	/*! brief Деструктор класса
	
	Освобождает память, занятую массивом*/
	~DynamicArray() {
		if (data_)
			delete[]data_;
	}
private:
	T* data_;			///! Указатель на массив элементов
	size_t capacity_;   ///!Вместимость массива
	size_t size_;		///! Размер массива
	

};


int main() {
	setlocale(LC_ALL, "ru");

	DynamicArray<int> arr1;

	arr1.push_back(2);
	arr1.push_back(4);
	arr1.push_back(3);
	arr1.push_back(5);
	arr1.push_back(12);
	arr1.Insert(2, 5);
	arr1.pop_back();

	std::cout <<"Размер массива-> " << std::size(arr1)<<'\n';

	for (const auto&i:arr1) {
		std::cout << i << ' ';
	}
	

	return 0;
}