/*
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri).
Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
*/
#include <iostream>
#include <vector>
using namespace std;

struct Segment {
    int left;
    int right;
};

class SegmentsCompare {
public:
    bool operator()( const Segment& first, const Segment& second ) {
        return isLessByLeft( first, second );
    }
private:
    bool isLessByLeft( const Segment& first, const Segment& second ){
        if( first.left < second.left ) {
            return true;
        }
        else {
            return false;
        }
    }
};

template <typename T, typename Compare>
void siftDown( typename vector<T>::iterator begin, typename vector<T>::iterator end, typename vector<T>::iterator element, Compare& cmp )
{
    typename vector<T>::iterator left = begin + 2 * distance( begin, element ) + 1;
    typename vector<T>::iterator right = begin + 2 * distance( begin, element ) + 2;
    // проверяем, есть ли больший сын
    typename vector<T>::iterator largest = element;
    if( left < end && cmp( *largest, *left ) )
        largest = left;
    if( right < end && cmp( *largest, *right ) )
        largest = right;
    // если нашли большего сына, то проталкиваем в него корень
    if( largest != element ) {
        iter_swap( largest, element );
        siftDown<T, Compare>( begin, end, largest, cmp );
    }
};

template <typename T>
void siftDown( typename vector<T>::iterator begin, typename vector<T>::iterator end, typename vector<T>::iterator data )
{
    less<T> cmp;
    siftDown<T, less<T>>( begin, end, data, cmp );
};

template <typename T, typename Compare>
void buildHeap( typename vector<T>::iterator begin, typename vector<T>::iterator end, Compare& cmp )
{
    for( int i = distance( begin, end ) / 2 - 1; i >= 0; --i ) {
        siftDown<T, Compare>( begin, end, begin + i, cmp );
    }
}

template <typename T>
void buildHeap( typename vector<T>::iterator begin, typename vector<T>::iterator end )
{
    less<T> cmp;
    buildHeap<T, less<T>>( begin, end, cmp );
}

template <typename T, typename Compare>
void heapSort( typename vector<T>::iterator begin, typename vector<T>::iterator end, Compare& cmp )
{
    int heapSize = distance( begin, end );
    while( heapSize > 1 ) {
        iter_swap( begin, --end );
        siftDown<T, Compare>( begin, end, begin, cmp );
        --heapSize;
    }
}

template <typename T>
void heapSort( typename vector<T>::iterator begin, typename vector<T>::iterator end )
{
    less<T> cmp;
    heapSort<T, less<T>>( begin, end, cmp );
}

int linePaintingInOneLayer( vector<Segment>::iterator begin, vector<Segment>::iterator end )
{
    SegmentsCompare cmp;
    buildHeap<Segment, SegmentsCompare>( begin, end, cmp);
    heapSort<Segment, SegmentsCompare>( begin, end, cmp);
    int sum = 0;
    vector<Segment>::iterator it = begin;
    // left-right - закрашенный единожды отрезок
    int left = (*it).left;
    int right = (*it).right;
    ++it;
    while( it < end ) {
        // если нет пересечения со следующим отрезком
        // увеличиваем сумму на right - left, запоминаем следующий отрезок
        if( right <= (*it).left ) {
            sum += right - left;
            left = (*it).left;
            right = (*it).right;
            ++it;
        }
        else {
            if( (*it).left > left ) {
                sum += (*it).left - left;
            }
            if( (*it).right > left ) {
                left = min((*it).right, right);
                right = max((*it).right, right);
            }
            ++it;
        }
    }
    sum += right - left;
    return sum;
}

int main()
{
    int N = 0;
    cin >> N;
    vector<Segment> segments(N);
    for( auto it = segments.begin(); it < segments.end(); ++it ) {
        cin >> (*it).left >> (*it).right;
    }
    int sum = 0;
    sum = linePaintingInOneLayer( segments.begin(), segments.end() );
    cout << sum << endl;
    return 0;
}
