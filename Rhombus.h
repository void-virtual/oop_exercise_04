#pragma once
#include "Point.h"

template <typename T>
class Rhombus {
public:
    Rhombus() = default;
    Rhombus(Point<T> p1_, Point<T> p2_, Point<T> p3_, Point<T> p4_);
    Point<T> Center() const;
    double Area() const;
    void Print(std::ostream& os) const;
    void Scan(std::istream& is);

private:
    Point<T> p1_, p2_, p3_, p4_;
};

template <typename T>
Rhombus<T>::Rhombus(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4)
        : p1_(p1), p2_(p2), p3_(p3), p4_(p4) {
    if (Vector<T>(p1_, p2_).length() == Vector<T>(p1_, p4_).length()
        && Vector<T>(p3_, p4_).length() == Vector<T>(p2_, p3_).length()
        && Vector<T>(p1_, p2_).length() == Vector<T>(p2_, p3_).length()) {

    } else if (Vector<T>(p1_, p4_).length() == Vector<T>(p1_, p3_).length()
               && Vector<T>(p2_, p3_).length() == Vector<T>(p2_, p4_).length()
               && Vector<T>(p1_, p4_).length() == Vector<T>(p2_, p4_).length()) {
        std::swap(p2_, p3_);
    } else if (Vector<T>(p1_, p3_).length() == Vector<T>(p1_, p2_).length()
               && Vector<T>(p2_, p4_).length() == Vector<T>(p3_, p4_).length()
               && Vector<T>(p1_, p2_).length() == Vector<T>(p2_, p4_).length()) {
        std::swap(p3_, p4_);
    } else {
        throw std::logic_error("This is not rhombus, sides arent equal");
    }
}

template <typename T>
double Rhombus<T>::Area() const {
    return Vector<T>(p1_, p3_).length() * Vector<T>(p2_, p4_).length() / 2;
}

template <typename T>
Point<T> Rhombus<T>::Center() const {
    return (p1_ + p3_) / 2;
}

template <typename T>
void Rhombus<T>::Print(std::ostream& os) const {
    os << "Rhombus, p1: " << p1_ << ", p2: " << p2_ << ", p3: " << p3_ << ", p4: " << p4_;
}

template <typename T>
void Rhombus<T>::Scan(std::istream &is) {
    Point<T> p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Rhombus(p1,p2,p3,p4);
}