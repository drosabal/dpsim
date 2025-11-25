#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <limits>
#include <chrono>
#include <cstdint>

using namespace std;

constexpr char CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> random_bool(0, 1);
uniform_int_distribution<int> random_char(0, sizeof(CHARS) - 2);

void dp_wacs(string& str1, string& str2, map<char, double>& w, double d);
void dp_maximal_square(vector<vector<char>>& b);
void print_error();
string random_str(int size);
vector<vector<char>> random_bool_matrix(int m, int n);

int main()
{
    int algo = 0;
    int data = 0;
    int str_size = 0;
    double d = 0.0;
    int64_t gen_time;
    int64_t run_time;

    cout << "1: Weighted approximate common substring" << endl;
    cout << "2: Maximal square" << endl;
    cout << "Choose DP algorithm: ";
    cin >> algo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;

    if (algo == 1) {
        cout << "1: w = 1, d = 10" << endl;
        cout << "2: w = relative frequency of letter" << endl;
    } else if (algo == 2) {
        cout << "1: 10 x 10 matrix" << endl;
        cout << "2: 10 x 100 matrix" << endl;
        cout << "3: 10 x 1000 matrix" << endl;
        cout << "4: 100 x 1000 matrix" << endl;
        cout << "5: 1000 x 1000 matrix" << endl;
    } else {
        print_error();
        return 1;
    }
    cout << "Choose data to simulate: ";
    cin >> data;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (algo == 1) {
        if (data == 2) {
            cout << "d: ";
            cin >> d;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "String size: ";
        cin >> str_size;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << endl;

    auto t1 = chrono::high_resolution_clock::now();
    auto t2 = t1;
    auto t3 = t1;
    if (algo == 1 && data == 1) {
        map<char, double> w = {
            {'A', 1.0},
            {'B', 1.0},
            {'C', 1.0},
            {'D', 1.0},
            {'E', 1.0},
            {'F', 1.0},
            {'G', 1.0},
            {'H', 1.0},
            {'I', 1.0},
            {'J', 1.0},
            {'K', 1.0},
            {'L', 1.0},
            {'M', 1.0},
            {'N', 1.0},
            {'O', 1.0},
            {'P', 1.0},
            {'Q', 1.0},
            {'R', 1.0},
            {'S', 1.0},
            {'T', 1.0},
            {'U', 1.0},
            {'V', 1.0},
            {'W', 1.0},
            {'X', 1.0},
            {'Y', 1.0},
            {'Z', 1.0}
        };
        d = 10.0;
        string str1 = random_str(str_size);
        string str2 = random_str(str_size);
        t2 = chrono::high_resolution_clock::now();
        dp_wacs(str1, str2, w, d);
        t3 = chrono::high_resolution_clock::now();
    } else if (algo == 1 && data == 2) {
        map<char, double> w = {
            {'A', 8.2},
            {'B', 1.5},
            {'C', 2.8},
            {'D', 4.3},
            {'E', 12.7},
            {'F', 2.2},
            {'G', 2.0},
            {'H', 6.1},
            {'I', 7.0},
            {'J', 0.16},
            {'K', 0.77},
            {'L', 4.0},
            {'M', 2.4},
            {'N', 6.7},
            {'O', 7.5},
            {'P', 1.9},
            {'Q', 0.12},
            {'R', 6.0},
            {'S', 6.3},
            {'T', 9.1},
            {'U', 2.8},
            {'V', 0.98},
            {'W', 2.4},
            {'X', 0.15},
            {'Y', 2.0},
            {'Z', 0.074}
        };
        string str1 = random_str(str_size);
        string str2 = random_str(str_size);
        t2 = chrono::high_resolution_clock::now();
        dp_wacs(str1, str2, w, d);
        t3 = chrono::high_resolution_clock::now();
    } else if (algo == 2 && data == 1) {
        vector<vector<char>> b = random_bool_matrix(10, 10);
        t2 = chrono::high_resolution_clock::now();
        dp_maximal_square(b);
        t3 = chrono::high_resolution_clock::now();
    } else if (algo == 2 && data == 2) {
        vector<vector<char>> b = random_bool_matrix(10, 100);
        t2 = chrono::high_resolution_clock::now();
        dp_maximal_square(b);
        t3 = chrono::high_resolution_clock::now();
    } else if (algo == 2 && data == 3) {
        vector<vector<char>> b = random_bool_matrix(10, 1000);
        t2 = chrono::high_resolution_clock::now();
        dp_maximal_square(b);
        t3 = chrono::high_resolution_clock::now();
    } else if (algo == 2 && data == 4) {
        vector<vector<char>> b = random_bool_matrix(100, 1000);
        t2 = chrono::high_resolution_clock::now();
        dp_maximal_square(b);
        t3 = chrono::high_resolution_clock::now();
    } else if (algo == 2 && data == 5) {
        vector<vector<char>> b = random_bool_matrix(1000, 1000);
        t2 = chrono::high_resolution_clock::now();
        dp_maximal_square(b);
        t3 = chrono::high_resolution_clock::now();
    } else {
        print_error();
        return 1;
    }

    gen_time = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    run_time = chrono::duration_cast<chrono::microseconds>(t3 - t2).count();
    cout << "Data generation time: " << gen_time / 1000.0 << "ms" << endl;
    cout << "Algorithm run time: " << run_time / 1000.0 << "ms" << endl;

    return 0;
}

void dp_wacs(string& str1, string& str2, map<char, double>& w, double d)
{
    int m = str1.size();
    int n = str2.size();
    double best_score = 0.0;
    string best_substr1 = "";
    string best_substr2 = "";
    vector<vector<pair<double, int>>> scores(m, vector<pair<double, int>>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            auto& [score, size] = scores[i][j];
            double s = (str1[i] == str2[j]) ? w[str1[i]] : -d;
            if (i == 0 || j == 0) {
                score = s;
                size = 1;
            } else {
                auto [prev_score, prev_size] = scores[i - 1][j - 1];
                score = prev_score + s;
                size = prev_size + 1;
                if (s > score) {
                    score = s;
                    size = 1;
                }
            }
            if (score > best_score) {
                best_score = score;
                best_substr1 = str1.substr(i - size + 1, size);
                best_substr2 = str2.substr(j - size + 1, size);
            }
        }
    }

    cout << "Best common substring 1: " << best_substr1 << endl;
    cout << "Best common substring 2: " << best_substr2 << endl;
    cout << "Score: " << best_score << endl;
}

void dp_maximal_square(vector<vector<char>>& b)
{
    int m = b.size();
    int n = b[0].size();
    int max_square_size = 0;
    vector<vector<int>> square_sizes(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] != 0) {
                continue;
            }
            if (i == 0 || j == 0) {
                square_sizes[i][j] = 1;
                max_square_size = max(max_square_size, 1);
                continue;
            }
            square_sizes[i][j] = 1 + min({
                square_sizes[i - 1][j],
                square_sizes[i][j - 1],
                square_sizes[i - 1][j - 1]
            });
            max_square_size = max(max_square_size, square_sizes[i][j]);
        }
    }

    cout << "k = " << max_square_size << endl;
}

void print_error()
{
    cout << "Invalid input." << endl;
}

string random_str(int size)
{
    string str;
    str.reserve(size);
    for (int i = 0; i < size; i++) {
        str += CHARS[random_char(gen)];
    }
    return str;
}

vector<vector<char>> random_bool_matrix(int m, int n)
{
    vector<vector<char>> b(m, vector<char>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = random_bool(gen);
        }
    }
    return b;
}
