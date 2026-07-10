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
    Rectangle(int a, int b, const char *s)
    {
        length = a;
        width = b;
        color = (char *)malloc((sizeof(char) * (strlen(s) + 1)));
        strcpy(color, s);
    }
    Rectangle(Rectangle &r)
    {
        length = r.length;
        width = r.width;
        color = (char *)malloc((sizeof(char) * (strlen(r.color) + 1)));
        strcpy(color, r.color);
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
        color = (char *)malloc((sizeof(char) * (strlen(s) + 1)));
        strcpy(color, s);
    }
    Rectangle *clone()
    {
        Rectangle *r = new Rectangle(length, width, color);
        return r;
    }
    ~Rectangle()
    {
        free(color);
    }
};
class Triangle
{
    int a, b, c;
    char *color;

public:
    Triangle() {};
    Triangle(int a, int b, int c, const char *s)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        color = (char *)malloc((sizeof(char) * (strlen(s) + 1)));
        strcpy(color, s);
    }
    Triangle(const Triangle &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
        color = (char *)malloc((sizeof(char) * (strlen(t.color) + 1)));
        strcpy(color, t.color);
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
        color = (char *)malloc((sizeof(char) * (strlen(s) + 1)));
        strcpy(color, s);
    }
    Triangle *clone()
    {
        Triangle *t = new Triangle(a, b, c, color);
        return t;
    }

    ~Triangle()
    {
        free(color);
    }
};

class Circle
{
    int radius;
    char *color;

public:
    Circle() {};
    Circle(int r, const char *s)
    {
        radius = r;
        color = (char *)malloc((sizeof(char) * (strlen(s) + 1)));
        strcpy(color, s);
    }
    Circle(const Circle &c)
    {
        radius = c.radius;
        color = (char *)malloc((sizeof(char) * (strlen(c.color) + 1)));
        strcpy(color, c.color);
    }
    int getr() { return radius; }
    char *getColor()
    {
        return color;
    }
    void setColor(const char *s)
    {
        free(color);
        color = (char *)malloc((sizeof(char) * (strlen(s) + 1)));
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
    Circle *clone()
    {
        Circle *c = new Circle(radius, color);
        return c;
    }
    ~Circle()
    {
        free(color);
    }
};

class ShapeCollection
{
    int rcapacity;
    int tcapacity;
    int ccapacity;
    Rectangle **rectangles;
    Triangle **triangles;
    Circle **circles;

    int rc = 0;
    int tc = 0;
    int cc = 0;

public:
    ShapeCollection()
    {
        rcapacity = 1;
        tcapacity = 1;
        ccapacity = 1;
        rectangles = new Rectangle *[rcapacity];
        triangles = new Triangle *[tcapacity];
        circles = new Circle *[ccapacity];
    }

    void add(Rectangle r)
    {
        if (rc == rcapacity)
        {

            Rectangle **newRectangles = new Rectangle *[rcapacity * 2];
            rcapacity *= 2;
            for (int i = 0; i < rc; i++)
            {
                newRectangles[i] = rectangles[i];
            }

            delete[] rectangles;
            rectangles = newRectangles;
            cout << "Increasing capacity of rectangles from " << rc << " to " << rcapacity << endl;

            
        }
        rectangles[rc++] = r.clone();
    }
    void add(Triangle t)
    {
        if (tc == tcapacity)
        {
            Triangle **newTriangles = new Triangle*[tcapacity * 2];
            tcapacity *= 2;
            for (int i = 0; i < tc; i++)
            {
                newTriangles[i] = triangles[i];
            }

            delete[] triangles;
            triangles = newTriangles;
            cout << "Increasing capacity of triangles from " << tc << " to " << tcapacity << endl;
        }
        triangles[tc++] = t.clone();
    }

    void add(Circle c)
    {
        if (cc == ccapacity)
        {
            Circle **newCircles = new Circle*[ccapacity * 2];
            ccapacity *= 2;
            for (int i = 0; i < cc; i++)
            {
                newCircles[i] = circles[i];
            }

            delete[] circles;
            circles = newCircles;
            cout << "Increasing capacity of circles from " << cc << " to " << ccapacity << endl;
        }
        circles[cc++] = c.clone();;
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
            cout << "Rectangle " << i << ": length: " << rectangles[i]->getlength() << " width: " << rectangles[i]->getWidth() << endl;
        }
    }
    void printTriangles()
    {
        for (int i = 0; i < tc; i++)
        {
            cout << "Triangle " << i << ": a: " << triangles[i]->geta() << " b: " << triangles[i]->getb() << " c: " << triangles[i]->getc() << endl;
        }
    }
    void printCircles()
    {
        for (int i = 0; i < cc; i++)
        {
            cout << "Circle " << i << ": radius: " << circles[i]->getr() << endl;
        }
    }
    ~ShapeCollection()
    {
        delete[] rectangles;
        delete[] triangles;
        delete[] circles;
    }
};

 
int main() {
    // Create rectangle with length, width, color
    Rectangle r1(10, 20, "Red");
    // The Color is stored using malloc, which will be freed during destruction
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
 
    /*
    When constructing the ShapeCollection class, you will create dynamic for 
    rectangles, triangles and circles. You have to dynamically allocate memory for this.
    */ 
    ShapeCollection shapes;
    /* IMPORTANT: You need to pass the objects by value to the add functions
    If you pass by value, the copy constructor will be called and the dynamically
    allocated memory will be copied. So, you have to write copy contructor so that 
    memory allocation is properly done and no double free error occurs.
    */ 
 
 
    shapes.add(r1);
    shapes.add(t1);
    shapes.add(c1);
 
    Rectangle r2(15, 25, "Black");
    Rectangle r3(150, 225, "Green");
    shapes.add(r2);
    shapes.add(r3);
    Triangle t2(5, 12, 13, "White");
    shapes.add(t2);
 
    cout << "Number of Rectangles: " << shapes.getRectCount() << endl;
    cout << "Number of Triangles: " << shapes.getTriCount() << endl;
    cout << "Number of Circles: " << shapes.getCircCount() << endl;
    cout << "--------------------------------------" << endl;
 
    shapes.printRectangles();
    shapes.printTriangles();
    shapes.printCircles();
 
    return 0;
}
 
 