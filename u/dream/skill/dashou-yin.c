// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// dashou-yin 密宗大手印

inherit SKILL;

string *action_msg = ({
        "$N一式「莲花合掌印」，双手向相，拇指、小指互触，面戴微笑，欺近$n的身前，印向$n的$l",
        "紧接着$N手指交插，拇指向外微分，手结「合掌观音印」，向$n当头切下，势不可挡",
        "$N使一式「准提佛母印」，手指交叉，食指朝天，面作沉思状，突然翻腕结手印拍向$n的$l",
        "$N手结「红阎婆罗印」，三睛怒睁、阔嘴大张、喝一声胜乐咒，左右手一擒一拿，捉向$n的下三路",
        "却见$N双手握拳，食指前伸，鼓足内力，结一式「药师佛根本印」，朝$n的$l擒过去",
        "只听得$N口中念念梵唱，神色庄严地施展「威德金刚印」，双手交叉，拇指相叠，一下扣住$n肩井大穴，抗起$n向後一摔",
        "$N面浮微笑，双手互握，手腕相触，一步抢到$n的身前，一式「上乐金刚印」切住$n后腰，轻轻一推",
        "$N一式「六臂智慧印」，结跏趺坐，口念核心咒，双手一下拿住$n胳膊，左脚顺势一绊",
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_combine(string combo) { return combo == "yujiamu-quan"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练密宗大手印必须空手。\n");

        if ((int)me->query("max_neili") < 350)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("lamaism", 1) < 20)
                return notify_fail("你对密宗心法的知识了解太少，无法理解密宗大手印。\n");

        if ((int)me->query_skill("lamaism", 1) < (int)me->query_skill("dashou-yin",1))
                return notify_fail("你受密宗心法知识的知识所限，难以进一步领悟大手印。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("dashou-yin",1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的密宗大手印。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(120), 
                "attack": 70 + random(10), 
                "dodge" : 70 + random(10), 
                "parry" : 70 + random(10), 
                "damage_type" : random(2)?"内伤":"瘀伤", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 80)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 80)
                return notify_fail("你的内力不够练密宗大手印。\n");
        me->receive_damage("qi", 70);
        me->add("neili", -70);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dashou-yin/" + action;
}

