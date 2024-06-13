#include "myString.h"

myString myString::int2Str(int num)
{
	char int_str[12]; // 存储一个32位整数的数组
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

std::vector<int> myString::buildPrefixTable(const char* needle)
{
	int m = std::strlen(needle);
	std::vector<int> prefixTable(m, 0);
	int j = 0;

	for (int i = 1; i < m; ++i) {
		while (j > 0 && needle[i] != needle[j]) 
		{
			j = prefixTable[j - 1];
		}
		if (needle[i] == needle[j]) {
			++j;
		}
		prefixTable[i] = j;
	}
	return prefixTable;
}

char* myString::str_pos(char* haystack, char* needle)
{
	if (!*needle) {
		return haystack;
	}

	int n = std::strlen(haystack);
	int m = std::strlen(needle);

	if (m > n) {
		return nullptr;
	}

	std::vector<int> prefixTable = buildPrefixTable(needle);

	int j = 0;

	for (int i = 0; i < n; ++i) {
		while (j > 0 && haystack[i] != needle[j])
		{
			j = prefixTable[j - 1];
		}
		if (haystack[i] == needle[j]) {
			++j;
		}
		if (j == m) {
			return haystack + i - m + 1;
		}
	}
	return nullptr;
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
	char* pos = str_pos(buffer, other.buffer);
	if (!pos)
	{
		std::cout << "在字符串 " << buffer << " 中没有找到字符串 " << other.buffer << " 删除失败 ";
	}
	else {
		size_t index = pos - buffer;
		memmove(buffer + index, pos + other.length, length - index - other.length + 1);
		length -= other.length;
	}
	return *this;
}

myString myString::str_replace(char* old_sub, char* new_sub)
{
	char* pos = str_pos(buffer, old_sub);

	if (!pos) {
		std::cout << "在字符串 " << buffer << " 中没有找到字符串 " << old_sub << " 替换失败 ";
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

int myString::str_find(char* sub)
{
	char* pos = str_pos(buffer, sub);
	if (pos) {
		return pos - buffer;
	}
	std::cout << "在字符串 " << buffer << " 中没有找到字符串 " << sub << " 查找失败 ";
	return -1;
}


