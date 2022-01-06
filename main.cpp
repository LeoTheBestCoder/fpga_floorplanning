#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> arch;


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

void construct_map(int R, int C, int S, int D) {
    vector<char> single_row;
    int col = S;
    for (int _ = 0; _ < S; _++) {
        single_row.push_back('C');
    }
    while (col < C) {
        if ((col - S) % D == 0)
            single_row.push_back('M');
        else
            single_row.push_back('C');
        col++;
    }
    for (int _ = 0; _ < R; _++) {
        arch.push_back(single_row);
    }
    
}

void print_map() {
    for (const auto line: arch) {
        for (const auto ch: line) {
            // cout << ch << " ";
            cout << ch;
        }
        cout << "\n";
    }
    cout << "\n";
}


int main(int argc, char** argv) {
    string arch_file = argv[1], module_file = argv[2], net_file = argv[3], floorplan_file = argv[4];

    ifstream ifs_arch("benchmarks/" + arch_file, ios::in);
    ifstream ifs_module("benchmarks/" + module_file, ios::in);

    vector<Module> all_module;

    // set FPGA architecture
    int R, C, S, D;
    string FPGA_arch;
    getline(ifs_arch, FPGA_arch);
    ifs_arch.close();
    R = stoi(split(FPGA_arch, " ")[0]);
    C = stoi(split(FPGA_arch, " ")[1]);
    S = stoi(split(FPGA_arch, " ")[2]);
    D = stoi(split(FPGA_arch, " ")[3]);
    printf("R = %d, C = %d, S = %d, D = %d\n", R, C, S, D);
    
    construct_map(R, C, S, D);
    print_map();
    exit(0);


    if (!ifs_module.is_open())
        cout << "fail to open file\n";
    else {
        string s;
        while (getline(ifs_module, s)) {
            vector<string> temp = split(s, " ");
            all_module.push_back(Module(stoi(temp[0]), stoi(temp[1]), stoi(temp[2])));
        }
        ifs_module.close();
    }

    for (auto m: all_module)
        m.info();
        
    return 0;
}