// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// baibian-daxue.c

inherit SKILL;

string *action_msg = ({
        "$N一招「指点江山」，手中$w疾点向$n的期门穴!",
        "$N吐气开声一招「银钩铁划」，$w如灵蛇吞吐，向$n白海穴戳去",
        "$N向前跨上一步，手中$w一晃，正是一招使出「灵蛇吐雾」，疾点$n的地仓穴",
        "$N手中的$w左右急晃，舞成一段光芒，使出「千变万化」带着呼呼风声笼罩了$n的章门穴",
        "$N飞身跃起，一式「千蛇出洞」，卷起漫天笔影，紧紧裹住$n",
        "$N凝气守中，$w逼出阵阵光芒，挥出「灵台观景」，一招快一招地攻向$n",
        "$N使出一招「神蛇引路」挺笔中宫直进，$w忽的颤动，中途忽然转而向上变幻无方",
        "$N侧身手中的$w斜刺，一招「奇采迭出」，刺向$n胸前檀中大穴",
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 150)
                return notify_fail("你的内力不够，没有办法练百变打穴法。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的内功火候不够，还不能学习百变打穴法!\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("baibian-daxue", 1))
                return notify_fail("你的基本杖法水平有限，无法领会更高深的百变打穴杖法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{        
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "dodge" : 50 + random(10),
                "parry" : 50 + random(10),
                "damage": 120 + random(50),
                "attack": 50 + random(10),
                "damage_type": "刺伤",
        ]);
          
}

int practice_skill(object me)
{       object ob;
        if( !(ob = me->query_temp("weapon")) ||
            (string)ob->query("skill_type") != "staff" )
                return notify_fail("你必须先找一根铁杖才能学习百变打穴法。\n");

        if( (int)me->query("qi") < 60)
                return notify_fail("你的气不够，没有办法练习百变打穴法。\n");

        if( (int)me->query("neili") < 60)
                return notify_fail("你的内力不够，没有办法练习百变打穴法。\n");

        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__ "baibian-daxue/" + action;
}

