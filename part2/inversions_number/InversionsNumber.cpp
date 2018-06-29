#include <iostream>
#include <vector>
using namespace std;

template <class InputIt, class T, class Compare>
void Merge( InputIt aBegin, InputIt aEnd, InputIt bBegin, InputIt bEnd, InputIt cBegin, int64_t* counter, Compare& cmp )
{
    InputIt i = aBegin;
    InputIt j = bBegin;
    while( i < aEnd && j < bEnd ) {
        if( !cmp( (*j), (*i) ) ) {    //(*i) <= (*j)
            iter_swap( cBegin + distance(aBegin, i) + distance(bBegin, j), i );
            ++i;
        } else {
            *counter += distance( i, aEnd );
            iter_swap( cBegin + distance(aBegin, i) + distance(bBegin, j), j );
            ++j;
        }
    }
    // Обработаем остаток.
    if( i == aEnd ) {
        for( ; j < bEnd; ++j )
            iter_swap( cBegin + distance(aBegin, i) + distance(bBegin, j), j );
    } else {
        for( ; i < aEnd; ++i ) {
            iter_swap( cBegin + distance(aBegin, i) + distance(bBegin, j), i );
        }
    }
}

template <class InputIt, class T>
void Merge( InputIt aBegin, InputIt aEnd, InputIt bBegin, InputIt bEnd, InputIt cBegin, int64_t* counter )
{
    less<T> cmp;
    Merge< InputIt, T, less<T> >( aBegin, aEnd, bBegin, bEnd, cBegin, counter, cmp );
}

template <class InputIt, class T, class Compare>
void MergeSort( InputIt begin, InputIt end, int64_t *counter, Compare& cmp )
{
    if( distance( begin, end ) <= 1 )
        return;
    int firstLen = distance( begin, end ) / 2;
    MergeSort<InputIt, T, Compare>( begin, begin + firstLen, counter, cmp );
    MergeSort<InputIt, T, Compare>( begin + firstLen, end, counter, cmp );

    vector<T> sorted(distance( begin, end ));
    Merge<InputIt, T, Compare>( begin, begin + firstLen, begin + firstLen, end, sorted.begin(), counter, cmp);
    copy( sorted.begin(), sorted.end(), begin );
}

template <class InputIt, class T>
void MergeSort( InputIt begin, InputIt end, int64_t *counter )
{
    less<T> cmp;
    MergeSort< InputIt, T, less<T> >( begin, end, counter, cmp );
}

int main()
{
    vector<int> data;
    while( !cin.eof() ) {
        int element;
        cin >> element;
        data.push_back( element );
    }
    data.pop_back();
    int64_t counter = 0;
    less<int> cmp;
    MergeSort< vector<int>::iterator, int, less<int> >( data.begin(), data.end(), &counter, cmp );
    cout << counter;
    return 0;
}