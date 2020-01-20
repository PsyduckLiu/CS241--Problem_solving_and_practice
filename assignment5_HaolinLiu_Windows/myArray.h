#ifndef MYARRARY_H_INCLUDED
#define MYARRARY_H_INCLUDED

template<typename Elem>

class myArray {
private:
	Elem *Array;
	int _size = 0;
	int _capacity = 10;

	void resize(int newsize) {
		Elem *newarray;
		newarray = new Elem[newsize];
		for (int i = 0; i < _size; i++) {
			newarray[i] = Array[i];
		}
		delete[] Array;
		Array = newarray;
		_capacity = newsize;
	}

public:
	myArray() {
		_size = 0;
		_capacity = 10;
		Array = new Elem[_capacity];
	}
	myArray(int size_of_array) {
		_size = size_of_array;
		_capacity = size_of_array;
		Array = new Elem[_size];
	}
	myArray(const myArray<Elem>&myarray) {
		_size = myarray._size;
		_capacity = myarray._capacity;
		Array = new Elem[_size];
		for (int i = 0; i < _size; i++) {
			Array[i] = myarray.Array[i];
		}
	}
	myArray(int size_of_array, const Elem& val) {
		_size = size_of_array;
		_capacity = size_of_array;;
		Array = new Elem[_size];
		for (int i = 0; i < _size; ++i)
			Array[i] = new Elem(val);
	}

	~myArray() {
		delete[] Array;
		_size = 0;
		_capacity = 0;
	}

	class iterator {	
	public:
		Elem *pos;
		iterator() = default;
		iterator(const iterator& other) {
			pos = other.pos;
		}
		iterator& operator=(const iterator& other) {
			pos = other.pos;
			return *this;
		}
		Elem& operator*() const {
			return *pos;
		}
		iterator& operator++() {
			++pos;
			return *this;
		}
		iterator operator++(int) {
			iterator tmp(*this);
			++pos;
			return tmp;
		}
		iterator& operator--() {
			--pos;
			return *this;
		}
		iterator operator--(int) {
			iterator tmp(*this);
			--pos;
			return tmp;
		}
		bool operator==(const iterator& other) const {
			return pos == other.pos;
		}
		bool operator!=(const iterator& other) const {
			return pos != other.pos;
		}
	};

	void push_back(const Elem& v) {
		if (_size == _capacity) {
			resize(2 * _capacity);
		}
		Array[_size] = v;
		_size++;
		
	}

	void pop_back() {
		_size--;
	}

	iterator begin() {
		iterator tmp;
		tmp.pos = Array;
		return tmp;
	}

	iterator end() {
		iterator tmp;
		tmp.pos = Array + _size - 1;
		return tmp;
	}

	int size() {
		return _size;
	}

	int capacity() {
		return _capacity;
	}

	Elem& operator [ ] (const int i) {
		return Array[i];
	}

	myArray& operator = (const myArray i) {
		delete[]Array;

		_size = i._size;
		_capacity = i._capacity;
		Array = new Elem[_size];
		for (int j = 0; j < _size; j++) {
			Array[j] = i.Array[j];
		}

		return *this;
	}

	Elem& operator= (const Elem i) {
		*this = i;
		return *this;
	}
};

#endif // MYARRARY_H_INCLUDED

	  
	 




