#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iterator>

struct Point {
    const double x;
    const double y;
    const std::string name;

    // Конструктор
    Point(double x_, double y_, std::string name_) 
        : x(x_), y(y_), name(std::move(name_)) {}

    // Метод создания из строки 
    static Point fromString(const std::string& line) {
        std::istringstream iss(line);
        double x, y;
        std::string name;
        if (iss >> x >> y) {
            std::getline(iss >> std::ws, name);
            return Point{x, y, name};
        }
        return Point{0.0, 0.0, ""}; 
    }

    // Преобразование в строку 
    std::string toString() const {
        std::ostringstream oss;
        oss << x << " " << y << " " << name;
        return oss.str();
    }
};

// Сложение двух точек
Point addPoints(const Point& a, const Point& b) {
    return Point{
        a.x + b.x,
        a.y + b.y,
        a.name + b.name
    };
}

// Чтение всех строк из файла как вектор строк 
std::vector<std::string> readFileLines(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    return lines;
}

// Преобразование вектора строк в вектор Point
std::vector<Point> mapToPoints(const std::vector<std::string>& lines) {
    std::vector<Point> points;
    points.reserve(lines.size());
    std::transform(lines.begin(), lines.end(), std::back_inserter(points),
                   &Point::fromString);
    return points;
}

// Преобразование вектора Point в вектор строк
std::vector<std::string> mapToStrings(const std::vector<Point>& points) {
    std::vector<std::string> strings;
    strings.reserve(points.size());
    std::transform(points.begin(), points.end(), std::back_inserter(strings),
                   [](const Point& p) { return p.toString(); });
    return strings;
}

// Запись вектора строк в файл 
void writeFileLines(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename);
    std::for_each(lines.begin(), lines.end(),
                  [&file](const std::string& line) {
                      file << line << "\n";
                  });
}

std::vector<Point> loadPointsFromFile(const std::string& filename) {
    return mapToPoints(readFileLines(filename));
}

// Строки  записать в файл
void savePointsToFile(const std::string& filename, const std::vector<Point>& points) {
    writeFileLines(filename, mapToStrings(points));
}

// Сложение двух векторов Point 
std::vector<Point> zipWithAdd(const std::vector<Point>& v1, const std::vector<Point>& v2) {
    if (v1.size() != v2.size()) {
        throw std::runtime_error("Vectors must have same size");
    }
    std::vector<Point> result;
    result.reserve(v1.size());
    std::transform(v1.begin(), v1.end(), v2.begin(), std::back_inserter(result),
                   &addPoints);
    return result;
}

// Взять два файла, сложить точки, вернуть новый вектор
std::vector<Point> transformFiles(const std::string& file1, const std::string& file2) {
    auto v1 = loadPointsFromFile(file1);
    auto v2 = loadPointsFromFile(file2);
    return zipWithAdd(v1, v2);
}

int main() {
    try {
        // Выполняем преобразование
        auto transformed = transformFiles("name1", "name2");

        // Записываем результат в name1 
        savePointsToFile("name1", transformed);

        std::cout << "Преобразование завершено. Обработано точек: " 
                  << transformed.size() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
