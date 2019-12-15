#include "all.h"

using namespace std;

bool GetContents(
    const string& filename,
    vector<vector<string> >& data,
    const char delimiter = ','
) {
    fstream fs(filename);
    if (!fs.is_open()) {
        return false;
    }

    while (!fs.eof()) {
        // >> operator defines whitespace as delimiter.
        string buf;
        // fs >> buf;
        getline(fs, buf);
        if (buf.empty()) 
            break;

        vector<string> record;
        istringstream stream_buf(buf);
        string token;
        while (getline(stream_buf, token, delimiter)) {
            record.push_back(token);
        }
        data.push_back(record);
    }

    return true;
}

int main(void) {
    string filename = "./sample.csv";
    vector<vector<string> > data;

    if (!GetContents(filename, data)) {
        return -1;
    }

    for (int r = 0; r < data.size(); r++) {
        vector<string> record = data[r];
        for (int c = 0; c < record.size(); c++) {
            cout << record[c];
            if (c < record.size() - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }
}
