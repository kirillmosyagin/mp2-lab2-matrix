// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------
void matrix_input(int choice, TDynamicMatrix<int>& m)
{
    switch (choice)
    {
    case 1:
        m.set_rand_matrix();
        break;
    case 2:
        cout << "Ввод матрицы (построчно):" << endl;
        cin >> m;
        cout << endl;
        break;
    default:
        throw exception("Значение должно быть равно 1 или 2.");
    }
}
void vector_input(int choice, TDynamicVector<int>& v)
{
    switch (choice)
    {
    case 1:
        v.set_rand_vector();
        break;
    case 2:
        cout << "Ввод вектора:" << endl;
        cin >> v;
        cout << endl;
        break;
    default:
        throw exception("Значение должно быть равно 1 или 2.");
    }
}


void main()
{
    setlocale(LC_ALL, "Russian");
    int scalar, size;
    cout << "Введите размер матриц/вектора с которыми вы собираетесь работать (от 1 до 10000)" << endl;
    cin >> size;
    cout << endl;
    TDynamicMatrix<int> m1(size), m2(size);
    TDynamicVector<int> v(size);

    size_t choice;

    cout << "Выберите тип операции:\n 1 - скаляраная (умножение матрицы на скаляр)";
    cout << "\n 2 - векторная (умножение матрицы на вектор)";
    cout << "\n 3 - матричная (сложение/вычитание/умножение матриц a+b/a-b/a*b)" << endl;
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        cout << "Введите скаляр c " << endl;
        cin >> scalar;
        cout << endl;
        cout << "Выберите способ заполнения матрицы:\n 1 - случайные числа \n 2 - ручной ввод" << endl;
        cin >> choice;
        cout << endl;
        matrix_input(choice, m1);
        cout << m1 << "\n\t * \n\t " << scalar << "\n\t = \n" << m1 * scalar << endl;
        break;
    case 2:
        cout << "Выберите способ заполнения матрицы и вектора:\n 1 - случайные числа \n 2 - ручной ввод" << endl;
        cin >> choice;
        matrix_input(choice, m1);
        vector_input(choice, v);
        cout << m1 << "\n\t * \n" << v << "\n\t = \n"<< m1 * v << endl;
        break;

    case 3:

        cout << "Выберите способ заполнения матрицы:\n 1 - случайные числа \n 2 - ручной ввод" << endl;
        cin >> choice;
        matrix_input(choice, m1);
        matrix_input(choice, m2);
        cout << "Выберите операцию:\n 1 - сложение a + b \n 2 - разность a - b \n 3 - произведение a * b"<< endl;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            cout << m1 << "\n\t + \n" << m2 << "\n\t = \n" << m1 + m2 << endl;
            break;
        case 2:
            cout << m1 << "\n\t - \n" << m2 << "\n\t = \n" << m1 - m2 << endl;
            break;
        case 3:
            cout << m1 << "\n\t * \n" << m2 << "\n\t = \n" << m1 * m2 << endl;
            break;
        default:
            cout << "Введеное значение должно равняться 1, 2 или 3" << endl;
            break;
        }

        break;
    default:
        cout << "Введеное значение должно равняться 1, 2 или 3" << endl;
        break;
    }
}
//---------------------------------------------------------------------------
