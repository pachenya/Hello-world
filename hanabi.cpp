
#include "hanabi.h"

#define WIDMAX 40
#define HGTMAX 22


bool
hanabi::is_hamidashi (double x, double y)
{
  bool rval = false;
  if (x >= 40 || x < 0 || y >= 20)
  {
    rval = true;
  }
  return rval;
}

hanabi::~hanabi ()
{
  std::list < hanabidama > itr;
  for (auto itr = hlst.begin (); itr != hlst.end ();)
  {
    itr = hlst.erase (itr);
  }
}

void
hanabi::seiton ()
{
  std::list < hanabidama > itr;
  for (auto itr = hlst.begin (); itr != hlst.end ();)
  {
    if (itr->k == 0)
      itr = hlst.erase (itr);
    else
      itr++;
  }
}

void
hanabi::do_it_nagare (std::list < hanabidama >::iterator itr)
{
  itr->x += itr->vx;
  itr->y += itr->vy;
  itr->vy += 0.03;
  if (is_hamidashi (itr->x, itr->y))
  {
    itr->k = 0;
  }
}

void
hanabi::do_it_uchiage (std::list < hanabidama >::iterator itr)
{
  itr->y += itr->vy;
  itr->vy *= 0.9;
  if (itr->vy > -0.5)
    itr->vy = -0.5;
  if ((itr->y <= 10 && rn (10) == 0) || itr->y <= 1)
  {
    int color = rn (2) ? C_P : C_LW;
    for (int i = 0; i < 11; i++)
    {
      double ddir = rndd (MY_PI * 2);
      double vx = cos (ddir) * (rndd (0.5) + 0.2);
      double vy = sin (ddir) * (rndd (0.5) + 0.2);
      hanabidama d (2, color, itr->x, itr->y, vx, vy);
      hlst.push_front (d);
    }
    itr->k = 0;
  }
}

void
hanabi::do_it ()
{
  std::list < hanabidama > itr;
  //auto itr = hlst.begin();
  mysleep (20);
  for (auto itr = hlst.begin (); itr != hlst.end (); itr++)
  {
    if (!itr->k)
      continue;
    switch (itr->tval)
    {
    case 1:
      do_it_uchiage (itr);
      break;
    case 2:
      do_it_nagare (itr);
      break;
    }
    if (itr->cnt++ >= 200)
    {
      itr->k = 0;
    }
    if (is_hamidashi (itr->x, itr->y))
    {
      itr->k = 0;
    }
  }

  if (rn (15) == 0)
  {
    hanabidama d (1, 15, rn (WIDMAX), 19, 0, -0.7 + rndd (1));
    hlst.push_front (d);
  }
  clear ();
  for (auto itr = hlst.begin (); itr != hlst.end (); itr++)
  {
    if (!itr->k)
      continue;
    set_color (itr->sval);
    if (itr->y >= 0)
    {
      mvaddch ((int) itr->y, (int) itr->x, '*');
    }
  }
  mvaddstr (0, 0, "[\'q\'_to_exit].");
  refresh ();
  seiton ();
}
