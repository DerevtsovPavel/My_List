#include "Node.h"
#include "Interface.h"
#pragma once


///����� ������������ ������, �� ����������� ��������.
template <typename e>
class List:InterfaceList<e> {
	private:
		Node<e>* head = nullptr;
		Node<e>* last = nullptr;
		Node<e>* count = nullptr;			//
		size_t size_l = 0;

		//������ ������� �������� 2� ����������� �� left �� mid � �� mid+1 �� right
		template <typename el>
		void Merge(List<el>& a, size_t left, size_t mid, size_t right) {
			size_t n = right - left + 1; //���-�� ������������ ���������
			size_t j = mid + 1;
			size_t l = left;
			List<el> buf(n); //�������� ������, � �� ����������� �� ����������� ��������

			for (size_t i = 0; i < n; i++) {
				if (l <= mid and j <= right) {
					if (a[l] > a[j])
						buf[i] = a[j++];
					else
						buf[i] = a[l++];
				}
				else {
					if (l <= mid)
						buf[i] = a[l++];
					else
						buf[i] = a[j++];
				}
			}

			j = 0;
			for (size_t i = left; i <= right; i++)
				a[i] = buf[j++];
			buf.clear();
		}
		///���������� �������� ������� a. right - ������� ������ ������, left - ����� ������; average O(n log(n))
		template <typename el>
		void merge_sort(List<el>& a, size_t right, size_t left = 0) {
			if (left >= right)
				return;
			size_t mid = (right + left) / 2;

			merge_sort(a, mid, left);
			merge_sort(a, right, mid + 1);
			Merge(a, left, mid, right); //������ ������� �������� 2� �����������
		}

		///����� ��������� �� ������ � ����� STL
		class iterator {
			Node<e>* current; //���������, � ������� �������� ������������ �� ������
		public:
			iterator(Node<e>* c) { // ����������� � ����������
				current = c;
			}

			///���������� ��������� �����
			bool operator == (const iterator& x) const {
				return current == x.current;
			}

			///���������� ��������� �� �����
			bool operator != (const iterator& x) const {
				return current != x.current;
			}

			///���������� ��������� ������� � ������
			e& operator *() {
				return current->data;
			}

			///���������� ��������� ����������� ���������
			iterator operator ++(e) {
				iterator tmp(current);
				current = current->next;
				return tmp;
			}

			///���������� ��������� ���������� ���������
			iterator operator ++() {
				current = current->next;
				return current;
			}
		};
	
	public:
		///�����������
		List(size_t s = 0) {
			if (s > 0) {

				Node<e>* a = new Node<e>;
				head = a;
				count = a;
				last = a;
				size_l = 1;
				for (size_t i = 1; i < s; i++) {
					Node<e>* a = new Node<e>;
					count->next = a;
					count = a;
					last = a;
					size_l++;
				}
			}
			
		}
		
		List(List<e>& b) {
			for (size_t i = 0; i < b.size_l; i++)
				(*this).add(b[i]);

		}

		List(List<e>&& b){
			for (size_t i = 0; i < b.size_l; i++)
				(*this).add(b[i]);
		}
		
		~List() {
			if (head != nullptr)
				(*this).clear();
		}

		///��������, ����������� �� ������ ������
		iterator begin() {
			return iterator(head);
		}

		///��������, ����������� �� ����� ������
		iterator end() {
			return iterator(last->next);
		}
		e& operator [](size_t index) {
			if (index > size_l or head == nullptr)
				throw "������ ������� �� �������";
			else {
				count = head;
				for (size_t i = 0; i < index; i++)
					count = count->next;
				return count->data;
			}
		}

		//�������� ������������ ������������
		List<e>& operator = (List<e>& b) {
			while ((*this).size() != 0) {
				(*this).del(0);
			}

			for (size_t i = 0; i < b.size(); i++)
				(*this).add(b[i]);
			return *this;
		}

		//�������� ������������ ������������
		List<e>& operator = (List<e>&& b) {
			while ((*this).size() != 0) {
				(*this).del(0);
			}

			for (size_t i = 0; i < b.size(); i++)
				(*this).add(b[i]);
			return *this;
		}

		///����� ������ ������
		size_t size() const{
			return size_l;
		}

		///���������� � ����� ������
		void add(e x) override {
			Node<e>* a = new Node<e>;
			a->data = x;
			if (size_l == 0 or head == nullptr) {
				head = a;
				last = a;
				size_l = 1;
			}
			else {
				last->next = a;
				last = a;
				size_l++;
			}

		}

		///�������� ������� x �� ����� index
		void insert(size_t index, e x) override
		{
			Node<e>* a = new Node<e>;
			a->data = x;

			if (index == 0) //������� � ������
			{
				a->next = head;
				head = a;
			}

			else if (index == size_l) { //������� � �����
				last->next = a;
				last = a;
			}
			else { //������� � ��������
				count = head;
				for (size_t i = 0; i < index - 1; i++)
					count = count->next;

				Node<e>* n;

				n = count->next;
				count->next = a;
				count = count->next;
				count->next = n;

				n = nullptr;
				delete n;

			}
			size_l++;
		}

		///������� ������� � ������� del
		void del(size_t index) override{
			if (head == nullptr)
				throw "������ ����"; 
			else {
				if (index == 0) { //������� �������
					Node<e>* a = head;
					head = head->next;
					delete a;
				}

				else if (index == size_l) { //������� ���������
					count = head;
					for (size_t i = 0; i < index - 1; i++)
						count = count->next;
					Node<e>* a = count->next;
					last = count;
					last->next = nullptr;
					delete a;
				}
				else { //������� �� ��������
					count = head;
					for (size_t i = 0; i < index - 1; i++)
						count = count->next;
					Node<e>* a = count->next;
					count->next = a->next;
					a->next = nullptr;
					delete a;
				}
				size_l--;
			}
		}

		///����� ������ �� ��������, ��������������� ��-�� �
		std::vector<size_t> find(e x)  override{
			size_t ind = 0;
			count = head;
			std::vector<size_t> a;

			if (count->data == x) {
				a.push_back(ind);
			}

			while (count->next != nullptr) {
				count = count->next;
				ind++;
				if (count->data == x)
					a.push_back(ind);
			}
			return a;
			
		}


		///��������� ������� ������
		void resize(size_t c) override {
			if (c > size_l) {
				while (c > size_l) {
					add(e()); // �() - ����������� ����������� ��� ����������� �����
				}
			}
			else {
				for (size_t i = 0; size_l>c; i++)
					del(size_l);
			}

		}

		///������� ���� ������
		void clear() {
			while (head != nullptr)
				del(0);
			last = nullptr;
			size_l = 0;
		}

		///������������ �������. ��������� - ������ ������, ������� ����� ������, ����� ������.
		List<e> operator + (List<e>& b) {

			List<e> F;
			for (size_t i = 0; i < size_l; i++)
				F.add((*this)[i]);
			for (size_t i = 0; i < b.size_l; i++)
				F.add(b[i]);

			return F;

		}

		///���������� ������ �� �������� � ��������
		void sort() {
			merge_sort((*this), size_l - 1);
		}

		///�������� ������������������
		void revers() {
			size_t z = size_l - 1;
			for (size_t i = 0; i < size_l/2; i++) {
				e q = (*this)[i];
				(*this)[i] = (*this)[z - i];
				(*this)[z - i] = q;
			}
			
		}
};
