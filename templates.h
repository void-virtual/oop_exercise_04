#pragma once

template <typename T>
struct is_point : std::false_type {};

template <typename T>
struct is_point<Point<T>> : std::true_type {};

template <typename T, typename = void, typename = void, typename = void, typename = void>
struct is_figure : std::false_type {};

template <typename T>
struct is_figure<T,
        std::void_t<decltype(std::declval<const T&>().Area())>,
        std::void_t<decltype(std::declval<const T&>().Center())>,
        std::void_t<decltype(std::declval<const T&>().Print(std::cout))>,
        std::void_t<decltype(std::declval<T&>().Scan(std::cin))>> : std::true_type {};

template <typename T> //площадь для всего, что имеет площадь
decltype(std::declval<const T&>().Area()) area(const T& figure) {
    return figure.Area();
}

template <typename T> //центр для всего, что имеет центр
decltype(std::declval<const T&>().Center()) center(const T& figure) {
    return figure.Center();
}

template <typename T, typename PrintReturnType = decltype(std::declval<const T&>().Print(std::cout))> //вывод для классов с функцией Print
std::ostream& operator << (std::ostream& os, const T& figure) {
    figure.Print(os);
    return os;
}

template <typename T, typename PrintReturnType = decltype(std::declval<T&>().Scan(std::cin))> //вывод для классов с функцией Print
std::istream& operator >> (std::istream& is, T& figure) {
    figure.Scan(is);
    return is;
}

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...>> : //проверяет, является ли T кортежом, из которых можно составить фигуру
        std::conjunction<is_point<Head>, std::is_same<Head, Tail>...> {};

template<size_t Id, class T>
double compute_area(const T& tuple) {
    if constexpr (Id >= std::tuple_size_v<T>){
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
    if constexpr (std::tuple_size_v<T> < 3){
        return 0;
    }else{
        return compute_area<2>(object);
    }
}


template<size_t Id, typename T>
std::tuple_element_t<0,T> compute_center(const T& tuple) {
    if constexpr (Id == std::tuple_size_v<T> - 1){
        return std::get<Id>(tuple);
    } else {
        return std::get<Id>(tuple) + compute_center<Id + 1>(tuple);
    }
}


template<typename T>
std::enable_if_t<is_figurelike_tuple<T>::value, std::tuple_element_t<0,T>> center(const T& object) {
    return compute_center<0>(object) / std::tuple_size_v<T>;
}

template<size_t Id, typename T>
void print_tuple(std::ostream& os, const T& tuple) {
    if constexpr (Id == std::tuple_size_v<T> - 1) {
        os << "(" << std::get<Id>(tuple) << ")";
    } else {
        os << "(" << std::get<Id>(tuple) << ") ";
        print_tuple<Id + 1>(os, tuple);
    }
}

template <typename T>
typename std::enable_if<is_figurelike_tuple<T>::value, std::ostream&>::type operator << (std::ostream& os, const T& tuple) {
    os << "Figurelike tuple of " << std::tuple_size_v<T> << " elements: ";
    print_tuple<0>(os, tuple);
    return os;
}

template<size_t Id, typename T>
void scan_tuple(std::istream& is, T& tuple) {
    if constexpr (Id == std::tuple_size_v<T> - 1) {
        is >> std::get<Id>(tuple);
    } else {
        is >> std::get<Id>(tuple);
        scan_tuple<Id + 1>(is, tuple);
    }
}

template <typename T>
typename std::enable_if<is_figurelike_tuple<T>::value, std::istream&>::type operator >> (std::istream& is, T& tuple) {
    scan_tuple<0>(is, tuple);
    return is;
}

template <typename T>
typename std::enable_if<is_figurelike_tuple<T>::value, void>::type process(T& tup) {
    std::cin >> tup;
    std::cout << tup << "\n";
    std::cout << "Area of figurelike tuple: " << area(tup) << "\n";
    std::cout << "Center of figurelike tuple: " << center(tup) << "\n";

}

template <typename T>
typename std::enable_if<is_figure<T>::value, void>::type process(T& fig) {
    std::cin >> fig;
    std::cout << fig << "\n";
    std::cout << "Area of figure: " << area(fig) << "\n";
    std::cout << "Center of figure: " << center(fig) << "\n";

}