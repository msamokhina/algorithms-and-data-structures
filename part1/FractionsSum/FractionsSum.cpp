/*
    Даны две рациональные дроби: a/b и c/d.
    Сложить их и результат представьте в виде несократимой дроби m/n.
    Вывести числа m и n.
    a, b, c, d ≤ 1000.
*/

#include <iostream>
#include <assert.h>
using namespace std;

int gcd ( int a, int b )
{
    return b ? gcd ( b, a % b ) : a;
}

class Fraction {
private:
    int numerator;
    int denominator;
public:
    Fraction();
    Fraction( int obj_numerator, int obj_denominator );
    friend Fraction operator+( const Fraction& obj1, const Fraction& obj2 );
    friend istream& operator>>( istream &s, Fraction& );
    friend ostream& operator<<( ostream &s, const Fraction& );
};

Fraction::Fraction() :
    numerator( 0 ),
    denominator( 1 )
{
}
Fraction::Fraction( int obj_numerator, int obj_denominator ) :
        numerator( obj_numerator )
{
    assert( obj_denominator );
    denominator = obj_denominator;
}


Fraction operator+( const Fraction& obj1, const Fraction& obj2 )
{
    int result_numerator, result_denominator;
    // Вычисляем числитель и знаменатель суммы
    result_numerator = obj1.numerator * obj2.denominator + obj2.numerator * obj1.denominator;
    result_denominator = obj1.denominator * obj2.denominator;

    // Находим НОД числителя и знаменателя, сокращаем на него дробь
    int gcd_numerator_denominator;
    gcd_numerator_denominator = gcd( result_numerator, result_denominator );
    result_numerator /= gcd_numerator_denominator;
    result_denominator /= gcd_numerator_denominator;

    return Fraction( result_numerator, result_denominator );
}

istream& operator>>( istream& s, Fraction& obj ) {
    cin >> obj.numerator;
    cin >> obj.denominator;
    assert( obj.denominator );
    return s;
}

ostream& operator<<( ostream &s, const Fraction& obj ) {
    s << obj.numerator << " " << obj.denominator;
    return s;
}

int main() {
    Fraction obj1, obj2;
    cin >> obj1 >> obj2;
    cout << obj1 + obj2;
    return 0;
}