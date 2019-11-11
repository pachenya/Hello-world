


#include "in.h"

char itli[BUFSIZ][BUFSIZ];
int item = 0;
int itn = 0;
int iid[BUFSIZ];

void
clitn ()
{
	itn = 0;
}

void
addtoli (char *str, int id)
{
	strcpy (itli[itn], str);
	iid[itn] = id;
	itn++;
}

void
showitem ()
{
	clear ();
	set_color (15);
	for (int i = 0; i < itn; i++)
	{
		set_color (C_DW);
		if (i == item)
		{
			set_color (C_LC);
			mvaddstr (2 + i, 0, ">>");
		}
		mvaddstr (2 + i, 2, itli[i]);
	}
	refresh ();
	return;
}

int
selec ()
{
	int rval = 0;
	item = 0;

	while (1)
	{
		int flgtmp = 0;
		showitem ();
		int ch = getch ();
		switch (ch)
		{
		case 'j':
		case KEY_DOWN:
			item++;
			if (item >= itn)
			{
				item = itn - 1;
				getch ();
			}
			break;
		case 'k':
		case KEY_UP:
			item--;
			if (item < 0)
				item = 0;
			break;
		case '\n':
		case '\r':
			rval = item;
			flgtmp = 1;
			break;
		case '\033':
			return -1;
		}
		//showitem ();
		if (flgtmp == 1)
			break;
	}
	return rval;
}

void
gamemain ()
{
	clitn ();
	char s[3][BUFSIZ] = { "namasu", "temaso", "Ice-ogoreya" };
	for (int i = 0; i < 3; i++)
	{
		addtoli (s[i], i);
	}
	showitem ();
#if 1
	int val = selec ();
	char buf[BUFSIZ];
	clear ();
	if (val != -1)
		sprintf (buf, "val == %d\n", val);
	mvaddstr (2, 2, buf);
#endif
	refresh ();
	waitk ();
	cleanall ();
}

void
colortest ()
{
	clear ();
	for (int i = 0; i < 16; i++)
	{
		set_color (i);
		std::stringstream ss;
		ss << i;
		mvaddstr (i + 1, 2, ss.str ().c_str ());
		refresh ();
	}
	getch ();
	clear ();
}

int
main ()
{
	initall ();
	colortest ();
	for (int i = 0; i < 10; i++)
	{
		clear ();
		pcen ("--Ice ogoreya--", i);
		refresh ();
		mysleep (30);
	}
	pcen ("[press any key to continue]", 15);
	getch ();
	gamemain ();
	endwin ();
	return 0;
}
