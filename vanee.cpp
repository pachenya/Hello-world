//
// vanee.cpp
//

#include "vanee.h"

#include <stdio.h>

#define _DEBUG_
void
DEBUGMSG (std::string s, int i = 1)
{
#ifdef _DEBUG_
  move (0, 0);
  printw ("%s%d", s.c_str (), i);
  refresh ();
  waitk ();
#endif
}

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
  k = 1;
}

psn_c::psn_c (psnd_t ini)
{
  k = 1;
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

bool
psn_c::operator< (const psn_c * right)
{
	const psn_c * left = this;
  if (left->sk < right->sk)
  {
    if (left->abssk < right->abssk)
    {
      return true;
    }
  }
  return false;
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
  MON_RANDY,
  MON_TETSUO,
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
   "ランディ", 2, 22, 150, 100, 150, 2000, 18, 9, 9, 8},
  {
   "テツオ", 2, 0, 80, 110, 100, 2000, 10, 12, 15, 12},
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
GameVanee::clnmsg (void)
{
  int cnt = 3;
  while (cnt--)
  {
    msgs.push_front ("                          ");
  }
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
  if (cnt >= MSGMAX)
  {
    msgs.pop_back ();
  }
  printmsgs ();
}

void
GameVanee::printmsgs ()
{
  int cnt = 3;
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
  all_rfrs ();
}

void
GameVanee::tOK (std::string s)
{
  clnmsg ();
  addmsg (s);
  printmsgs ();
  selel.clrlst ();
  selel.addto ("OK", 0);
  selel.sele ();
}

int
GameVanee::talkYN (std::string s)
{
  clnmsg ();
  addmsg (s);
  selel.clrlst ();
  selel.addto ("Yes", 1);
  selel.addto ("No", 0);
  int rval = selel.sele ();
  selel.clrlst ();
  return rval;
}

void
GameVanee::all_rfrs ()
{
  for (int i = 0; i < 4; i++)
  {
    if (mons[i].k)
      printpsn_at (1, 13 + i * 2, mons[i]);
  }
}

int
GameVanee::do_attk (psn_c * atk, psn_c * def)
{
  int rval = 0;
  std::stringstream ss;
  if (rn (20) && rn (atk->stDex / 2))
  {
    int dam = 1 + rn (atk->stStr / 2) + rn (atk->stStr / 2);
    ss << atk->name << "は" << def->name << "への攻撃を当てた！" << "(" << dam << ")";
    def->hp -= dam;
    tOK (ss.str ());
    if (def->hp < 0)
      rval = 1;
  }
  else
  {
    ss << atk->name << "の" << def->name << "への攻撃は外れた！";
    tOK (ss.str ());
    rval = 0;
  }
  return rval;
}

int
GameVanee::batoru ()
{
  int rval = 0, done = 0;
	psn_c * m[16] = {&mons[0], &mons[1]};
  int abssk[2] = { 1, 2 };
  for (int i = 0; i < 2; i++)
  {
    m[i]->sk = 100;
  }
  int goflg;

  while (!done)
  {
    goflg = 0;
#if 0
    for (int i = 0; i < 2; i++)
    {
      int r = rn (2);
      //swap
      int tmp = abssk[i];
      abssk[i] = abssk[r];
      abssk[r] = tmp;
    }
    for (int i = 0; i < 2; i++)
    {
      m[i]->abssk = abssk[i];
    }
#endif
    for (int i = 0; i < 2; i++)
    {
      m[i]->sk -= (10 + rn (m[i]->stDex / 2));
      if (m[i]->sk <= 0)
      {
        goflg = 1;
      }
    }
		if (!goflg) 
			continue;
    if (goflg)
    {
      for (int i = 0; i < 2; i++)
      {
        psn_c *mtmp = m[i];
        if (!mtmp->is_enemy && mtmp->sk <= 0)
        {
          mtmp->sk += 100;
          do_attk (mtmp, &mons[1]);
          if (mons[1].hp < 0)
          {
            rval = 1;
            done = 1;
          }
        }
        else if (mtmp->is_enemy && mtmp->sk <= 0) // is enem
        {
          mtmp->sk += 100;
          do_attk (mtmp, &mons[0]);
          if (mons[0].hp <= 0)
          {
            rval = 0;
            done = 1;
          }
        }
      }
    }
    if (!m[0]->k || !m[1]->k)
      done = 1;
  }
  if (rval == 0)
    tOK ("きみは負けた……");
  else
    tOK ("勝った！");
  return rval;
}

void
GameVanee::walkStreet ()
{
  int mbflg = 0;
  while (1)
  {
    tOK ("きみは公園のようなところにいる。");
    if (flgs[FL_ST] < 1)
      tOK ("見覚えの無い風景だ。");
    addmsg ("さて、どうしたものだろう？");
    selel.clrlst ();
    selel.addto ("しばし休憩をする", 1);
    if (flgs[1] == 0)
    {
      selel.addto ("喫茶店へ行く", 2);
      selel.addto ("ラーメン屋へ行く", 2);
      selel.addto ("さいぜり屋さんへ行く", 2);
    }
    if (!flgs[2])
    {
      selel.addto ("モルゴスをこらしめる", 4);
      selel.addto ("サウロンをこらしめる", 4);
    }
    if (flgs[1])
      selel.addto ("家に帰る", 5);
    switch (selel.sele ())
    {
    case 1:
      tOK ("きみはいつの間にかベンチで眠ってしまった。");
      mons[0].hp = mons[0].mhp;
      mons[0].mp = mons[0].mmp;
      tOK ("そして奇怪な夢から目覚めた。");
      break;
    case 5:
      if (flgs[FL_ST] == 3)
      {
        tOK ("きみは家の場所を思い出した！");
        tOK ("この公園はうちの近所だ！");
        tOK ("だがそれ以上は思い出せない");
        tOK ("まあとにかく家には帰れそうだ．");
        mbflg = 1;
      }
      else if (flgs[FL_ST] > 3)
      {
        mbflg = 1;
      }
      else if (flgs[FL_ST] == 0)
      {
        addmsg ("すべてを忘れたと思ったが……");
        tOK ("家の場所はなんとなく思い出せそうだ‥‥‥");
      }
      else if (flgs[FL_ST] == 1)
      {
        tOK ("思い出せるはず……");
      }
      else if (flgs[FL_ST] > 0)
      {
        tOK ("もうちょっと頑張ればあるいは……");
      }
      flgs[FL_ST] += 1;
      break;
    case 2:
    case 3:
      if (!flgs[1])
      {
        tOK ("きみはここがどこなのかすらわからない！");
        tOK ("記憶の糸をたどりたいが……");
        tOK ("とくに移動しないことにした……");
        flgs[1] = 1;
      }
      break;
    case 4:
      if (!flgs[2])
      {
        tOK ("Angbandはできそうもない……");
        flgs[2] += 1;
        break;
      }
    }
    if (mbflg)
      break;
  }
}

void
GameVanee::itemGetRand ()
{
  item_c itm ("★★止まらない『ヒザ』", 1, item_c::TV_ARM, 1, 1);
  mons[0].getItem (itm);
#if 0
  item_c itm2 ("★アイスごと投げられる", 1, item_c::TV_ARM, 1, 2);
  mons[1] getItem (itm2);
#endif
  item_c itm3 ("★★★『本場のファイト』", 1, item_c::TV_ARM, 1,
               3);
  mons[1].getItem (itm3);
#if 0
  m_ptr[0]->getItem (itm3);
  item_c itm4 ("★ユリ超ごっついタイガーバズーカ", 1,
               item_c::TV_ARM, 1, 4);
  m_ptr[1]->getItem (itm4);
#endif
}


int
GameVanee::dg_moveto ()
{
  addmsg ("どこへ行く？");
  selel.clrlst ();
  selel.addto ("公園", 1);
  selel.addto ("自宅", 2);
  int rval = selel.sele ();
  if (rval == 1)
    walkStreet ();
  else
  {
    tOK ("-- Coming soon --");
    return 1;
  }
  return 0;
}

void
GameVanee::do_game ()
{
  // printplayer
  mons.push_back (psn_c (u[0]));
  mons.push_back (psn_c (u[1]));
  mons.push_back (psn_c (u[2]));
  mons.push_back (psn_c (u[3]));
  mons.push_back (psn_c (u[4]));
  itemGetRand ();
  move (2, 2);
  set_color (15);
  mons[0].mp = 60;
	mons[0].is_enemy = 0;
	mons[1].is_enemy = 1;
	mons[2].k = 0;
	mons[3].k = 0;
	mons[4].k = 0;
  DEBUGMSG ("batoru hajime.");
  batoru ();
  DEBUGMSG ("batoru owari.");
  mons[0].hp = 10 + rn (20);
  mons[1].k = 0;
  tOK ("......");
  tOK ("きみは公園のようなところで目を覚ました。");
  walkStreet ();
  while (1)
  {
    if (dg_moveto ())
      break;;
  }
  addmsg ("きみは街を歩いている。");
  talkYN ("きみは今、すこしは楽しいだろうか？");
  tOK ("なるほど。じゃあね。");
}
