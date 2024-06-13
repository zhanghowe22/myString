#include <iostream>
#include "myString.h"


int main() {
	/* 1. “123456789” + “abc”  得到 “123456789abc” */
	myString str0("123456789");
	myString str1("abc");
	std::cout << "[1] " << str0 << " + " << str1 << " = ";
	std::cout << str0 + str1 << std::endl;

	/* “123456789” - “456”  得到 “123789” */
	myString str2("123456789");
	myString str3("456");
	std::cout << "[2] " << str2 << " - " << str3 << " = ";
	std::cout << str2 - str3 << std::endl;

	/* “123456789”  34修改为 abc 得到 12abc56789 */
	myString str4("123456789");
	std::cout << "[3] " << str4 << " ----> ";
	char char1[]{ "34" };
	char char2[]{ "abc" };
	std::cout << str4.str_replace(char1, char2) << std::endl;

	/* 123456 查 34 得到 34的位置 2 */
	myString str5("123456789");
	std::cout << "[4] " << str5 << " ----> ";
	char char3[]{ "34" };
	std::cout << str5.str_find(char3) << std::endl;

	/* 重载 = 实现 int 转 hstring 字符串 */
	myString str6("abcdef");
	int num_1 = 10000011;
	int num_2 = -10000011;
	std::cout << "[5] " << str6 << " + " << num_1 << " = ";
	std::cout << str6 + num_1 << std::endl;
	std::cout << "[6] " << str6 << " + " << num_2 << " = ";
	std::cout << str6 + num_2 << std::endl;
}
