

#ifndef __HANABI_H_INC__
#define __HANABI_H_INC__

#include "in.h"

class hanabidama
{
public:
  int k;
  int tval, sval;
  double x, y;
	double vx, vy;
	unsigned int cnt;
	hanabidama(int tval, int sval, double x, double y, double vx, double vy) : tval(tval) , sval(sval), x(x), y(y), vx(vx), vy(vy)
  {
    k=1;
		cnt = 0;
  }
	void kill() {k=0;}
};

class hanabi {
private:
  std::list <hanabidama> hlst;
public:
	void do_it();
	void do_it_uchiage(std::list<hanabidama>::iterator itr);
	void do_it_nagare(std::list<hanabidama>::iterator itr);
  void seiton();
  bool is_hamidashi(double x, double y);
	~hanabi();
};

#endif


