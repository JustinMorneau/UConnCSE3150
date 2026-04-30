#include "fraction.h"
#include <iostream>
#include <stdexcept>

Fraction::Fraction() : numer_(new int(0)), denom_(new int(1)) {
    std::cout << "I am in the default constructor" << std::endl;
}

Fraction::Fraction(int numer, int denom) : numer_(nullptr), denom_(nullptr) {
    std::cout << "I am in the custom constructor" << std::endl;
    if (denom == 0) {
        throw std::runtime_error("Can't divide by zero!");
    }
    numer_ = new int(numer);
    denom_ = new int(denom);
}

Fraction::Fraction(const Fraction& other) : numer_(nullptr), denom_(nullptr) {
    std::cout << "I am in the copy constructor" << std::endl;
    if (other.numer_ == nullptr || other.denom_ == nullptr) {
        throw std::runtime_error("can't dereference null pointers");
    }
    numer_ = new int(*other.numer_);
    denom_ = new int(*other.denom_);
}

Fraction::Fraction(Fraction&& other) : numer_(other.numer_), denom_(other.denom_) {
    std::cout << "I am in the move constructor" << std::endl;
    other.numer_ = nullptr;
    other.denom_ = nullptr;
}

Fraction& Fraction::operator=(const Fraction& other) {
    std::cout << "I am in the assignment operator (lvalue)" << std::endl;
    if (this == &other) return *this;
    if (other.numer_ == nullptr || other.denom_ == nullptr) {
        throw std::runtime_error("can't dereference null pointers");
    }
    delete numer_;
    delete denom_;
    numer_ = new int(*other.numer_);
    denom_ = new int(*other.denom_);
    return *this;
}

Fraction& Fraction::operator=(Fraction&& other) {
    std::cout << "I am in the assignment operator (rvalue)" << std::endl;
    if (this == &other) return *this;
    delete numer_;
    delete denom_;
    numer_ = other.numer_;
    denom_ = other.denom_;
    other.numer_ = nullptr;
    other.denom_ = nullptr;
    return *this;
}

Fraction::~Fraction() {
    std::cout << "I am in the destructor" << std::endl;
    delete numer_;
    delete denom_;
}

double Fraction::convertToDecimal() {
    std::cout << "I am in the convertToDecimal" << std::endl;
    if (numer_ == nullptr || denom_ == nullptr) {
        throw std::runtime_error("can't dereference null pointers");
    }
    return static_cast<double>(*numer_) / static_cast<double>(*denom_);
}

Fraction operator+(const Fraction& a, const Fraction& b) {
    std::cout << "I am in the plus operator" << std::endl;
    if (a.numer_ == nullptr || a.denom_ == nullptr || b.numer_ == nullptr || b.denom_ == nullptr) {
        throw std::runtime_error("can't dereference null pointers");
    }
    int new_numer = (*a.numer_) * (*b.denom_) + (*b.numer_) * (*a.denom_);
    int new_denom = (*a.denom_) * (*b.denom_);
    return Fraction(new_numer, new_denom);
}

Fraction operator*(const Fraction& a, const Fraction& b) {
    std::cout << "I am in the multiplication operator" << std::endl;
    if (a.numer_ == nullptr || a.denom_ == nullptr || b.numer_ == nullptr || b.denom_ == nullptr) {
        throw std::runtime_error("can't dereference null pointers");
    }
    int new_numer = (*a.numer_) * (*b.numer_);
    int new_denom = (*a.denom_) * (*b.denom_);
    return Fraction(new_numer, new_denom);
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    std::cout << "I am in the << operator" << std::endl;
    if (f.numer_ == nullptr || f.denom_ == nullptr) {
        throw std::runtime_error("can't dereference null pointers");
    }
    os << *f.numer_ << "/" << *f.denom_;
    return os;
}
