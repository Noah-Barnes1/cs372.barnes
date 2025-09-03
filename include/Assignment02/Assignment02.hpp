#pragma once
#include <chrono>
#include <iostream>
#include <vector>

template <typename t>;
class vector{
public:
	vector() {
		arr = new t[1];
		vCapacity = 1;
		length = 0;
	}
	vector(vector& obj) {
		this->arr = new t[obj.capacity()];
		for (int i = 0, i < obj.size(), i++) {
			this->put(i, obj.at(i));
		}
	}
	~vector() {
		delete[] arr;
		arr = nullptr;
	}
	void put(t data, int index) {
		if (index == vCapacity) {
			push_back(data);
		}
		else {
			arr[index] = data;
		}
	}
	void push_back() {
		if (length == vCapacity) {
			expand(2 * vCapicity);
		}
		arr[length] = data;
		length++;
	}
	t& at(int index) {
		if (index<0 || index>length) {
			std::cerr << "";
			exit(1);
		}
	}
private:
	t* arr = new t[1];
	int vCapacity = 1;
	int length = 1;
}
return 0;