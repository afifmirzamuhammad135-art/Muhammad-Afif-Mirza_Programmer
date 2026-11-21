#include <iostream>
#include <vector>
#include <string>

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
        if (index == digits.length()) {
            hasil.push_back(kombinasiSaatIni);
            return;
        }
        
        int d = digits[index] - '0';
        if (d < 2 || d > 9) return;
        string hurufTersedia = keypad[d];
        
        for (char c : hurufTersedia) {
            kombinasiSaatIni.push_back(c);
            backtrack(digits, index + 1, kombinasiSaatIni, hasil, keypad);
            kombinasiSaatIni.pop_back();
        }
    }
};

int main() {
    Solution sol;
    string digits;
    
    cout << "Masukkan angka (2-9): ";
    cin >> digits;
    
    vector<string> output = sol.letterCombinations(digits);
    
    cout << "Total kombinasi: " << output.size() << endl;
    cout << "Output: [";
    for (size_t i = 0; i < output.size(); ++i) {
        cout << "\"" << output[i] << "\"";
        if (i < output.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}