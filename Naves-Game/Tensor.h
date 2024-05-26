#pragma once
#include <stdexcept>
#include <initializer_list>
#include <cmath>
#include <ctime>

template <typename T>
class Tensor
{
private:
	T* data;
	int n_size;
public:
	Tensor();
	Tensor(const Tensor& other);
	Tensor(std::initializer_list<T> values);
	~Tensor();
	T& operator[](int index);
	bool operator==(const Tensor& other) const;
	void resize(int s);
	void resize_value(int s, T value);
	void push(T d);
	void push_if_not(T d);
	void pop(std::initializer_list<int> pots);
	void pop(Tensor<int> pots);
	int size();
};

template<typename T>
inline Tensor<T>::Tensor() : data(nullptr), n_size(0)
{
}

template<typename T>
inline Tensor<T>::Tensor(const Tensor& other) : data(nullptr), n_size(0)
{
	this->resize(other.n_size);
	for (int i = 0; i < this->n_size; i++)
	{
		this->data[i] = other.data[i];
	}
}

template<typename T>
inline Tensor<T>::Tensor(std::initializer_list<T> values) : data(nullptr), n_size(0)
{
	this->resize(values.size()); int i = 0;
	for (const T& val : values)
	{
		this->data[i++] = val;
	}
}

template<typename T>
inline Tensor<T>::~Tensor()
{
}

template<typename T>
T& Tensor<T>::operator[](int index)
{
	if (index < 0 || index >= this->n_size) {
		throw std::out_of_range("Error Index Range");
	}
	return this->data[index];
}

template<typename T>
inline bool Tensor<T>::operator==(const Tensor& other) const
{
	bool value_return = true;
	if (this->n_size != other.n_size) value_return = false;
	else {
		for (int i = 0; i < this->n_size; i++) {
			if (this->data[i] != other.data[i]) {
				value_return = false;
				break;
			}
		}
	}
	return value_return;
}

template<typename T>
void Tensor<T>::resize(int s)
{
	if (s < 0) throw std::out_of_range("Error Negative");
	if (this->data != nullptr) delete[] this->data;
	this->data = new T[s];
	this->n_size = s;
}

template<typename T>
inline void Tensor<T>::resize_value(int s, T value)
{
	this->resize(s);
	for (int i = 0; i < this->n_size; i++)
	{
		this->data[i] = value;
	}
}

template<typename T>
inline void Tensor<T>::push(T d)
{
	T* aux;
	aux = new T[this->n_size + 1];
	for (int i = 0; i < this->n_size; i++)
	{
		aux[i] = this->data[i];
	}
	aux[this->n_size] = d;
	if (this->data != nullptr) delete[]this->data;
	this->data = aux;
	this->n_size++;
}

template<typename T>
inline void Tensor<T>::push_if_not(T d)
{
	bool value_not_find = true;
	for (int i = 0; i < this->n_size; i++)
	{
		if (this->data[i] == d) {
			value_not_find = false;
			break;
		}
	}
	if (value_not_find) this->push(d);
}

template<typename T>
inline void Tensor<T>::pop(std::initializer_list<int> pots)
{
	T* temp = new T[(this->n_size - pots.size())];
	int counter = 0;
	for (int i = 0; i < this->n_size; i++)
	{
		bool value_find = true;
		for (const int& pot : pots)
		{
			if (pot == i) value_find = false;
		}
		if (value_find) temp[counter++] = this->data[i];
	}
	if (this->data != nullptr) delete[] this->data;
	this->data = temp;
	this->n_size -= pots.size();
}

template<typename T>
inline void Tensor<T>::pop(Tensor<int> pots)
{
	T* temp = new T[(this->n_size - pots.size())];
	int counter = 0;
	for (int i = 0; i < this->n_size; i++)
	{
		bool value_find = true;
		for (int j = 0; j < pots.size(); j++)
		{
			if (pots[j] == i) value_find = false;
		}
		if (value_find) temp[counter++] = this->data[i];
	}
	if (this->data != nullptr) delete[] this->data;
	this->data = temp;
	this->n_size -= pots.size();
}

template<typename T>
int Tensor<T>::size()
{
	return this->n_size;
}