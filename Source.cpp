#include <vector>
#include <iostream>

using namespace std;

template <typename My_type>
class MyVector
{

public:

	MyVector();
	MyVector(const int set_size);
	MyVector(const int set_size, My_type value);
	MyVector(const MyVector& source);

	~MyVector();

	void My_pushback(My_type pushback_i);
	void My_erase(int from, int to);
	void My_insert(int where, int how_much, My_type value);
	void My_pop_back();

	void My_print();

	My_type& operator[](const int index);

private:

	My_type* ptr;
	unsigned my_size;
	unsigned my_capacity = 1;
	
	void Memory_check();
	void Memory_move();

};



int main()
{

	MyVector<char> a;
	a.My_pushback('4');

	a.My_print();

}

template <typename My_type>
void MyVector<My_type>::My_print()
{

	cout << " From print. Size = " << my_size << ", capacity = " << my_capacity << endl; 

	for (int j = 0; j < my_size; ++j) cout << j << "-th element: " << *(ptr + j) << ", adr = " << (&ptr + j) << endl;


}

template <typename My_type>
void MyVector<My_type>::My_pushback(My_type pushback_i)
{

	cout << "Pushback\n";

	Memory_check();

	*(ptr + my_size) = pushback_i;
	++my_size;

}

template <typename My_type>
void MyVector<My_type>::My_erase(int from, int to)			// erase elements, including both (from) and (to)
{

	My_type* ptr_tmp = new My_type[my_size - to];
	
	memcpy(ptr_tmp, ptr + (to + 1), (my_size - (to + 1)) * sizeof(My_type));			// always work
	memcpy(ptr + from, ptr_tmp, (my_size - (to + 1)) * sizeof(My_type));

	delete[] ptr_tmp;

	//memcpy(ptr + (from + 1), ptr + to, (my_size - to - 1) * sizeof(int));			// work sometimes

	my_size -= (to - from + 1);

	Memory_check();

}

template <typename My_type>
void MyVector<My_type>::My_insert(int where, int how_much, My_type value)
{

	my_size += how_much;
	Memory_check();

	memcpy(ptr + where + how_much, ptr + where, (my_size - (how_much + where)) * sizeof(My_type));		// Self-overwrite

	for (int i = 0; i < how_much; ++i) *(ptr + where + i) = value;

}

template <typename My_type>
void MyVector<My_type>::My_pop_back()
{

	--my_size;

	Memory_check();

}

template <typename My_type>
MyVector<My_type>::~MyVector()
{

	cout << "Destroyed\n";
	delete[] ptr;

}

template <typename My_type>
My_type& MyVector<My_type>::operator[](const int index)
{

	return ptr[index];

}


template <typename My_type>
void MyVector<My_type>::Memory_check()
{
	cout << "size = " << my_size << ", capacity = " << my_capacity << endl;

	if (my_size >= my_capacity)			// reserve is too small
	{
		do {
			my_capacity = my_capacity << 1;
		} while (my_size >= my_capacity);

		cout << "capacity is " << my_capacity << " now\n";
		Memory_move();
	}
	if (my_size < my_capacity >> 1)	// reserve is too big
	{
		do {
			my_capacity = my_capacity >> 1;
		} while (my_size < my_capacity >> 1);

		cout << "capacity is " << my_capacity << " now\n";
		Memory_move();
	}

}

template <typename My_type>
void MyVector<My_type>::Memory_move()
{

	My_type* ptr_tmp = new My_type[my_capacity];			// reserve new block of memory

	memcpy(ptr_tmp, ptr, my_size * sizeof(My_type));	// copy current to new

	delete[] ptr;									// delete current

	ptr = ptr_tmp;									// ptr rewrite



}

template <typename My_type>
MyVector<My_type>::MyVector()
{
	//my_capacity = 5;
	ptr = new My_type[my_capacity];
	//for (int j = 0; j < my_size; ++j) *(ptr + j) = 10;
	
}

template <typename My_type>
MyVector<My_type>::MyVector(const int set_size)
{
	my_size = set_size;
	my_capacity = 1;

	do {
		my_capacity = my_capacity << 1;
	} while (my_size >= my_capacity);

	ptr = new My_type[my_capacity];
	for (int j = 0; j < my_size; ++j) *(ptr + j) = 0;
}

template <typename My_type>
MyVector<My_type>::MyVector(const int set_size, My_type value)
{

	my_size = set_size;
	
	my_capacity = 1;

	do {
		my_capacity = my_capacity << 1;
	} while (my_size >= my_capacity);

	ptr = new My_type[my_capacity];
	for (int j = 0; j < my_size; ++j) *(ptr + j) = value;

}

template <typename My_type>
MyVector<My_type>::MyVector(const MyVector& source)
	: my_size (source.my_size), my_capacity (source.my_capacity)
{

	ptr = new My_type[my_capacity];

	for (int i = 0; i < my_size; ++i) *(ptr + i) = *(source.ptr + i);

}
