/*
На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0.
Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий).
Один ящик можно вложить в другой, если его можно перевернуть так,
что размеры одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим осям.
Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
*/
#include <iostream>
struct Box {
    int boxIndex;
    int xSize;
    int ySize;
    int zSize;
};

void sortByXYZ( Box* myBox ) {
    if( myBox->xSize > myBox->ySize ) {
        std::swap( myBox->xSize, myBox->ySize );
    }
    if( myBox->ySize > myBox->zSize ) {
        std::swap( myBox->ySize, myBox->zSize );
    }
    else {
        return;
    }
    if( myBox->xSize > myBox->ySize ) {
        std::swap( myBox->xSize, myBox->ySize );
    }
}

bool isLessByX( Box* box1, Box* box2 ) {
    if (box1->xSize < box2->xSize) {
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
void insertionSort( T* arr, int arrSize, bool (*isLess)( T*, T* ) ) {
    for( int i = 1; i < arrSize; ++i ) {
        for( int j = i; j > 0 && isLess( &arr[j], &arr[j - 1] ); --j ) {
            std::swap( arr[j - 1], arr[j] );
        }
    }
}

int main() {
    int boxCount = 0;
    std::cin >> boxCount;
    Box* boxArr = new Box[boxCount];
    for( int i = 0; i < boxCount; ++i ) {
        std::cin >> boxArr[i].xSize >> boxArr[i].ySize >> boxArr[i].zSize;
        boxArr[i].boxIndex = i;
    }

    for( int i = 0; i < boxCount; ++i ) {
        sortByXYZ( &boxArr[i] );
    }

    insertionSort( boxArr, boxCount, isLessByX );

    for( int i = 0; i < boxCount; ++i ) {
        std::cout << boxArr[i].boxIndex << " ";
    }
    delete [] boxArr;
    return 0;
}