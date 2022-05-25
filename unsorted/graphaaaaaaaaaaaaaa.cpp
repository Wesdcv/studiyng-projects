#include "TXLib.h"
#include <math.h>
#define COORDx1 50
#define COORDy1 50
#define COORDx2 1000
#define COORDy2 550
#define SCALING 20

typedef double (*func) (double);

void createSys (struct CoordSys);
void drawLine (double xscale, double yscale, double xvalues[10], double yvalues[10], CoordSys Coord);

struct CoordSys
{
	CoordSys (int ax, int bx, int ay, int by) :
		x0 (ax),
		x1 (bx),
		y0 (ay),
		y1 (by) {}

	CoordSys () :
		x0 (COORDx1),
		x1 (COORDx2),
		y0 (COORDy1),
		y1 (COORDy2) {}

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

		double getx()

		{
			return x0;
		}

		const char* text;

		func fct;

		RECT area = {x0, y0, x1, y1};

		void drawButton()
		{
            txSetFillColor (TX_WHITE);
			txRectangle (x0, y0, x1, y1);
			txSetColor (TX_LIGHTBLUE);
			txTextOut (x0 + 10, y0 + 10, text);
		}

		/*bool trigger()
		{
			return (In (txMousePos(), area));
		}  */

		void drawFunc (double arg)
		{
            double scale = SCALING;
            txBegin();

			while (arg < COORDx2 - COORDx1)
			{

				double delta = 0.05;
				if ((COORDy2 - scale*fct (arg)) > 100)
				{
                    txLine (COORDx1 + scale*arg, COORDy2 - scale*fct (arg), COORDx1 + scale*(arg + delta), COORDy2 - scale* fct (arg + delta));
				}
				arg += delta;
			}

			 txEnd();
		}

		button (double x0, double y0, double x1, double y1, func fct_,  char* text1) :

			x0 (x0),
			y0 (y0),
			x1 (x1),
			y1 (y1),
			fct (fct_),
			text (text1) {}



};



/*double CoordSys::clearall (double a)
{
    txSetFillColor (TX_BLACK);
    txClear();
    txSetColor (TX_LIGHTGREEN);
    createSys (Sys1);
    createSys (Sys2);
    return 1;
}   */

void drawButtons (button Buttons_[])
{
	for (int i = 0; Buttons_[i].getx() != 0; i++)
	{
		Buttons_[i].drawButton();
	}
}

double clear_reset (double nothing)
{
    txSetFillColor (TX_BLACK);
    txClear();
    txSetColor (TX_LIGHTGREEN);
    txLine (COORDx1, COORDy1, COORDx1, COORDy2);
	txLine (COORDx1, COORDy2, COORDx2, COORDy2);
    txSetColor (TX_LIGHTBLUE);
}



int main()
{
	txCreateWindow (1000, 600);
	txSetColor (TX_LIGHTGREEN);

	CoordSys Sys1;
	//CoordSys Sys2 (550, 50, 950, 550);

	createSys (Sys1);
	//createSys (Sys2);

	txSetColor (TX_LIGHTBLUE);

	button Buttons[] { button (10  , 10, 210 , 60, sin, "синус"),
	                   button (220 , 10, 420 , 60, cos, "косинус"),
	                   button (430 , 10, 630 , 60, tan, "тангенс"),
	                   button (640 , 10, 840 , 60, atan, "арктангенс"),
	                   button (860 , 10, 960 , 60, clear_reset, "удоли"),
	                   button (0   , 0 , 0   ,  0, 0, NULL)
	                 } ;

	drawButtons(Buttons);

	while (txMouseButtons() != 3)
	{

		if (txMouseButtons() & 1)
		{

			for (int i = 0; Buttons[i].getx() != 0; i++)
			{
				double x = 0;

				if (In (txMousePos(), Buttons[i].area))
				{
					txSetColor (TX_LIGHTBLUE);
					Buttons[i].drawFunc (x);
				}
			}
		}
	}



	while (txMouseButtons() != 2)     //наверное можно в отдельную функцию(?)
	{

	}
}

void createSys (CoordSys Coord)
{
	txLine (Coord.x0, Coord.y0, Coord.x0, Coord.y1);
	txLine (Coord.x0, Coord.y1, Coord.x1, Coord.y1);
}
