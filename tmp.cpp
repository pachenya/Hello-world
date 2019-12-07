


#include "in.h"

#include "hanabi.h"
#include "vanee.h"

void
gamemain ()
{
	lstc li;
	std::string s[] =
		{ "Hanabi", "Start the Game",  "Exit", ""};
						//"『アイス』おごれや……!?", "" };
	for (int i = 0; i < 10; i++)
	{
		if (s[i].empty ())
		{
			break;
		}
		li.addto (s[i], i);
	}
	int val = li.sele ();
	clear ();
#if 1
  std::stringstream ss;
	ss << "val == " << val << '.' << std::endl;
	mvaddstr (2, 2, ss.str().c_str());
	mvaddstr (3, 2, "[press enter to continue]"); 
	refresh();
	waitk();
#endif
	if(val == 0)
  {
	  hanabi h;
    for (int i = 0;i<880;i++)
	  {
      h.do_it();
	    wtimeout(stdscr, 0);
		  int ch=getch();
		  if (ch == 'q' || ch == 'Q')
		  {
        break;
		  }
			mvaddstr(0,0,"\'q\' to exit.");
	  }
	}
  else if (val == 1)
  {
    clear();
		set_color(C_P);
    GameVanee vamp;
		vamp.do_game();
		refresh();
		cleanall();
  }
  else if (val ==2)
  {
    ;
    // do nothing...;
  }

	mvaddstr(1,1, "[press enter to exit]");
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
