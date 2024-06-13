/* �ַ��������� */
#pragma once
#include <iostream>
#include <cstring>

class myString
{
	char* buffer; // �洢����ʱ�Ļ�����
	size_t buffer_size; // ��������С
	size_t length; // ��Ч���ݴ�С

	void resizeBuffer(size_t new_size)
	{
		char* new_buffer = new char[new_size * 2];
		memcpy(new_buffer, buffer, length +1);
		delete[] buffer;
		buffer = new_buffer;
		buffer_size = new_size * 2;
	}

	myString int2Str(int num);



public:
	myString(unsigned capacity = 16);

	myString(const char* str);

	myString(const myString& other);

	~myString();

	myString& operator+(const myString& other);

	myString& operator-(const myString& other);

	myString str_replace(const char* old_sub, const char* new_sub);

	int str_find(const char* sub) const;

	myString& operator+(const int num);

	friend std::ostream& operator<<(std::ostream& os, const myString& str) {
		os << str.buffer;
		return os;
	}
};