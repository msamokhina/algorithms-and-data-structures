/*
 * Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
 */
#include <iostream>

int min( int a, int b )
{
    return ( a > b ) ? b : a;
}

long long widePyramid( int N )
{
    long long** Array = new long long* [N + 1];
    for( int i = 0; i <= N; ++i ) {
        Array[i] = new long long [N + 1];
    }
    for( int i = 0; i <= N; ++i )
        for ( int j = 0; j <= i; ++j ) {
            Array[i][j] = 0;
        }
    int begin = 1;
    long long previous_sum = 0;
    int j = 1;
    for( int i = 1; i <= N; ++i ) {
        while( j < i ) {
            Array[i][j] = Array[i - j][min( j - 1, i - j )] + previous_sum;
            previous_sum = Array[i][j];
            if( !previous_sum ) {
                begin = j;
            }
            ++j;
        }
        Array[i][j] = previous_sum + 1;
        previous_sum = 0;
        j = begin;
    }

    long long result = Array[N][N];
    for( int i = 0; i <= N; ++i ) {
        delete[] Array[i];
    }
    delete[] Array;
    return result;
}

int main()
{
    int N;
    std::cin >> N;
    long long result = widePyramid( N );
    std::cout << result;
    return 0;
}