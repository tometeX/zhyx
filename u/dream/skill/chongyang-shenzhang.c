// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit SKILL;

string *action_msg = ({
        "$N双掌一错，一招「阳关三叠」幻出层层掌影奔向$n的$l",
        "$N暴喝一声，单掌猛然推出，一招「地久天长」强劲的掌风直扑$n的$l",
        "$N双掌纷飞，一招「金龙戏水」直取$n的$l",
        "$N按北斗方位急走，一招「万物复苏」，阵阵掌风无孔不入般地击向$n的$l",
        "$N回身错步，双掌平推，凝神聚气，一招「回光反照」拍向$n的$l",
        "$N左掌立于胸前，右掌推出，一招「神光乍现」迅然击向$n$l",
        "$N使出「百里千长」，身形急进，快速向$n出掌攻击",
        "$N一招「星游九天」，双掌虚虚实实的击向$n的$l",
        "$N左掌画了个圈圈，右掌推出，一招「北斗易位」击向$n$l",
});

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练重阳神掌必须空手。\n");

        if ((int)me->query("max_neili") < 800)
                return notify_fail("你的内力修为不足，无法练重阳神掌。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法练重阳神掌。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法水平有限，无法学重阳神掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chongyang-shenzhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的重阳神掌。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "zhongnan-zhi";
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(50), 
                "attack": 60 + random(10), 
                "dodge" : 60 + random(10), 
                "parry" : 60 + random(10), 
                "damage_type" : random(2)?"瘀伤":"内伤", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力不够了，休息一下再练吧。\n");

        if ((int)me->query("neili") < 65)
                return notify_fail("你的内力不够了，休息一下再练吧。\n");

        me->receive_damage("qi", 60);
        me->add("force", -55);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chongyang-shenzhang/" + action;
}
