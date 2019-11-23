


#include "in.h"

#include "hanabi.h"

void
gamemain ()
{
	lstc li;
	std::string s[] =
		{ "なます", "てまそ", "『アイス』おごれや……!?", "" };
	for (int i = 0; i < 10; i++)
	{
		if (s[i].empty ())
			break;
		li.addto (s[i], i);
	}
	li.printlist (1, 5);
#if 1
	int val = li.sele (1, 5);
	clear ();
  std::stringstream ss;
	ss << "val == " << val << '.' << std::endl;
	mvaddstr (2, 2, ss.str().c_str());
	refresh();
	waitk();
	hanabi h;
	for (int i = 0;i<1000;i++)
	{
    h.do_it();
	}
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
		mysleep (10);
	}
	pcen ("[press any key to continue]", 15);
	getch ();
	gamemain ();
	endwin ();
	return 0;
}
