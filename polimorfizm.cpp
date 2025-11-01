/*#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс Shape
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

    // Виртуальные методы
    virtual void display() const {
        cout << "Фигура '" << name << "' в позиции (" << x << ", " << y << ")" << endl;
    }

    virtual double getArea() const {
        return 0.0;
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    string getName() const { return name; }
};

// Класс Rectangle (прямоугольник)
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

// Класс Triangle (треугольник)
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
    cout << "\n=== Демонстрация полиморфизма ===" << endl;

    // Создание объектов разных классов через указатели на базовый класс
    cout << "\n1. Создание объектов через указатели на Shape:" << endl;
    Shape* shape1 = new Rectangle("Rect 1", 0, 0, 10, 5);
    Shape* shape2 = new Triangle("Tri 1", 5, 5, 8, 6);
    Shape* shape3 = new Shape("Simple Shape", 2, 2);

    cout << "\n2. Вызов виртуальных методов:" << endl;
    shape1->display();  // Вызовется Rectangle::display()
    shape2->display();  // Вызовется Triangle::display()
    shape3->display();  // Вызовется Shape::display()

    cout << "\n3. Площади фигур:" << endl;
    cout << "Площадь " << shape1->getName() << ": " << shape1->getArea() << endl;
    cout << "Площадь " << shape2->getName() << ": " << shape2->getArea() << endl;
    cout << "Площадь " << shape3->getName() << ": " << shape3->getArea() << endl;

    cout << "\n4. Удаление объектов:" << endl;
    delete shape1;
    delete shape2;
    delete shape3;
}

/*
int main_polimorf() {
    cout << "=== ПРОГРАММА 3: ПОЛИМОРФИЗМ ===" << endl;
    demoPolymorphism();
    return 0;
}
*/