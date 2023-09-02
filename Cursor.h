#ifndef CURSOR_H
#define CURSOR_H

using namespace std;

class Cursor {
public:
	Cursor(double x, double y);
	virtual ~Cursor();

	virtual double getX();
	virtual double getY();

private:
    double x;
    double y;

};

#endif // CURSOR_H
