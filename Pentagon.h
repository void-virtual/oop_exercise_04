#pragma once

#include "Point.h"

template <typename T>
class Pentagon {
public:
    Pentagon() = default;
    explicit Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5);
    Point<T> Center() const;
    double Area() const;
    void Print(std::ostream& os) const;
    void Scan(std::istream& is);

private:
    Point<T> p1_, p2_, p3_, p4_, p5_;
};

template <typename T>
Pentagon<T>::Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4, const Point<T>& p5)
        : p1_(p1), p2_(p2), p3_(p3), p4_(p4), p5_(p5) {}

template <typename T>
double Pentagon<T>::Area() const {
    return
            point_and_line_distance(p1_, p2_, p3_) * Vector<T>(p2_, p3_).length() / 2
            + point_and_line_distance(p1_, p3_, p4_) * Vector<T>(p3_, p4_).length() / 2
            + point_and_line_distance(p1_, p4_, p5_) * Vector<T>(p4_, p5_).length() / 2;
}

template <typename T>
Point<T> Pentagon<T>::Center() const {
    return (p1_ + p2_ + p3_ + p4_ + p5_) / 5;
}

template <typename T>
void Pentagon<T>::Print(std::ostream& os) const {
    os << "Pentagon, p1: " << p1_ << ", p2: " << p2_ << ", p3: " << p3_ << ", p4: " << p4_ << ", p5: " << p5_;
}

template <typename T>
void Pentagon<T>::Scan(std::istream &is) {
    Point<T> p1, p2, p3, p4, p5;
    is >> p1 >> p2 >> p3 >> p4 >> p5;
    *this = Pentagon(p1,p2,p3,p4,p5);
}