#include "Rhombus.h"

Rhombus::Rhombus(Point p1, Point p2, Point p3, Point p4)
: p1_(p1), p2_(p2), p3_(p3), p4_(p4) {
    if (Vector(p1_, p2_).length() == Vector(p1_, p4_).length()
        && Vector(p3_, p4_).length() == Vector(p2_, p3_).length()
        && Vector(p1_, p2_).length() == Vector(p2_, p3_).length()) {

    } else if (Vector(p1_, p4_).length() == Vector(p1_, p3_).length()
           && Vector(p2_, p3_).length() == Vector(p2_, p4_).length()
           && Vector(p1_, p4_).length() == Vector(p2_, p4_).length()) {
        std::swap(p2_, p3_);
    } else if (Vector(p1_, p3_).length() == Vector(p1_, p2_).length()
              && Vector(p2_, p4_).length() == Vector(p3_, p4_).length()
              && Vector(p1_, p2_).length() == Vector(p2_, p4_).length()) {
        std::swap(p3_, p4_);
    } else {
        throw std::logic_error("This is not rhombus, sides arent equal");
    }
}

double Rhombus::Area() const {
    return Vector(p1_, p3_).length() * Vector(p2_, p4_).length() / 2;
}

Point Rhombus::Center() const {
    return (p1_ + p3_) / 2;
}

void Rhombus::Print(std::ostream& os) const {
    os << "Rhombus, p1: " << p1_ << ", p2: " << p2_ << ", p3: " << p3_ << ", p4: " << p4_;
}

void Rhombus::Scan(std::istream &is) {
    Point p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Rhombus(p1,p2,p3,p4);
}