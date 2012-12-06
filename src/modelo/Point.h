#ifndef _POINT_H
#define _POINT_H
#include <math.h>
#include <string>
using namespace std;

struct Point {
	Point();
	Point(double px, double py);
	~Point();
	void desplazar(double desplazamientoX,double desplazamientoY);

	string tostring()                   const;
	double distanceFrom(const Point& p) const;
	double x;
	double y;
	void setPos(Point* otroPunto);
	double dotProduct(Point* otroPunto);
	Point segmento(Point* otroPunto);
	double norma();
	void normalizar();
	Point* getNormalizado();
	Point proyectar(Point* eje );
};

bool operator == (const Point& lhs, const Point& rhs);
bool operator != (const Point& lhs, const Point& rhs);
bool operator  < (const Point& lhs, const Point& rhs);
bool operator  > (const Point& lhs, const Point& rhs);
bool operator <= (const Point& lhs, const Point& rhs);
bool operator >= (const Point& lhs, const Point& rhs);



ostream& operator << (ostream& os, const Point& p);

#endif
