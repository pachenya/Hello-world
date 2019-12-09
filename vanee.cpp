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
}

// #define DEFY 11

void
GameVanee::tOK (std::string s)
{
  addmsg (s);
  printmsgs ();
  selel.clrlst ();
  selel.addto ("OK", 0);
  selel.sele ();
  //selel.clrlst ();
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

int
GameVanee::batoru (psn_c * player_s[2], psn_c * monster_s[2])
{
  int cnt = 0;
  int sk[4] = { 1, 1, 1, 1 };
  psn_c p[2] = { *player_s[0], *player_s[1] };
  psn_c m[2] = { *monster_s[0], *monster_s[1] };
  while (1)
  {
    int abssk[4] = { 1, 2, 3, 4 };
    for (int i = 0; i < 4; i++)
    {
      //shaffuru
      int r = rn (4);
      int tmp = abssk[i];
      abssk[i] = abssk[r];
      abssk[r] = tmp;
    }
    while (1)
    {
      sk[0] += (p[0].stDex / 2) + rn (6);
      //sk[1] += (p[1].stDex / 2) + rn (6);
      sk[2] += (m[0].stDex / 2) + rn (6);
      //sk[3] += (m[1].stDex / 2) + rn (6);
      for (int k = 0; k < 4; k++)
      {
        if (sk[k] < 100) continue;
          sk[k] = 0;
        enum
        {
          CM_AT,
          CM_SK,
          CM_GA,
          CM_EC,
          N_CMS,
        };

        printpsn_at (1, 17, p[0]);
        printpsn_at (1, 19, m[0]);
        if (k <= 1 && p[k].hp > 0)
        {
          lstc cmd;
          cmd.addto ("攻撃", CM_AT);
          cmd.addto ("技", CM_SK);
          cmd.addto ("防御", CM_GA);
          cmd.addto ("逃走", CM_EC);
          int action = cmd.sele ();
					cmd.clrlst();
          if (action == CM_EC)
          {
            if (rn (20) && rn (20) + 1 < p[k].stDex / 2)
            {
              tOK ("きみは逃走に成功した！");
              return 0;
            }
            else
            {
              tOK ("逃げられなかった！");
            }
          }
          else if (action == CM_GA)
          {
            tOK ("きみは防御する！");
            ;
          }
          else if (action == CM_AT)
          {
            if (rn (20))
            {
              int dam = 1 + rn (p[k].stStr + rn (p[k].stStr) + p[k].stStr);
              char buf[BUFSIZ];
              sprintf (buf,
                       "%sは%sに攻撃をあてた！ (%d)",
											 p[k].name.c_str(),
                       m[0].name.c_str (), dam);
              tOK (buf);
							m[0].hp -= dam;
							if (m[0].hp <= 0)
							{
							  tOK ("きみは勝った！");
								return 0;
							}
            }
            else
            {
              tOK ("攻撃は命中しなかった！");
            }
          }
        }
        else                    // monst
        {
				  char buf[BUFSIZ];
              int dam = 1 + rn (m[k].stStr + rn (m[k].stStr) + m[k].stStr);
					sprintf(buf, "%sは%sに攻撃をあてた！(%d)",
				    m[0].name.c_str(),
						p[0].name.c_str(), dam);
					  p[0].hp -= dam;
						tOK(buf);
						if (p[0].hp <= 0)
						{
              printpsn_at (1, 17, *p_ptr[0]);
				      tOK("負けた……"); 
						  return 0;
						}
				}
      }
    }
  }
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
    selel.addto ("家に帰る", 5);
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
    printpsn_at (1, 17, *p_ptr[0]);
    switch (selel.sele ())
    {
    case 1:
      tOK ("きみはいつの間にかベンチで眠ってしまった。");
      p_ptr[0]->hp = p_ptr[0]->mhp;
      p_ptr[0]->mp = p_ptr[0]->mmp;
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
  p_ptr[0]->getItem (itm);
  item_c itm2 ("★アイスごと投げられる", 1, item_c::TV_ARM, 1, 2);
  p_ptr[1]->getItem (itm2);
	item_c itm3 ("★★★『本場のファイト』", 1, item_c::TV_ARM, 1, 3);
	m_ptr[0]->getItem (itm3);
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
  p_ptr[0] = new psn_c (u[0]);
  p_ptr[1] = new psn_c (u[1]);
  m_ptr[0] = new psn_c (u[2]);
  m_ptr[1] = new psn_c (u[3]);
  itemGetRand ();
  move (2, 2);
  set_color (15);
  printpsn_at (1, 17, *p_ptr[0]);
  printpsn_at (1, 19, *p_ptr[1]);
  DEBUGMSG ();
  batoru (p_ptr, m_ptr);
  p_ptr[0]->hp = (rn (5) + 10);
  tOK ("......");
  tOK ("きみは公園のようなところで目を覚ました。");
  walkStreet ();
  while (1)
  {
    if (dg_moveto ())
      break;;
  }
  addmsg ("きみは街を歩いている。");
  addmsg ("街路樹は寒そうだ。");
  talkYN ("きみは今、寒いだろうか？");
  tOK ("なるほど。じゃあな。");
  delete (p_ptr[0]);
  delete (p_ptr[1]);
  delete (m_ptr[0]);
  delete (m_ptr[1]);
}
