
#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(unsigned int rows, unsigned int cols) {
    this->rows = rows;
    this->cols = cols;
    this->data = new double[rows * cols];
}

Matrix::~Matrix() {
    delete [] this->data;
}

unsigned int Matrix::getRows() {
    return this->rows;
}

unsigned int Matrix::getCols() {
    return this->cols;
}

double Matrix::Get(unsigned int row, unsigned int col) {
    if (row >= this->rows)
        throw std::invalid_argument("invalid row");
    if (col >= this->cols)
        throw std::invalid_argument("invalid col");
    return this->data[row * this->cols + col];
}

void Matrix::Set(unsigned int row, unsigned int col, double number) {
    if (row >= this->rows)
        throw std::invalid_argument("invalid row");
    if (col >= this->cols)
        throw std::invalid_argument("invalid col");
    this->data[row * this->cols + col] = number;
}

Matrix Matrix::operator+(Matrix m) {
    if ((this->cols != m.cols) || (this->rows != m.rows))
        throw std::invalid_argument("The number of rows and columns of the matrix is not match");
    Matrix result(this->rows, this->cols);
    for (unsigned int i = 0; i < this->rows; ++i) {
        for (unsigned int j = 0; j < this->cols; ++j) {
            result.Set(i, j, this->data[i * this->rows + j] + m.data[i * m.rows + j]);
        }
    }
    return result;
}

Matrix Matrix::operator-(Matrix m) {
    if ((this->cols != m.cols) || (this->rows != m.rows))
        throw std::invalid_argument("The number of rows and columns of the matrix is not match");
    Matrix result(this->rows, this->cols);
    for (unsigned int i = 0; i < this->rows; ++i) {
        for (unsigned int j = 0; j < this->cols; ++j) {
            result.Set(i, j, this->data[i * this->rows + j] - m.data[i * m.rows + j]);
        }
    }
    return result;
}

Matrix Matrix::operator*(Matrix m) {
    unsigned int r = this->rows;
    unsigned int c = m.cols;
    Matrix result(r, c);
    for (unsigned int i = 0; i < r; ++i) {
        for (unsigned int j = 0; j < c; ++j) {
            double number = 0;
            unsigned int k = 0;
            do {
                number += this->Get(i, k) * m.Get(k, j);
            } while((++k) < ((this->getCols() < m.getRows()) ? this->getCols() : m.getRows()));
            result.Set(i, j, number);
        }
    }
    return result;
}

bool Matrix::operator==(Matrix m) {
    if ((this->cols != m.cols) || (this->rows != m.rows))
        throw std::invalid_argument("The number of rows and columns of the matrix is not match");
    for (unsigned int i = 0; i < m.getRows(); ++i) {
        for (unsigned int j = 0; j < m.getCols(); ++j) {
            if (this->Get(i, j) != m.Get(i, j)) return false;
        }
    }
    return true;
}