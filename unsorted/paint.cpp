#include "TXLib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef void (*func) ();

//to do:
//layer manager
//прозрачность
//сохранение и загрузка
//отмена и повтор

class vector
{
	public:

		double x, y, z;

		vector() : x (0), y (0), z (0) {}

		vector (double xx, double yy, double zz) : x (xx), y (yy), z (zz) {}


		vector operator + (vector a);
		vector operator * (double multiplicator);
		void operator ~ ();
		vector operator & (vector multiplicator);

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

void vector::operator ~ ()
{
	if (x > 1)
	{
		x = 1;
	}

	if (y > 1)
	{
		y = 1;
	}

	if (z > 1)
	{
		z = 1;
	}
}


class KindaAbstract_button
{

	protected:

		double x0, y0;
		double x1, y1;
		COLORREF buttonColor = RGB (150, 150, 150);

	public:

		const char* text;

		func fct;
		RECT area = {x0, y0, x1, y1};

		virtual bool if_triggered()
		{
			if ( (txMouseX() >= x0) && (txMouseX() <= x1) && (txMouseY() >= y0) && (txMouseY() <= y1))
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

			txRectangle (x0 + 10, y0 + 10, x1 + 10, y1 + 10);

			if (strcmp("oops", text) == 0)
			{
                return;
            }

			HDC icon = txLoadImage (text);
			txBitBlt (txDC(), x0, y0, 0, 0, icon);
            txDeleteDC (icon);
		}

		void drawFunc ()
		{
			fct();
		}

		KindaAbstract_button (double x0_, double y0_, double x1_, double y1_,
		                      func fct_, const char* text1) :
			x0 (x0_),
			y0 (y0_),
			x1 (x1_),
			y1 (y1_),

			fct (fct_),
			text (text1)   {}

};

int count_ = 0;
const int max_count = 10;

class Manager
{
	public:

		KindaAbstract_button* Buttons [max_count];

		void if_pressed()
		{
			for (int i = count_; i > 0; i--)
			{

				if ( (*Buttons[i]).if_triggered())
				{
					(*Buttons[i]).drawFunc();
				}
			}
		}

		void drawButtons()
		{
			for (int i = count_; i > 0; i--)
			{
				(*Buttons[i]).drawButton();
			}
		}


		void newButton (KindaAbstract_button* button)
		{
			if (count_ < max_count)
			{
				Buttons[count_] = button;
				count_++;
			}
		};

		Manager() {}

		~Manager()
		{
			for (int i = count_; i > 0; i--)
			{
				delete Buttons[i];
			}

		}



};

bool movement (double MouseX, double MouseY)
{
	txSleep (5);                                                   //алгоритм дерьма, - аргументы - слип + загуглить функцию ожидания + сохранить координаты

	if ( (txMouseX() == MouseX) && (txMouseY() == MouseY))
	{
		return false;
	}

	return true;
}

void drawInterface()
{
	txSetFillColor (TX_LIGHTGRAY);
	txSetColor (TX_LIGHTGRAY, 5);
	txRectangle (0, 0, 1400, 200);
	txSetFillColor (TX_WHITE);
	txRectangle (0, 200, 1400, 800);
}

void justDraw()
{
    while (movement(txMouseX(), txMouseY()))
    {
        int x = txMouseX();
        int y = txMouseY();
        txCircle(x, y, 2.5);
        txSleep (5);
        txCircle(x, y, 2.5);
        txLine(x, y, txMouseX(), txMouseY());
    }
}

int main()
{
	txCreateWindow (1400, 800);
	txTextCursor (false);

	drawInterface();

	POINT size = {1000, 600};

	RGBQUAD* buf = NULL;
	HDC dc = txCreateDIBSection (size.x, size.y, &buf);
	HDC cat = txLoadImage ("Images\\cute_cat.bmp");
	txBitBlt (txDC(), 400, 200, 0, 0, cat);
	txDeleteDC (cat);

	Manager Buttonsie;

	Buttonsie.newButton(new KindaAbstract_button (10, 10, 50, 40, justDraw, "oops"));



	/*
	  менеджер кнопок, кнопки (карандаш и выбор цвета)
	*/

    /* for (int y = 0; y < size.y; y++)
    for (int x = 0; x < size.x; x++)
    {
    RGBQUAD* color = & buf [x + y * size.x];

    color->rgbRed      = (BYTE) color->rgbRed   * 255;
    color->rgbGreen    = (BYTE) color->rgbGreen * 255;
    color->rgbBlue     = (BYTE) color->rgbBlue  * 255;

    }
    txLock();

    *(txVideoMemory() + 200*1400) = *color;   //сделать нормально или через CreateCompatibleBitmap и GetDIBits

    //txVideoMemory() = color;

    txUnlock();
    */
    Buttonsie.drawButtons();

	while (!txGetAsyncKeyState (VK_ESCAPE))
	{
        Buttonsie.if_pressed();
	}

	txDeleteDC (dc);


	return 0;


}
