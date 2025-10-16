#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Build the prefix (LPS) array for the pattern
vector<int> buildLPS(const string &pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);

    int len = 0; // length of the previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // fallback
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

// KMP algorithm to search for pattern in text
vector<int> KMPSearch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> result;

    if (m == 0 || n < m) return result;

    vector<int> lps = buildLPS(pattern);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            result.push_back(i - j); // match found
            j = lps[j - 1]; // continue searching
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return result;
}

int main() {
    string text = "abxabcabcaby";
    string pattern = "abcaby";

    vector<int> matches = KMPSearch(text, pattern);

    if (!matches.empty()) {
        cout << "Pattern found at indices: ";
        for (int idx : matches) {
            cout << idx << " ";
        }
        cout << "\n";
    } else {
        cout << "Pattern not found.\n";
    }

    return 0;
}
