#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w一转，回身一剑，刺向$n$l，正是一招「回剑式」",
        "force"  : 120,
        "dodge"  : 80,
        "parry"  : 70,
        "attack" : 100,
        "damage" : 90,
	"lvl"    : 0,
        "damage_type" : "刺伤",
        "skill_name"  : "回剑式",
]),
([      "action" :  "只见$N身法陡然加快，施展出「拂风式」，剑风荡漾，$w瞬间已至$n$l",
        "force"  : 160,
        "dodge"  : 85,
        "parry"  : 75,
        "attack" : 110,
        "damage" : 100,
	"lvl"    : 25,
        "damage_type" : "刺伤",
        "skill_name"  : "拂风式",
]),
([      "action" : "$N纵身跃起，使出一招「落剑式」，陡见$w从半空直指$N$l",
        "force"  : 200,
        "dodge"  : 90,
        "parry"  : 80,
        "attack" : 120,
        "damage" : 110,
	"lvl"    : 50,
        "damage_type" : "刺伤",
        "skill_name"  : "落剑式",
]),
([      "action" : "$N腾空而起，一招「雁翔式」来势又准又快，手中$w已到$n$l",
        "force"  : 220, 
        "dodge"  : 95,
        "parry"  : 85,
        "attack" : 130,
        "damage" : 120,
	"lvl"    : 75,
        "damage_type" : "刺伤",
        "skill_name"  : "雁翔式",
]),
([      "action" : "$N剑峰忽转，一剑笔直地向$n$l刺来，内劲十足，正是一招「平剑式」",
        "force"  : 240,
        "dodge"  : 100,
        "parry"  : 90,
        "attack" : 140,
        "damage" : 130,
	"lvl"    : 100,
        "damage_type" : "刺伤",
        "skill_name"  : "平剑式",
]),
([      "action" : "$N手中$w猛然回撤，紧接着一剑，气势磅礴，剑气纵横，正是「凝剑式」",
        "force"  : 260,
        "dodge"  : 105,
        "parry"  : 95,
        "attack" : 160,
        "damage" : 140,
	"lvl"    : 120,
        "damage_type" : "刺伤",
        "skill_name"  : "凝剑式",
]),
});

int valid_learn(object me)
{
        object ob;

        if (! (ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword")
                return notify_fail("你必须先找一把剑才能练剑法。\n");

        if ((int)me->query("max_neili") < 800)
                return notify_fail("你的内力修为不够，无法学习回风落雁剑。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候太浅，无法学习回风落雁剑。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法火候不够，无法学习回风落雁剑。\n");

        if (me->query_skill("sword", 1) < me->query_skill("luoyan-jian", 1))
		return notify_fail("你的基本剑法火候有限，无法领会更高深的回风落雁剑。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;

        level = (int) me->query_skill("luoyan-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
       object weapon;

       if (! objectp(weapon = me->query_temp("weapon"))
          || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

       if((int)me->query("neili") < 30 )
        	   return notify_fail("你的内力不足，没有办法练习回风落雁剑。\n");

       if ((int)me->query("qi") < 35)
        	   return notify_fail("你的体力不够练回风落雁剑。\n");

       me->receive_damage("qi", 40);
       me->add("neili", -50);
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoyan-jian/" + action;
}

