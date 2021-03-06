#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action":"$N力聚双臂，拳上白虎之气闪现，击打向$l" ]),
});
mapping query_action(object me, object weapon)
{
        return action[0];
}

string main_skill() { return "sixiang-shengong"; }

int valid_learn(object me)
{
        object ob;
  
        if ((int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你已将这种劲力融入四象神功，不必再分开练习了。\n");
        
        if (me->query("str") < 30)
                return notify_fail("你的先天力量不足，无法爆发出白虎劲。\n");

        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("你的暗器技能不够娴熟。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("baihu-jing", 1))
                return notify_fail("你的基本暗器水平有限，难以体会更精妙的白虎劲。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("baihu-jing", 1))
                return notify_fail("你的基本拳脚水平有限，难以爆发更强劲的白虎劲。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "throwing";
}

int practice_skill(object me)
{
        return notify_fail("白虎劲只能通过参悟白虎卷和实战来提高。\n");
}

string perform_action_file(string action)
{
        return __DIR__"baihu-jing/" + action;
}
