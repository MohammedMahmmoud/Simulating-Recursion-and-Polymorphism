#include <iostream>
#include <math.h>

using namespace std;

struct shape_V_table;           //struct containing the virtual function that will be changed based on the shape

struct Shape                    //that struct represent the parent -super- class which be inherit
{
    shape_V_table* vTable;      //only has the virtual functions
};

struct shape_V_table
{
    double (*GetArea)(Shape*);      //one function that represent all shape area function based on the parameter *Shape which will differ --casted-- on each shape area function
};
double GetArea(Shape* shape)        //the abstract function to get the area
{
    shape->vTable->GetArea(shape);  //call the virtual function for the shape super class calling that accessing the virtual function from the table
}

struct Circle                       //represent the circle class
{
    Shape parent;                   //aggregation with the -super class- shape that representing the inheritance
    int radius;                     //the radius of the circle
};
double CircleArea(Circle* circle)                           //function that get the area of the circle
{
    double pi=3.14159265359;
    double area=pi*circle->radius*circle->radius;           //area= pi*r^2
    return area;
}
shape_V_table circleTable={                                         //virtual table containing the overridden GetArea abstract function for the circle
                            (double(*)(Shape*)) CircleArea          //casting CircleArea function to match getArea abstract function
                          };
void CircleInitialize(Circle* circle, int radius)                   //function that represent the constructor of the circle class
{
    circle->parent.vTable=&circleTable;                             //initialize super class virtual function to the overridden circleArea
    circle->radius=radius;                                          //initialize the circle radius
}

struct Rectangle                                                    //struct represent the inherited class rectangle
{
    Shape parent;                                                   //aggregation with the -super class- shape that representing the inheritance
    int height,width;                                               //rectangle's width and height
};
double rectangleArea(Rectangle* rec)                                //function that get the rectangle's area
{
    double area = rec->height * rec->width;                         //area = height * width
    return area;
}
shape_V_table rectangleTable={                                             //virtual table containing the overridden GetArea abstract function for the rectangle
                                (double(*)(Shape*)) rectangleArea          //casting the rectangleArea function to match the super class's one
                             };
void RectangleInitialize(Rectangle* rec, int hight, int width)              //representing the rectangle constructor
{
    rec->parent.vTable = &rectangleTable;                                   //initialize super class virtual function to the overridden rectangleArea
    rec->height=hight;                                                      // initialize height and width of the rectangle
    rec->width=width;
}

struct Triangle                                                                 //representing the inherited triangle class
{
    Shape parent;                                                               //aggregation with the -super class- shape that representing the inheritance
    int side1, side2, side3;                                                    //triangle's 3 sides
};
double triArea(Triangle* tri)                                                   //the function that calculate the triangle's area
{
    double s=(double)(tri->side1+tri->side2+tri->side3)/2;
    double underroot=(double) s*(s-tri->side1)*(s-tri->side2)*(s-tri->side3);   //herons formula A = sqrt( s(s-a)(s-b)(s-c) )
    double area=sqrt(underroot);

    /*double a=(double)tri->side1/2, b=(double)tri->side2/2, c=(double)tri->side3/2;
    double area=4*a*a*b*b-(a*a + b*b - c*c)*(a*a + b*b - c*c);
    cout<<area;
    area=sqrt(area);
    area/=4;*/
    return area;
}
shape_V_table triTable={                                        //virtual table containing the overridden GetArea abstract function for the triangle
                            (double(*)(Shape*)) triArea         //casting the triArea function to match the based virtual function
                       };
TriangleInitialize(Triangle* tri, int a, int b ,int c)          //representing triangle constructor
{
    tri->parent.vTable = &triTable;                             //initialize super class virtual function to the overridden triangleArea
    tri->side1=a;                                               //initialize the 3 sides of the triangles
    tri->side2=b;
    tri->side3=c;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Triangle triangle;
    TriangleInitialize(&triangle, 7, 4, 12); // triangle with side lengths: 7, 4, 12

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle; shapes[1]=(Shape*)&rectangle; shapes[2]=(Shape*)&triangle;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
    }
    cout<<total_area<<endl; // check if the value is correct
return 0;
}
