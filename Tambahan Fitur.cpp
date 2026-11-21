#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

class LetterCombiner {
private:
    // Fitur 1: Ekspansi tombol 0 dan 1 selain 2-9
    const vector<string> keypad = {
        "#",      // 0: Simbol pemisah
        "-_",     // 1: Simbol kontrol
        "abc",    // 2
        "def",    // 3
        "ghi",    // 4
        "jkl",    // 5
        "mno",    // 6
        "pqrs",   // 7
        "tuv",    // 8
        "wxyz"    // 9
    };

    void backtrack(const string& digits, int index, string& current,
                   vector<string>& results, int caseMode) {
        if (index == (int)digits.length()) {
            results.push_back(current);
            return;
        }

        int d = digits[index] - '0';
        if (d < 0 || d > 9) return;

        // Fitur 2: Mode kapitalisasi (1: kecil, 2: KAPITAL, 3: campuran)
        string pool = "";
        for (char c : keypad[d]) {
            if (caseMode == 1) {
                pool += tolower(c);
            } else if (caseMode == 2) {
                pool += toupper(c);
            } else {
                pool += tolower(c);
                if (isalpha(c)) pool += toupper(c);
            }
        }

        for (char c : pool) {
            current.push_back(c);
            backtrack(digits, index + 1, current, results, caseMode);
            current.pop_back();
        }
    }

public:
    vector<string> generate(const string& digits, int caseMode) {
        if (digits.empty()) return {};
        vector<string> results;
        string current = "";
        backtrack(digits, 0, current, results, caseMode);
        return results;
    }

    // Fitur 3: Pencarian / filter hasil berdasarkan kata kunci
    vector<string> filterResults(const vector<string>& results, const string& keyword) {
        vector<string> filtered;
        for (const string& s : results) {
            if (s.find(keyword) != string::npos) {
                filtered.push_back(s);
            }
        }
        return filtered;
    }

    // Fitur 4: Ekspor output ke file eksternal (.txt)
    void exportToTxt(const string& digits, const vector<string>& results) {
        ofstream file("hasil_kombinasi.txt");
        if (file.is_open()) {
            file << "Input Digit     : " << digits << endl;
            file << "Total Kombinasi : " << results.size() << endl;
            for (size_t i = 0; i < results.size(); ++i) {
                file << (i + 1) << ". " << results[i] << endl;
            }
            file.close();
            cout << "[INFO] Tersimpan ke file 'hasil_kombinasi.txt'." << endl;
        }
    }
};

int main() {
    LetterCombiner solver;
    string digits, keyword;
    int caseMode;

    cout << "Masukkan digit (0-9): ";
    cin >> digits;

    cout << "Pilih mode huruf (1 = kecil, 2 = KAPITAL, 3 = campuran): ";
    cin >> caseMode;

    vector<string> output = solver.generate(digits, caseMode);

    cout << "\nTotal kombinasi: " << output.size() << endl;
    cout << "Output: [";
    for (size_t i = 0; i < output.size(); ++i) {
        cout << "\"" << output[i] << "\"";
        if (i < output.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "\nMasukkan kata kunci filter (atau ketik '-' untuk melewati): ";
    cin >> keyword;
    if (keyword != "-") {
        vector<string> filtered = solver.filterResults(output, keyword);
        cout << "Hasil filter (" << filtered.size() << " ditemukan): ";
        for (const string& s : filtered) cout << s << " ";
        cout << endl;
    }

    solver.exportToTxt(digits, output);
    return 0;
}