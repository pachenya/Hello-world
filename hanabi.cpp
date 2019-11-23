
#include "hanabi.h"

#define WIDMAX 40
#define HGTMAX 22

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
hanabi::do_it ()
{
	std::list < hanabidama > itr;
	//auto itr = hlst.begin();
	mysleep(20);
	for (auto itr = hlst.begin (); itr != hlst.end (); itr++)
	{
    if (!itr-> k)
      continue;
		switch (itr->tval)
		{
		case 1:
			{
				itr->y += itr->vy;
				itr->vy *= 0.99;
				if (itr->vy > -0.5)
								itr->vy = -0.5;
				if (itr->y <= 10)
				{
					if (rn (7) == 0)
					{
						double speed = rndd (1) + 0.5;
						for (int i = 0; i < 33; i++)
						{
							double ddir = ((MY_PI*2) / 33) * i;
							double vx = cos (ddir) * speed,
										 vy = sin (ddir) * speed;
							int color = rn(16);
							hanabidama d (2, color, 
  							itr->x, itr->y, vx, vy);
							hanabidama d2 (2, color, 
								itr->x, itr->y, vx * 0.5, vy * 0.5);
							hlst.push_front (d);
							hlst.push_front (d2);
						}
						itr->k = 0;
					}
				}
			}
			break;
		case 2:
			{
				itr->x += itr->vx;
				itr->y += itr->vy;
				itr->vx *= 0.9;
				itr->vy *= 0.9;
				if (itr->x < 0 || 
				    itr->x > WIDMAX - 1  || itr->y >  HGTMAX-1)
				{
					itr->k = 0;
				}
				if (itr->cnt++ >= 40)
				{
					itr->k = 0;
				}
			}
			break;
		}
	}
	if (rn (15) == 0)
	{
		hanabidama d (1, 15, rn (WIDMAX), HGTMAX-1, 0, -0.7 + rndd(1));
		hlst.push_front (d);
	}
	clear ();
	for (auto itr = hlst.begin (); itr != hlst.end (); itr++)
	{
    if (!itr->k) continue;
		set_color (itr->sval);
		if (itr->x < 0 || itr->x > WIDMAX -1  || itr->y > HGTMAX)
		{
			itr->k = 0;
		}
		mvaddch ((int) itr->y, (int) itr->x, '*');
	}
	refresh();
	seiton();
}



