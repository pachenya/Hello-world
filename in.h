

#ifndef __INH_INCED__
#define __INH_INCED__

#include <ncurses.h>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <random>
//#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define MY_PI 3.14159265359

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

#define DWID 40
#define DHGT 20

int rn (int n);

double rndd (double maxpoint);

void mysleep (int n);

void pcen (std::string s, int y);

void
waitk ();

int
initall ();

void
cleanall ();

void set_color (int i);

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
	int rooru;
	enum
	{
		N_STRSMAX = 64,
	};
  std::string items[N_STRSMAX];
	int itemval[N_STRSMAX];
public:
	void clrlst ()
	{
    itemi = 0;
		rooru = 0;
		nitems = 0;
	}
	void addto (std::string s, int val);
	void printlist (int x, int y);
	int sele (int x = 2, int y = 10);
  void scrollit(int y);
  void cleanuplist(int x, int y);
	lstc ()
	{
		nitems = 0;
		itemi = 0;
		rooru = 0;
	}
};

//timeout(50);

#endif //__INH_INCED__
