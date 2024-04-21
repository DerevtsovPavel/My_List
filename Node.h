//Автор: Деревцов Павел ВМК-22
#pragma once


///класс узла
template <typename e>
class Node {
public:
	e data;
	Node* next = nullptr;
};