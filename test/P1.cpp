#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
#include <fstream>

using namespace std;

class Matrix {
private:
    vector<vector<int>> mat;

public:
    Matrix(unsigned int rows, unsigned int cols) {
        mat.resize(rows, vector<int>(cols));
    }

    void load(istream &is) {
        unsigned int rows, cols;
        is >> rows >> cols;
        
        if(rows > mat.max_size() || cols > mat[0].max_size()) {
            throw std::length_error("Matrix size is too large");
        }
        
        mat.resize(rows, vector<int>(cols));
        for(auto& row: mat) for(auto& val: row) is >> val;
    }

    Matrix operator*(const Matrix &rhs) const {
        unsigned int rows = mat.size();
        unsigned int cols = rhs.mat[0].size();
        Matrix result(rows, cols);
        for(unsigned int i = 0; i < rows; i++) {
            for(unsigned int j = 0; j < cols; j++) {
                result.mat[i][j] = 0;
                for(unsigned int k = 0; k < rhs.mat.size(); k++) {
                    result.mat[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        return result;
    }

    void print(int colWidth) const {
        string divider = string(colWidth * mat[0].size(), '-');
        cout << divider << endl;
        for(const auto& row: mat) {
            for(const auto& val: row) {
                cout << '|' << setw(colWidth) << val;
            }
            cout << '|' << endl << divider << endl;
        }
    }
};

int main() {
    ifstream file1("f1.txt"), file2("f2.txt");
    int colWidth = 6;

    Matrix mat1(0,0), mat2(0,0);
    
    try {
        mat1.load(file1);
        mat2.load(file2);
    } catch (const std::length_error &le) {
        cerr << "Error loading matrix: " << le.what() << endl;
        return 1;
    }

    Matrix result = mat1 * mat2;
    result.print(colWidth);
    return 0;
}