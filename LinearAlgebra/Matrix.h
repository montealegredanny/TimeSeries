#pragma once
#pragma once
#include <vector>
#include <iostream>

class Matrix 
{
    private:
        std::vector<std::vector<double>> m_data;

    public:
        // rule of 5
        Matrix() : m_data() {};
        Matrix(std::vector<std::vector<double>> mat);
        Matrix(const Matrix& other); 
        Matrix(Matrix&& other) noexcept; 
        Matrix& operator=(const Matrix& other); 
        Matrix& operator=(Matrix&& other) noexcept;                                  
        ~Matrix(); // destructor

        // overload some operators
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
        friend Matrix operator* (const double scale, const Matrix& mat);
        friend Matrix operator* (const Matrix& mat,  const double scale);
        friend Matrix operator+ (const Matrix& left, const Matrix& right);
        friend Matrix operator- (const Matrix& left, const Matrix& right);
        friend Matrix operator* (const Matrix& left, const Matrix& right);
        static Matrix MatMul(const Matrix& left, const Matrix& right);

        // getter setter methods 
        std::vector<std::vector<double>> getData() const; 
        double get(int i, int j) const;
        int getNumRows() const;
        int getNumCols() const;
        void set(int i, int j, double val);

        // misc 
        Matrix transpose() const; 
};

