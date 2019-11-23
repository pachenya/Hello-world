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
	for (f = 0; f < 16; f++)
	{
		init_pair (f, f, 0);
	}
	curs_set (0);
	keypad (stdscr, TRUE);
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

#if 0
class pos
{
private:
	int x, y;
public:
	int gtx ()
	{
		return x;
	}
	int gty ()
	{
		return y;
	}
	void stx (int n)
	{
		x = n;
	}
	void sty (int n)
	{
		y = n;
	}
	pos (int x, int y):x (x), y (y)
	{;
	}
};

class dpos
{
private:
	double dx, dy, r;
public:
	double x ()
	{
		return dx;
	}
	double y ()
	{
		return dy;
	}
	void stx (double x)
	{
		dx = x;
	}
	void sty (double y)
	{
		dy = y;
	}
	dpos (double x = 0, double y = 0, double r = 0)
	{
		dx = x;
		dy = y;
		this->r = r;
	}
};

class lstc
{
private:
	int nitems;
	int itemi;
	enum
	{
		N_STRSMAX = 16,
	};
	  std::string items[N_STRSMAX];
	int itemval[N_STRSMAX];
public:
	void clrlst ()
	{
		nitems = 0;
	}
	void addto (std::string s, int val);
	void printlist (int x, int y);
	int sele (int x, int y);
	lstc ()
	{
		nitems = 0;
		itemi = 0;
	}
};
#endif

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
lstc::printlist (int x, int y)
{
	clear ();
	for (int i = 0; i < nitems; i++)
	{
		set_color (C_LW);
		if (i == itemi)
		{
			set_color (C_LC);
			mvaddstr (y + i, x, ">>");
		}
		mvaddstr (y + i, x + 2, items[i].c_str ());
	}
	refresh ();
}

//timeout(50);

int
lstc::sele (int x = 2, int y = 5)
{
	int eflg = 0, rval = 0;
	itemi = 0;
	if (nitems <= 0)
	{
		addto ("ok", 0);
	}
	while (1)
	{
		clear ();
		printlist (x, y);
		int ch = getch ();
		switch (ch)
		{
		case 'j':
		case KEY_DOWN:
			itemi++;
			if (itemi >= nitems)
				itemi = nitems - 1;
			break;
		case 'k':
		case KEY_UP:
			itemi--;
			if (itemi < 0)
				itemi = 0;
			break;
		case '\n':
		case '\r':
		case '\033':
			return itemval[itemi];
			break;
		}
	}
	return 0;
}

