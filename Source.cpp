#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

/* TO DO list

shrink to fit

reserve

pop_back

two-param constructor

template typename

copying constructor (?)

*/



class MyVector
{

public:

	MyVector();
	MyVector(const int set_size);

	~MyVector();

	void My_pushback(int pushback_i);
	void My_erase(int from, int to);
	void My_insert(int where, int how_much, int value);

	void My_print();

	int& operator[](const int index);

private:

	int* ptr;
	unsigned my_size;
	unsigned my_capacity=1;
	
	void Memory_check();
	void Memory_move();

};



int main()
{

	MyVector a;
	
	vector<int> b(5);
	
	

	a.My_print();

	a.My_pushback(0);

	a.My_print();

	a.My_pushback(0);

	a.My_print();

	cout << a[0] << endl;

	a.My_pushback(1);
	a.My_pushback(2);
	a.My_pushback(3);
	a.My_pushback(4);
	a.My_pushback(5);
	
	a.My_print();

	cout << "erase" << endl;

	a.My_erase(2, 3);
	a.My_print();

	a.My_insert(1, 5, 10);

	a.My_print();

}

void MyVector::My_print()
{

	for (int j = 0; j < my_size; ++j) cout << j << "-th element: " << *(ptr + j) << ", adr = " << (ptr + j) << endl;


}

void MyVector::My_pushback(int pushback_i)
{

	cout << "Pushback\n";

	Memory_check();

	*(ptr + my_size) = pushback_i;
	++my_size;

}

void MyVector::My_erase(int from, int to)
{

	/*int* ptr_tmp = new int[my_size - to];
	memcpy(ptr_tmp, ptr + to, (my_size - to) * sizeof(int));
	memcpy(ptr+from, ptr_tmp, (my_size - to) * sizeof(int));*/

	memcpy(ptr + from, ptr + to, (my_size - to) * sizeof(int));

	my_size -= (to - from);

	Memory_check();

}

void MyVector::My_insert(int where, int how_much, int value)
{

	my_size += how_much;
	Memory_check();

	memcpy(ptr + where + how_much, ptr + where, how_much * sizeof(int));		// Self-overwrite

	for (int i = 0; i < how_much; ++i) *(ptr + where + i) = value;

}

MyVector::~MyVector()
{

	delete[] ptr;

}

int& MyVector::operator[](const int index)
{

	return ptr[index];

}


void MyVector::Memory_check()
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

void MyVector::Memory_move()
{

	int* ptr_tmp = new int[my_capacity];			// reserve new block of memory

	memcpy(ptr_tmp, ptr, my_size * sizeof(int));	// copy current to new

	delete[] ptr;									// delete current

	ptr = ptr_tmp;									// ptr rewrite



}

MyVector::MyVector()
{
	//my_capacity = 5;
	ptr = new int[my_capacity];
	//for (int j = 0; j < my_size; ++j) *(ptr + j) = 10;
	
}

MyVector::MyVector(const int set_size)
{
	my_size = set_size;
	my_capacity = my_size + 5;
	ptr = new int[my_capacity];
	for (int j = 0; j < my_size; ++j) *(ptr + j) =15;
}
