//
// vanee.cpp
//

#include "vanee.h"

#include <stdio.h>

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
  sval = 0;
  nitems = 0;
}

item_c & item_c::operator = (const item_c & r)
{
  iname = r.iname;
  stackable = r.stackable;
  tval = r.tval;
  sval = r.sval;
  nitems = r.nitems;
  return *this;
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
  for (int i = 0; i < N_BAG; i++)
  {
    items[i] = r.items[i];
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
  if (a.nitems == 0 || b.nitems == 0)
    return true;
  if (a.tval == b.tval && a.sval == b.sval)
    return true;
  return false;
}

int
psn_c::getItem (item_c itm)
{
  for (int i = 0; i < N_BAG; i++)
  {
    if (items[i].is_stackable (itm))
    {
      items[i] = itm;
      items[i].nitems += itm.nitems;
      return 1;
    }
  }
  return 0;
}

//
//typedef struct psnd_t_def
//{
//  std::string name;
//  int level, expe;
//  int hp, mmp, msta;
//  int dgold;
//  int Str, Dex, Int, Chr;
//} psnd_t;
//
psnd_t u[] = {
  {
   "ゴリ夫", 1, 5, 100, 100, 125, 3000, 16, 10, 9, 5},
  {
   "テツオ", 2, 0, 80, 110, 100, 2000, 10, 12, 15, 12},
  {
   "ランディ", 2, 22, 150, 100, 150, 2000, 18, 9, 9, 8},
  {
   "", 0, 0, 0, 0, 0, 999, 10, 10, 10, 10},
};

void
GameVanee::printpsn_at (int x, int y, psn_c & o)
{
  char buf[BUFSIZ];
  move (y, x);
  set_color (15);
  addstr (o.name.c_str ());
  sprintf (buf, " HP:%3d/%3d TP:%3d/%3d",
           o.hp, o.mhp, o.mp, o.mmp);
  buf[BUFSIZ - 1] = '\0';
	addstr(buf);
  mvaddstr (y + 1, x, o.items[0].iname.c_str());
#if 0
  std::stringstream ss;
  ss << " HP:" << o.hp << "/" << o.mhp << " TP:" << o.mp << "/" << o.mmp;
  mvaddstr (y + 1, x, ss.str ().c_str ());
  ss.str ("");
  ss << "能力 : " << o.items[0].iname;
  mvaddstr (y + 2, x, ss.str ().c_str ());
#endif
}

void
GameVanee::itemGetRand ()
{
  item_c itm ("★止まらない『ヒザ』", 1, item_c::TV_ARM, 1, 1);
  p_ptr->getItem (itm);
  item_c itm2 ("★アイスごと投げられる", 1, item_c::TV_ARM, 1, 2);
  p_ptr2->getItem (itm2);
}


void
GameVanee::do_game ()
{
  // printplayer
  p_ptr = new psn_c (u[0]);
  p_ptr2 = new psn_c (u[1]);
  itemGetRand ();
  move (2, 2);
  set_color (15);
  printpsn_at (1, 10, *p_ptr);
  printpsn_at (1, 12, *p_ptr2);
  waitk ();
  delete (p_ptr);
  delete (p_ptr2);
}
