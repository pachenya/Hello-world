//
// vanee.h
//

#ifndef __VANEE_H_INC__
#define __VANEE_H_INC__

#include "in.h"

class item_c
{
public:
  std::string iname;
private:
  int stackable;
public:
  enum
  {
    TV_NONE,
    TV_FOOD,
    TV_WEAP,
    TV_ARM,
    TV_SPECIAL,
    TV_USE,
    N_TV_ITEMS,
  };
  int tval, sval;
  int nitems;

  bool is_stackable (item_c b);
    item_c & operator = (const item_c & r);
    item_c (std::string s, int sta, int tval, int sval, int nitems);
    item_c ();
};

typedef struct psnd_t_def
{
  std::string name;
  int level, expe;
  int hp, mmp, msta;
  int dgold;
  int Str, Dex, Int, Chr;
} psnd_t;

class skill_c
{
public:
  std::string sname;
  int opened;
  int rank;
  int next_skill;
};

class psn_c
{
public:
  std::string name;
  int hp, mhp, mp, mmp;
  int sta, msta;
  int gold;
  int level, expe;
  int stStr, stDex, stInt, stChr;
  enum
  {
    SK_FIG,                     // == 0
    SK_STG,
    SK_MAGIC,
    SK_PRAYER,
    N_SKILLS,
  };
  enum
  {
    SKILLMAX = 20,
  };
  skill_c skills[N_SKILLS];
  enum
  {
    N_BAG = 20,
  };
  item_c items[N_BAG];
  int itemnum;
    psn_c ();
    psn_c (psnd_t ini);
  int gsr (int skn);            // get_skill_rank();
  int getItem (item_c itm);
    psn_c & operator = (const psn_c & r);
};

class GameVanee
{
private:
  psn_c * p_ptr;
  psn_c *p_ptr2;
  enum
  {
    MSGMAX = 22,
    ENEMAX = 32,
  };
  psn_c enem[ENEMAX];
	enum {
					FL_ST,
					FL_OKKKI,
					FL_KN_SAIZE,
				  N_FLGS,
	};
	int flgs[N_FLGS];
  int dungrealm;
  int dunglevel;
  lstc selel;
  std::list < std::string > msgs;
  void printpsn (psn_c * o);
  void printpsn_at (int x, int y, psn_c & o);
  int gainer_expe (psn_c atk, psn_c def);
  void itemGetRand ();
  void printmsgs ();
  void addmsg (std::string s);
  void tOK (std::string s);
  int talkYN (std::string s);
  void walkStreet ();
	int dg_moveto();
public:
  void do_game ();
    GameVanee ()
  {
    dunglevel = 0;
  }
};

#endif //  __VANEE_H_INC_


