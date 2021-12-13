/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

string s, t;
int Next[100006][26], cur[26], num[26], Sum[100006][26];

bool Check(int ptr) {
    for(int c = 0; c < 26; ++c)
    if (Sum[ptr][c] < num[c]) return false;

    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> s >> t; int n = s.size(), m = t.size();
    for(int i = 0; i < (int) m; ++i) ++num[t[i]-'a'];

    for(int i = 0; i < 26; ++i) cur[i] = n+1;
    for(int i = n; i >= 0; --i) {
        for(int j = 0; j < 26; ++j) {
            Next[i][j] = cur[j];
            Sum[i][j] = Sum[i+1][j];
        }

        if (i > 0) {
            cur[s[i-1]-'a'] = i;
            ++Sum[i][s[i-1]-'a'];
        }
    }

    vector<char> ans;

    for(int i = 1, ptr = 0; i <= m; ++i) {
        bool ok = false;
        for(int c = 0; c < 26; ++c)
        if (num[c] && Check(Next[ptr][c])) {
            --num[c];
            ans.push_back(c + 'a');
            ptr = Next[ptr][c];
            ok = true;
            break;
        }

        if (!ok) {
            cout << "-1";
            return 0;
        }
    }

    for(char c: ans) cout << c;

    return 0;
}
