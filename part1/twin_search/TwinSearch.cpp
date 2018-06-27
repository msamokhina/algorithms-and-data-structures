/*
 * Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
 * Время работы поиска для каждого элемента B[i]: O(log(k)).
 * n ≤ 110000, m ≤ 1000.
*/

#include <iostream>
#include <assert.h>

int* search( int* interval, size_t interval_size, int element )
{
    size_t first = 0;
    size_t last = interval_size;

    while( first < last ) {
        size_t middle = first + (last - first) / 2;
        if( element <= interval[middle] )
            last = middle;
        else
            first = middle + 1;
    }

    return interval + first;
}

size_t find_twin( int* A, size_t size_A, int element )
{
    // Поиск интервала
    size_t interval_size = 1;
    size_t remaining_elements_counter = size_A;
    int* interval_begin = A;
    int* interval_end = A;
    while( 1 ) {
        remaining_elements_counter -= interval_size;
        // Если элемент меньше последнего элемента, то нужный интервал найден
        if( element <= *interval_end ) {
            break;
        }
        // Иначе
        if( remaining_elements_counter >= interval_size * 2 ) {
            interval_begin += interval_size;
            interval_size *= 2;
            interval_end += interval_size;
        }
        else {
            if( remaining_elements_counter ) {
                interval_begin += interval_size;
                interval_size = remaining_elements_counter;
                interval_end = interval_begin + interval_size - 1;
            }
            break;
        }
    }

    // Бинарный поиск по интервалу
    if( element > *interval_end )
        return size_A - 1;
    int* search_result = search( interval_begin, interval_size, element );
    if( search_result == A )
        return 0;
    if( *search_result - element  <  element - *(search_result - 1) )
        return search_result - A;
    else
        return  search_result - 1 - A;
}

int main()
{
    size_t size_A;
    std::cin >> size_A;
    assert( size_A );
    int* A = new int[size_A];
    for( int i = 0; i < size_A; ++i ) {
        std::cin >> A[i];
    }

    size_t size_B;
    std::cin >> size_B;
    int* B = new int[size_B];
    size_t index_nearest = 0;
    for( int i = 0; i < size_B; ++i ) {
        std::cin >> B[i];
        index_nearest = find_twin( A, size_A, B[i] );
        std::cout << index_nearest << " ";
    }

    delete[] A;
    delete[] B;
    return 0;
}