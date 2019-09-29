#include <iostream>
#include <complex>

using namespace std;

template<class T> inline void swap_gen(T& d, T& s) {
    T temp = d;
    d = s;
    s = temp;
}

// int& is a reference.
inline void swap(int& i, int& j) {
    // cout << "a is " << i << endl;
    // cout << "b is " << j << endl;
    int temp = i;
    i = j;
    j = temp;
}

void swap_c_style(int* i, int* j) {
    cout << "address of a = " << i << " value of a = " << *i << endl;
    cout << "address of b = " << j << " value of b = " << *j << endl;
    int temp = *i;
    *i = *j;
    *j = temp;
}

int main(void) {
    int a = 100;
    int b = 200;
    cout << "a is " << a << "  b is " << b << endl;;

    cout << "c style swap exec" << endl;
    swap_c_style(&a, &b);
    cout << "a is " << a << "  b is " << b << endl;

    cout << "c++ style swap exec" << endl;
    swap(a, b);
    cout << "a is " << a << "  b is " << b << endl;


    cout << "generics swap exec" << endl;
    int n1 = 111;
    int n2 = 2222;
    cout << "n1 is " << n1 << "  n2 is " << n2 << endl;
    swap_gen(n1, n2);
    cout << "n1 is " << n1 << "  n2 is " << n2 << endl;

    double d1 = 123.456;
    double d2 = 987.066;
    cout << "d1 is " << d1 << "  d2 is " << d2 << endl;
    swap_gen(d1, d2);
    cout << "d1 is " << d1 << "  d2 is " << d2 << endl;

    complex<double> r(2.4, 1.8), s(11.23, 3.1415);
    cout << "r is " << r << "  s is " << s << endl;
    swap_gen(r, s);
    cout << "r is " << r << "  s is " << s << endl;
    
    string str1 = "abcde", str2 = "kobayashi";
    cout << "str1 is " << str1 << "  str2 is " << str2 << endl;
    swap_gen(str1, str2);
    cout << "str1 is " << str1 << "  str2 is " << str2 << endl;

}
