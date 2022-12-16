// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <ctime> 

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;


// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > 100000000)
      throw out_of_range("Vector size should be greater than zero and less than 100000000");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    if (sz == 0 || sz > 100000000)
        throw out_of_range("Array size should be greater than zero and less than 100000000");
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      if (sz != v.sz) 
      {
          T* p = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = p;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      sz = 0;
      delete[] pMem;
      pMem = nullptr;
      swap(*this, v);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  //заполнение случайными числами (int)
  void set_rand_vector()
  {
      srand(time(0));
      for (size_t i = 0; i < sz; i++)
          (*this)[i] = rand() % 200 - 100;
  }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= 0 && ind < MAX_VECTOR_SIZE)
          return pMem[ind];
      else
          throw out_of_range("Index out of range");
  }
  const T& at(size_t ind) const
  {
      if (ind >= 0 && ind < MAX_VECTOR_SIZE)
          return pMem[ind];
      else
          throw out_of_range("Index out of range")
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return 0;
      for (size_t i = 0; i < v.sz; i++)
          if ((*this)[i] != v[i])
              return 0;
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp[i] += val;
      return tmp;
  }
  TDynamicVector operator-(double val)
  {
      double tmp = -val;
      return (*this) + tmp;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp[i] *= val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw exception("Sizes of vectors should be equal");
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < v.sz; i++)
          tmp[i] = (*this)[i] + v[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw exception("Sizes of vectors should be equal");
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < v.sz; i++)
          tmp[i] = (*this)[i] - v[i];
      return tmp;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) throw exception("Sizes of vectors should be equal");
      T tmp = 0;
      for (size_t i = 0; i < v.sz; i++)
      tmp += (*this)[i] * v[i];
      return tmp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << "  "; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if(s >= MAX_MATRIX_SIZE)
        throw out_of_range("Matrix size should be less than 10000");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  //заполнение случайными числами (int)
  void set_rand_matrix() 
  {
      srand(time(0));
      for (size_t i = 0; i < sz; i++)             //почему то при вызове set_rand_vector                                      
          for (size_t j = 0; j < sz; j++)         //заполняет все строки одним и тем же случаным вектором  
              (*this)[i][j] = rand() % 200 - 100;
  }

  //гетер размера
  size_t size() const noexcept { return sz; }

  // индексация с контролем
  T& at(int ind1, int ind2)
  {
      if (ind1 < 0 || ind1 >= MAX_MATRIX_SIZE || ind2 < 0 || ind2 >= MAX_MATRIX_SIZE)
         throw out_of_range("Index out of range");
      return (*this)[ind1][ind2];    
  }


  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = (*this)[i] * val;
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = (*this)[i] * v;
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      //if (sz != m.sz)
      //    throw exception("Sizes of matrices should be equal");
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = (*this)[i] + m[i];
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      //if (sz != m.sz)
         // throw exception("Sizes of matrices should be equal");
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = (*this)[i] - m[i];
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw exception("Sizes of matrices should be equal");
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) 
          for (size_t j = 0; j < sz; j++) 
              for (size_t k = 0; k < sz; k++) 
                  tmp[i][j] += (*this)[i][k] * m.pMem[k][j];
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          for (size_t j = 0; j < v.sz; j++)
              istr >> v[i][j];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
        {
            for (size_t j = 0; j < v.sz; j++)
                ostr << v[i][j] << "\t";
            ostr << " \n";
        }
        return ostr;
  }
};

#endif
