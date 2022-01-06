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
        printf("Module No.%3d: clb = %3d, mul = %3d, pos = (r=%d, c=%d)\n", idx, clb, mul, r, c);
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
    vector<Module> all_module;

    ifstream ifs("benchmarks/case1.module", ios::in);
    if (!ifs.is_open())
        cout << "fail to open file\n";
    else {
        string s;
        while (getline(ifs, s)) {
            vector<string> temp = split(s, " ");
            all_module.push_back(Module(stoi(temp[0]), stoi(temp[1]), stoi(temp[2])));
        }
        ifs.close();
    }

    for (auto m: all_module)
        m.info();
        
    return 0;
}