#include "geometry.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

Matrix::Matrix(int r, int c)
    : m(std::vector<std::vector<float> >(r, std::vector<float>(c, 0.f))),
      rows(r),
      cols(c) {}

<<<<<<< HEAD
Matrix::Matrix(int r, int c) : m(std::vector<std::vector<float> >(r, std::vector<float>(c, 0.f))), rows(r), cols(c) {}

Matrix::Matrix(std::vector<float> nums) {
    assert(nums.size() == 16 || nums.size() == 9);

    rows = 3;
    if (nums.size() == 16) rows = 4;
    cols = rows;

    m = std::vector<std::vector<float>>(rows, std::vector<float>(rows, 0.f));

    for (int i = 0; i < nums.size(); i++) {
        m[i / rows][i % rows] = nums[i];
    }
}


Matrix::Matrix(Vec3f v) {
    rows = 4;
    cols = 1;
    m = std::vector<std::vector<float>> (rows, std::vector<float>(1, 1.f));
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
}

=======
int Matrix::nrows() { return rows; }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d

int Matrix::ncols() { return cols; }


double det(Matrix &m) {
    assert(m.nrows() == m.ncols());
    if (m.nrows() == 1) {
        return m[0][0];
    }
    if (m.nrows() == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }
    double result = 0;
    for (int i = 0; i < m.nrows(); i++) {
        Matrix submatrix(m.nrows() - 1, m.ncols() - 1);
        for (int j = 1; j < m.nrows(); j++) {
            for (int k = 0; k < m.ncols(); k++) {
                if (k < i) {
                    submatrix[j - 1][k] = m[j][k];
                } else if (k > i) {
                    submatrix[j - 1][k - 1] = m[j][k];
                }
            }
        }
        result += m[0][i] * det(submatrix) * ((i % 2 == 0) ? 1 : -1);
    }
    return result;
}


Matrix Matrix::identity(int dimensions) {
    Matrix E(dimensions, dimensions);
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            E[i][j] = (i == j ? 1.f : 0.f);
        }
    }
    return E;
}

<<<<<<< HEAD
std::vector<float> &Matrix::operator[](const int i) {
=======
std::vector<float>& Matrix::operator[](const int i) {
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    assert(i >= 0 && i < rows);
    return m[i];
}

Matrix Matrix::operator*(const Matrix &a) {
    assert(cols == a.rows);
    Matrix result(rows, a.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.m[i][j] = 0.f;
            for (int k = 0; k < cols; k++) {
                result.m[i][j] += m[i][k] * a.m[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix &a) {
    assert(cols == a.cols && rows == a.rows);
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.m[i][j] = m[i][j] + a.m[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const float b) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.m[i][j] = m[i][j] * b;
        }
    }
    return result;
}

Matrix Matrix::transpose() {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++)
<<<<<<< HEAD
        for (int j = 0; j < cols; j++)
            result[j][i] = m[i][j];
=======
        for (int j = 0; j < cols; j++) result[j][i] = m[i][j];
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    return result;
}

Matrix Matrix::inverse() {
    assert(rows == cols);
<<<<<<< HEAD
    // augmenting the square matrix with the identity matrix of the same dimensions a => [ai]
    Matrix result(rows, cols * 2);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = m[i][j];
    for (int i = 0; i < rows; i++)
        result[i][i + cols] = 1;
    // first pass
    for (int i = 0; i < rows - 1; i++) {
        // normalize the first row
        for (int j = result.cols - 1; j >= 0; j--)
            result[i][j] /= result[i][i];
=======
    // augmenting the square matrix with the identity matrix of the same
    // dimensions a => [ai]
    Matrix result(rows, cols * 2);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) result[i][j] = m[i][j];
    for (int i = 0; i < rows; i++) result[i][i + cols] = 1;
    // first pass
    for (int i = 0; i < rows - 1; i++) {
        // normalize the first row
        for (int j = result.cols - 1; j >= 0; j--) result[i][j] /= result[i][i];
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
        for (int k = i + 1; k < rows; k++) {
            float coeff = result[k][i];
            for (int j = 0; j < result.cols; j++) {
                result[k][j] -= result[i][j] * coeff;
            }
        }
    }
    // normalize the last row
    for (int j = result.cols - 1; j >= rows - 1; j--)
        result[rows - 1][j] /= result[rows - 1][rows - 1];
    // second pass
    for (int i = rows - 1; i > 0; i--) {
        for (int k = i - 1; k >= 0; k--) {
            float coeff = result[k][i];
            for (int j = 0; j < result.cols; j++) {
                result[k][j] -= result[i][j] * coeff;
            }
        }
    }
    // cut the identity matrix back
    Matrix truncate(rows, cols);
    for (int i = 0; i < rows; i++)
<<<<<<< HEAD
        for (int j = 0; j < cols; j++)
            truncate[i][j] = result[i][j + cols];
    return truncate;
}

std::ostream &operator<<(std::ostream &s, Matrix &m) {
=======
        for (int j = 0; j < cols; j++) truncate[i][j] = result[i][j + cols];
    return truncate;
}

std::ostream& operator<<(std::ostream& s, Matrix& m) {
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    for (int i = 0; i < m.nrows(); i++) {
        for (int j = 0; j < m.ncols(); j++) {
            s << m[i][j];
            if (j < m.ncols() - 1) s << "\t";
        }
        s << "\n";
    }
    return s;
}

<<<<<<< HEAD
Matrix operator*(float b, Matrix &m) {
=======
Matrix operator*(float b, Matrix& m) {
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    Matrix result(m.nrows(), m.ncols());
    for (int i = 0; i < result.nrows(); i++) {
        for (int j = 0; j < result.ncols(); j++) {
            result.m[i][j] = m[i][j] * b;
        }
    }
    return result;
}




