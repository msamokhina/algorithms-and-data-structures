/*
В большой IT-фирме есть только одна переговорная комната.
Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
Число заявок ≤ 100000.
*/

#include <iostream>
#include <assert.h>
struct Segment{
    int begin;
    int end;
};

void QuickSortEnd( Segment* array, int first, int last )
{
    if ( first < last ) {
        int left = first, right = last, middle = array[( left + right ) / 2].end;
        do
        {
            while( array[left].end < middle )
                left++;
            while( array[right].end > middle )
                right--;
            if( left <= right )
            {
                int tmp = array[left].end;
                array[left].end = array[right].end;
                array[right].end = tmp;

                tmp = array[left].begin;
                array[left].begin = array[right].begin;
                array[right].begin = tmp;

                left++;
                right--;
            }
        } while ( left <= right );
        QuickSortEnd( array, first, right );
        QuickSortEnd( array, left, last );
    }
}

int MaxCount( Segment* array, int count )
{
    QuickSortEnd( array, 0, count - 1 );

    int result = 1;
    int bCurrent = array[0].end;
    for( int i = 1; i < count; ++i ) {
        if( ( array[i].end != bCurrent ) && ( array[i].begin >= bCurrent ) ) {
            ++result;
            bCurrent = array[i].end;
        }
    }

    return result;
}

int main()
{
    Segment* array = (Segment*) malloc( 2 * sizeof(Segment) );
    int arraySize = 2;
    int segmentCount = 0;

    while( !std::cin.eof() ) {
        if( segmentCount == arraySize ) {
            Segment* newPtr = (Segment*) realloc( array, arraySize * 2 * sizeof(Segment) );
            if ( newPtr ) {
                array = newPtr;
                arraySize *= 2;
            } else {
                free( array ) ;
                assert( newPtr );
            }
        }

        std::cin >> array[segmentCount].begin >> array[segmentCount].end;
        ++segmentCount;
    }

    --segmentCount;

    if( !segmentCount )
        std::cout << 0;
    else {
        int result;
        result = MaxCount( array, segmentCount );
        std::cout << result;
    }
    free( array );
    return 0;
}