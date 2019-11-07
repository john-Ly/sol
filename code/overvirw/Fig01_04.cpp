#include <iostream>
using std::cout;

void printDigit( int n )
{
    cout << n;
}

void printOut( int n )  // Print nonnegative n
{
    if( n >= 10 )
        printOut( n / 10 );
    printDigit( n % 10 );
}

//  avoid using the mod routine (which can be very expensive) 
//  because n%10 = n − [n/10] * 10 （取下底）is true for positive n.

int main(  )
{
    printOut( 1369 );
    cout << "\n";
    return 0;
}
