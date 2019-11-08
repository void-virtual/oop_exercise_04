#include <iostream>
#include <type_traits>
#include <tuple>
#include <string>
#include "Point.h"
#include "Pentagon.h"


using namespace std;

template <typename T>
struct is_point : false_type {};

template <>
struct is_point<Point> : true_type {};

template <typename T> //площадь для всего, что имеет площадь
decltype(declval<const T&>().Area()) area(const T& figure) {
    return figure.Area();
}

template <typename T> //центр для всего, что имеет центр
decltype(declval<const T&>().Center()) center(const T& figure) {
    return figure.Center();
}

template <typename T, typename PrintReturnType = decltype(declval<const T&>().Print(cout))> //вывод для классов с функцией Print
ostream& operator << (ostream& os, const T& figure) {
    figure.Print(os);
    return os;
}

template <typename T, typename PrintReturnType = decltype(declval<T&>().Scan(cin))> //вывод для классов с функцией Print
istream& operator >> (istream& is, const T& figure) {
    figure.Scan(is);
    return is;
}

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...>> : //проверяет, является ли T кортежом, из которых можно составить фигуру
        conjunction<is_point<Head>, is_same<Head, Tail>...> {};

template<size_t Id, class T>
double compute_area(const T& tuple) {
    if constexpr (Id >= tuple_size_v<T>){
        return 0;
    }else{
        const auto dx1 = std::get<Id - 0>(tuple).x - std::get<0>(tuple).x;
        const auto dy1 = std::get<Id - 0>(tuple).y - std::get<0>(tuple).y;
        const auto dx2 = std::get<Id - 1>(tuple).x - std::get<0>(tuple).x;
        const auto dy2 = std::get<Id - 1>(tuple).y - std::get<0>(tuple).y;
        const double local_area = std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
        return local_area + compute_area<Id + 1>(tuple);
    }
}

template<typename T>
std::enable_if_t<is_figurelike_tuple<T>::value, double> area(const T& object) {
    if constexpr (tuple_size_v<T> < 3){
        return 0;
    }else{
        return compute_area<2>(object);
    }
}


template<size_t Id, typename T>
Point compute_center(const T& tuple) {
    if constexpr (Id == tuple_size_v<T> - 1){
        return get<Id>(tuple);
    }else{
        return get<Id>(tuple) + compute_center<Id + 1>(tuple);
    }
}


template<typename T>
std::enable_if_t<is_figurelike_tuple<T>::value, Point> center(const T& object) {
    return compute_center<0>(object) / tuple_size_v<T>;
}

template<size_t Id, typename T>
void print_tuple(ostream& os, const T& tuple) {
    if constexpr (Id == tuple_size_v<T> - 1) {
        os << "(" << get<Id>(tuple) << ")";
    } else {
        os << "(" << get<Id>(tuple) << ") ";
        print_tuple<Id + 1>(os, tuple);
    }
}

template <typename T>
typename enable_if<is_figurelike_tuple<T>::value, ostream&>::type operator << (ostream& os, const T& tuple) {
    os << "Figurelike tuple of " << tuple_size_v<T> << " elements: ";
    print_tuple<0>(os, tuple);
    return os;
}

template<size_t Id, typename T>
void scan_tuple(istream& is, T& tuple) {
    if constexpr (Id == tuple_size_v<T> - 1) {
        is >> get<Id>(tuple);
    } else {
        is >> get<Id>(tuple);
        scan_tuple<Id + 1>(is, tuple);
    }
}

template <typename T>
typename enable_if<is_figurelike_tuple<T>::value, istream&>::type operator >> (istream& is, T& tuple) {
    scan_tuple<0>(is, tuple);
    return is;
}

int main() {
    return 0;
}