#include <iostream>
#include <limits>
#include <ctime>
#include <vector>
#include <string>

using namespace std;
typedef float T; // Change the type here

template <class T>
int Partition(vector<T> &A, int j, int low, int high) {
	int tmp = A[j];
	A[j] = A[low];
	A[low] = tmp;

	int pivot = A[low];
	while (low < high)
	{
		while (low < high && A[high] >= pivot) high--;
		A[low] = A[high];
		while (low < high && A[low] <= pivot)  low++;
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}

template<typename T>
void Quicksort(vector<T> &A, int low, int high) {
	if (low < high)
	{
		int middle = Partition(A, high, low, high);
		Quicksort(A, low, middle - 1);
		Quicksort(A, middle + 1, high);
	}
}

template<typename T>
T  Rselect(vector<T> &A, int k, int low, int high) {
		int res = 0;
		if (low == high) return A[low];
		if (low < high) { 
			int pivot_pos = Partition(A, low, low, high);
			if (pivot_pos + 1 == k)
				return A[pivot_pos];
			else if (pivot_pos + 1 > k)
				Rselect(A, k, low, pivot_pos - 1);
			else
				Rselect(A, k, pivot_pos + 1, high);
		}
		else		
			return  -1;
		
	
}

template<typename T>
int partition(vector<T> &A, int low, int high, T beginval) { 
	T temp;
	int beginpos;    
	for (int i = 0; low <= high - low + 1; ++i)        
		if (A[low + i] == beginval) { 
			beginpos = low + i;          
			break; 
		}    
	temp = A[low];    
	A[low] = A[beginpos];    
	A[beginpos] = temp;    
	temp = A[low];    
	while (low < high) { 
		while (A[high] >= temp && low < high) 
			--high;        
		A[low] = A[high];        
		while (A[low] <= temp && low < high) 
			++low;        
		A[high] = A[low]; 
	}    
	A[low] = temp;    
	return low; 
}

template<typename T>
T Dselect(vector<T> &A, int i, int low , int high) {
	T temp; 
	int j;
	if (high - low < 5) { 
		Quicksort(A, low, high);        
		return A[low + i - 1];
	}
	else { 
		int num = (high - low + 1) / 5;
		if (5 * num != high - low + 1)            
			++num;        
		for (j = 0; j < num - 1; ++j) { 
			Quicksort(A, low + j * 5, low + j * 5 + 4);            
			temp = A[low + j];            
			A[low + j] = A[low + j * 5 + 2];            
			A[low + j * 5 + 2] = temp; 
		}        
		Quicksort(A, low + j * 5,  high);        
		T midval = Dselect(A, num / 2, low, low + num);        
		int midpos = partition(A, low, high, midval);
		int ranking = midpos - low + 1;        
		if (i <= ranking)
			return Dselect(A, i, low, midpos);
		else           
			return Dselect(A, i - ranking,midpos + 1, high);
	}
	
}


int main()
{
	int x , r, round, i_th;
	char ch;
    int pos = 0;
	vector<int> a1;


	// Q1:
	cout << "--------------------------------- " << endl;
	cout << " Q1: Test Partition" << endl;
	cout << "--------------------------------- " << endl;

	cout << "How many times you want to test Partition?" << endl;
	cin >> round;
	// input 0 to skip this part
	for (int i = 0; i < round; ++i) {
		// clear the input buffer, no need to change.
		a1.clear();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		pos = 0;
		
		cout << "Input values: ";
		char ch = getchar();
		if (ch == '\n') {
			cout << "The input array is empty" << endl;
			continue;
		}
		else cin.putback(ch);
		while (cin >> x) {
			a1.push_back(x);
			pos += 1;
			if (getchar() == '\n')
			{
				break;
			}
		}

		cout << "Partition array by random select pivot" << endl;
		// to do :
		int n = pos;
		r = rand() % (n); // n is the size of current array
		cout << "the value of r is :" << r << endl;
		cout << "the value of A[r] is :" << a1.at(r) << endl;
		/*
		 * to do ：print r and A[r];
		 */
		Partition(a1, r, 0, --n);
		cout << "print the rearranged array:";
		for (int i = 0; i <= n; i++) {
			cout << a1[i]<<' ';
		}
		cout << endl;
		 /*
		  * to do : Partition array by A[r]
		  *         print the rearranged array
		  */	
	}


	// Q2:
	// clear the input buffer, no need to change.
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "--------------------------------- " << endl;
	cout << " Q2: Test Quicksort " << endl;
	cout << "--------------------------------- " << endl;

	cout << "How many times you want to test Quicksort?" << endl;
	cin >> round;
	// ----- input 0 to skip this part
	for (int i = 0; i < round; ++i) {
		// clear the input buffer, no need to change.
		a1.clear();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		pos = 0;

		cout << "Input values: ";
		char ch = getchar();
		if (ch == '\n') {
			cout << "The input array is empty" << endl;
			continue;
		}
		else cin.putback(ch);
		while (cin >> x) {
			a1.push_back(x);
			pos += 1;
			if (getchar() == '\n')
			{
				break;
			}
		}

		cout << "Sort Array" << endl;
		Quicksort(a1, 0, --pos);
		for (int i = 0; i <= pos; i++) {
			cout << a1[i] << ' ';
		}
		cout << endl;
		/*
		 *to do : quicksort
		 *        print the sorted array
		 */
	}


	// Q3:
    // clear the input buffer, no need to change.
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "--------------------------------- " << endl;
	cout << " Q3: Test Rselect " << endl;
	cout << "--------------------------------- " << endl;

	cout << "How many times you want to test Rselect?" << endl;
	cin >> round;
	//input 0 to skip this part
	for (int i = 0; i < round; ++i) {
		// clear the input buffer, no need to change.
		a1.clear();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		pos = 0;

		cout << "Input values: ";
		char ch = getchar();
		if (ch == '\n') {
			cout << "The input array is empty" << endl;
			continue;
		}
		else cin.putback(ch);
		while (cin >> x) {
			a1.push_back(x);
			pos += 1;
			if (getchar() == '\n')
			{
				break;
			}
		}

		// to do:
		int n = pos;
		i_th = rand() % (n)+1; // n is the size of current array
		cout << "select i-th smallest element" << endl;

		cout << "i-th is :" << i_th << endl;
		cout << "i-th value is :" << Rselect(a1, i_th, 0, --pos) << endl;

		/*
		 *to do : random selection
		 *        print i-th and i-th value
		 */
	}


	// Q4:
	// clear the input buffer, no need to change.
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "--------------------------------- " << endl;
	cout << " Q4: Test Dselect " << endl;
	cout << "--------------------------------- " << endl;

	cout << "How many times you want to test Dselect?" << endl;
	cin >> round;
	//input 0 to skip this part
	for (int i = 0; i < round; ++i) {
		// clear the input buffer, no need to change.
		a1.clear();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		pos = 0;

		cout << "Input values: ";
		char ch = getchar();
		if (ch == '\n') {
			cout << "The input array is empty" << endl;
			continue;
		}
		else cin.putback(ch);
		while (cin >> x) {
			a1.push_back(x);
			pos += 1;
			if (getchar() == '\n')
			{
				break;
			}
		}

		// to do :
		int n = pos;
		i_th = rand() % (n)+1; // n is the size of current array

		cout << "select i-th smallest element" << endl;
		cout << "i-th is :" << i_th << endl;
		cout << "i-th value is :" << Dselect(a1, i_th, 0, --pos) << endl;
		/*
		 *to do : deterministic selection
		 *        print i-th and i-th value
		 */
	}
                system("pause");
	return 0;
}