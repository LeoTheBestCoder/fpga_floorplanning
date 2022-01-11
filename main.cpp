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
string arch_file, module_file, net_file, floorplan_file;

class Module {
private:
    int _clb, _mul, _idx;
    int _r = 0, _c = 0;
    int _w = 0, _h = 0;
    bool put;
    // r, c stand for the upper left corner

public:
    Module(int idx, int clb, int mul) {
        _idx = idx;
        _clb = clb;
        _mul = mul;
        put = false;
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
    vector<int> get_size() {
        return {_w, _h};
    }
    void showinfo() {
        printf("Module No.%3d: clb = %3d, mul = %3d, (r, c) = (%3d, %3d), (w, h) = (%2d, %2d), put = %d\n", _idx, _clb, _mul, _r, _c, _w, _h, put);
    }
    void put_success() {
        put = true;
    }
    bool status() {
        return put;
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
            printf("%d", (int)i/10 % 10);
        else 
            printf(" ");
        
    }
    printf("\n    ");
    for (int i = 0; i < C; i++) {
        printf("%d", i % 10);
    }
    printf("\n");
    for (const auto line: arch) {
        printf(NONE"%3d ", r);
        r++;
        for (const auto ch: line) {
            // cout << ch << " ";
            // cout << ch;
            if (ch == 'X')
                printf(GREEN"%c", ch);
            else if (ch == 'V')
                printf(RED"%c", ch);
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

void drawV(int r, int c, int w, int h, int idx) {
    for (int i = r; i < r + h; i++) {
        for (int j = c; j < c + w; j++) {
            // arch[i][j] = idx + '0';
            arch[i][j] = 'V';
        }
    }
}


void place(Module& m) {
    int acc_R = 0;
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
                    printf("Module No.%3d is put at (r, c) = (%3d, %3d) with (w, h) = (%2d, %2d)\n", idx, r, c, width, height);
                    drawX(r, c, width, height, idx);
                    m.set_pos(r, c, width, height);
                    m.put_success();
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
                        printf("Module No.%3d is put at (r, c) = (%3d, %3d) with (w, h) = (%2d, %2d)\n", idx, r, c, width, height);
                        drawX(r, c, width, height, idx);
                        m.set_pos(r, c, width, height);
                        m.put_success();
                        // m.showinfo();
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


void global_search(Module& m) {
    // int acc_R = 0;
    int height, width;
    int clb_needed = m.get_clb(), mul_needed = m.get_mul(), idx = m.get_idx();
    int clb_included = 0, mul_included = 0;
    // int r = start_row;
    bool same_row = true;
    bool can_put = false;
    printf("=====================\n");
    printf("Placing Module No.%3d\n", idx);
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (arch[r][c] != 'C' && arch[r][c] != 'M')    // this position is already occupied
                continue;
            else {
                if (mul_needed == 0) 
                    height = 1;
                else
                    height = mul_needed * 3 <= R ? mul_needed * 3 : R;
                width = 1;

                if (arch[r][c + width - 1] == 'C')
                    clb_included += 1 * height;
                if (arch[r][c + width - 1] == 'M')
                    mul_included += (int) height / 3;

                if (mul_included >= mul_needed && clb_included >= clb_needed) {
                    can_put = true;
                    start_row = r;
                    prev_height = height;
                    printf("Module No.%3d is put at (r, c) = (%3d, %3d) with (w, h) = (%2d, %2d)\n", idx, r, c, width, height);
                    drawV(r, c, width, height, idx);
                    m.set_pos(r, c, width, height);
                    m.put_success();
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
                    if (mul_included >= mul_needed && clb_included >= clb_needed) {
                        can_put = true;
                        start_row = r;
                        prev_height = height;
                        printf("Module No.%3d is put at (r, c) = (%3d, %3d) with (w, h) = (%2d, %2d)\n", idx, r, c, width, height);
                        drawV(r, c, width, height, idx);
                        m.set_pos(r, c, width, height);
                        m.put_success();
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
    }
}


double calcHPWL() {
    double total = 0.0;
    ifstream ifs_net("benchmarks/" + net_file, ios::in);
    ifstream ifs_flr("outputs/" + arch_file.substr(0, 5) + ".floorplan");
    map<int, double> center_x_dict;
    map<int, double> center_y_dict;
    map<int, vector<int>> net;
    string s, n;

    while (getline(ifs_flr, s)) {
        vector<string> temp = split(s, " ");
        center_x_dict[stoi(temp[0])] = stoi(temp[3]) % 2 != 0 ? stoi(temp[1]) + stoi(temp[3]) / 2 : (double)(stoi(temp[1]) + (double)(stoi(temp[3]) - 1) / 2);
        center_y_dict[stoi(temp[0])] = stoi(temp[4]) % 2 != 0 ? stoi(temp[2]) + stoi(temp[4]) / 2 : (double)(stoi(temp[2]) + (double)(stoi(temp[4]) - 1) / 2);
    }
    ifs_flr.close();
    
    while (getline(ifs_net, n)) {
        n.erase(remove(n.begin(), n.end(), '{'), n.end());
        n.erase(remove(n.begin(), n.end(), '}'), n.end());
        // cout << n << "\n";
        vector<string> temp2 = split(n, " ");
        vector<double> c_x, c_y;
        for (int i = 1; i < temp2.size(); i++) {
            c_x.push_back(center_x_dict[stoi(temp2[i])]);
            c_y.push_back(center_y_dict[stoi(temp2[i])]);
        }
        // for (int i = 0; i < c_x.size(); i++) {
        //     printf("c_x = %lf, c_y = %lf\n", c_x[i], c_y[i]);
        // }
        total += (double)*max_element(c_x.begin(), c_x.end()) - (double)*min_element(c_x.begin(), c_x.end());
        total += (double)*max_element(c_y.begin(), c_y.end()) - (double)*min_element(c_y.begin(), c_y.end());
        // printf("delta x = %lf, delta y = %lf, HPWL = %lf\n", (double)*max_element(c_x.begin(), c_x.end()) - (double)*min_element(c_x.begin(), c_x.end()), 
        //                                                      (double)*max_element(c_y.begin(), c_y.end()) - (double)*min_element(c_y.begin(), c_y.end()), 
        //                                                      total);
    }
    ifs_net.close();

    
    return total;
}



int main(int argc, char** argv) {
    arch_file = argv[1];
    module_file = argv[2];
    net_file = argv[3];
    floorplan_file = argv[4];

    ifstream ifs_arch("benchmarks/" + arch_file, ios::in);
    ifstream ifs_module("benchmarks/" + module_file, ios::in);
    ofstream ofs_floorplan;
    ofs_floorplan.open("outputs/" + arch_file.substr(0, 5) + ".floorplan");

    vector<Module> all_module;
    double HPWL;

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

    for (auto &m: all_module) {
        place(m);
        m.showinfo();
        // print_map();
    }
    for (auto &m: all_module) {
        // if (m.status())
        //     printf("Module No.%3d is placed successfully!\n", m.get_idx());
        // else
        //     printf("Module No.%3d needs global search.\n", m.get_idx());
        if (!m.status()) {
            printf("Module No.%3d needs global search.\n", m.get_idx());
            global_search(m);
            printf("After global search, it's placed at (r, c) = (%3d, %3d) with (w, h) = (%3d, %3d)\n", m.get_pos()[0], m.get_pos()[1], m.get_size()[0], m.get_size()[1]);
            // print_map();
        }
    }
    printf("=====================\n      FINISH\n=====================\n");
    print_map();
    printf(NONE);
    if (!ofs_floorplan.is_open())
        cout << "fail to write file\n";
    else {
        for (auto m: all_module) {
            // printf("%d %d %d\n", R, m.get_pos()[0], m.get_size()[1]);
            ofs_floorplan << m.get_idx() << " " << m.get_pos()[1] << " "  << R - m.get_pos()[0] - m.get_size()[1] << " "
                          << m.get_size()[0] << " " << m.get_size()[1] << "\n";
            m.showinfo();
        }
        ofs_floorplan.close();
    }
    HPWL = calcHPWL();
    printf("HPWL = %lf\n", HPWL);
    return 0;
}