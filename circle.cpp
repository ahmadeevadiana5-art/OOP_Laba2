#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Базовый класс Point (упрощенная версия)
class Point {
protected:
    int x;
    int y;
    string name;

public:
    // Конструкторы
    Point() : x(0), y(0), name("Unnamed Point") {
        cout << "Point() для " << name << endl;
    }

    Point(int xVal, int yVal, string pointName) : x(xVal), y(yVal), name(pointName) {
        cout << "Point(int, int, string) для " << name << endl;
    }

    Point(const Point& other) : x(other.x), y(other.y), name(other.name + " (copy)") {
        cout << "Point(const Point&) для " << name << endl;
    }

    // Деструктор
    virtual ~Point() {
        cout << "~Point() для " << name << endl;
    }

    // Методы
    virtual void display() const {
        cout << "Точка '" << name << "': (" << x << ", " << y << ")" << endl;
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    string getName() const { return name; }
    void setName(string newName) { name = newName; }
    int getX() const { return x; }
    int getY() const { return y; }
};

// Класс-наследник Circle (Окружность)
class Circle : public Point {
private:
    double radius;
    static constexpr double M_PI = 3.14;

public:
    // Конструкторы
    Circle() : Point(), radius(1.0) {
        name = "Unnamed Circle";
        cout << "Circle() для " << name << endl;
    }

    // Конструктор с параметрами - используем список инициализации
    Circle(int xVal, int yVal, double r, string circleName)
        : Point(xVal, yVal, circleName), radius(r) {
        cout << "Circle(int, int, double, string) для " << name << endl;
    }

    // Конструктор копирования
    Circle(const Circle& other)
        : Point(other), radius(other.radius) {
        name = other.name + " (copy)";
        cout << "Circle(const Circle&) для " << name << endl;
    }

    // Деструктор
    ~Circle() {
        cout << "~Circle() для " << name << endl;
    }

    // Переопределение метода display
    void display() const override {
        cout << "Окружность '" << name << "': центр(" << x << ", " << y
            << "), радиус=" << radius << ", площадь=" << getArea() << endl;
    }

    // Новые методы
    double getArea() const {
        return M_PI * radius * radius;
    }

    double getCircumference() const {
        return 2 * M_PI * radius;
    }

    void setRadius(double r) {
        radius = r;
    }

    double getRadius() const {
        return radius;
    }
};

// Демонстрация наследования
void demoInheritance() {
    cout << "\n=== Демонстрация наследования: Circle наследует от Point ===" << endl;

    // Создание объекта Circle
    cout << "\n1. Создание Circle:" << endl;
    Circle circle1(10, 20, 5.0, "My Circle");
    circle1.display();

    // Проверка переопределенного метода
    cout << "\n2. Вызов переопределенного метода:" << endl;
    circle1.display();

    // Вызов унаследованного метода
    cout << "\n3. Вызов унаследованного метода move():" << endl;
    circle1.move(5, -5);
    circle1.display();

    // Создание копии
    cout << "\n4. Создание копии Circle:" << endl;
    Circle circle2 = circle1;
    circle2.setName("Copied Circle");
    circle2.display();

    // Динамическое создание
    cout << "\n5. Динамическое создание Circle:" << endl;
    Circle* dynamicCircle = new Circle(0, 0, 3.0, "Dynamic Circle");
    dynamicCircle->display();

    cout << "\n6. Удаление динамического Circle:" << endl;
    delete dynamicCircle;

    cout << "\n7. Конец функции demoInheritance()" << endl;
}

int main() {
    cout << "=== ПРОГРАММА 2: НАСЛЕДОВАНИЕ ===" << endl;
    demoInheritance();
    return 0;
}