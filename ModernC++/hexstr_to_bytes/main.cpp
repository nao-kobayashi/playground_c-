#include <iostream>
#include <vector>

using namespace std;

unsigned char hexchar_to_int(const char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    throw invalid_argument("Invalid hexadecimal character");
}

vector<unsigned char> hexstr_to_bytes(string_view str) {
    vector<unsigned char> result;

    vector<char> str_chars;
    if (str.length() % 2 != 0) {
        str_chars.push_back('0');
    }
    for (size_t i = 0; i < str.size(); i++) {
        str_chars.push_back(str[i]);
    }

    for (size_t i = 0; i < str_chars.size(); i += 2) {
        result.push_back(hexchar_to_int(str_chars[i]) << 4 | hexchar_to_int(str_chars[i + 1]));
    }

    return result;
}

int main() {
    vector<unsigned char> expected { 0xBA, 0xAD, 0xF0, 0x0D, 0x42 };
    assert(hexstr_to_bytes("BAADF00D42") == expected);
    assert(hexstr_to_bytes("baadf00d42") == expected);

    vector<unsigned char> expected2 { 0x0B, 0xAD };
    assert(hexstr_to_bytes("BAD") == expected2);
    return 0;
}
