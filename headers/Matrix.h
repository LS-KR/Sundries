
#ifndef H_MATRIX
#define H_MATRIX

class Matrix {
public:
    Matrix(unsigned int rows, unsigned int cols);
    ~Matrix();
    Matrix operator+(Matrix m);
    Matrix operator-(Matrix m);
    Matrix operator*(Matrix m);
    double Get(unsigned int row, unsigned int col);
    void Set(unsigned int row, unsigned int col, double number);
    unsigned int getRows();
    unsigned int getCols();
    bool operator==(Matrix m);
private:
    unsigned int rows;
    unsigned int cols;
    double* data;
};

#endif