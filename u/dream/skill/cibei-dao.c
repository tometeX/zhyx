// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// cibei-dao.c 慈悲刀

inherit SHAOLIN_SKILL;

string *action_msg = ({
        "$N手中$w斜指，一招「停车问路」，反身一顿，一刀向$n的$l撩去",
        "$N一招「童子挂画」，左右腿虚点，$w一提一收，平刃挥向$n的颈部",
        "$N展身虚步，提腰跃落，一招「推窗望月」，刀锋一卷，拦腰斩向$n",
        "$N一招「开门见山」，$w大开大阖，自上而下划出一个大弧，笔直劈向$n",
        "$N手中$w一沉，一招「临溪观鱼」，双手持刃拦腰反切，砍向$n的胸口",
        "$N挥舞$w，使出一招「张弓望的」，上劈下撩，左挡右开，齐齐罩向$n",
        "$N一招「风送轻舟」，左脚跃步落地，$w顺势往前，挟风声劈向$n的$l",
        "$N盘身驻地，一招「川流不息」，挥出一片流光般的刀影，向$n的全身涌去",
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_combine(string combo) { return combo == "fumo-jian"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的内功火候不够。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("cibei-dao", 1))
                return notify_fail("你的基本刀法水平有限，无法领会更高深的慈悲刀法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 90 + random(40), 
                "attack": 40 + random(10),
                "dodge" : 40 + random(10),
                "parry" : 40 + random(10),
                "damage_type": random(2) ? "挫伤" : "割伤", 
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力不够练慈悲刀。\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("你的内力不够。\n");

        if( (int)me->query_skill("luohan-quan", 1) < 30 )
                return notify_fail("你的罗汉拳修为还不够。\n");

        me->receive_damage("qi", 40);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action) 
{
        return __DIR__"cibei-dao/" + action; 
}
