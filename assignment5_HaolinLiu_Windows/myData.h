#ifndef MYDATA_H_INCLUDED
#define MYDATA_H_INCLUDED

template<typename T>
struct myData {
	T val;
	myData<T> *addr = nullptr;
	
	myData() {
		val = 0;
		addr = nullptr;
	}
	myData(const T x) {
		val = x;
		addr = nullptr;
	}
};

template<typename T>
struct Cmp_by_val {
	bool operator () (myData<T> a, myData<T> b) {
		return a.val < b.val;
	}
};

template<typename T> 
struct Cmp_by_addr {
	bool operator ( ) (myData<T> a, myData<T> b) {
		return a.addr < b.addr;
	}
};

#endif // MYDATA_H_INCLUDED