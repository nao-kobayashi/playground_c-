#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale>

using namespace std;

bool GetContents(
	const string& filename,
	vector<vector<wstring>>& data,
	const wchar_t delimiter = ','
) {
	wfstream fs(filename);
	if (!fs.is_open()) {
		return false;
	}

	while (!fs.eof()) {
		// >> operator defines whitespace as delimiter.
		wstring buf;
		// fs >> buf;
		getline(fs, buf);
		if (buf.empty())
			break;

		vector<wstring> record;
		wistringstream stream_buf(buf);
		wstring token;
		while (getline(stream_buf, token, delimiter)) {
			record.push_back(token);
		}
		data.push_back(record);
	}

	return true;
}

int main(void) {
	std::locale::global(std::locale("ja_JP.UTF8"));

	string filename = "./sample.csv";
	vector<vector<wstring>> data;

	if (!GetContents(filename, data)) {
		return -1;
	}

	for (int r = 0; r < data.size(); r++) {
		vector<wstring> record = data[r];
		for (int c = 0; c < record.size(); c++) {
			wcout << record[c];
			if (c < record.size() - 1) {
				wcout << ",";
			}
		}
		wcout << endl;
	}

	int work;
	cin >> work;
}
