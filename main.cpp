#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <exception>
#include <tuple>
#include "Point.h"
#include "Trapeze.h"
#include "templates.h"
#include "Rhombus.h"
#include "Pentagon.h"

int main() {
    std::string command;
    while (std::cin >> command) {
        if (command == "exit") {
            break;
        } else if (command == "pentagon") {
            try {
                Pentagon<double> fig;
                process(fig);
            } catch (std::exception& ex) {
                std::cout << ex.what() << "\n";
                continue;
            }
        } else if (command == "rhombus") {
            try {
                Rhombus<double> fig;
                process(fig);
            } catch (std::exception& ex) {
                std::cout << ex.what() << "\n";
                continue;
            }
        } else if (command == "trapeze") {
            try {
                Trapeze<double> fig;
                process(fig);
            } catch (std::exception& ex) {
                std::cout << ex.what() << "\n";
                continue;
            }
        } else if (command == "tuple") {
            int size;
            std::cout << "Enter size of tuple\n";
            std::cin >> size;
            if (size == 3) {
                std::tuple<Point<double>,Point<double>,Point<double>> tuple;
                process(tuple);
            } else if (size == 4) {
                std::tuple<Point<double>,Point<double>,Point<double>,Point<double>> tuple;
                process(tuple);
            } else if (size == 5) {
                std::tuple<Point<double>,Point<double>,Point<double>,Point<double>,Point<double>> tuple;
                process(tuple);
            } else if (size == 5) {
                std::tuple<Point<double>,Point<double>,Point<double>,Point<double>,Point<double>, Point<double>> tuple;
                process(tuple);
            } else {
                std::cout << "Wrong size\n";
                continue;
            }
        } else {
            std::cout << "Wrong type\n";
            continue;
        }
    }
    return 0;
}