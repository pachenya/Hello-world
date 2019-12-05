//
// vanee.cpp
//

#include "vanee.h"

item_c::item_c (std::string s, int sta, int tval, int sval, int nitems)
{
  iname = s;
  stackable = sta;
  this->tval = tval;
  this->sval = sval;
  this->nitems = nitems;
}

item_c::item_c ()
{
  iname = "(nothing)";
  stackable = 0;
  tval = 0;
}

psn_c::psn_c (psnd_t ini)
{
  name = ini.name;
  hp = mhp = ini.hp;
  mp = mmp = ini.mmp;
  sta = msta = ini.msta;
  gold = ini.dgold;
  level = ini.level;
  expe = ini.expe;
  stStr = ini.Str;
  stDex = ini.Dex;
  stInt = ini.Int;
  stChr = ini.Chr;
}

psn_c & psn_c::operator = (const psn_c & r)
{
  hp = r.hp;
  mhp = r.mhp;
  mp = r.mp;
  mmp = r.mmp;
  sta = r.sta;
  msta = r.msta;
  gold = r.gold;
  level = r.level;
  expe = r.expe;
  stStr = r.stStr;
  stDex = r.stDex;
  stInt = r.stInt;
  stChr = r.stChr;
  itemnum = r.itemnum;
  for (int i = 0; i < N_SKILLS; i++)
  {
    skills[i] = r.skills[i];
  }
  return *this;
}

int
psn_c::gsr (int skn)
{
  return psn_c::skills[skn].rank;
}

bool
item_c::is_stackable (item_c b)
{
  item_c a = *this;
  if ((a.stackable && b.stackable) && a.tval == b.tval && a.sval == b.sval)
  {

    if ((a.stackable + b.stackable) <= a.stackable)
    {
      return true;
    }
  }
  else
  {
    if (a.tval == 0 || b.tval == 0)
    {
      return true;
    }
  }
  return false;
}

int 
psn_c::getItem (item_c itm)
{
  for (int i = 0; i < N_BAG; i++)
  {
    if (items[i].is_stackable (itm))
    {
      items[i].nitems += itm.nitems;
      return 1;
    }
  }
  return 0;
}

psnd_t u = 
{
  
  "ゴリ夫", 1, 5, 100, 100, 125, 3000, 16, 10, 9, 5
};

void
GameVanee::do_game ()
{
  // printplayer
  p_ptr = new psn_c (u);
	move(2,2);
	set_color(15);
  printw ("%s hp:%d/%d", p_ptr->name.c_str(), p_ptr->hp, p_ptr->mhp);
  waitk ();
  delete (p_ptr);
}


