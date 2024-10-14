#include <assert.h>
#include "List.h"

#include <vector>
#pragma once


void Test() {

	List<int> a;
	assert(a.size() == 0);
	for (size_t i = 0; i < 8; i++)
		a.add(i);

	assert(a.size() == 8);

	for (size_t i = 0; i < a.size(); i++)
		assert(a[i] == i);

	a.insert(0, -2);
	assert(a[0] == -2);

	a.insert(4, -1);
	assert(a[4] == -1);

	assert(a[5] == 3);

	a.insert(a.size()-1, -5);
	assert(a.size() == 11);
	assert(a[a.size() - 2] == -5);


	a.del(0);
	assert(a[0] == 0);
	a.del(3);
	assert(a[3] == 3);
	a.del(a.size() - 2);
	assert(a[7] == 7);

	a.add(5);

	std::vector<size_t> f = a.find(5);

	assert(f[0] == 5);
	assert(f[1] == 8);

	a.resize(5);
	assert(a.size() == 5);
	assert(a[4] == 4);

	a.resize(10);
	assert(a.size() == 10);

	for (size_t i = 0; i < a.size(); i++)
		a[i] = i;

	assert(a[9] == 9);

	List<int> b(5);
	for (size_t i = 0; i < b.size(); i++)
		b[i] = i * 2;

	List<int> s;
	 s = a + b;

	assert(s.size() == 10 + 5);

	assert(s[0] == a[0]);
	assert(s[10] == b[0]);
	assert(s[14] == b[4]);

	s.clear();
	a.clear();
	b.clear();

	List<int> m(8);

	m[0] = 49;
	m[1] = 1;
	m[2] = -3;
	m[3] = 0;
	m[4] = 81;
	m[5] = -100;
	m[6] = 9;
	m[7] = 11;

	m.sort();

	assert(m[0] == -100);
	assert(m[1] == -3);
	assert(m[2] == 0);
	assert(m[3] == 1);
	assert(m[4] == 9);
	assert(m[5] == 11);
	assert(m[6] == 49);
	assert(m[7] == 81);

	try {
		s[20];
		assert(0); // проверка если исключение не будет брошено
	}
	catch (const char* f) {
		assert(f == "Ошибка доступа по индексу");
	}

	try {
		s.del(0);
		assert(0);
	}
	catch (const char* f) {
		assert(f == "Список пуст");
	}

	List<int> it(8);

	for (int i = 0; i < 8; i++) {
		it[i] = i;
	}

	int j = 0;
	for (int i : it) {
		assert(i == j++);
	}

	it.add(8);

	j = 0;
	for (int i : it) {
		assert(i == j++);
	}
}