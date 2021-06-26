#include <iostream>
#include <array>
#include <sstream>

using namespace std;

class ipv4 {
    array<unsigned char, 4> data;
public:
    constexpr ipv4(): ipv4(0, 0, 0, 0) {}

    constexpr ipv4(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
            : data{{a, b, c, d}} {}

    explicit constexpr ipv4(unsigned long a)
            : ipv4(static_cast<unsigned char>((a >> 24) & 0xFF),
                   static_cast<unsigned char>((a >> 16) & 0xFF),
                   static_cast<unsigned char>((a >> 8) & 0xFF),
                   static_cast<unsigned char>(a  & 0xFF)) {}

    ipv4(const ipv4 &other) noexcept : data(other.data) {}

    ipv4& operator=(const ipv4 &other) noexcept {
        data = other.data;
        return *this;
    }

    ipv4& operator++() {
        *this = ipv4(1 + to_long());
        return *this;
    }

    ipv4 operator++(int) {
        ipv4 result(*this);
        ++(*this);
        return result;
    }


    string to_string() const {
        stringstream ss;
        ss << *this;
        return ss.str();
    }

    constexpr unsigned long to_long() const noexcept {
        return (static_cast<unsigned long>(data[0] << 24)) |
            (static_cast<unsigned long>(data[1] << 16)) |
            (static_cast<unsigned long>(data[2] << 8)) |
            (static_cast<unsigned long>(data[3]));
    }

    friend bool operator==(const ipv4 &a1, const ipv4 &a2) {
        return a1.data == a2.data;
    }

    friend bool operator!=(const ipv4 &a1, const ipv4 &a2) {
        return !(a1 == a2);
    }

    friend bool operator<(const ipv4 &a1, const ipv4 &a2) {
        return a1.to_long() < a2.to_long();
    }

    friend bool operator>(const ipv4 &a1, const ipv4 &a2) {
        return  a2 < a1;
    }

    friend bool operator<=(const ipv4 &a1, const ipv4 &a2) {
        return !(a1 > a2);
    }

    friend bool operator>=(const ipv4 &a1, const ipv4 &a2) {
        return !(a1 < a2);
    }

    friend ostream& operator<<(ostream &os, const ipv4 &a) {
        os << static_cast<int>(a.data[0]) << "."
            << static_cast<int>(a.data[1]) << "."
            << static_cast<int>(a.data[2]) << "."
            << static_cast<int>(a.data[3]);

        return os;
    }

    friend istream& operator>>(istream &is, ipv4 &a) {
        char d1, d2, d3;
        int b1, b2, b3, b4;
        is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
        if (d1 == '.' && d2 == '.' && d3 == '.') {
            a = ipv4(b1, b2, b3, b4);
        } else {
            is.setstate(ios_base::failbit);
        }
        return is;
    }
};

int main() {
    ipv4 address(168, 192, 0, 1);
    cout << address << endl;

    ipv4 ip;
    cout << ip << endl;
    cin >> ip;
    if (!cin.fail())
        cout << ip << endl;

    cout << "input range: ";
    ipv4 a1, a2;
    cin >> a1 >> a2;

    if (a2 > a1) {
        for (ipv4 a = a1; a <= a2; a++) {
            cout << a << endl;
        }
    } else {
        cerr << "invalid range" << endl;
    }

    return 0;
}
