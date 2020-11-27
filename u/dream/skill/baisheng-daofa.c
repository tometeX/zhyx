// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit SKILL;

string *action_msg = ({
        "$N手持$w一刀劈下，迅即无比，势不可当",
        "$N刀锋自下而上划了个半弧，$w忽深忽吐，刺向$n的颈部",
        "$N忽然将$w舞得天花乱坠，闪电般压向$n",
        "$N一横$w，刀锋像门板一样向$n推去，封住$n所有的退路",
        "$N转身跃起，手舞$w，身与刀进合做一道电光射向$n",
        "$N挥舞$w，乱砍乱杀，$w化作道道白光，上下翻飞罩向$n",
        "$N将$w使得毫无章法，不守半点规矩，偏生快得出奇，$w挟风声劈向$n的$l",
        "$N大喝一声，手中的$w就如长虹一般向$n直劈而下",
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 600)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("blade", 1) < 60)
                return notify_fail("你的基本刀法火候不够，无法学习百胜刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("baisheng-daofa", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的百胜刀法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(30), 
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2) ? "挫伤" : "割伤", 
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
            || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力不够，练不了百胜刀法。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够，练不了百胜刀法。\n");

        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baisheng-daofa/" + action;
}
