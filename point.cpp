#include <iostream>
#include <string>

using namespace std;

class Point {
private:
    int x;
    int y;

protected:
    string name;

public:
    Point() {
        x = 0;
        y = 0;
        name = "Unnamed Point";
        cout << "Вызван конструктор Point() для " << name << endl;
    }

    Point(int xVal, int yVal, string pointName) {
        x = xVal;
        y = yVal;
        name = pointName;
        cout << "Вызван конструктор Point(int, int, string) для " << name << endl;
    }

    ~Point() {
        cout << "Вызван деструктор ~Point() для " << name << endl;
    }

    void display() const {
        cout << "Точка '" << name << "': (" << x << ", " << y << ")" << endl;
    }
};

int main() {
    cout << "=== Программа 1: Базовый класс Point ===" << endl;
    
    Point p1;
    p1.display();
    
    Point p2(5, 10, "Test Point");
    p2.display();
    
    return 0;
}