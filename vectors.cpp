#include "TXLib.h"
#include <math.h>


class vector
{
    private:
        double x, y;
        //double r = sqrt(x*x + y*y);

    public:

        double getx()
        {
            return x;
        }
        double gety()
        {
            return y;
        }
        /*double getr()
        {
            return r;
        } */

        void setx(double temp)
        {
            x = temp;
        }
        void sety(double temp)
        {
            y = temp;
        }

        vector normalize();

        vector operator+(vector a);
        vector operator*(double multiplicator);
        vector operator-();
        void drawVector(struct CoordSys Sys);

        void drawLine(double x0, double y0)
        {
            txLine(x0, y0, x, y);
        }

        vector() : x(0), y(0) {}

        vector(double xx, double yy) : x(xx), y(yy) {}

};

struct CoordSys
{
        int x0, y0;
        int x1, y1;

        void createSys()
        {
            txLine(x0, y0, x0, y1);
            txLine(x0, y1, x1, y1);
        }

        CoordSys() : x0(0), y0(0), x1(0), y1(0) { }
        CoordSys(int xi0, int yi0, int xi1, int yi1) : x0(xi0), y0(yi0), x1(xi1), y1(yi1) { }

};

vector vector::operator+(vector a)
{
    return vector(x + a.x, y + a.y);
}

vector vector::operator*(double multiplicator)
{
    return vector(x * multiplicator, y * multiplicator);
}

vector vector::operator-()
{
    return vector((-1)*x, (-1)*y);
}

vector vector::normalize()
{
    double r = sqrt(x*x + y*y);
    x = x/r;
    y = y/r;
    return vector(x, y);
}

void vector::drawVector(struct CoordSys Sys)
{
    txSetColor(TX_WHITE);
    double r = sqrt(x*x + y*y);
    txLine(Sys.x0, Sys.y1, x, y);
    txLine(x, y, x - y*8/r, y + x*8/r);
    if ((x < 350)&&(y < 400))
    {
        txLine(x, y, x + y*8/r, y + x*8/r);
    }
    else
    {
        txLine(x, y, x - y*8/r, y - x*8/r);
    }
}

int main()
{
    txCreateWindow(800, 600);
    txSetColor(TX_LIGHTGREEN);

    CoordSys Sys(50, 50, 750, 550);
    Sys.createSys();

    vector v;

    while(txMouseButtons() != 3)
    {
        if (txMouseButtons() & 1)
        {
            v.setx(txMouseX());
            v.sety(txMouseY());
            v.drawVector(Sys);
        }
    }

    return 0;

}
