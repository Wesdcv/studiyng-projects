#include "TXLib.h"
#include <math.h>

class vector
{
    private:
        double x, y, z;
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
        double getz()
        {
            return z;
        }

        void setx(double temp)
        {
            x = temp;
        }
        void sety(double temp)
        {
            y = temp;
        }
        void setz(double temp)
        {
            z = temp;
        }

        void normalize();

        vector operator+(vector a);
        vector operator*(double multiplicator);
        vector operator-();
        double operator^(vector a);

        void drawVector(struct CoordSys coord);

        void drawLine(double x0, double y0, double x1, double y1)
        {
            txLine(x0 - x, y - y0, x1 - x, y - y1);
        }

        vector() : x(0), y(0), z(0) {}

        vector(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

};

struct CoordSys
{
        int x0, y0;
        int x1, y1;

        void createSys()
        {
            txLine(x0, y0, x0, y1);
            txLine(x0, y1, x1, y1);
            txLine(x0, y1, x0, 2*y1);
            txLine(0, y1, x0, y1);

        }

        CoordSys() : x0(0), y0(0), x1(0), y1(0) { }
        CoordSys(int xi0, int yi0, int xi1, int yi1) : x0(xi0), y0(yi0), x1(xi1), y1(yi1) { }

};


vector vector::operator+(vector a)
{
    return vector(x + a.x, y + a.y, z + a.z);
}

vector vector::operator*(double multiplicator)
{
    return vector(x * multiplicator, y * multiplicator, z*multiplicator);
}

vector vector::operator-()
{
    return vector((-1)*x, (-1)*y, (-1)*z);
}

void vector::normalize()
{
    double r = sqrt(x*x + y*y + z*z);
    x = x/r;
    y = y/r;
    z = z/r;
}

double vector::operator^(vector a)
{
    if (( (x*x + y*y + z*z) * (a.x*a.x + a.y*a.y + a.z*a.z) ) == 0)
    {
        return 0;
    }
    return( ((x * a.x) + (y * a.y) + (z + a.z)) / ( sqrt(x*x + y*y + z*z) * sqrt(a.x*a.x + a.y*a.y + a.z*a.z) ) );
}


int main()
{
    txCreateWindow(800, 600);
    txSetColor(TX_LIGHTGREEN);

    CoordSys Sys(400, 0, 800, 300);
    Sys.createSys();

    double r = 122.5;
    vector light(0, -0, 300);
    //vector init;

    for (int x = - r; x < r; x++)
    {
        for (int y = - r; y < r; y++)
        {
            if (sqrt(x*x + y*y) < r)
            {
                double z = sqrt(r*r - x*x - y*y);
                vector n(x, y, z);
                vector minn(-x, -y, -z);
                vector falllight = minn + light;
                double cos = n^falllight;

                if (cos < 0)
                {
                    //cos = 0;
                    //printf("%f", cos);
                }

                txSetPixel(x + Sys.x0, Sys.y1 + y, RGB(255*z/r, 255*z/r, 255*z/r));
            }


        }
    }

}
