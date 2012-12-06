#include "Point.h"
#include <cmath>
#include <sstream>

Point::Point(double px, double py)
  : x(px), y(py)
{}
  
Point::Point()
  : x(0), y(0)
{}

Point::~Point(){

}
  
bool operator == (const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator != (const Point& lhs, const Point& rhs)
{
    return ! (lhs == rhs);
}

bool operator  < (const Point& lhs, const Point& rhs)
{
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

bool operator  > (const Point& lhs, const Point& rhs)
{
    return rhs < lhs;
}

bool operator <= (const Point& lhs, const Point& rhs)
{
    return ! (lhs > rhs);
}

bool operator >= (const Point& lhs, const Point& rhs)
{
    return ! (lhs < rhs);
}

double Point::distanceFrom(const Point& p) const
{
    return sqrt( (x - p.x)*(x-p.x) + (y - p.y)*(y - p.y));
}

string Point::tostring() const
{
    ostringstream out;
    out << "(" << x << ", " << y << ")";
    return out.str();
}

ostream& operator << (ostream& os, const Point& p)
{
    os << p.tostring();
    return os;
}

void Point::desplazar(double desplazamientoX,double desplazamientoY){
	this->x += desplazamientoX;
	this->y += desplazamientoY;
}

void Point::setPos(Point* otroPunto){
	this->x = otroPunto->x;
	this->y = otroPunto->y;
}

double Point::dotProduct(Point* otroPunto){
	return (this->x * otroPunto->x + this->y * otroPunto->y);
}

// Devuelve un nuevo punto que simboliza la recta que une a ambos
Point Point::segmento(Point* otroPunto){
	double segX, segY = 0;
	segX = otroPunto->x - this->x;
	segY = otroPunto->y - this->y;
	Point p(segX, segY);
	p.normalizar();
	return p;
}

double Point::norma(){
	return sqrt(this->x * this->x + this->y * this->y);
}

Point* Point::getNormalizado(){
	double norma = this->norma();
	double unX = this->x / norma;
	double unY = this->y / norma;
	return new Point(unX, unY);
}

void Point::normalizar(){
	double norma = this->norma();
	this->x = this->x / norma;
	this->y = this->y / norma;
}

Point Point::proyectar(Point* eje ){
	double numerador = (this->x * eje->x + this->y * eje->y );
	double denominador = (eje->x * eje->x + eje->y * eje->y);
	double unX = (numerador * eje->x) / denominador;
	double unY = (numerador * eje->y) / denominador;
	return Point(unX, unY);
}
