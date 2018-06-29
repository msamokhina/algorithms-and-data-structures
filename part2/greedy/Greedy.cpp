/*
Вовочка ест фрукты из бабушкиной корзины.
В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм.
Каждый фрукт весит не более K грамм.
За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно,
откусывает от каждого половину и кладет огрызки обратно в корзину.
Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.

Определить за сколько подходов Вовочка съест все фрукты в корзине.

Вначале вводится n - количество фруктов и n строк с массами фруктов. n ≤ 50000.
Затем K - "грузоподъемность". K ≤ 1000.
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <assert.h>
using namespace std;

template <class T>
class BinaryHeap {
public:
    void buildHeap( typename vector<T>::iterator, typename vector<T>::iterator );
    T getMax() const;
    void extractMax();
    bool isEmpty() const;
    void insert(T);
private:
    vector<T> heapElements;
    void siftDown( int );
    void siftUp( int );
};

template <class T>
void BinaryHeap<T>::siftDown( int index )
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    // проверяем, есть ли больший сын
    int largest = index;
    if( left < heapElements.size() && heapElements[largest] < heapElements[left] )
        largest = left;
    if( right < heapElements.size() && heapElements[largest] < heapElements[right] )
        largest = right;
    // если нашли большего сына, то проталкиваем в него корень
    if( largest != index ) {
        swap( heapElements[largest], heapElements[index] );
        siftDown( largest );
    }
}

template <class T>
void BinaryHeap<T>::siftUp( int index )
{
    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;
        if( heapElements[index] <= heapElements[parent] )
            return;
        swap( heapElements[index], heapElements[parent] );
        index = parent;
    }
}

template <class T>
void BinaryHeap<T>::buildHeap(typename vector<T>::iterator begin, typename vector<T>::iterator end )
{
    heapElements.resize( distance( begin, end ) );
    copy( begin, end, heapElements.begin() );
    for( int i = heapElements.size() / 2 - 1; i >= 0; --i ) {
        siftDown( i );
    }
}

template <class T>
T BinaryHeap<T>::getMax() const
{
    return heapElements[0];
}

template <class T>
bool BinaryHeap<T>::isEmpty() const
{
    if( heapElements.empty() )
        return true;
    return false;
}

template <class T>
void BinaryHeap<T>::insert(T value)
{
    heapElements.insert( heapElements.end(), value );
    siftUp( heapElements.size() - 1 );
}

template <class T>
void BinaryHeap<T>::extractMax()
{
    if( heapElements.size() > 1 ) {
        heapElements[0] = heapElements[heapElements.size() - 1];
        heapElements.pop_back();
        siftDown(0);
    }
    else {
        if( heapElements.size() == 1 )
            heapElements.pop_back();
        else
            assert( !isEmpty() );
    }
}

int fruitBasketEating( vector<short>::iterator begin, vector<short>::iterator end , short K )
{
    vector<short> bitten; // Уже взятые фрукты
    int approachesCounter = 0;
    BinaryHeap<short> myBasket;
    myBasket.buildHeap( begin, end );
    short remainsToRaise = K;

    while( !myBasket.isEmpty() || !bitten.empty() ) {
        //Если в корзине остались фрукты, и еще может поднять
        if( !myBasket.isEmpty() && remainsToRaise >= myBasket.getMax() ) {
            remainsToRaise -= myBasket.getMax();
            bitten.push_back( myBasket.getMax() / 2 );
            myBasket.extractMax();
        }
        //Если не может поднять оставшиеся фрукты или поднимать нечего
        else {
            remainsToRaise = K;
            ++approachesCounter;
            //Возвращаем в корзину фрукты из прошлого подхода
            while( !bitten.empty() ) {
                if( bitten[bitten.size() - 1] )
                    myBasket.insert(bitten[bitten.size() - 1]);
                bitten.pop_back();
            }
        }
    }
    return approachesCounter;
}

int main()
{
    int n = 0;
    cin >> n;
    vector<short> fruitBasket(n);
    for( vector<short>::iterator i = fruitBasket.begin(); i < fruitBasket.end(); ++i ) {
        cin >> *i;
    }
    short K = 0;
    cin >> K;
    int approachesCounter = 0;
    approachesCounter = fruitBasketEating( fruitBasket.begin(), fruitBasket.end(), K );
    cout << approachesCounter;
    return 0;
}