// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// duanjia-jian.c 段家剑

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N左手捏了个剑诀，右手$w平平递出，一式「"HIY"其利断金"NOR"」直刺$n的前胸",
        "$N纵身向前，$w从一个想不到的角度突然弹出，一式「"HIG"碧鸡报晓"NOR"」直刺$n的左肋",
        "$N一招「"HIY"金马腾空"NOR"」，身形跃在半空，$w横削而出?，直向$n的头部",
        "$N剑身斜挥，剑尖指向$n的腹部，一招「"HIG"碧渊腾蛟"NOR"」，自下而上，剖向$n",
        "$N双脚离地，斜飞而出，$w射向$n的$l,好一招「"HIG"笑指天南"NOR"」",
        "$N长啸一声，横剑轻挥隐隐透出王道之意，正是段家不传之秘「"HIY"逐鹿中原"NOR"」，剑风罩住$n的全身",
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("kurong-changong", 1) < 20)
                return notify_fail("你的枯荣禅功火候太浅。\n");
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
                "damage_type" : random(2)?"刺伤":"割伤",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力不够练段家剑法。\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够。\n");
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"duanjia-jian/" + action;
}

