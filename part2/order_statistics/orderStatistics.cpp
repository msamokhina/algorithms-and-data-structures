#include <iostream>
#include <vector>
using namespace std;

template<class T, class Compare>
int Partition( typename vector<T>::iterator& begin, typename vector<T>::iterator& left, typename vector<T>::iterator& right, Compare& cmp )
{
    int index = rand() % ( distance( left, right ) + 1 ) + distance( begin, left );
    typename vector<T>::iterator pivot = begin + index;
    iter_swap( pivot, right );
    typename vector<T>::iterator i = left;
    typename vector<T>::iterator j = left;
    while( i <= right && !cmp( *right, *i ) )
        ++i;
    if( i >= right )
        return distance( begin, right );
    j = i + 1;
    while( j < right ) {
        while( cmp( *right, *j ) )
            j++;
        if( j < right )
            iter_swap( i++, j++ );
    }
    iter_swap( i, right );
    return distance( begin, i );
}

// Возвращает k-ую порядковую статистику. k считается от 0.
template<class T, class Compare>
T KStat( typename vector<T>::iterator begin, typename vector<T>::iterator end, int k, Compare& cmp )
{
    typename vector<int>::iterator left = begin;
    typename vector<int>::iterator right = end - 1;
    while( true ) {
        int pivotPos = Partition<T, Compare>( begin, left, right, cmp );
        if( pivotPos == k ) {
            return *(begin + k);
        }
        if( pivotPos < k ) {
            left = begin + pivotPos + 1;
        } else {
            right = begin + pivotPos - 1;
        }
    }
}

int main()
{
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    vector<int> data(n);
    for( int i = 0; i < n; ++i ) {
        cin >> data[i];
    }

    less<int> cmp;
    cout << KStat<int, less<int>>( data.begin(), data.end(), k, cmp );

    return 0;
}