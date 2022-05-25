#include "TXLib.h"
#include <math.h>

typedef double (*func) (double);

void createSys (struct CoordSys);
void drawLine (double xscale, double yscale, double xvalues[10], double yvalues[10], CoordSys Coord);

struct CoordSys
{
    CoordSys (int ax, int bx, int ay, int by):
    x0 (ax),
    x1 (bx),
    y0 (ay),
    y1 (by) {}

	int x0, y0;
	int x1, y1;
	double scalex;
	double clearall (double a);
};

class button
{
	private:

		double x0, y0;
		double x1, y1;

	public:

        double gety()
        {
            return y1;
        }

        const char* text;

		func fct(arg)
		{
            while (arg < 1000)
            {
                double arg1 = arg + 0.1;
                txLine (arg, fctn (arg), arg1, fctn (arg1));
                arg += 0.1;
            }

            txSetColor (TX_LIGHTGREEN);
            createSys (Sys);

            return 0;
        };

		RECT area = {x0, y0, x1, y1};

		void drawButton()
		{
			txRectangle (x0, y0, x1, y1);
			txSetColor (TX_LIGHTBLUE);
			txTextOut (x0 + 10, y0 + 10, text);
		}

		/*bool trigger()
		{
			return (In (txMousePos(), area));
		}  */



        button (double x0, double y0, double x1, double y1, func fct_,  char* text1) :

        x0 (x0),
        y0 (y0),
        x1 (x1),
        y1 (y1),
        fct (fct_),
        text (text1) {}



};



double CoordSys::clearall (double a)
{
    txSetFillColor (TX_BLACK);
    txClear();
    txSetColor (TX_LIGHTGREEN);
    createSys (Sys1);
    createSys (Sys2);
    return 1;
}

void drawButtons(Buttons[])
{
    for (int i = 0; Buttons[i].gety() != 0; i++)
    {
        Buttons[i].drawButton();
    }
}



int main()
{
	txCreateWindow (1000, 600);
	txSetColor (TX_LIGHTGREEN);

	CoordSys Sys1 (50, 50, 450, 550);
	CoordSys Sys2 (550, 50, 950, 550);

	createSys (Sys1);
	createSys (Sys2);

	txSetColor (TX_LIGHTBLUE);

	//double (*fctn)(double);

	button Buttons[] { button (10  , 10, 210 , 60, sin, "�����"),
	                   button (220 , 10, 420 , 60, cos, "�������"),
	                   button (430 , 10, 630 , 60, tan, "�������"),
	                   button (640 , 10, 840 , 60, atan, "����������"),
	                   //button (850 , 10, 990 , 60, clearall, "�������� ���"),
	                   button (0   , 0 , 0   ,  0, 0, NULL)
	                 } ;

    void drawButtons(Buttons[]);

    while (txMouseButtons() != 3)
    {

        if (txMouseButtons() & 1)
        {

            for (int i = 0; Buttons[i].getnumber() != 0; i++)
            {
                double x = 0;

                if (In (txMousePos(), Buttons[i].area))
                {
                    txSetColor (TX_LIGHTBLUE);
                    Buttons[i].func (x, Sys1);
                }
            }
        }
    }



	while (txMouseButtons() != 2)     //�������� ����� � ��������� �������(?)
	{

	}
}

void createSys (CoordSys Coord)
{
	txLine (Coord.x0, Coord.y0, Coord.x0, Coord.y1);
	txLine (Coord.x0, Coord.y1, Coord.x1, Coord.y1);
}
