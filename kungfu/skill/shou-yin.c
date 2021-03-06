// shou-yin.c 手印(徐子陵)

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N使出一招「莲花合掌印」，双掌做锥，直直刺向$n的前胸",
        "force"    : 400,
        "attack"   : 220,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 200,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "刺伤",
]),
([      "action" : "$N使出一招「合掌观音印」，飞身跃起，双手如勾，抓向$n的$l",
        "force"    : 440,
        "attack"   : 240,
        "dodge"    : 140,
        "parry"    : 140,
        "damage"   : 250,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "刺伤",
]),
([      "action" : "$N使出一招「准提佛母印」，运力于指，直取$n的$l",
        "force"    : 480,
        "attack"   : 240,
        "dodge"    : 150,
        "parry"    : 150,
        "damage"   : 280,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "刺伤",
]),
([      "action" : "$N使出一招「红阎婆罗印」，怒吼一声，一掌当头拍向$n的$l",
        "force"    : 520,
        "attack"   : 260,
        "dodge"    : 160,
        "parry"    : 160,
        "damage"   : 300,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "内伤",
]),
([      "action" : "$N使出一招「药师佛根本印」，猛冲向前，掌刀如游龙般砍向$n",
        "force"    : 540,
        "attack"   : 260,
        "dodge"    : 180,
        "parry"    : 180,
        "damage"   : 320,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "割伤",
]),
([      "action" : "$N使出一招「威德金刚印」，伏身疾进，双掌自下扫向$n的$l",
        "force"    : 560,
        "attack"   : 280,
        "dodge"    : 200,
        "parry"    : 200,
        "damage"   : 340,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "割伤",
]),
([      "action" : "$N使出一招「上乐金刚印」，飞身横跃，双掌前后击出，抓向$n的咽"
                   "喉",
        "force"    : 580,
        "attack"   : 290,
        "dodge"    : 210,
        "parry"    : 210,
        "damage"   : 350,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "刺伤",
]),
([      "action" : "$N使出一招「六臂智慧印」，顿时劲气弥漫，天空中出现无数掌影打"
                   "向$n",
        "force"    : 600,
        "attack"   : 300,
        "dodge"    : 220,
        "parry"    : 220,
        "damage"   : 360,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "割伤",
]),
});

int double_attack() { return 1; }

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练手印必须空手。\n");

        if (me->query("str") < 34)
                return notify_fail("你的臂力孱弱，无法练习手印。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你的武学修养太低，无法修习手印。\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("hand", 1) < 200)
                return notify_fail("你的基本手法火候太浅。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("shou-yin",1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的手印。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
                  level   = (int) me->query_skill("shou-yin",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练大手印法必须空手。\n");

        if ((int)me->query("qi") < 800)
                return notify_fail("你的体力不够，练不了手印。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你的内力不够，练不了手印。\n");

        me->receive_damage("qi", 500 + random(200));
        me->add("neili", -500 - random(200));
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 100) return 0;

        if (damage_bonus / 6 > victim->query_str())
        {
                victim->receive_wound("qi", (damage_bonus - 140) / 2);
                return HIR "只听" + victim->name() +
                       HIR "一声闷哼，一双" NOR + HIW "手印"
                       NOR + HIR "重重的印在胸前，“哇”"
                       "的喷出了一大口鲜血！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"shou-yin/" + action;
}

