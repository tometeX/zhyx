// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit SKILL;

string *action_msg = ({
        "$N以掌化爪，五指如钩，直逼$n的膻中要穴",
        "$N左手虚晃，右手上下直击，反扣$n的肩井大穴",
        "$N掌指齐出，拍拿并施，拿向$n的三路要害",
        "$N左手鹰抓，右手蛇举，疾扣$n的中节大脉",
        "$N上前一步，四面八方出现无数掌影，一爪抓向$n的胸口",
        "$N两手环扣，全身关节啪啪作响，击向$n的$l",
        "$N十指齐伸，遮天蔽日般地笼罩$n的全身要穴",
        "$N岳立霆峙，在一阵暴雷声中，双手同时拍向$n的全身各处",
});

int valid_enable(string usage)
{
        return usage == "hand" || usage == "parry";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练缠丝擒拿手必须空手。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功火候不够，无法学缠丝擒拿手。\n");

        if ((int)me->query("max_neili") < 500)
                return notify_fail("你的内力修为太弱，无法练缠丝擒拿手。\n");

        if ((int)me->query_skill("hand", 1) < 80)
                return notify_fail("你的基本手法不够，无法练缠丝擒拿手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("chansi-shou", 1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的缠丝擒拿手。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage_type": random(2)?"瘀伤":"内伤",
                "dodge" : 50 + random(10),
                "parry" : 50 + random(10),
                "attack": 50 + random(10),
                "force" : 250 + random(60),
        ]);
}

int practice_skill(object me)
{
        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("你必须空手练习！\n");

        if ((int)me->query("qi") < 60)
                return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("你的内力不够练缠丝擒拿手。\n");

        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chansi-shou/" + action;
}

