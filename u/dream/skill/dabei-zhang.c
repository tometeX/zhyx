// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit SKILL;
#include <ansi.h>

string *action_msg = ({
        "$N连续上步，一式「"+YEL+"大慈大悲"+NOR+"」，左右手分靠，变拳为掌，击向$n的$l",
        "$N左脚虚踏，全身右转，一招「"+RED+"悲从心生"+NOR+"」，右掌猛地插向$n的$l",
        "$N使一招「"+HIB+"苦海回头"+NOR+"」，上身前探，双手划了个半圈，击向$n的$l",
        "$N双掌划弧，一记「"+HIY+"回头是岸"+NOR+"」，掌出如电，一下子切到$n的手上",
        "$N施出「"+WHT+"苦海无边"+NOR+"」，双拳拳出如风，同时打向$n头，胸，腹三处要害",
});
int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("学大悲掌必须空手。\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力太弱，无法练大悲掌。\n");
        if (me->query_skill("strike", 1) <= me->query_skill("dabei-zhang", 1))
                return notify_fail("你的基础不够，无法领会更高深的技巧。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force" : 300 + random(30), 
                "attack": 50 + random(10), 
                "dodge" : 50 + random(10), 
                "parry" : 50 + random(10), 
                "damage_type" : random(2)?"瘀伤":"内伤", 
        ]); 
}

int practice_skill(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练大悲掌必须空手。\n");
                
        if ((int)me->query("qi") < 60)
                return notify_fail("你的体力太低了。\n");
                
        if ((int)me->query("neili") < 60)
                return notify_fail("你的内力不够练大悲掌。\n");
                
        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dabei-zhang/" + action;
}

