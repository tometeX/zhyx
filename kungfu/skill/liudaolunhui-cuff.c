// liudaolunhui-cuff.c
// 华夏玩家car的自创武功：六道轮回拳法
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "car";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "天道循环",
        "action":  "$N左手擎天，右手撑地，一招「天道循环」，带出漫天拳影冲向$n$l",
        "dodge" : 80,
        "damage": 180,
        "force" : 330,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "地狱之火",
        "action":  "$N双手交叉横在胸前，「地狱之火」自下而上聚起火影无数把$n完全吞噬掉",
        "dodge" : 90,
        "damage": 190,
        "force" : 340,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "修罗杀戮",
        "action":  "$N历喝一声「修罗杀戮」，好似天降修罗三头六臂砸向$n上身各处",
        "dodge" : 95,
        "damage": 200,
        "force" : 350,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "饿鬼索魂",
        "action":  "$N矮身向前，似守还攻，一招「饿鬼索魂」自不可思议的角度攻向$n",
        "dodge" : 105,
        "damage": 210,
        "force" : 360,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "人间地狱",
        "action":  "$N绕着$n四处游走，一化二，二化四，幻成「人间地狱」自四面八方攻出",
        "dodge" : 110,
        "damage": 220,
        "force" : 370,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "瘀伤"
]),
([      "skill_name":    "孽畜翻生",
        "action":  "$N忽然倒在地上，$n大喜之下一脚踩去，不料$N招出「孽畜翻生」突然跃起，打向$n下身",
        "dodge" : 115,
        "damage": 230,
        "force" : 380,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "瘀伤"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力不够，没有办法练六道轮回拳法。\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("你的武学修养不够，没有办法练六道轮回拳法。\n");

    if( ob = me->query_temp("weapon") )
        return notify_fail("你必须空手才能修炼拳法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="cuff" || usage=="parry";
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
    level   = (int) me->query_skill("liudaolunhui-cuff",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("你的体力不足以练习六道轮回拳法。\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("你的内力不够，没有办法练习六道轮回拳法。\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liudaolunhui-cuff/" + action;
}
