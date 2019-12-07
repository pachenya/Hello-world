//
// in.cpp
// 

#include "in.h"


std::mt19937 mt(0);

int
rn (int n)
{
	if (n <= 0)
		return 0;
	return (mt () % n);
}

double
rndd (double maxpoint)
{
	return ((double) mt()  / (double) 0xffffffff) * maxpoint;
}

void
mysleep (int n)
{
	usleep (n * 1000);
}

void
pcen (std::string s, int y)
{
	int len = s.length ();
	mvaddstr (y, (DWID - len) / 2, s.c_str ());
}

void
waitk ()
{
	while (1)
	{
		char ch = getch ();
		if (ch == ' ' || ch == '\033' || ch == '\n' || ch == '\r')
		{
			break;
		}
	}
}

int
initall ()
{
	int f;
	initscr ();
	noecho ();
	start_color ();
	//nonl();
	//cbreak();
	for (f = 0; f < 16; f++)
	{
		init_pair (f, f, 0);
	}
	curs_set (0);
	keypad (stdscr, TRUE);
	leaveok(stdscr, TRUE);
	clear ();
	mt.seed(2);
	//srand (time (0));
	return 0;
}

void
cleanall ()
{
	curs_set (1);
	endwin ();
}

void
set_color (int i)
{
	attrset (COLOR_PAIR (i));
}

void
lstc::addto (std::string s, int val)
{
	if (nitems >= N_STRSMAX)
		return;
	items[nitems] = s;
	itemval[nitems] = val;
	nitems++;
}

void
lstc::cleanuplist(int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		mvaddstr(y + i, x, 
    "                               ");
	}
}

void
lstc::printlist (int x, int y)
{
  int ofs = 0;
  cleanuplist(x, y);
	for (int i = 0; i < nitems; i++)
	{
    int iy = ofs + i + y;
		if (iy < y) continue;
		//if (iy >= y + max - 1) continue;
		set_color (C_LW);
		if (i == itemi)
		{
			set_color (C_LC);
			mvaddstr (iy, x, ">>");
		}
		mvaddstr (iy, x + 2, items[i].c_str ());
	}
	refresh ();
}

//timeout(50);

void
lstc::scrollit(int y)
{
				itemi += y;
				if (itemi >= nitems)
				{
								itemi = nitems - 1;
				}
				if (itemi < 0)
				{
								itemi = 0;
				}
}

int
lstc::sele (int x, int y)
{
	int eflg = 0;
	itemi = 0;
	if (nitems <= 0)
	{
		addto ("ok", 0);
	}
	while (1)
	{
		printlist (x, y);
		int ch = getch ();
		switch (ch)
		{
		case 'j':
		case KEY_DOWN:
      scrollit(1);;
			break;
		case 'k':
		case KEY_UP:
			scrollit(-1);
			break;
		case '\n':
		case '\r':
		//case '\033':
		  eflg = 1;
			break;
		}
		if (eflg)
						break;
	}
	clear();
	refresh();
	return itemval[itemi];
}

