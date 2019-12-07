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

psn_c::psn_c ()
{
  name = "[U.N.Owen]";
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


enum
{
  MON_GORIO,
  MON_TETSUO,
  MON_RANDY,
  MON_KURAGE,
  MON_SKURAGE,
  MON_KIRIKUWA,
  N_MONS,
};
//
//typedef struct psnd_t_def
//{
//  std::string name;
//  int level, expe, hp, mmp, msta;
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
   "クラゲ", 1, 5, 100, 100, 125, 3000, 8, 4, 3, 3},
  {
   "超クラゲ", 5, 40, 255, 100, 150, 3000, 18, 4, 3, 3},
  {
   "切り裂きクワガタムシ",
   5, 100, 90, 100, 125, 2, 9, 22, 3, 3},
  {
   "", 0, 0, 0, 0, 0, 999, 10, 10, 10, 10},
};

int
GameVanee::gainer_expe (psn_c atk, psn_c def)
{
  int tbl[11] = {
    5, 10, 20, 30, 40,
    50,
    60, 70, 80, 90, 100,
  };
  int i;
  int alev = atk.level, blev = def.level;
  i = (blev - alev) + 5;
  if (i < 0)
    i = 0;
  if (i > 10)
    i = 10;
  return tbl[i];
}

void
GameVanee::printpsn_at (int x, int y, psn_c & o)
{
  char buf[BUFSIZ];
  move (y, x);
  set_color (15);
  addstr (o.name.c_str ());
  sprintf (buf, " Level:%2d HP:%3d/%3d TP:%3d/%3d Exp:%d", o.level, o.hp,
           o.mhp, o.mp, o.mmp, o.expe);
  buf[BUFSIZ - 1] = '\0';
  addstr (buf);
  mvaddstr (y + 1, x, o.items[0].iname.c_str ());
}

void
GameVanee::addmsg (std::string s)
{
  int cnt = 0;
  msgs.push_front (s);
  std::list < std::string > itr;
  for (auto itr = msgs.begin (); itr != msgs.end (); itr++)
  {
    cnt++;
  }
  while (cnt >= MSGMAX)
  {
    msgs.pop_back ();
  }
  printmsgs ();
}

void
GameVanee::printmsgs ()
{
  int cnt = 8;
  std::list < std::string > itr;
  for (auto itr = msgs.begin (); itr != msgs.end (); itr++)
  {
    mvaddstr (cnt, 1, "                           ");
    set_color (C_LW);
    mvaddstr (cnt, 1, itr->c_str ());
    cnt--;
    if (cnt <= 0)
      break;
  }
}

#define DEFY 11

void
GameVanee::tOK (std::string s)
{
  addmsg (s);
  printmsgs ();
  selel.clrlst ();
  selel.addto ("OK", 0);
  selel.sele ();
  selel.clrlst ();
}

int
GameVanee::talkYN (std::string s)
{
  addmsg (s);
  selel.clrlst ();
  selel.addto ("Yes", 1);
  selel.addto ("No", 0);
  int rval = selel.sele ();
  selel.clrlst ();
  return rval;
}

void
GameVanee::walkStreet ()
{
  int mbflg = 0;
  while(1)
	{
  tOK ("きみは公園のようなところで目を覚ました。");
  tOK ("見覚えの無い風景だ。");
	addmsg("さて、どうしたものだろう？");
  selel.addto("しばし休憩をとる",1);
  selel.addto("ストリートへ行く",2);
  selel.addto("サイゼリ屋さんへ行く",3);
  selel.addto("モルゴスをこらしめる",4);
  selel.addto("家に帰る",5);
	switch(selel.sele())
	{
  case 1:
					tOK("きみはいつの間にか眠ってしまった。");
					tOK("そして奇怪な夢から目覚めた。");
					break;
  case 5: 
				  if (flgs[FL_ST] >= 5)
					{
							tOK("きみは家の場所を思い出した！");
							tOK("この公園はうちの近所だ！");
							if (flgs[FL_ST] >= 6)
							{
							  mbflg = 1;
							}
					}
					else
					{
					  tOK("家の場所はなんとなく思い出せそうだ‥‥‥");
					flgs[FL_ST]++;
					}
          break;
  case 2:
	case 3:
					if (flgs[FL_ST] >= 7)
					{
									tOK("おぼろげに思い出してきたような気がする……");
					}
					else
					{
					  tOK("きみはここがどこなのかすらわからない！");
					}
					break;
	case 4:
					tOK("Angbandはできそうもない……");
					break;
  }
	if (mbflg) break;
	}
}

void
GameVanee::itemGetRand ()
{
  item_c itm ("★★止まらない『ヒザ』", 1, item_c::TV_ARM, 1, 1);
  p_ptr->getItem (itm);
  item_c itm2 ("★アイスごと投げられる", 1, item_c::TV_ARM, 1, 2);
  p_ptr2->getItem (itm2);
}

void
DEBUGMSG ()
{
#ifdef _DEBUG_
  static unsigned char p = 0;
  addch ('a' + p);
  p++;
  refresh ();
  waitk ();
#endif
}

int GameVanee::dg_moveto()
{
				addmsg("どこへ行く？");
				selel.clrlst();
				selel.addto("公園", 1);
		return 0;	
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
  printpsn_at (1, 17, *p_ptr);
  printpsn_at (1, 20, *p_ptr2);
  DEBUGMSG ();
  walkStreet ();
  addmsg ("きみは街を歩いている。");
  addmsg ("街路樹は寒そうだ。");
  talkYN ("きみは今、寒いだろうか？");
  tOK ("なるほど。じゃあな。");
  delete (p_ptr);
  delete (p_ptr2);
}


