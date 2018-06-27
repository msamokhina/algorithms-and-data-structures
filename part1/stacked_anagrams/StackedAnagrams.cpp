/*
Пара слов называется стековой анаграмой, если одно слово можно получить из другого,
проведя последовательность стековых операций с его буквами
(взять очередную букву исходного слова и поместить ее в стек;
взять букву из стека и добавить ее в конец выходного слова).

Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций,
переводящую первое слово во второе.

Все буквы в слове различные.
Длина анаграммы ≤ 10000.

YES, если последовательность стековых операций существует и NO в противном случае.
*/
#include <iostream>
#include <assert.h>
#include <cstring>

class Stack {
private:
    struct Node {
        char Data;
        Node* Next;

        Node( char data ) : Data( data ), Next( nullptr ) {}
    };

    Node* head;
    void free();
public:
    Stack() : head( nullptr ) {}
    ~Stack() { free(); }

    bool IsEmpty() { return head == nullptr; }
    void Push( char data );
    char Pop();
    const char Top();
};

void Stack::free()
{
    while( !IsEmpty() ) {
        Pop();
    }
}
void Stack::Push( char data )
{
    Node* newNode = new Node( data );
    newNode->Next = head;
    head = newNode;
}

char Stack::Pop()
{
    assert( !IsEmpty() );

    Node* nodeToDelete = head;
    char returnData = nodeToDelete->Data;
    head = head->Next;
    delete[] nodeToDelete;
    return returnData;
}

const char Stack::Top()
{
    assert( !IsEmpty() );
    return head->Data;
}

bool StackAnagram( char* word, char* anagramWord )
{
    int size = strlen( word );
    Stack myStack;
    int i = 0, j = 0;
    while( j < size ) {
        if( !myStack.IsEmpty() && ( myStack.Top() == anagramWord[j] ) ) {
            myStack.Pop();
            ++j;
            continue;
        }
        if( i < size ) {
            if( word[i] == anagramWord[j] ) {
                ++i;
                ++j;
            }
            else {
                myStack.Push( word[i] );
                ++i;
            }
            continue;
        }
        return false;
    }
    return true;
}

int main()
{
    char* word = new char[5000] ;
    char* anagramWord = new char[5000];
    std::cin >> word;
    std::cin >> anagramWord;
    assert( strlen( word ) == strlen( anagramWord ) );
    if( StackAnagram( word, anagramWord ) == false ) {
        std::cout << "NO";
    }
    else {
        std::cout << "YES";
    }
    delete[] word;
    delete[] anagramWord;
    return 0;
}