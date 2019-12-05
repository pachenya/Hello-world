


#include "in.h"

#include "hanabi.h"
#include "vanee.h"

void
gamemain ()
{
	lstc li;
	std::string s[] =
		{ "花火", "スタート・ザ・ゲーム",  "終了", ""};
						//"『アイス』おごれや……!?", "" };
	for (int i = 0; i < 10; i++)
	{
		if (s[i].empty ())
			break;
		li.addto (s[i], i);
	}
	int val = li.sele ();
	clear ();
  //std::stringstream ss;
	//ss << "val == " << val << '.' << std::endl;
#if 1
	//mvaddstr (2, 2, ss.str().c_str());
	//mvaddstr (3, 2, "[press enter to continue]"); 
	//refresh();
	//waitk();
#endif
	if(val == 0)
  {
	  hanabi h;
    for (int i = 0;i<2500;i++)
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
#if 1
    GameVanee vamp;
		vamp.do_game();
#else
    pcen("--[Coming soon]--", 11);
#endif
		refresh();
		waitk();
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
		mysleep (10);
	}
	pcen ("[press any key to continue]", 15);
	getch ();
	gamemain ();
	endwin ();
	return 0;
}
