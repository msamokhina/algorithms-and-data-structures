/*
    Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
    Найти количество таких пар индексов (i, j), что A[i] + B[j] = k.
    Время работы O(n + m).
    n, m ≤ 100000.
 */

#include <iostream>

int find( int* A, int* B, int size_A, int size_B, int k )
{
    int counter = 0;
    // Обход массива А с начала, массива В от конца
    int i = 0, j = size_B - 1;
    while( i < size_A && j >= 0 ) {
        // Если сумма больше нужной, берем следующий меньший элемент B[j]
        if( A[i] + B[j] > k ) {
            --j;
        }
        // Если сумма меньше нужной, берем следующий больший элемент A[i]
        else if( A[i] + B[j] < k ) {
            ++i;
        }
        else {
            ++counter;
            ++i;
        }
    }
    return counter;
}

int main()
{
    //Считываем массив А
    int size_A;
    std::cin >> size_A;
    int *A = new int[size_A];
    for( int i = 0; i < size_A; ++i ) {
        std::cin >> A[i];
    }

    //Считываем массив В
    int size_B;
    std::cin >> size_B;
    int *B = new int[size_B];
    for( int i = 0; i < size_B; ++i ) {
        std::cin >> B[i];
    }

    int k;
    std::cin >> k;

    int counter;
    counter = find( A, B, size_A, size_B, k );

    std::cout << counter;

    delete[] A;
    delete[] B;

    return 0;
}