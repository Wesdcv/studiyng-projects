#include "TXLib.h"
#include <math.h>
#define COORDx1 50
#define COORDy1 50
#define COORDx2 1000
#define COORDy2 550
#define SCALING 20

//to do:
//переписать класс системы и кнопки
//стркмп
//единый счетчик
/*
система
зависит от размеров окна
начало координат в центре
рисование сетки
нормальные функции рисования системы после стирания

кнопка
поле - указатель на систему
координаты - только центр кнопки
параметр скейл (кнопки)
повторное нажатие скейлит функцию
*/

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

class KindaAbstract_button
{

	protected:

		double x0, y0;
		double x1, y1;
		int r, g, b;


	public:

		COLORREF buttonColor = RGB (r, g, b);

		double getx()
		{
			return x0;
		}

		const char* text;

		func fct;
		RECT area = {x0, y0, x1, y1};

		virtual bool if_triggered()
		{
			if (txGetPixel (txMouseX(), txMouseY()) == buttonColor)
			{
				return true;
			}

			else
			{
				return false;
			}
		}

		virtual void drawButton()
		{

			txSetFillColor (buttonColor);
			txSetColor (buttonColor);

			txLine (area.left, area.top, area.right, area.bottom);
			txLine (area.left, area.bottom, area.right, area.top);

			txSetColor (TX_WHITE);
			txTextOut (x0 + 30, y0 + 30, text);
		}

		void drawFunc (double arg)
		{
			double scale = SCALING;
			double delta = 0.05;

			if (fct (arg) == fct (arg + delta))
			{
				fct (arg);
				return;
			}

			txBegin();

			while (arg < COORDx2 - COORDx1)
			{

				if ( (COORDy2 - scale * fct (arg)) > 100)
				{
					txLine (COORDx1 + scale * arg, COORDy2 - scale * fct (arg), COORDx1 + scale * (arg + delta), COORDy2 - scale * fct (arg + delta));
				}

				arg += delta;
			}

			txEnd();
		}

		KindaAbstract_button (double x0, double y0, double x1, double y1,
		                      func fct_, const char* text1, int r_, int g_, int b_) :
			x0 (x0),
			y0 (y0),
			x1 (x1),
			y1 (y1),

			fct (fct_),
			text (text1),

			r (r_),
			g (g_),
			b (b_)     {}

};

class RoundButton: public KindaAbstract_button
{
    public:

		RoundButton (double x0, double y0, double x1, double y1,
		             func fct_, const char* text1, int r_, int g_, int b_) :

			KindaAbstract_button (x0, y0, x1, y1, fct_, text1, r_, g_, b_) {}

		virtual void drawButton() override
		{

			txSetFillColor (buttonColor);
			txSetColor (buttonColor);

			txCircle (x0, y0, y1 - y0);

			txSetColor (TX_WHITE);
			txTextOut (x0 + 30, y0 + 30, text);
		}

};

class EllipseButton: public KindaAbstract_button
{
    public:

		EllipseButton (double x0, double y0, double x1, double y1,
		               func fct_, const char* text1, int r_, int g_, int b_) :

			KindaAbstract_button (x0, y0, x1, y1, fct_, text1, r_, g_, b_) {}

		virtual void drawButton() override
		{

			txSetFillColor (buttonColor);
			txSetColor (buttonColor);

			txEllipse (area.left, area.bottom, area.right, area.top);

			txSetColor (TX_WHITE);
			txTextOut (x0 + 30, y0 + 30, text);
		}

};

class RectButton: public KindaAbstract_button
{
    public:

		RectButton (double x0, double y0, double x1, double y1,
		            func fct_, const char* text1, int r_, int g_, int b_) :

			KindaAbstract_button (x0, y0, x1, y1, fct_, text1, r_, g_, b_) {}


		virtual void drawButton() override
		{

			txSetFillColor (buttonColor);
			txSetColor (buttonColor);

			txRectangle (x0, y0, x1, y1);

			txSetColor (TX_WHITE);
			txTextOut (x0 + 30, y0 + 30, text);
		}

};

int count_ = 0;
const int max_count = 10;

class Manager
{
	public:

		KindaAbstract_button* Buttons [max_count];

		void if_pressed()
		{
			for (int i = 0; (*Buttons[i]).getx() != 0; i++)
			{
				double x = 0;

				if ( (*Buttons[i]).if_triggered())
                {
                    txSetColor (TX_LIGHTBLUE);
					(*Buttons[i]).drawFunc (x);
				}
			}
		}

		void drawButtons()
		{
			for (int i = 0; (*Buttons[i]).getx() != 0; i++)
			{
				(*Buttons[i]).drawButton();
			}
		}

		/*double clear_reset (double nothing)
        {
            txSetFillColor (TX_BLACK);
            txClear();
            txSetColor (TX_LIGHTGREEN);
            txLine (COORDx1, COORDy1, COORDx1, COORDy2);
            txLine (COORDx1, COORDy2, COORDx2, COORDy2);
            void drawButtons();
            return 1;
        }*/

		void new_button (KindaAbstract_button* button)
		{
			if (count_ < max_count)
			{
				Buttons[count_] = button;
				count_++;
			}
		};

		Manager(){}

		~Manager()
		{
			for (int i = count_; i > 0; i--)
			{
				delete Buttons[i];
			}

		}



};



void drawButtons (KindaAbstract_button Buttons_[])
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
	return 1;
}

void createSys (CoordSys Coord)
{
	txLine (Coord.x0, Coord.y0, Coord.x0, Coord.y1);
	txLine (Coord.x0, Coord.y1, Coord.x1, Coord.y1);
}

double change_color(double nothing)
{
    txSetColor (TX_LIGHTRED);
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

	Manager easy;

	easy.new_button (new RoundButton          (30  , 30, 210 , 60, sin        , "синус"  , 255, 0  , 0  ));
	easy.new_button (new EllipseButton        (220 , 30, 420 , 60, cos        , "косинус", 0  , 255, 0  ));
	easy.new_button (new RectButton           (430 , 30, 630 , 60, tan        , "тангенс", 0  , 0  , 255));
	easy.new_button (new RectButton           (430 , 330, 630 , 360, change_color       , "color", 0  , 0  , 255));
	easy.new_button (new KindaAbstract_button (860 , 30, 960 , 60, clear_reset, "удоли"  , 255, 255, 0  ));
	easy.new_button (new KindaAbstract_button (0   , 0 , 0   , 0 , 0          , "NULL"   , 0  , 0  , 0  ));


	easy.drawButtons();

	while (txMouseButtons() != 3)
	{
		if (txMouseButtons() == 1)
		{
			easy.if_pressed();
		}
	}

    return 0;
}

