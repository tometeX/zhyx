// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// cuixin-zhang.c 摧心掌

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N攸地变爪为掌，身形不动，右臂陡长，「忽」的一掌朝$n$l劈去",
        "$N乘势疾上，双臂直上直下，飘忽不定。跟着大喝一声，双掌同时推出",
        "$N双掌不住地舞动，只听「喀喇」一声轻响，右掌一立，左掌已向$n$l击去",
        "$N身形挫动，风声虎虎，接着朝$n连发数掌，一掌快似一掌，一掌猛似一掌",
        "$N一声长啸，形如飘风，左掌已如风行电挚般拍出，掌未到，风先至，迅猛已极",
});

int valid_enable(string usage) { return usage == "strike" || usage=="parry"; }

int valid_combine(string combo) { return combo=="jiuyin-baiguzhao"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练摧心掌必须空手。\n");
                
        if ((int)me->query("max_neili") < 500)
                return notify_fail("你的内力太弱，无法练摧心掌。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(90), 
                "attack": 60 + random(10), 
                "dodge" : 60 + random(10), 
                "parry" : 60 + random(10), 
                "damage_type" : random(2)?"瘀伤":"内伤", 
        ]); 
}

int practice_skill(object me)
{
        return notify_fail("没有九阴真经，不能自行领悟或修炼摧心掌。\n");
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (me->query_temp("weapon"))
                return 0;

        lvl = me->query_skill("cuixin-zhang", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

string perform_action_file(string action)
{
        return __DIR__"cuixin-zhang/" + action;
}
