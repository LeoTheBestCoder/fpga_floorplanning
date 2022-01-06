#include <bits/stdc++.h>
using namespace std;

class Module {
private:
    int clb, mul, idx;
    int r = 0, c = 0;

public:
    Module(int _idx, int _clb, int _mul) {
        idx = _idx;
        clb = _clb;
        mul = _mul;
    }
    int get_idx() {
        return idx;
    }
    int get_clb() {
        return clb;
    }
    int get_mul() {
        return mul;
    }
    void set_pos(int _r, int _c) {
        r = _r;
        c = _c;
    }
    vector <int> get_pos() {
        return {r, c};
    }
    void info() {
        printf("Module No.%3d: clb = %3d, mul = %3d, pos = (r=%3d, c=%3d)\n", idx, clb, mul, r, c);
    }
};


const vector<string> split(const string& str, const string& pattern) {
    vector<string> result;
    string::size_type begin, end;

    end = str.find(pattern);
    begin = 0;

    while (end != string::npos) {
        if (end - begin != 0) {
            result.push_back(str.substr(begin, end-begin)); 
        }    
        begin = end + pattern.size();
        end = str.find(pattern, begin);
    }

    if (begin != str.length()) {
        result.push_back(str.substr(begin));
    }
    return result;
}

int main() {
    vector<string> content;
    vector<Module> all_module;

    ifstream ifs("benchmarks/case1.module", ios::in);
    if (!ifs.is_open())
        cout << "fail to open file\n";
    else {
        string s;
        while (getline(ifs, s)) {
            // cout << s << "\n";
            content.push_back(s);
        }
        ifs.close();
    }
    ifs.close();

    // for (const auto line: content){
    //     cout << line << "\n";
    // }

    cout << content.size() << "\n";

    for (const auto ch: split("hello world today is Thursday", " ")) {
        cout << ch << "\n";
    }
    return 0;
}