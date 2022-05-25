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
        vector norm();
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

vector vector::norm()
{
    double r = sqrt(x*x + y*y + z*z);
    return vector(x/r, y/r, z/r);
}

double vector::operator^(vector a)
{
    if (( (x*x + y*y + z*z) * (a.x*a.x + a.y*a.y + a.z*a.z) ) == 0)
    {
        return 0;
    }
    return( ((x * a.x) + (y * a.y) + (z * a.z)) / ( sqrt(x*x + y*y + z*z) * sqrt(a.x*a.x + a.y*a.y + a.z*a.z) ) );
}


int main()
{
    txCreateWindow(800, 600);
    txSetColor(TX_LIGHTGREEN);

    CoordSys Sys(400, 0, 800, 300);
    Sys.createSys();

    double r = 122.5;
    vector light(200, -100, 300);
    vector cam(0, 0, 400);

    vector colorlight(1, 0.5, 0.95);
    vector ambientlight(0.2, 0.15, 0.25);
    vector initcolor(0.2, 0.3, 0.5);
    vector blikcolor(0.8, 0.9, 0.6);


    for (int x = - r; x < r; x++)
    {
        for (int y = - r; y < r; y++)
        {
            if (sqrt(x*x + y*y) < r)
            {
                double z = sqrt(r*r - x*x - y*y);
                vector n(x, y, z);
                vector falllight = -n + light;
                double cos = n.norm()^falllight;
                vector blik = -falllight + ((n.norm())*2);
                vector camdist = cam + (-n);
                double sintemp = sqrt(1 - (blik^camdist)*(blik^camdist));

                if (fabs(blik^camdist) < 0.1)
                {
                    printf("%f", (blik^camdist));
                }

                if (sintemp > 0.9)
                {
                    printf("%f", sintemp);
                }

                double sin = pow(sintemp, 20);


                if (cos < 0)
                {
                    cos = 0;
                }

                vector endcolor(255*(ambientlight.getx() + colorlight.getx()*cos*initcolor.getx() + sin*blikcolor.getx()), 255*(ambientlight.gety() + colorlight.gety()*cos*initcolor.gety() + sin*blikcolor.gety()), 255*(ambientlight.getz() + colorlight.getz()*cos*initcolor.getz() + sin*blikcolor.getz()));

                if ((ambientlight.getx() + colorlight.getx()*cos*initcolor.getx() + sin*blikcolor.getx()) > 1)
                {
                    endcolor.setx(255);
                }

                if ((ambientlight.gety() + colorlight.gety()*cos*initcolor.gety() + sin*blikcolor.gety()) > 1)
                {
                    endcolor.sety(255);
                }

                if ((ambientlight.getz() + colorlight.getz()*cos*initcolor.getz() + sin*blikcolor.getz()) > 1)
                {
                    endcolor.setz(255);
                }

                txSetPixel(x + Sys.x0, Sys.y1 + y, RGB(endcolor.getx(), endcolor.gety(), endcolor.getz()));
            }
        }
    }
}
