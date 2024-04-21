#include <vector>
#pragma once

template <typename e>
class InterfaceList {

	public:
		///добавление элемента в конец
		void virtual add(e x) = 0;

		///вернёт размер
	//	size_t virtual size() = 0;

		///вставить эл а на место index
		void virtual insert(size_t index, e a) = 0;

		///удалить элемент с места index
		void virtual del(size_t index) = 0;

		///изменение доступного элемента
		void virtual resize(size_t count) = 0;

		///вернёт вектор из всех индексов, соответствующих элементу а
		std::vector<size_t> virtual find(e a)  = 0;
};