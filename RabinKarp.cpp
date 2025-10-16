#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Rabin-Karp Algorithm for pattern searching
// Returns indices of all occurrences of pattern in text
vector<int> rabinKarp(const string &text, const string &pattern) {
    const int prime = 101; // A prime number for hashing
    int m = pattern.size();
    int n = text.size();
    vector<int> result;

    if (m > n) return result;

    long long patternHash = 0, textHash = 0, power = 1;

    // Compute initial hash values for pattern and first window of text
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * prime + pattern[i]);
        textHash = (textHash * prime + text[i]);
        if (i > 0) power *= prime;
    }

    // Slide over the text
    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            // Hashes match, verify characters one by one
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) result.push_back(i);
        }

        // Calculate hash for next window
        if (i < n - m) {
            textHash = (textHash - text[i] * power) * prime + text[i + m];
        }
    }

    return result;
}

int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    vector<int> occurrences = rabinKarp(text, pattern);

    if (!occurrences.empty()) {
        cout << "Pattern found at indices: ";
        for (int idx : occurrences) {
            cout << idx << " ";
        }
        cout << "\n";
    } else {
        cout << "Pattern not found in the text.\n";
    }

    return 0;
}
