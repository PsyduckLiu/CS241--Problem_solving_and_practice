#ifndef MYSORT_H_INCLUDED
#define MYSORT_H_INCLUDED

template <class Iterator>
void mySort(Iterator first, Iterator last) {
	if (first == last) return;
	else {
		for (Iterator i = first + 1; i != last; ++i)
			linear_insert(first, i, value_type(first));
	}
}

template <class Iterator, class T>
inline void linear_insert(Iterator first, Iterator last, T*) {
	T value = *last;
	if (value < *first) {
		copy_backward(first, last, last + 1);
		*first = value;
	}
	else    unguarded_linear_insert(last, value);
}

template <class Iterator, class T>
void unguarded_linear_insert(Iterator last, T value) {
	Iterator next = last;
	--next;
	while (value < *next) {
		*last = *next;
		last = next;
		--next;
	}
	*last = value;
}

template<typename Iterator, typename Compare>
void mySort(Iterator first, Iterator last, Compare comp) {
	Iterator p = first;
	Iterator q = last;
	--q;

	for (Iterator i = first, j = q; i != j;) {
		while (!(i == p || comp(*p, *i)))
			++i;
		if (i != p) {
			my_swap(*p, *i);
			p = i;
		}
		while (!(j == p || comp(*j, *p)))
			--j;
		if (j != p) {
			my_swap(*p, *j);
			p = j;
		}
	}
	Iterator it = first;
	++it;
	if (p != first && p != it)
		mySort(first, p, comp);
	it = p;
	++it;
	if (it != last && it != q)
		mySort(it, last, comp);
}


template<typename type>
void my_swap(type& a, type& b) {
	type c = a;
	a = b;
	b = c;
}

#endif // MYSORT_H_INCLUDED
