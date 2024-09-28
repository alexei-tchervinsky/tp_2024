#include "T3.hpp"
#include <algorithm>
#include <functional>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Filename not provided!" << std::endl;
        return 1;
    }

    std::vector<std::shared_ptr<Polygon>> polygons;
    readPolygonsFromFile(argv[1], polygons);

    std::string command;
    while (std::getline(std::cin, command)) {
        processCommand(command, polygons);
    }

    return 0;
}

void readPolygonsFromFile(const std::string& filename,
    std::vector<std::shared_ptr<Polygon>>& polygons) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Polygon polygon;
        int vertexCount;
        if (!(iss >> vertexCount)) continue;

        polygon.points.reserve(vertexCount);
        for (int i = 0; i < vertexCount; ++i) {
            char open, semicolon, close;
            Point p;
            if (iss >> open >> p.x >> semicolon >> p.y >> close
                && open == '(' && semicolon == ';' && close == ')') {
                polygon.points.push_back(p);
            }
            else {
                polygon.points.clear();
                break;
            }
        }

        if (polygon.points.size() == vertexCount) {
            polygons.push_back(std::make_shared<Polygon>(polygon));
        }
    }
}

void processCommand(const std::string& command,
    const std::vector<std::shared_ptr<Polygon>>& polygons) {
    std::istringstream iss(command);
    std::string cmd, args;
    if (!(iss >> cmd)) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }
    std::getline(iss, args);

    if (cmd == "AREA") {
        commandArea(args, polygons);
    }
    else if (cmd == "MAX") {
        commandMax(args, polygons);
    }
    else if (cmd == "MIN") {
        commandMin(args, polygons);
    }
    else if (cmd == "COUNT") {
        commandCount(args, polygons);
    }
    else if (cmd == "LESSAREA") {
        commandLessArea(args, polygons);
    }
    else if (cmd == "SAME") {
        commandSame(args, polygons);
    }
    else {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

void commandArea(const std::string& args,
    const std::vector<std::shared_ptr<Polygon>>& polygons) {
    std::istringstream iss(args);
    std::string param;
    if (!(iss >> param)) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }

    if (param == "MEAN") {
        if (polygons.empty()) {
            std::cout << 0.0 << std::endl;
            return;
        }
        double totalArea = 0.0;
        for (const auto& polygon : polygons) {
            totalArea += calculateArea(*polygon);
        }
        std::cout << std::fixed << std::setprecision(1)
            << (totalArea / polygons.size()) << std::endl;
    }
    else {
        bool even = (param == "EVEN");
        double totalArea = 0.0;
        for (const auto& polygon : polygons) {
            if ((polygon->points.size() % 2 == 0) == even) {
                totalArea += calculateArea(*polygon);
            }
        }
        std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
    }
}

void commandMax(const std::string& args,
    const std::vector<std::shared_ptr<Polygon>>& polygons) {
    if (polygons.empty()) {
        std::cout << 0 << std::endl;
        return;
    }

    std::istringstream iss(args);
    std::string param;
    if (!(iss >> param)) {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
    }

    if (param == "AREA") {
        // Use std::max_element with a lambda for comparison
        std::shared_ptr<Polygon> maxElem = *std::max_element(
            polygons.begin(), polygons.end(),
            [](const std::shared_ptr<Polygon>& a, const std::shared_ptr<Polygon>& b) {
                return calculateArea(*a) < calculateArea(*b);
            });
        std::cout << std::fixed << std::setprecision(1) << calculateArea(*maxElem)
            << std::endl;
    }
    else if (param == "VERTEXES") {
        std::shared_ptr<Polygon> maxElem = *std::max_element(
            polygons.begin(), polygons.end(),
            [](const std::shared_ptr<Polygon>& a, const std::shared_ptr<Polygon>& b) {
                return a->points.size() < b->points.size();
            });
        std::cout << maxElem->points.size() << std::endl;
    }
    else {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

// Similar refactoring applies to the other command functions...