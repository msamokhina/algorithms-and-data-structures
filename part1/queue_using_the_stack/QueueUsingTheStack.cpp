/*
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 2 - pop front
a = 3 - push back
Команда 3 задана с неотрицательным параметром b.
Если дана команда pop*, то число b - ожидаемое значение.
Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.

Требуется напечатать YES - если все ожидаемые значения совпали.
Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

Реализовать очередь с помощью двух стеков.
Использовать стек, реализованный с помощью динамического буфера.
*/

#include <iostream>
#include <assert.h>

class Stack {
private:
    int* stackPtr;
    int size;
    int top;

public:
    Stack();
    ~Stack();
    void PushStack(int element);
    int PopStack();
    bool IsEmpty() const { return stackPtr == nullptr; }
};

Stack::Stack() :
    stackPtr( nullptr ),
    size( 0 ),
    top( 0 )
{
}

Stack::~Stack()
{
    free(stackPtr);
}

void Stack::PushStack(int element)
{
    if( IsEmpty() ) {
        stackPtr = (int*) malloc( 2 * sizeof(int) );
        size = 2;
    }
    else {
        if ( size - 1 == top ) {
            int* newPtr = (int*) realloc( stackPtr, size * 2 * sizeof(int) );
            if ( newPtr ) {
                stackPtr = newPtr;
                size *= 2;
            } else {
                free( stackPtr ) ;
                assert(0);
            }
        }
        ++top;
    }
    stackPtr[top] = element;
}

int Stack::PopStack()
{
    if( top ) {
        int return_element = stackPtr[top];
        --top;
        return return_element;
    }
    else
        if( !IsEmpty() ) {
            int return_element = stackPtr[top];
            free( stackPtr );
            stackPtr = nullptr;
            size =  0;
            return return_element;
        }
        else
            return -1;
}

class Queue
{
private:
    Stack pushStack;
    Stack popStack;
public:
    void Enqueue(int);
    int Dequeue();
};

void Queue::Enqueue(int element)
{
    pushStack.PushStack(element);
}

int Queue::Dequeue()
{
    if( popStack.IsEmpty() )
        while( !pushStack.IsEmpty() )
            popStack.PushStack( pushStack.PopStack() );

    if( popStack.IsEmpty() )
        return -1;

    int element = popStack.PopStack();
    return element;
}

enum {
    popFront = 2,
    pushBack = 3,
};

int main() {
    int commandsCount = 0;
    std::cin >> commandsCount;
    Queue queue;
    for( int i = 0; i < commandsCount; ++i ) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        switch( command ) {
        case popFront:
            if( queue.Dequeue() != value ) {
                std::cout << "NO";
                return 0;
            }
            break;
        case pushBack:
            queue.Enqueue(value);
            break;
        }
    }
    std::cout << "YES";
    return 0;
}