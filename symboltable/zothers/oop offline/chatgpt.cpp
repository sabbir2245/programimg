#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

// Base Shape class (optional for future extensibility)
class Shape {
public:
    virtual Shape* clone() const = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape {
    int length;
    int width;
    char *color;

public:
    Rectangle() : length(0), width(0), color(nullptr) {}

    Rectangle(int a, int b, const char *s) : length(a), width(b) {
        color = new char[strlen(s) + 1];
        strcpy(color, s);
    }

    Rectangle(const Rectangle &r) : length(r.length), width(r.width) {
        if (r.color) {
            color = new char[strlen(r.color) + 1];
            strcpy(color, r.color);
        } else {
            color = nullptr;
        }
    }

    Rectangle& operator=(const Rectangle &r) {
        if (this != &r) {
            length = r.length;
            width = r.width;
            delete[] color;
            if (r.color) {
                color = new char[strlen(r.color) + 1];
                strcpy(color, r.color);
            } else {
                color = nullptr;
            }
        }
        return *this;
    }

    int getLength() const { return length; }
    int getWidth() const { return width; }

    int getPerimeter() const {
        return 2 * (length + width);
    }

    int getArea() const {
        return length * width;
    }

    string getColor() const {
        return color ? string(color) : "No Color";
    }

    void setColor(const char *s) {
        delete[] color;
        color = new char[strlen(s) + 1];
        strcpy(color, s);
    }

    Rectangle* clone() const override {
        return new Rectangle(*this);
    }

    ~Rectangle() override {
        delete[] color;
    }
};

class Triangle : public Shape {
    int a, b, c;
    char *color;

public:
    Triangle() : a(0), b(0), c(0), color(nullptr) {}

    Triangle(int a, int b, int c, const char *s) : a(a), b(b), c(c) {
        color = new char[strlen(s) + 1];
        strcpy(color, s);
    }

    Triangle(const Triangle &t) : a(t.a), b(t.b), c(t.c) {
        if (t.color) {
            color = new char[strlen(t.color) + 1];
            strcpy(color, t.color);
        } else {
            color = nullptr;
        }
    }

    Triangle& operator=(const Triangle &t) {
        if (this != &t) {
            a = t.a;
            b = t.b;
            c = t.c;
            delete[] color;
            if (t.color) {
                color = new char[strlen(t.color) + 1];
                strcpy(color, t.color);
            } else {
                color = nullptr;
            }
        }
        return *this;
    }

    int getA() const { return a; }
    int getB() const { return b; }
    int getC() const { return c; }

    int getPerimeter() const {
        return a + b + c;
    }

    double getArea() const {
        double s = getPerimeter() / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    string getColor() const {
        return color ? string(color) : "No Color";
    }

    void setColor(const char *s) {
        delete[] color;
        color = new char[strlen(s) + 1];
        strcpy(color, s);
    }

    Triangle* clone() const override {
        return new Triangle(*this);
    }

    ~Triangle() override {
        delete[] color;
    }
};

class Circle : public Shape {
    int radius;
    char *color;

public:
    Circle() : radius(0), color(nullptr) {}

    Circle(int r, const char *s) : radius(r) {
        color = new char[strlen(s) + 1];
        strcpy(color, s);
    }

    Circle(const Circle &c) : radius(c.radius) {
        if (c.color) {
            color = new char[strlen(c.color) + 1];
            strcpy(color, c.color);
        } else {
            color = nullptr;
        }
    }

    Circle& operator=(const Circle &c) {
        if (this != &c) {
            radius = c.radius;
            delete[] color;
            if (c.color) {
                color = new char[strlen(c.color) + 1];
                strcpy(color, c.color);
            } else {
                color = nullptr;
            }
        }
        return *this;
    }

    int getRadius() const { return radius; }

    string getColor() const {
        return color ? string(color) : "No Color";
    }

    void setColor(const char *s) {
        delete[] color;
        color = new char[strlen(s) + 1];
        strcpy(color, s);
    }

    double getPerimeter() const {
        return 2 * 3.1416 * radius;
    }

    double getArea() const {
        return 3.1416 * radius * radius;
    }

    Circle* clone() const override {
        return new Circle(*this);
    }

    ~Circle() override {
        delete[] color;
    }
};

class ShapeCollection {
    // Capacities for each shape type
    int rcapacity = 1;
    int tcapacity = 1;
    int ccapacity = 1;

    // Arrays of pointers to shapes
    Rectangle** rectangles;
    Triangle** triangles;
    Circle** circles;

    // Current counts for each shape type
    int rc = 0;
    int tc = 0;
    int cc = 0;

public:
    ShapeCollection() {
        rectangles = new Rectangle*[rcapacity];
        triangles = new Triangle*[tcapacity];
        circles = new Circle*[ccapacity];
    }

    // Overloaded add() functions
    void add(const Rectangle &r) { 
        if(rc == rcapacity){
            // Resize rectangles array
            Rectangle** newRectangles = new Rectangle*[rcapacity * 2];
            cout << "Increasing capacity of rectangles from " << rcapacity 
                 << " to " << rcapacity * 2 << endl;
            // Clone existing rectangles
            for(int i = 0; i < rc; i++){
                newRectangles[i] = rectangles[i]->clone();
            }
            // Delete old rectangles
            for(int i = 0; i < rc; i++){
                delete rectangles[i];
            }
            delete[] rectangles;
            rectangles = newRectangles;
            rcapacity *= 2;
        }
        // Clone and add the new rectangle
        rectangles[rc++] = r.clone();
    }

    void add(const Triangle &t) {
        if(tc == tcapacity){
            // Resize triangles array
            Triangle** newTriangles = new Triangle*[tcapacity * 2];
            cout << "Increasing capacity of triangles from " << tcapacity 
                 << " to " << tcapacity * 2 << endl;
            // Clone existing triangles
            for(int i = 0; i < tc; i++){
                newTriangles[i] = triangles[i]->clone();
            }
            // Delete old triangles
            for(int i = 0; i < tc; i++){
                delete triangles[i];
            }
            delete[] triangles;
            triangles = newTriangles;
            tcapacity *= 2;
        }
        // Clone and add the new triangle
        triangles[tc++] = t.clone();
    }

    void add(const Circle &c) {
        if(cc == ccapacity){
            // Resize circles array
            Circle** newCircles = new Circle*[ccapacity * 2];
            cout << "Increasing capacity of circles from " << ccapacity 
                 << " to " << ccapacity * 2 << endl;
            // Clone existing circles
            for(int i = 0; i < cc; i++){
                newCircles[i] = circles[i]->clone();
            }
            // Delete old circles
            for(int i = 0; i < cc; i++){
                delete circles[i];
            }
            delete[] circles;
            circles = newCircles;
            ccapacity *= 2;
        }
        // Clone and add the new circle
        circles[cc++] = c.clone();
    }

    // Getter functions for counts
    int getRectCount() const { return rc; }
    int getTriCount() const { return tc; }
    int getCircCount() const { return cc; }

    // Print functions
    void printRectangles() const {
        for (int i = 0; i < rc; i++) {
            cout << "Rectangle " << i << ": length: " 
                 << rectangles[i]->getLength() 
                 << " width: " << rectangles[i]->getWidth() << endl;
        }
    }

    void printTriangles() const {
        for (int i = 0; i < tc; i++) {
            cout << "Triangle " << i << ": a: " << triangles[i]->getA() 
                 << " b: " << triangles[i]->getB() 
                 << " c: " << triangles[i]->getC() << endl;
        }
    }

    void printCircles() const {
        for (int i = 0; i < cc; i++) {
            cout << "Circle " << i << ": radius: " << circles[i]->getRadius() << endl;
        }
    }

    // Destructor
    ~ShapeCollection(){
        // Delete all rectangles
        for(int i = 0; i < rc; i++){
            delete rectangles[i];
        }
        delete[] rectangles;

        // Delete all triangles
        for(int i = 0; i < tc; i++){
            delete triangles[i];
        }
        delete[] triangles;

        // Delete all circles
        for(int i = 0; i < cc; i++){
            delete circles[i];
        }
        delete[] circles;
    }
};

int main()
{
    // Create rectangle with length, width, color
    Rectangle r1(10, 20, "Red");
    // The color is stored using new, which will be freed during destruction
    cout << "Rectangle Perimeter: " << r1.getPerimeter() << endl;
    cout << "Rectangle Area: " << r1.getArea() << endl;
    cout << "Rectangle Color: " << r1.getColor() << endl;
    // When changing the color, you need to delete the memory of the old color
    // and allocate new memory for the new color
    r1.setColor("Yellow");
    cout << "Rectangle Color: " << r1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    // Create triangle with a, b, c, color. (a, b, c are lengths of the sides)
    Triangle t1(3, 4, 5, "Blue");
    cout << "Triangle Perimeter: " << t1.getPerimeter() << endl;
    cout << "Triangle Color: " << t1.getColor() << endl;
    cout << "Triangle Area: " << t1.getArea() << endl;
    t1.setColor("Orange");
    cout << "Triangle Color: " << t1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    // Create circle with radius, color
    Circle c1(7, "Green");
    cout << "Circle Perimeter: " << c1.getPerimeter() << endl;
    cout << "Circle Area: " << c1.getArea() << endl;
    cout << "Circle Color: " << c1.getColor() << endl;
    c1.setColor("Purple");
    cout << "Circle Color: " << c1.getColor() << endl;
    cout << "--------------------------------------" << endl;

    // Test ShapeCollection
    ShapeCollection shapes;
    shapes.add(r1);
    shapes.add(t1);
    shapes.add(c1);

    Rectangle r2(15, 25, "Black");
    shapes.add(r2); // This should trigger resizing for rectangles

    Triangle t2(5, 12, 13, "White");
    shapes.add(t2); // This should trigger resizing for triangles

    cout << "Number of Rectangles: " << shapes.getRectCount() << endl;
    cout << "Number of Triangles: " << shapes.getTriCount() << endl;
    cout << "Number of Circles: " << shapes.getCircCount() << endl;
    cout << "--------------------------------------" << endl;

    shapes.printRectangles();
    shapes.printTriangles();
    shapes.printCircles();

    return 0;
}
