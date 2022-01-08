#include <bits/stdc++.h>
#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define GREEN "\033[0;32;32m"
using namespace std;

vector<vector<char>> arch;
int R, C, S, D;

int prev_height;
int highest_in_the_row;
int start_row;

class Module {
private:
    int _clb, _mul, _idx;
    int _r = 0, _c = 0;
    int _w, _h;
    // r, c stand for the upper left corner

public:
    Module(int idx, int clb, int mul) {
        _idx = idx;
        _clb = clb;
        _mul = mul;
    }
    int get_idx() {
        return _idx;
    }
    int get_clb() {
        return _clb;
    }
    int get_mul() {
        return _mul;
    }
    void set_pos(int r, int c, int w, int h) {
        _r = r;
        _c = c;
        _w = w;
        _h = h;
    }
    vector <int> get_pos() {
        return {_r, _c};
    }
    void showinfo() {
        printf("Module No.%3d: clb = %3d, mul = %3d, pos = (r=%d, c=%d)\n", _idx, _clb, _mul, _r, _c);
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

void construct_map() {
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
    int r = 0;
    printf("    ");
    for (int i = 0; i < C; i++) {
        if (i % 10 == 0) 
            printf("%d", (int)i/10);
        else 
            printf(" ");
        
    }
    printf("\n    ");
    for (int i = 0; i < C; i++) {
        printf("%d", i % 10);
    }
    printf("\n");
    for (const auto line: arch) {
        printf("%3d ", r);
        r++;
        for (const auto ch: line) {
            // cout << ch << " ";
            // cout << ch;
            if (ch != 'C' && ch != 'M')
                printf(GREEN"%c", ch);
            else
                printf(NONE"%c", ch);
        }
        // cout << "\n";
        printf("\n");
    }
    printf("\n");
    // cout << "\n";
}


inline bool comp(Module& a, Module& b) {
    return a.get_mul() != b.get_mul() ? a.get_mul() > b.get_mul() : a.get_clb() > b.get_clb();
}


void drawX(int r, int c, int w, int h, int idx) {
    for (int i = r; i < r + h; i++) {
        for (int j = c; j < c + w; j++) {
            // arch[i][j] = idx + '0';
            arch[i][j] = 'X';
        }
    }
}


void place(Module& m) {
    int left_col, upper_row, acc_R = 0;
    int height, width;
    int clb_needed = m.get_clb(), mul_needed = m.get_mul(), idx = m.get_idx();
    int clb_included = 0, mul_included = 0;
    int r = start_row;
    bool same_row = true;
    bool can_put = false;
    printf("=====================\n");
    printf("Placing Module No.%3d\n", idx);
    while (r < R) {
        // printf("searching row %3d ...\n", r);
        // printf("highest in the row is %d\n", highest_in_the_row);
        for (int c = 0; c < C; c++) {
            if (arch[r][c] != 'C' && arch[r][c] != 'M')    // this position is already occupied
                continue;
            else {
                upper_row = r;
                left_col = c;
                if (mul_needed == 0) 
                    height = prev_height;
                else
                    height = mul_needed * 3 <= R ? mul_needed * 3 : R;
                width = 1;
                // printf("r = %d, c = %d, height = %d, mul need: %d, clb need: %d\n", r, c, height, mul_needed, clb_needed);

                if (c == 0 && mul_needed > 0) {
                    highest_in_the_row = mul_needed * 3;
                }
                else if (c == 0 && mul_needed == 0) {
                    highest_in_the_row = prev_height;
                }

                if (arch[r][c + width - 1] == 'C')
                    clb_included += 1 * height;
                if (arch[r][c + width - 1] == 'M')
                    mul_included += (int) height / 3;

                // printf("mul inc = %d, clb inc = %d (origin)\n", mul_included, clb_included);
                if (mul_included >= mul_needed && clb_included >= clb_needed) {
                        can_put = true;
                        start_row = r;
                        prev_height = height;
                        printf("Module No.%3d is put at (r, c) = (%3d, %3d) with (w, h) = (%2d, %2d)\n", idx, upper_row, left_col, width, height);
                        drawX(upper_row, left_col, width, height, idx);
                        return;
                }
                while (mul_included < mul_needed || clb_included < clb_needed) {
                    width++;
                    if (c + width - 1 > C - 1) {
                        same_row = false;
                        break;
                    }
                    if (arch[r][c + width - 1] == 'C')
                        clb_included += 1 * height;
                    if (arch[r][c + width - 1] == 'M')
                        mul_included += (int) height / 3;
                    // printf("mul inc = %d, clb inc = %d\n", mul_included, clb_included);
                    if (mul_included >= mul_needed && clb_included >= clb_needed) {
                        can_put = true;
                        start_row = r;
                        prev_height = height;
                        printf("Module No.%3d is put at (r, c) = (%3d, %3d) with (w, h) = (%2d, %2d)\n", idx, upper_row, left_col, width, height);
                        drawX(upper_row, left_col, width, height, idx);
                        return;
                    }
                }
                if (!same_row) {
                    mul_included = 0;
                    clb_included = 0;
                    break;
                }
            }
        }
        mul_included = 0;
        clb_included = 0;
        r += highest_in_the_row;
    }
}



int main(int argc, char** argv) {
    string arch_file = argv[1], module_file = argv[2], net_file = argv[3], floorplan_file = argv[4];

    ifstream ifs_arch("benchmarks/" + arch_file, ios::in);
    ifstream ifs_module("benchmarks/" + module_file, ios::in);

    vector<Module> all_module;

    // set FPGA architecture
    string FPGA_arch;
    getline(ifs_arch, FPGA_arch);
    ifs_arch.close();
    R = stoi(split(FPGA_arch, " ")[0]);
    C = stoi(split(FPGA_arch, " ")[1]);
    S = stoi(split(FPGA_arch, " ")[2]);
    D = stoi(split(FPGA_arch, " ")[3]);
    construct_map();
    // print_map();

    // save all the modules and sort them by (mul, clb)
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

    sort(all_module.begin(), all_module.end(), comp);

    for (auto m: all_module) {
        // m.showinfo();
        place(m);
        print_map();
    }
        
    return 0;
}