

#ifndef __INH_INCED__
#define __INH_INCED__
#include <ncurses.h>
#include <string>
#include <sstream>
#include <list>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#if 1 
#define C_DW 0
#define C_DR 1
#define C_DG 2
#define C_DY 3
#define C_B  4
#define C_DM 5
#define C_DC 6
#define C_DW2 7
#define C_GR 8
#define C_R 9
#define C_GRN 10
#define C_Y 11
#define C_DB 12
#define C_P 13
#define C_LC 14
#define C_LW 15
#endif

const int DWID = 40;
const int DHGT = 20;

int rn(int n)
{
  if (n <= 0) return 0;
	return (rand() % n);
}

void
mysleep(int n)
{
  usleep(n*1000);
}

void pcen(std::string s, int y)
{
  int len = s.length();
	mvaddstr(y, (DWID-len)/2, s.c_str());
}

void waitk()
{
  while (1)
  {
    char ch = getch();
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
	noecho();
  start_color ();
  for (f = 0; f < 16; f++)
  {
    init_pair (f, f, 0);
  }
	curs_set(0);
  clear ();
  srand (time (0));
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

class dpos {
private:
  double dx, dy, r;
public:
	double x(){return dx;}
	double y(){return dy;}
	void stx(double x){dx=x;}
	void sty(double y){dy=y;}
	dpos(double x=0, double y=0, double r=0)
	{
    dx=x;
		dy = y;
		this->r=r;
	}
};


#endif //__INH_INCED__

