#include <chrono>
#include <iostream>

template <typename t>;
class vector{
public:
	void put(t data, int index);
	void push_back(t data);
	t at(int index);
	int size();
	int capacity();
	void traverse();
private:
	t* arr = new t[1];
	int vCapacity = 1;
	int length = 1;
	vector() {
		arr = new t[1];
		vCapacity = 1;
		length = 1;
	}
	~vector() {
		delete[] arr;
		arr = nullptr;
	}
}
return 0;