#include "TXLib.h"
#include <math.h>


class vector
{
    private:

        double x, y, z;

    public:

        vector() : x (0), y (0), z (0) {}

        vector (double xx, double yy, double zz) : x (xx), y (yy), z (zz) {}

        double getx ()
        {
            return x;
        }
        double gety ()
        {
            return y;
        }
        double getz ()
        {
            return z;
        }

        void setx (double temp)
        {
            x = temp;
        }
        void sety (double temp)
        {
            y = temp;
        }
        void setz (double temp)
        {
            z = temp;
        }

        void normalize ();

        vector operator + (vector a);
        vector operator * (double multiplicator);
        vector operator - ();
        vector operator & (vector multiplicator);
        vector norm ();
        double length ();
        double operator^ (vector a);
        void lightcheck();

        void drawVector (struct CoordSys coord);

        void drawLine (double x0, double y0, double x1, double y1)
        {
            txLine (x0 - x, y - y0, x1 - x, y - y1);
        }



};

struct CoordSys
{
    int x0, y0;
    int x1, y1;

    void createSys()
    {
        txLine (x0, y0, x0, y1);
        txLine (x0, y1, x1, y1);
        txLine (x0, y1, x0, 2 * y1);
        txLine (0, y1, x0, y1);

    }

    CoordSys() : x0 (0), y0 (0), x1 (0), y1 (0) { }
    CoordSys (int xi0, int yi0, int xi1, int yi1) : x0 (xi0), y0 (yi0), x1 (xi1), y1 (yi1) { }

};


vector vector::operator + (vector a)
{
    return vector (x + a.x, y + a.y, z + a.z);
}

vector vector::operator * (double multiplicator)
{
    return vector (x * multiplicator, y * multiplicator, z * multiplicator);
}

vector vector::operator & (vector multiplicator)
{
    return vector (x * multiplicator.x, y * multiplicator.y, z * multiplicator.z);
}

vector vector::operator - ()
{
    return vector ( (-1) * x, (-1) * y, (-1) * z);
}

void vector::normalize()
{
    double r = sqrt (x * x + y * y + z * z);
    x = x / r;
    y = y / r;
    z = z / r;
}

double vector::length()
{
    double r = sqrt (x * x + y * y + z * z);
    return (r);
}

vector vector::norm()
{
    double r = sqrt (x * x + y * y + z * z);
    return vector (x / r, y / r, z / r);
}

double vector::operator ^ (vector a)
{
    if ( ( (x * x + y * y + z * z) * (a.x * a.x + a.y * a.y + a.z * a.z)) == 0)
    {
        return 0;
    }

    return ( ( (x * a.x) + (y * a.y) + (z * a.z)) / (length() * a.length()));
}

void vector::lightcheck()
{
    if (x > 255)
    {
        x = 255;
    }

    if (y > 255)
    {
        y = 255;
    }

    if (z > 255)
    {
        z = 255;
    }

}

/*double clamp (double value, double min, double max)
    {
        return (value < min)? min : (value > max)? max : value;
    }*/


void raycast (double r, vector colorlight, vector ambientlight, vector initcolor, vector blikcolor,
                                                               CoordSys Sys, vector scolorlight, vector sblikcolor)
{
    double previousangle = 0;
    vector cam (0, 0, 5 * r);

    vector slight (-100, 0, 130);
    vector addendcolor;
    //double radc = rad * rad;

    while (txMouseButtons() != 1)
    {
        double angle = std::fmod ( (previousangle + 0.08), 2 * txPI);
        double coordx = 2 * r * cos (angle);
        double coordy = 2 * r * sin (angle);
        previousangle = angle;

        vector light (coordx, coordy, 300);
        //double rad = sqrt (pow (light.getx(), 2) + pow (light.gety(), 2));
        //double radc = rad * rad;

        txBegin();
        for (double x = - r; x < r; x++)
        {
            for (double y = - r; y < r; y++)
            {
                if (sqrt (x * x + y * y) < r)
                {
                    double z = sqrt (r * r - x * x - y * y);
                    vector n (x, y, z);
                    vector falllight  = -n + light;
                    vector sfalllight = -n + slight;

                    double cos        = n.norm() ^ falllight;
                    double fllength   = falllight.length();
                    double delta      = sqrt (2 * (fllength) * (fllength) - fllength * 4 * (1 - 2 * (cos)));

                    double scos       = n.norm() ^ sfalllight;
                    double sfllength  = sfalllight.length();
                    double sdelta     = sqrt (2 * (sfllength) * (sfllength) - sfllength * 4 * (1 - 2 * (scos)));

                    vector blik       = falllight + (n.norm() * delta) * (-1);
                    vector camdist    = cam + (-n);

                    vector sblik      = sfalllight + (n.norm() * sdelta) * (-1);
                    vector scamdist   = cam + (-n);

                    blik.normalize();
                    camdist.normalize();

                    double anglcos = blik ^ camdist;

                    sblik.normalize();
                    scamdist.normalize();

                    double sanglcos = sblik ^ scamdist;

                    //double sintemp = sqrt (1 - (anglcos) * (anglcos));

                    //double sin = pow(sintemp, 2000);
                    double sin  = pow ( (anglcos), 6);
                    double ssin = pow ( (sanglcos), 10);

                    if (cos < 0)
                    {
                        cos = 0;
                    }

                    if (scos < 0)
                    {
                        scos = 0;
                    }

                    vector sendcolor = (initcolor & (scolorlight * scos)) + ambientlight & initcolor +
                    (sblikcolor * ssin);
                    vector endcolor = sendcolor + (initcolor & (colorlight * cos)) + (ambientlight & initcolor) +
                    (blikcolor * sin);
                    endcolor = endcolor * 255;
                    endcolor.lightcheck();

                    RGBQUAD rgb = { (BYTE) (int)(endcolor.getx()),
                                    (BYTE) (int)(endcolor.gety()),
                                    (BYTE) (int)(endcolor.getz()) };

                    //txBegin();
                    txLock();

                    *(txVideoMemory() + (int) (x + Sys.x0) + ( (int) ( - Sys.y1 - y) +
                     2 * (int) Sys.y1) * 2 * (int) Sys.x0) = rgb;


                    //txRedrawWindow();
                    txUnlock();
                    //txEnd();


                    //txSetPixel (x + Sys.x0, Sys.y1 + y, RGB (endcolor.getx(), endcolor.gety(), endcolor.getz()));
                    coordx ++;

                }
            }
        }
        txEnd();
        printf("%f \n", txGetFPS());
    }

}

int main()
{
    txCreateWindow (800, 600);
    txSetColor (TX_LIGHTGREEN);

    CoordSys Sys (400, 0, 800, 300);
    Sys.createSys();

    double r = 122.5;
    /*vector light (2 * r, -2 * r, 130);
    double rad = sqrt (pow (light.getx(), 2) + pow (light.gety(), 2));
    //double radc = rad * rad;
    vector cam (0, 0, 5 * r);  */

    vector color (0.43, 0.5, 0.05);
    vector scolor (0.9, 0.8, 0.5);
    vector ambient (0.2, 0.15, 0.25);
    vector init (0.2, 0.2, 0.2);
    vector blik (1, 0.1, 0.1);
    vector sblik (0.1, 1, 1);

    raycast (r, color, ambient, init, blik, Sys, scolor, sblik);


    /*for (double x = - r; x < r; x++)
    {
        for (double y = - r; y < r; y++)
        {
            if (sqrt (x * x + y * y) < r)
            {
                double z = sqrt (r * r - x * x - y * y);
                vector n (x, y, z);
                vector falllight = -n + light;

                double cos = n.norm() ^ falllight;
                double fllength = falllight.length();
                double delta = sqrt (2 * (fllength) * (fllength) - fllength * 4 * (1 - 2 * (cos)));

                vector blik = falllight + (n.norm()*delta) * (-1);
                vector camdist = cam + (-n);

                blik.normalize();
                camdist.normalize();
                double anglcos = blik ^ camdist;
                //double sintemp = sqrt (1 - (anglcos) * (anglcos));

                //double sin = pow(sintemp, 2000);
                double sin = pow((anglcos), 4);

                if (cos < 0)
                {
                    cos = 0;
                }

                vector endcolor = (initcolor & (colorlight * cos)) + ambientlight & initcolor + (blikcolor * sin);
                endcolor = endcolor * 255;
                endcolor.lightcheck();

                txSetPixel (x + Sys.x0, Sys.y1 + y, RGB (endcolor.getx(), endcolor.gety(), endcolor.getz()));

            }
        }
    } */
}
