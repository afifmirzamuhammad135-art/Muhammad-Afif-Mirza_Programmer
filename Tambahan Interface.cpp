#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        vector<string> keypad = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        vector<string> hasil;
        string kombinasiSaatIni = "";
        backtrack(digits, 0, kombinasiSaatIni, hasil, keypad);
        return hasil;
    }

private:
    void backtrack(const string& digits, int index, string& kombinasiSaatIni,
                   vector<string>& hasil, const vector<string>& keypad) {
        if (index == (int)digits.length()) {
            hasil.push_back(kombinasiSaatIni);
            return;
        }

        string hurufTersedia = keypad[digits[index] - '0'];
        for (char c : hurufTersedia) {
            kombinasiSaatIni.push_back(c);
            backtrack(digits, index + 1, kombinasiSaatIni, hasil, keypad);
            kombinasiSaatIni.pop_back();
        }
    }
};

void tampilkanKeypadUI() {
    cout << "+===============================================+" << endl;
    cout << "|         T9 LETTER COMBINATION INTERFACE       |" << endl;
    cout << "+===============+===============+===============+" << endl;
    cout << "|  1 [  ---  ]  |  2 [  abc  ]  |  3 [  def  ]  |" << endl;
    cout << "+---------------+---------------+---------------+" << endl;
    cout << "|  4 [  ghi  ]  |  5 [  jkl  ]  |  6 [  mno  ]  |" << endl;
    cout << "+---------------+---------------+---------------+" << endl;
    cout << "|  7 [ pqrs  ]  |  8 [  tuv  ]  |  9 [ wxyz  ]  |" << endl;
    cout << "+===============+===============+===============+" << endl;
}

bool validasiDigit(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (c < '2' || c > '9') return false;
    }
    return true;
}

int main() {
    Solution sol;
    int menu;

    while (true) {
        cout << "\n";
        tampilkanKeypadUI();
        cout << "| [1] Jalankan Generator Kombinasi              |" << endl;
        cout << "| [2] Lihat Contoh Kasus (Test Cases)           |" << endl;
        cout << "| [0] Keluar Program                            |" << endl;
        cout << "+-----------------------------------------------+" << endl;
        cout << "Pilih menu [0-2]: ";

        if (!(cin >> menu)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[PERINGATAN] Input harus berupa angka menu!" << endl;
            continue;
        }

        if (menu == 0) {
            cout << "Program selesai. Terima kasih!" << endl;
            break;
        } 
        else if (menu == 1) {
            string digits;
            cout << "\nMasukkan rangkaian angka (hanya 2-9): ";
            cin >> digits;

            if (!validasiDigit(digits)) {
                cout << "[ERROR] Input ditolak! Gunakan hanya angka 2 sampai 9." << endl;
                continue;
            }

            vector<string> hasil = sol.letterCombinations(digits);

            cout << "\n+-----------------------------------------------+" << endl;
            cout << "| Input  : " << left << setw(37) << digits << "|" << endl;
            cout << "| Total  : " << left << setw(37) << hasil.size() << "|" << endl;
            cout << "+-----------------------------------------------+" << endl;
            cout << "Hasil Kombinasi:" << endl;

            for (size_t i = 0; i < hasil.size(); ++i) {
                cout << setw(6) << hasil[i];
                if ((i + 1) % 8 == 0) cout << endl;
            }
            cout << endl;
        } 
        else if (menu == 2) {
            cout << "\n--- PANDUAN CONTOH KASUS ---" << endl;
            cout << "- Input \"23\"   -> 9 kombinasi  (ad, ae, af, bd, ...)" << endl;
            cout << "- Input \"79\"   -> 16 kombinasi (pw, px, py, pz, ...)" << endl;
            cout << "- Input \"3258\" -> 81 kombinasi" << endl;
        } 
        else {
            cout << "[PERINGATAN] Pilihan menu tidak tersedia." << endl;
        }
    }

    return 0;
}