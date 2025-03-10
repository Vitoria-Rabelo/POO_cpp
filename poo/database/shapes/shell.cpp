#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>
using namespace std;

template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "");
        ss << f(*it);
    }
    return ss.str();
}

class Shape{
    public:
        virtual double getArea() const = 0;
        virtual double getPerimeter() const = 0;
        virtual string getName() const = 0;
        virtual string str() const = 0;
        virtual ~Shape() = default;

};

class Point2D {
    double x;
    double y;

    public:
        Point2D(double x = 0, double y = 0) : x(x), y(y) {};

        double getX() const{
            return this->x;
        }

        double getY() const{
            return this->y;
        }

        string str() const{
            stringstream ss;
            ss << fixed << setprecision(2) <<  "(" << x << ", " << y << ")";
            return ss.str();
        }

};

class Circle : public Shape{
    Point2D center;
    double radius;

    public:
        Circle(Point2D center, double radius = 0) : center(center), radius(radius){};

        double getArea() const override{
            return M_PI * radius * radius;
        }

        double getPerimeter() const override{
            return 2 * M_PI * radius;
        }

        string getName() const override{
            return "Circ: ";
        }

        string str() const override{
            stringstream ss;
            ss << getName() << "C=" << center.str() << ", R=" << fixed << setprecision(2) << this->radius;
            return ss.str();
        }
};

class Rectangle : public Shape{
    Point2D p1;
    Point2D p2;

    public:
        Rectangle(Point2D p1, Point2D p2) : p1(p1), p2(p2){};
        double getArea() const override{
            return abs(p1.getX() - p2.getX()) * abs(p1.getY() - p2.getY());
        }

        double getPerimeter() const override{
            return 2 * (abs(p1.getX() - p2.getX()) + abs(p1.getY() - p2.getY()));
        }

        string getName() const override{
            return "Rect: ";
        }

        string str() const override{
            stringstream ss;
            ss << getName() << "P1=" << p1.str() << " P2=" << p2.str();
            return ss.str();
        }

};

int main() {
    Point2D p;
    vector<shared_ptr<Shape>> shapes;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")  { 
            break;                                  
        }
        else if (cmd == "show") { 
            for(auto& s : shapes){
                cout << s->str() << endl;
            }
        }
        else if (cmd == "circle") { 
            double x{}, y{}, radius{};
            ss >> x >> y >> radius;
            shapes.push_back(make_shared<Circle>(Point2D(x, y), radius));
        }
        else if (cmd == "rect") {
            double x1{}, y1{}, x2{}, y2{};
            ss >> x1 >> y1 >> x2 >> y2;
            shapes.push_back(make_shared<Rectangle>(Point2D(x1, y1), Point2D(x2, y2)));
        }
        else if (cmd == "info") {
            for(auto& s : shapes){
                cout << s->getName() << "A=" << fixed << setprecision(2) << s->getArea()
                << " P=" << fixed << setprecision(2) << s->getPerimeter() << endl;
            }
        }
        else {
            cout << "fail: comando inválido" << '\n';
        }
    }
}
