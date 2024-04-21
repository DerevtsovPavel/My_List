#include <vector>
#pragma once

template <typename e>
class InterfaceList {

	public:
		///���������� �������� � �����
		void virtual add(e x) = 0;

		///����� ������
	//	size_t virtual size() = 0;

		///�������� �� � �� ����� index
		void virtual insert(size_t index, e a) = 0;

		///������� ������� � ����� index
		void virtual del(size_t index) = 0;

		///��������� ���������� ��������
		void virtual resize(size_t count) = 0;

		///����� ������ �� ���� ��������, ��������������� �������� �
		std::vector<size_t> virtual find(e a)  = 0;
};