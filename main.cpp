#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

// ========== КЛАСС POINT ==========
class Point {
protected:
    int x;
    int y;
    string name;
public:
    // Конструкторы
    Point() {
        x = 0; y = 0; name = "Unnamed Point";
        cout << "Вызван конструктор Point() для " << name << endl;
    }

    Point(int xVal, int yVal, string pointName) {
        x = xVal; y = yVal; name = pointName;
        cout << "Вызван конструктор Point(int, int, string) для " << name << endl;
    }

    // Конструктор копирования
    Point(const Point& other) {
        x = other.x; y = other.y; name = other.name + " (copy)";
        cout << "Вызван конструктор копирования Point(const Point&) для " << name << endl;
    }

    // Деструктор
    ~Point() {
        cout << "Вызван деструктор ~Point() для " << name << endl;
    }

    // Методы
    void setX(int xVal) { x = xVal; }
    void setY(int yVal) { y = yVal; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setName(string pointName) { name = pointName; }
    string getName() const { return name; }

    void display() const {
        cout << "Точка '" << name << "': (" << x << ", " << y << ")" << endl;
    }

    void move(int dx, int dy) {
        cout << "Перемещаем точку '" << name << "' на (" << dx << ", " << dy << ")" << endl;
        x += dx; y += dy;
    }
};

// Демонстрация Point
void demoPoint() {
    cout << "\n=== ПРОГРАММА 1: БАЗОВЫЙ КЛАСС POINT ===" << endl;

    cout << "\n1. Создание статического объекта:" << endl;
    Point staticPoint;
    staticPoint.setName("Static Point");
    staticPoint.display();

    cout << "\n2. Создание объекта с параметрами:" << endl;
    Point paramPoint(5, 15, "Parameter Point");
    paramPoint.display();

    cout << "\n3. Создание копии объекта:" << endl;
    Point copiedPoint = paramPoint;
    copiedPoint.setName("Copied Point");
    copiedPoint.display();

    cout << "\n4. Создание динамического объекта:" << endl;
    Point* dynamicPoint = new Point(100, 200, "Dynamic Point");
    dynamicPoint->display();

    cout << "\n5. Работа с методами:" << endl;
    dynamicPoint->move(50, -25);
    dynamicPoint->display();

    cout << "\n6. Удаление динамического объекта:" << endl;
    delete dynamicPoint;

    cout << "\n7. Конец программы" << endl;
}

// ========== КЛАСС CIRCLE ==========
class Circle : public Point {
private:
    double radius;
    static constexpr double PI = 3.14159;
public:
    // Конструкторы
    Circle() : Point(), radius(1.0) {
        name = "Unnamed Circle";
        cout << "Circle() для " << name << endl;
    }

    Circle(int xVal, int yVal, double r, string circleName)
        : Point(xVal, yVal, circleName), radius(r) {
        cout << "Circle(int, int, double, string) для " << name << endl;
    }

    // Деструктор
    ~Circle() {
        cout << "~Circle() для " << name << endl;
    }

    // Переопределение метода display
    void display() const  {
        cout << "Окружность '" << name << "': центр(" << getX() << ", " << getY()
            << "), радиус=" << radius << ", площадь=" << getArea() << endl;
    }

    // Новые методы
    double getArea() const {
        return PI * radius * radius;
    }

    void setRadius(double r) { radius = r; }
    double getRadius() const { return radius; }
};

// Демонстрация наследования
void demoInheritance() {
    cout << "\n=== ПРОГРАММА 2: НАСЛЕДОВАНИЕ CIRCLE ОТ POINT ===" << endl;

    cout << "\n1. Создание Circle:" << endl;
    Circle circle1(10, 20, 5.0, "My Circle");
    circle1.display();

    cout << "\n2. Вызов переопределенного метода:" << endl;
    circle1.display();

    cout << "\n3. Вызов унаследованного метода move():" << endl;
    circle1.move(5, -5);
    circle1.display();

    cout << "\n4. Создание копии Circle:" << endl;
    Circle circle2 = circle1;
    circle2.setName("Copied Circle");
    circle2.display();

    cout << "\n5. Динамическое создание Circle:" << endl;
    Circle* dynamicCircle = new Circle(0, 0, 3.0, "Dynamic Circle");
    dynamicCircle->display();

    cout << "\n6. Удаление динамического Circle:" << endl;
    delete dynamicCircle;

    cout << "\n7. Конец программы" << endl;
}

// ========== КЛАССЫ ДЛЯ ПОЛИМОРФИЗМА ==========
class Shape {
protected:
    string name;
    int x, y;
public:
    Shape(string shapeName, int xVal = 0, int yVal = 0)
        : name(shapeName), x(xVal), y(yVal) {
        cout << "Shape() для " << name << endl;
    }

    virtual ~Shape() {
        cout << "~Shape() для " << name << endl;
    }

    virtual void display() const {
        cout << "Фигура '" << name << "' в позиции (" << x << ", " << y << ")" << endl;
    }

    virtual double getArea() const {
        return 0.0;
    }

    string getName() const { return name; }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(string rectName, int x, int y, double w, double h)
        : Shape(rectName, x, y), width(w), height(h) {
        cout << "Rectangle() для " << name << endl;
    }

    ~Rectangle() {
        cout << "~Rectangle() для " << name << endl;
    }

    void display() const override {
        cout << "Прямоугольник '" << name << "': позиция(" << x << ", " << y
            << "), размеры " << width << "x" << height
            << ", площадь=" << getArea() << endl;
    }

    double getArea() const override {
        return width * height;
    }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(string triName, int x, int y, double b, double h)
        : Shape(triName, x, y), base(b), height(h) {
        cout << "Triangle() для " << name << endl;
    }

    ~Triangle() {
        cout << "~Triangle() для " << name << endl;
    }

    void display() const override {
        cout << "Треугольник '" << name << "': позиция(" << x << ", " << y
            << "), основание=" << base << ", высота=" << height
            << ", площадь=" << getArea() << endl;
    }

    double getArea() const override {
        return 0.5 * base * height;
    }
};

// Демонстрация полиморфизма
void demoPolymorphism() {
    cout << "\n=== ПРОГРАММА 3: ПОЛИМОРФИЗМ ===" << endl;

    cout << "\n1. Создание объектов через указатели на Shape:" << endl;
    Shape* shape1 = new Rectangle("Rect 1", 0, 0, 10, 5);
    Shape* shape2 = new Triangle("Tri 1", 5, 5, 8, 6);
    Shape* shape3 = new Shape("Simple Shape", 2, 2);

    cout << "\n2. Вызов виртуальных методов:" << endl;
    shape1->display();
    shape2->display();
    shape3->display();

    cout << "\n3. Площади фигур:" << endl;
    cout << "Площадь " << shape1->getName() << ": " << shape1->getArea() << endl;
    cout << "Площадь " << shape2->getName() << ": " << shape2->getArea() << endl;
    cout << "Площадь " << shape3->getName() << ": " << shape3->getArea() << endl;

    cout << "\n4. Удаление объектов:" << endl;
    delete shape1;
    delete shape2;
    delete shape3;
}

// ========== MAIN ФУНКЦИЯ ==========
int main() {
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 2: ОБЪЕКТЫ И КЛАССЫ ===" << endl;
    cout << "ВЫБЕРИТЕ ПРОГРАММУ:" << endl;
    cout << "1 - Базовый класс Point" << endl;
    cout << "2 - Наследование Circle" << endl;
    cout << "3 - Полиморфизм" << endl;
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        demoPoint();
        break;
    case 2:
        demoInheritance();
        break;
    case 3:
        demoPolymorphism();
        break;
    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    cout << "\n=== Конец лабораторной работы ===" << endl;
    return 0;
}