#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace filesystem;

void remove_empty_lines(path filepath) {
    ifstream filein(filepath.native(), ios::in);
    if (!filein.is_open())
        throw runtime_error("cannot open input file");

    auto temp_path = temp_directory_path() / "temp.txt";
    ofstream fileout(temp_path.native(), ios::out | ios::trunc);
    if (!fileout.is_open())
        throw runtime_error("cannot create temporary file");

    string line;
    while(getline(filein, line)) {
        if (line.length() > 0 && line.find_first_not_of(' ') != line.npos) {
            fileout << line << '\n';
        }
    }

    filein.close();
    fileout.close();

    remove(filepath);
    rename(temp_path, filepath);
}

int main() {
    string filepath;
    cout << "input target file path: ";
    cin >> filepath;

    try {
        remove_empty_lines(path(filepath));
    } catch (runtime_error re) {
        cout << re.what() << endl;
    }

    return 0;
}
