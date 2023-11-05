// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class T>
class TVector
{
protected:
  T *pVector;
  int size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  T& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const T &val);   // прибавить скаляр
  TVector  operator-(const T &val);   // вычесть скаляр
  TVector  operator*(const T &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  T  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class T>
TVector<T>::TVector(int s, int si)
{
	//Новый код
	if ( (s < 0) || (s > MAX_VECTOR_SIZE) )
		throw s;
	if (si < 0) throw si;
	//if (size < StartIndex) throw (s);
	size = s;
	StartIndex = si;
	pVector = new T[size];
	for (int i = 0; i < size; i++) {
		pVector[i] = 0;
	}
} /*-------------------------------------------------------------------------*/

template <class T> //конструктор копирования
TVector<T>::TVector(const TVector<T> &v)
{
	pVector = new T[v.size];
	size = v.size;
	StartIndex = v.StartIndex;
	for (int i = 0; i < size; i++)
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class T>
TVector<T>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class T> // доступ
T& TVector<T>::operator[](int pos)
{
	if ((pos < 0) || (pos  > MAX_VECTOR_SIZE))
		throw ("Error index");
	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TVector<T>::operator==(const TVector &v) const
{
	if (v.size != size) return false;
	else {
		for (int i = 0; i < size; i++)
			if (pVector[i] != v.pVector[i]) return false;
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TVector<T>::operator!=(const TVector &v) const
{
	if (*this == v) return false;
	else
		return true;
} /*-------------------------------------------------------------------------*/

template <class T> // присваивание
TVector<T>& TVector<T>::operator=(const TVector &v)
{
	delete[] pVector;
	pVector = new T[v.size];
	StartIndex = v.StartIndex;
	size = v.size;
	for (int i = 0; i < size; i++)
		pVector[i] = v.pVector[i];
	return *this;
} /*-------------------------------------------------------------------------*/

template <class T> // прибавить скаляр
TVector<T> TVector<T>::operator+(const T &val)
{
	TVector<T> res(size);
	for (int i = 0; i < size; i++)
		res.pVector[i] = pVector[i] + val;
	return res;
} /*-------------------------------------------------------------------------*/

template <class T> // вычесть скаляр
TVector<T> TVector<T>::operator-(const T &val)
{
	TVector<T> res(size);
	for (int i = 0; i < size; i++) 
		res.pVector[i] = pVector[i] - val;
	return res;
} /*-------------------------------------------------------------------------*/

template <class T> // умножить на скаляр
TVector<T> TVector<T>::operator*(const T &val)
{
	TVector<T> res(size);
	for (int i = 0; i < size; i++) 
		res.pVector[i] = pVector[i] * val;
	return res;
} /*-------------------------------------------------------------------------*/

template <class T> // сложение
TVector<T> TVector<T>::operator+(const TVector<T> &v)
{
	if (v.size != size) throw ("Differnt sizes");
	TVector<T> res(size);
	for (int i = 0; i < size; i++)
		res.pVector[i] = pVector[i] + v.pVector[i];
	return res;
} /*-------------------------------------------------------------------------*/

template <class T> // вычитание
TVector<T> TVector<T>::operator-(const TVector<T> &v)
{
	if (v.size != size) throw ("Different sizes");
	TVector<T> res(size);
	for (int i = 0; i < size; i++)
		res.pVector[i] = pVector[i] - v.pVector[i];
	return res;
} /*-------------------------------------------------------------------------*/

template <class T> // скалярное произведение
T TVector<T>::operator*(const TVector<T> &v)
{
	if (v.size != size) throw ("Different sizes");
	T res = 0;
	for (int i = 0; i < size; i++)
		res = res + (v.pVector[i] * pVector[i]);
	return res;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class T>
class TMatrix : public TVector<TVector<T> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &m);                    // копирование
  TMatrix(const TVector<TVector<T> > &m); // преобразование типа
  bool operator==(const TMatrix &m) const;      // сравнение
  bool operator!=(const TMatrix &m) const;      // сравнение
  TMatrix& operator= (const TMatrix &m);        // присваивание
  TMatrix  operator+ (const TMatrix &m);        // сложение
  TMatrix  operator- (const TMatrix &m);        // вычитание
  
  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &m)
  {
    for (int i = 0; i < m.size; i++)
      in >> m.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &m)
  {
    for (int i = 0; i < m.size; i++)
      out << m.pVector[i] << endl;
    return out;
  }
};

template <class T>
TMatrix<T>::TMatrix(int s): TVector<TVector<T>>(s)
{
	if (s < 0 || s > MAX_MATRIX_SIZE)
		throw ("Wrong size");
	size = s;
	for (int i = 0; i < size; i++) {
		TVector<T> tmp(size - i, i);
		pVector[i] = tmp;
	}
} /*-------------------------------------------------------------------------*/

template <class T> // конструктор копирования
TMatrix<T>::TMatrix(const TMatrix<T> &m):
  TVector<TVector<T> >(m) {}

template <class T> // конструктор преобразования типа
TMatrix<T>::TMatrix(const TVector<TVector<T> > &m):
  TVector<TVector<T> >(m) {}


template <class T> // сравнение
bool TMatrix<T>::operator==(const TMatrix<T> &m) const
{
	if (size != m.size)
		return false;
	for (int i = 0; i < size; i++) {
		if (pVector[i] != m.pVector[i])
			return false;
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TMatrix<T>::operator!=(const TMatrix<T> &m) const
{	
	if (*this == m)
		return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class T> // присваивание
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T> &m)
{
	if (this == &m)
		return *this;
	if (size != m.size) {
		delete[] pVector;
		size = m.size;
		pVector = new TVector<T>[size];
	}
	for (int i = 0; i < size; i++) {
		pVector[i] = m.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class T> // сложение
TMatrix<T> TMatrix<T>::operator+(const TMatrix<T> &m)
{
	return TVector<TVector<T> > :: operator+(m);
} /*-------------------------------------------------------------------------*/

template <class T> // вычитание
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T> &m)
{
	return TVector<TVector<T> > :: operator-(m);

} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
