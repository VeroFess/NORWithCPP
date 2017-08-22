#include <string>
#include <iostream>
#include <iomanip>
#include <functional>

#include "NOR.h"

using namespace std;

typedef function<int(int, int)> calcfunction;

void printresult(string type, calcfunction function1, calcfunction function2, int number1, int number2) {
	int result1 = function1(number1, number2);
	int result2 = function2(number1, number2);
	cout << setbase(16) << "test of " << type << " (number 1 = " << number1 << ",  number 2 = " << number2 << "), result of nor is " << result1 << " , org c is " << result2 << (result1 == result2 ? "....pass!" : "....error!") << endl;
}

int main() {
	cout << "Begin mathematical calculation test" << endl;
	printresult("add", NOR::nor_add, [](int a, int b) { return a + b; }, 0x0fff0001, 0x000fff01);
	printresult("add", NOR::nor_sub, [](int a, int b) { return a - b; }, 0x0fff0001, 0x000fff01);
	printresult("mul", NOR::nor_mul, [](int a, int b) { return a * b; }, 0x0fff0001, 0x000fff01);
	printresult("div", NOR::nor_div, [](int a, int b) { return a / b; }, 0x0fff0001, 0x000fff01);
	cout << "Begin logical calculation test" << endl;
	printresult("xor", NOR::nor_xor, [](int a, int b) { return a ^ b; }, 0x0fff0001, 0x000fff01);
	printresult("and", NOR::nor_and, [](int a, int b) { return a & b; }, 0x0fff0001, 0x000fff01);
	printresult("not", [](int a, int b) { return NOR::nor_not(a); }, [](int a, int b) { return ~a; }, 0x0fff0001, 0);
	printresult("or", NOR::nor_or, [](int a, int b) { return a | b; }, 0x0fff0001, 0x000fff01);
	system("pause");
}