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


// ========== КОМПОЗИЦИЯ: КЛАСС LINE ==========
class Line {
private:
    Point start;  // композиция - объект Point
    Point end;    // композиция - объект Point  
    string name;

public:
    // Конструктор с списком инициализации
    Line(int x1, int y1, int x2, int y2, string lineName)
        : start(x1, y1, "Start"), end(x2, y2, "End"), name(lineName) {
        cout << "Line() для " << name << endl;
    }

    ~Line() {
        cout << "~Line() для " << name << endl;
    }

    void display() const {
        cout << "Линия '" << name << "':" << endl;
        cout << "  Начало: "; start.display();
        cout << "  Конец: "; end.display();
    }
};




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

    // Метод, демонстрирующий доступ к protected полям предка
    void demonstrateProtectedAccess() {
        cout << "Демонстрация protected доступа в Circle:" << endl;
        cout << "  Можно напрямую обращаться к protected полям:" << endl;
        cout << "  x = " << x << ", y = " << y << ", name = " << name << endl;

        // Можем изменять protected поля
        x += 10;
        y += 10;
        name += " (modified)";
        cout << "  После изменения: x = " << x << ", y = " << y << ", name = " << name << endl;
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



// ========== КОМПОЗИЦИЯ С УКАЗАТЕЛЯМИ: КЛАСС POLYLINE ==========
class Polyline {
private:
    vector<Point*> points;  // композиция через указатели
    string name;

public:
    // Конструктор
    Polyline(string polyName) : name(polyName) {
        cout << "Polyline() для " << name << endl;
    }

    // Деструктор - удаляем все точки
    ~Polyline() {
        cout << "~Polyline() для " << name << " - удаление " << points.size() << " точек" << endl;
        for (Point* point : points) {
            delete point;
        }
        points.clear();
    }

    // Добавление точки
    void addPoint(int x, int y, string pointName) {
        Point* newPoint = new Point(x, y, pointName);
        points.push_back(newPoint);
        cout << "Добавлена точка '" << pointName << "' в Polyline '" << name << "'" << endl;
    }

    void display() const {
        cout << "Ломаная '" << name << "' содержит " << points.size() << " точек:" << endl;
        for (size_t i = 0; i < points.size(); ++i) {
            cout << "  Точка " << i + 1 << ": ";
            points[i]->display();
        }
    }

    // Метод для демонстрации разницы между объектом и указателем
    void demonstratePointerVsObject() {
        if (points.size() >= 2) {
            cout << "\n--- Демонстрация разницы объекта и указателя ---" << endl;

            // Создаем копию объекта
            Point pointCopy = *points[0];
            pointCopy.setName("Копия объекта");
            pointCopy.setX(999);

            // Создаем копию указателя
            Point* pointerCopy = points[0];
            pointerCopy->setName("Копия указателя");

            cout << "После изменений:" << endl;
            cout << "Оригинал: "; points[0]->display();
            cout << "Копия объекта: "; pointCopy.display();
            cout << "Копия указателя: "; pointerCopy->display();
        }
    }
};

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

    cout << "\n7. Копирование указателей:" << endl;
    Point* original = new Point(1, 2, "Original");
    Point* copyPtr = original;  // Оба указывают на один объект

    cout << "original: "; original->display();
    cout << "copyPtr: "; copyPtr->display();

    original->setX(100);  // Меняем через original
    cout << "После изменения через original:" << endl;
    cout << "original: "; original->display();
    cout << "copyPtr: "; copyPtr->display();  // copyPtr тоже видит изменения!

    delete original;

    cout << "\n8. Конец программы" << endl;
}

// Демонстрация композиции
void demoComposition() {
    cout << "\n=== ДЕМОНСТРАЦИЯ КОМПОЗИЦИИ ОБЪЕКТОВ ===" << endl;

    cout << "\n1. Создание Line с композицией Point:" << endl;
    Line line(0, 0, 10, 10, "My Line");
    line.display();

    cout << "\n2. Конец функции - автоматическое удаление Line и его компонентов" << endl;
}

// Демонстрация композиции с указателями и protected доступа
void demoAdvancedFeatures() {
    cout << "\n=== ДЕМОНСТРАЦИЯ РАСШИРЕННЫХ ВОЗМОЖНОСТЕЙ ===" << endl;

    cout << "\n1. Композиция с указателями (Polyline):" << endl;
    Polyline polyline("Моя ломаная");
    polyline.addPoint(0, 0, "Точка A");
    polyline.addPoint(10, 10, "Точка B");
    polyline.addPoint(20, 5, "Точка C");
    polyline.display();

    cout << "\n2. Демонстрация разницы объект vs указатель:" << endl;
    polyline.demonstratePointerVsObject();

    cout << "\n3. Демонстрация protected доступа:" << endl;
    Circle circle(5, 5, 2.0, "Test Circle");
    circle.demonstrateProtectedAccess();

    cout << "\n4. Автоматическое удаление при выходе из области видимости:" << endl;
    // Polyline автоматически удалит все свои точки в деструкторе
}

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

    cout << "\n5. Сравнение MyBase* obj = new MyDeriv() vs MyBase obj = MyDeriv():" << endl;

    // Правильно - через указатель (работает полиморфизм)
    Shape* polyShape = new Rectangle("Poly Rect", 0, 0, 4, 3);
    cout << "Shape* polyShape = new Rectangle(): ";
    polyShape->display();  // Вызывается Rectangle::display()

    // Проблема - объект напрямую (не работает полиморфизм)
    Shape slicedShape = Rectangle("Sliced Rect", 0, 0, 4, 3);
    cout << "Shape slicedShape = Rectangle(): ";
    slicedShape.display();  // Вызывается Shape::display() - slicing problem!

    delete polyShape;
}

// ========== MAIN ФУНКЦИЯ ==========
int main() {
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 2: ОБЪЕКТЫ И КЛАССЫ ===" << endl;
    cout << "Выберите программу:" << endl;
    cout << "1 - Базовый класс Point" << endl;
    cout << "2 - Композиция объектов" << endl;
    cout << "3 - Наследование Circle" << endl;
    cout << "4 - Полиморфизм" << endl;
    cout << "5 - Другие, композиция с указателямидав" << endl;
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        demoPoint();
        break;
    case 2:
        demoComposition();
        break;
    case 3:
        demoInheritance();
        break;
    case 4:
        demoPolymorphism();
        break;
    case 5:
        demoAdvancedFeatures();
        break;
    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    cout << "\n=== Конец лабораторной работы ===" << endl;
    return 0;
}