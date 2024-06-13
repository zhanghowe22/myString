#include "myString.h"

myString myString::int2Str(int num)
{
	char int_str[12]; // �洢һ��32λ����������
	int len = 0;
	bool is_negative = num < 0;
	if (is_negative) {
		num = -num;
	}
	do
	{
		int_str[len++] = '0' + (num % 10);
		num /= 10;
	} while (num > 0);

	if (is_negative) {
		int_str[len++] = '-';
	}

	for (int i = 0; i < len / 2; ++i)
	{
		std::swap(int_str[i], int_str[len - i - 1]);
	}
	int_str[len] = '\0';

	myString ret_str(int_str);

	return ret_str;
}

myString::myString(unsigned capacity)
{
	length = 0;
	buffer_size = capacity;
	buffer = new char[capacity];
	buffer[0] = '\0';
}

myString::myString(const char* str)
{
	length = strlen(str);
	buffer_size = length + 1;
	buffer = new char[buffer_size];
	memcpy(buffer, str, length + 1);
}

myString::myString(const myString& other)
{
	length = other.length;
	buffer_size = other.buffer_size;
	buffer = new char[buffer_size];
	memcpy(buffer, other.buffer, length + 1);
}

myString::~myString()
{
	delete[] buffer;
}

myString& myString::operator+(const myString& other)
{
	if (other.length > buffer_size - length) {
		resizeBuffer(other.length + length + 1);
	}
	memcpy(buffer + length, other.buffer, other.length + 1);
	length = other.length + length;
	return *this;
}

myString& myString::operator+(const int num)
{
	myString int_str = int2Str(num);
	return *this + int_str;
}

myString& myString::operator-(const myString& other)
{
	char* pos = std::strstr(buffer, other.buffer);
	if (!pos)
	{
		std::cout << "���ַ��� " << buffer << " ��û���ҵ��ַ��� " << other.buffer << " ɾ��ʧ�� ";
	}
	else {
		size_t index = pos - buffer;
		memmove(buffer + index, pos + other.length, length - index - other.length + 1);
		length -= other.length;
	}
	return *this;
}

myString myString::str_replace(const char* old_sub, const char* new_sub)
{
	char* pos = std::strstr(buffer, old_sub);

	if (!pos) {
		std::cout << "���ַ��� " << buffer << " ��û���ҵ��ַ��� " << old_sub << " �滻ʧ�� ";
		return "";
	}

	size_t pos_index = pos - buffer;

	size_t old_len = strlen(old_sub);
	size_t new_len = strlen(new_sub);
	size_t new_total_length = length - old_len + new_len;
	if (new_total_length >= buffer_size) {
		resizeBuffer(new_total_length + 1);
	}

	std::memmove(buffer + pos_index + new_len, buffer + pos_index + old_len, length - pos_index - old_len + 1);

	std::memcpy(buffer + pos_index, new_sub, new_len);

	length = new_total_length;

	return *this;
}

int myString::str_find(const char* sub) const
{
	char* pos = std::strstr(buffer, sub);
	if (pos) {
		return pos - buffer;
	}
	std::cout << "���ַ��� " << buffer << " ��û���ҵ��ַ��� " << sub << " ����ʧ�� ";
	return -1;
}


