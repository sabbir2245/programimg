#include <iostream>
#include <string>
#include <vector>

#include <cstring>
#include <math.h>

using namespace std;

class Rectangle
{
    int length;
    int width;
    char *color;

public:
    Rectangle() {};
    Rectangle(int a, int b,const char *s)
    {
        length = a;
        width = b;
        color = (char *)malloc((sizeof(char) * strlen(s)));
        strcpy(color, s);
    }
    int getlength() { return length; }
    int getWidth() { return width; }
    int getPerimeter()
    {
        return 2 * (length + width);
    }
    int getArea()
    {
        return length * width;
    }
    string getColor()
    {
        return color;
    }
    void setColor(const char *s)
    {
        free(color);
        color = (char *)malloc((sizeof(char) * strlen(s)));
        strcpy(color, s);
    }
};
class Triangle
{
    int a, b, c;
    char *color;

public:
Triangle() {};
    Triangle(int a, int b, int c,const char *s)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        color = (char *)malloc((sizeof(char) * strlen(s)));
        strcpy(color, s);
    }
    int geta() { return a; }
    int getb() { return b; }
    int getc() { return c; }
    int getPerimeter()
    {
        return a + b + c;
    }
    int getArea()
    {
        double s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    char *getColor()
    {
        return color;
    }
    void setColor(const char *s)
    {
        free(color);
        color = (char *)malloc((sizeof(char) * strlen(s)));
        strcpy(color, s);
    }
};

class Circle
{
    int radius;
    char *color;

public:
 Circle() {};
    Circle(int r,const char *s)
    {
        radius = r;
        color = (char *)malloc((sizeof(char) * strlen(s)));
        strcpy(color, s);
    }
    int getr() { return radius; }
    char *getColor()
    {
        return color;
    }
    void setColor(const char *s)
    {
        free(color);
        color = (char *)malloc((sizeof(char) * strlen(s)));
        strcpy(color, s);
    }
    double getPerimeter()
    {
        return 3.1416 * 2 * radius;
    }
    double getArea()
    {
        return 3.1416 * radius * radius;
    }
};

class ShapeCollection
{
    Rectangle rectangles[100];
    Triangle triangles[100];
    Circle circles[100];

    int rc = 0;
    int tc = 0;
    int cc = 0;

public:
  ShapeCollection() = default;
    void addRectangle(Rectangle& r)
    {
        rectangles[rc++] = r;
    }
    void addTriangle(Triangle& t)
    {
        triangles[tc++] = t;
    }
    void addCircle(Circle& c)
    {
        circles[cc++] = c;
    }
    int getRectCount()
    {
        return rc;
    }
    int getTriCount()
    {
        return tc;
    }
    int getCircCount()
    {
        return cc;
    }
    /*Rectangle 0: length: 10 width: 20
Rectangle 1: length: 15 width: 25
Triangle 0: a: 3 b: 4 c: 5
Triangle 1: a: 5 b: 12 c: 13
Circle 0: radius: 7*/
    void printRectangles()
    {
        for (int i = 0; i < rc; i++)
        {
            cout << "Rectangle " << i << ": length: " << rectangles[i].getlength() << " width: " << rectangles[i].getWidth() << endl;
        }
    }
    void printTriangles()
    {
        for (int i = 0; i < tc; i++)
        {
            cout << "Triangle " << i << ": a: " << triangles[i].geta() << " b: " << triangles[i].getb() << " c: " << triangles[i].getc() << endl;
        }
    }
    void printCircles()
    {
        for (int i = 0; i < cc; i++)
        {
            cout << "Circle " << i << ": radius: " << circles[i].getr() << endl;
        }
    }
};

int main()
{
    // Create rectangle with length, width, color
    Rectangle r1(10, 20, "Red");
    // The color is stored using malloc, which will be freed during destruction
    cout << "Rectangle Perimeter: " << r1.getPerimeter() << endl;
    cout << "Rectangle Area: " << r1.getArea() << endl;
    cout << "Rectangle Color: " << r1.getColor() << endl;
    // When changing the color, you need to free the memory of the old color
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
    shapes.addRectangle(r1);
    shapes.addTriangle(t1);
    shapes.addCircle(c1);
    Rectangle r2(15, 25, "Black");
    shapes.addRectangle(r2);
    Triangle t2(5, 12, 13, "White");
    shapes.addTriangle(t2);
    cout << "Number of Rectangles: " << shapes.getRectCount() << endl;
    cout << "Number of Triangles: " << shapes.getTriCount() << endl;
    cout << "Number of Circles: " << shapes.getCircCount() << endl;
    cout << "--------------------------------------" << endl;
    shapes.printRectangles();
    shapes.printTriangles();
    shapes.printCircles();
    
    return 0;
}