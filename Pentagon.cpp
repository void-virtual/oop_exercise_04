//
// Created by ilya on 13.10.2019.
//

#include "Pentagon.h"

Pentagon::Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5)
        : p1_(p1), p2_(p2), p3_(p3), p4_(p4), p5_(p5) {}

double Pentagon::Area() const {
    return
            point_and_line_distance(p1_, p2_, p3_) * Vector(p2_, p3_).length() / 2
            + point_and_line_distance(p1_, p3_, p4_) * Vector(p3_, p4_).length() / 2
            + point_and_line_distance(p1_, p4_, p5_) * Vector(p4_, p5_).length() / 2;
}

Point Pentagon::Center() const {
    return (p1_ + p2_ + p3_ + p4_ + p5_) / 5;
}

void Pentagon::Print(std::ostream& os) const {
    os << "Pentagon, p1: " << p1_ << ", p2: " << p2_ << ", p3: " << p3_ << ", p4: " << p4_ << ", p5: " << p5_;
}

void Pentagon::Scan(std::istream &is) {
    Point p1, p2, p3, p4, p5;
    is >> p1 >> p2 >> p3 >> p4 >> p5;
    *this = Pentagon(p1,p2,p3,p4,p5);
}