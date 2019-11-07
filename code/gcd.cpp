#include <iostream>
#include <algorithm>
using namespace std;

// @TODO egcd

long gcd_iteration( long m, long n )
{
    while( n != 0 )
    {
        long rem = m % n; // m > n && rem < n
        m = n;
        n = rem;
    }
    return m;
}

long gcd_native( long m, long n )
{
    if(m < n) swap(m, n);
    if(n == 0 ) return m;
    return gcd_native(m-n, n);
}

long gcd_mod( long m, long n )
{
    if(n == 0 ) return m;
    return gcd_mod(n, m%n);
}

int main( )
{
    cout << "gcd_mod( 1989, 1590 ) = " << gcd_mod( 1989, 1590 ) << endl;
    cout << "gcd_native( 1989, 1590 ) = " << gcd_native( 1989, 1590 ) << endl;
    cout << "gcd_iteration( 1989, 1590 ) = " << gcd_iteration( 1989, 1590 ) << endl;
    return 0;
}
