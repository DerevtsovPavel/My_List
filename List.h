#include "Node.h"
#include "Interface.h"
#pragma once


///Класс односвязного списка, со встроенными методами.
template <typename e>
class List:InterfaceList<e> {
	private:
		Node<e>* head = nullptr;
		Node<e>* last = nullptr;
		Node<e>* count = nullptr;			//
		size_t size_l = 0;

		//меняем местами элементы 2х подмассивов от left до mid и от mid+1 до right
		template <typename el>
		void Merge(List<el> a, size_t left, size_t mid, size_t right) {
			size_t n = right - left + 1; //кол-во обмениваемых элементов
			size_t j = mid + 1;
			size_t l = left;
			List<el> buf(n); //буферный массив, в нём распологаем по возрастанию элементы

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
		///сортировка слиянием массива a. right - крайний правый индекс, left - левый индекс; average O(n log(n))
		template <typename el>
		void merge_sort(List<el> a, size_t right, size_t left = 0) {
			if (left >= right)
				return;
			size_t mid = (right + left) / 2;

			merge_sort(a, mid, left);
			merge_sort(a, right, mid + 1);
			Merge(a, left, mid, right); //меняем местами элементы 2х подмассивов
		}
	
	public:
		///конструктор
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
		
		/*
		~List() {
			if (head != nullptr)
				(*this).clear();
		}*/

		e& operator [](size_t index) {
			count = head;
			for (size_t i = 0; i < index; i++)
				count = count->next;
			return count->data;
		}

		///вернёт размер списка
		size_t size() const{
			return size_l;
		}

		///добавление в конец списка
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

		///вставить элемент x на место index
		void insert(size_t index, e x) override
		{
			Node<e>* a = new Node<e>;
			a->data = x;

			if (index == 0) //вставка в начало
			{
				a->next = head;
				head = a;
			}

			else if (index == size_l) { //вставка в конец
				last->next = a;
				last = a;
			}
			else { //вставка в середину
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

		///удалить элемент с позиции del
		void del(size_t index) override{
			if (index == 0) { //удалить первыйй
				Node<e>* a = head;
				head = head->next;
				delete a;
			}

			else if (index == size_l) { //удалить последний
				count = head;
				for (size_t i = 0; i < index - 1; i++)
					count = count->next;
				Node<e>* a = count->next;
				last = count;
				last->next = nullptr;
				delete a;
			}
			else { //удалить из середины
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

		///вернёт вектор из индексов, соответствующих эл-ту а
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


		///изменение размера списка
		void resize(size_t c) override {
			if (c > size_l) {
				while (c > size_l) {
					add(e()); // е() - стандартный конструктор для примитивных типов
				}
			}
			else {
				for (size_t i = 0; size_l>c; i++)
					del(size_l);
			}

		}

		///удалить весь список
		void clear() {
			while (head != nullptr)
				del(0);
			last = nullptr;
			size_l = 0;
		}

		///Конкатенация списков. Результат - третий список, сначала левый список, затем правый.
		List<e> operator + (List<e>& b) {

			List<e> F;
			for (size_t i = 0; i < size_l; i++)
				F.add((*this)[i]);
			for (size_t i = 0; i < b.size_l; i++)
				F.add(b[i]);

			return F;

		}

		///сортировка списка от меньшего к большему
		void sort() {
			merge_sort((*this), size_l - 1);
		}

		///развернёт последовательность
		void revers() {
			size_t z = size_l - 1;
			for (size_t i = 0; i < size_l/2; i++) {
				e q = (*this)[i];
				(*this)[i] = (*this)[z - i];
				(*this)[z - i] = q;
			}
			
		}
};
