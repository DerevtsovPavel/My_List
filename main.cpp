#include <iostream>
#include "List.h"
#include "Test.h"
using namespace std;
int main() {
	Test();
	List<int> a(10);

	for (size_t i = 0; i < a.size(); i++)
		a[i] = i;

	for (size_t i = 0; i < a.size(); i++)
		cout << a[i] << " ";

	cout << "\n-------" << endl;

	List<int> b(8);
	for (size_t i = 0; i < b.size(); i++)
		b[i] = 2 * i;

	for (size_t i = 0; i < b.size(); i++)
		cout << b[i] << " ";

	cout << "\n-------" << endl;

	List<int> s;

	s = a + b;

	for (size_t i = 0; i < s.size(); i++)
		cout << s[i] << " ";

	cout << "\n-------" << endl;

	s.sort();

	for (size_t i = 0; i < s.size(); i++)
		cout << s[i] << " ";
	cout << "\n-------" << endl;

	s.revers();
	for (size_t i = 0; i < s.size(); i++)
		cout << s[i] << " ";
	cout << "\n-------" << endl;
}