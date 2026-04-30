#pragma once
#include "abstract_decimal.h"
#include <iostream>
#include <stdexcept>

class Fraction : public Decimal {
private:
    int* numer_;
    int* denom_;

public:
    Fraction();
    Fraction(int numer, int denom);
    Fraction(const Fraction& other);
    Fraction(Fraction&& other);
    Fraction& operator=(const Fraction& other);
    Fraction& operator=(Fraction&& other);
    ~Fraction();

    double convertToDecimal() override;

    friend Fraction operator+(const Fraction& a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, const Fraction& b);
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};
