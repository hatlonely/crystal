//
//  matrix.hpp
//  CALCULATOR
//
//  Created by hatlonely on 16/10/9.
//
//

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <exception>

template <typename T>
class Matrix {
    std::vector<std::vector<T>> _vvt;
    size_t _m = 0;
    size_t _n = 0;
    
    friend std::ostream& operator << (std::ostream& out, const Matrix<T>& matrix) {
        out << "{" << std::endl;
        for (const auto& vt : matrix._vvt) {
            out << "    {";
            std::copy(vt.begin(), vt.end(), std::ostream_iterator<T>(out, ", "));
            out << "}" << std::endl;
        }
        out << "}";
        return out;
    }
public:
    Matrix(const std::initializer_list<std::initializer_list<T>>& llt);
    Matrix(const std::vector<std::vector<T>>& vvt);
    Matrix(std::vector<std::vector<T>>&& vvt);
    Matrix add(const Matrix& matrix) const;
    Matrix sub(const Matrix& matrix) const;
    Matrix mul(const Matrix& matrix) const;
    Matrix mul(const T& num) const;
    
    std::string toString() const;
};

class MatrixException : public std::exception {
    std::string _message;
public:
    MatrixException(const std::string& message="") : _message(message) {}
    const char* what() const noexcept {
        return _message.c_str();
    }
    
    template <typename T>
    MatrixException& operator << (const T& t) {
        std::stringstream ss;
        ss << t;
        _message += ss.str();
        
        return *this;
    }
};

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& llt) {
    if (llt.size() != 0) {
        _m = llt.size();
        _n = llt.begin()->size();
        _vvt.reserve(llt.size());
        for (const auto& lt : llt) {
            if (lt.size() != _n) {
                throw MatrixException() << "each list size should be same";
            }
            _vvt.push_back(lt);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& vvt) {
    if (!vvt.empty()) {
        _m = vvt.size();
        _n = vvt.begin()->size();
        _vvt.reserve(vvt.size());
        for (const auto& vt : vvt) {
            if (vt.size() != _n) {
                throw MatrixException() << "each list size should be same";
            }
            _vvt.push_back(vt);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>>&& vvt) {
    std::cout << "xiaokeai" << std::endl;
    _vvt.swap(vvt);
}

template <typename T>
std::string Matrix<T>::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

template <typename T>
Matrix<T> Matrix<T>::add(const Matrix<T>& matrix) const {
    if (matrix._m != _m || matrix._n != _n) {
        throw MatrixException() << "add operation (" << _m << ", " << _n << ") should equal "
              << "matrix(" << matrix._m << ", " << matrix._n << ")";
    }
    
    std::vector<std::vector<T>> vvt;
    vvt.resize(_m);
    for (size_t i = 0; i < _m; i++) {
        vvt[i].resize(_n);
        for (size_t j = 0; j < _n; j++) {
            vvt[i][j] = _vvt[i][j] + matrix._vvt[i][j];
        }
    }

    return Matrix<T>(std::move(vvt));
}

template <typename T>
Matrix<T> Matrix<T>::sub(const Matrix& matrix) const {
    if (matrix._m != _m || matrix._n != _n) {
        throw MatrixException() << "sub operation (" << _m << ", " << _n << ") should equal "
              << "matrix(" << matrix._m << ", " << matrix._n << ")";
    }
    
    std::vector<std::vector<T>> vvt;
    vvt.resize(_m);
    for (size_t i = 0; i < _m; i++) {
        vvt[i].resize(_n);
        for (size_t j = 0; j < _n; j++) {
            vvt[i][j] = _vvt[i][j] - matrix._vvt[i][j];
        }
    }
    
    return Matrix<T>(std::move(vvt));
}

template <typename T>
Matrix<T> Matrix<T>::mul(const Matrix<T>& matrix) const {
    if (_n != matrix._m) {
        throw MatrixException() << "mul operation this.n[" << _n << "] is not equal other.m["
              << matrix._m << "]";
    }
    
    std::vector<std::vector<T>> vvt;
    vvt.resize(_m);
    for (size_t i = 0; i < _m; i++) {
        vvt[i].resize(matrix._n);
        for (size_t j = 0; j < matrix._n; j++) {
            vvt[i][j] = T();
            for (size_t k = 0; k < _n; k++) {
                vvt[i][j] += _vvt[i][k] * matrix._vvt[k][j];
            }
        }
    }
    
    return Matrix<T>(std::move(vvt));
}

template <typename T>
Matrix<T> Matrix<T>::mul(const T& num) const {
    std::vector<std::vector<T>> vvt;
    vvt.resize(_m);
    for (size_t i = 0; i < _m; i++) {
        vvt[i].resize(_n);
        for (size_t j = 0; j < _n; j++) {
            vvt[i][j] = _vvt[i][j] * num;
        }
    }
    
    return Matrix<T>(std::move(vvt));
}
