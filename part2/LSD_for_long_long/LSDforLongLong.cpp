/*
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 10^6.
Отсортировать массив методом поразрядной сортировки LSD по байтам.
*/

#include <iostream>
#include <vector>
using namespace std;

static int MaxChar = 255;
#define DigitByte(it, mask, byte) ((*it) >> 8 * byte & mask)

template <typename T>
void CountingSort( const typename vector<T>::iterator& begin, const typename vector<T>::iterator& end, int byte )
{
    int* C = new int[MaxChar + 1];
    for( int i = 0; i <= MaxChar; ++i )
        C[i] = 0;
    T mask = 0xFF;;
    //подсчетывем количество объектов, byte-ный разряд которых одинаковый
    for( auto it = begin; it < end; ++it ) {
        C[DigitByte(it, mask, byte)]++;
    }
    int count = 0;
    //определяем положения объектов в массиве B
    for( int i = 0; i <= MaxChar; ++i ) {
        int tmp = C[i];
        C[i] = count;
        count += tmp;
    }

    vector<T> B(distance( begin, end ));

    for( int i = 0; i < B.size(); ++i ) {
        //d = digit(A[i], byte)
        //B[C[d]] = A[i]
        //C[d]++
        B[C[DigitByte((begin + i), mask, byte)]++] = *(begin + i);
    }
    delete[] C;
    copy( B.begin(), B.end(), begin );
}

template  <typename T>
void LSDSort( const typename vector<T>::iterator& begin, const typename vector<T>::iterator& end )
{
    for( int r = 0; r < sizeof(T); ++r )
        CountingSort<T>( begin, end, r );
}

int main() {
    int N;
    cin >> N;
    vector<unsigned long long> data(N);
    for( auto it = data.begin(); it < data.end(); ++it ) {
        cin >> (*it);
    }

    LSDSort<unsigned long long>( data.begin(), data.end() );

    for( auto it = data.begin(); it < data.end(); ++it ) {
        cout << (*it) << ' ';
    }
    return 0;
}