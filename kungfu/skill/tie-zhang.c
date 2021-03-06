#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N右掌一拂而起，施出「推窗望月」自侧面连消带打，登时将$n力道带斜",
        "force"  : 200,
        "attack" : 100,
        "dodge"  : 50,
        "parry"  : 50,
        "damage" : 70,
        "lvl"    : 0,
        "skill_name" : "推窗望月",
        "damage_type": "瘀伤"
]),
([      "action": "$N施出「分水擒龙」，左掌陡然沿着伸长的右臂一削而出，斩向$n的$l",
        "force"  : 230,
        "attack" : 110,
        "dodge"  : 60,
        "parry"  : 60,
        "damage" : 75,
        "lvl"    : 40,
        "skill_name" : "推窗望月",
        "damage_type": "瘀伤"
]),
([      "action": "$N一招「白云幻舞」，双臂如旋风一般一阵狂舞，刮起一阵旋转的气浪",
        "force"  : 260,
        "attack" : 120,
        "dodge"  : 70,
        "parry"  : 70,
        "damage" : 80,
        "lvl"    : 80,
        "skill_name" : "推窗望月",
        "damage_type": "瘀伤"
]),
([      "action": "$N陡然一招「掌内乾坤」，侧过身来，右臂自左肋下翻出，直拍向$n而去",
        "force"  : 290,
        "attack" : 130,
        "dodge"  : 80,
        "parry"  : 80,
        "damage" : 85,
        "lvl"    : 120,
        "skill_name" : "掌内乾坤",
        "damage_type": "瘀伤"
]),
([      "action": "$N一招「落日赶月」，伸掌一拍一收，顿时一股阴柔无比的力道向$n迸去",
        "force"  : 320,
        "attack" : 140,
        "dodge"  : 90,
        "parry"  : 90,
        "damage" : 90,
        "lvl"    : 160,
        "skill_name" : "落日赶月",
        "damage_type": "瘀伤"
]),
([      "action": "$N身行暴起，一式「蛰雷为动」，双掌横横向$n切出，呜呜呼啸之声狂作",
        "force"  : 350,
        "attack" : 150,
        "dodge"  : 67,
        "parry"  : 90,
        "damage" : 95,
        "lvl"    : 180,
        "skill_name" : "蛰雷为动",
        "damage_type": "瘀伤"
]),
([      "action": "$N一招「天罗地网」，左掌大圈而出，右掌小圈而发，两股力道同时击向$n",
        "force"  : 380,
        "attack" : 160,
        "dodge"  : 100,
        "parry"  : 100,
        "damage" : 100,
        "lvl"    : 200,
        "skill_name" : "天罗地网",
        "damage_type": "瘀伤"
]),
([      "action": "$N施一招「五指幻山」，单掌有如推门，另一掌却是迅疾无比的一推即收",
        "force"  : 410,
        "attack" : 170,
        "dodge"  : 110,
        "parry"  : 110,
        "damage" : 105,
        "lvl"    : 220,
        "skill_name" : "五指幻山",
        "damage_type": "瘀伤"
]),
([      "action": "$N突然大吼一声，一招「铁掌神威」，身行疾飞而起，再猛向$n直扑而下",
        "force"  : 440,
        "attack" : 180,
        "dodge"  : 110,
        "parry"  : 110,
        "damage" : 110,
        "lvl"    : 240,
        "skill_name" : "铁掌神威",
        "damage_type": "瘀伤"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练铁掌掌法必须空手。\n");

        if (me->query("str") < 32)
                return notify_fail("你的先天臂力孱弱，难以修炼铁掌掌法。\n");

        if (me->query("con") < 32)
                return notify_fail("你的先天根骨孱弱，难以修炼铁掌掌法。\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("你的内力修为太弱，难以修炼铁掌掌法。\n");

        if ((int)me->query_skill("force") < 230)
                return notify_fail("你的内功火候不足，难以修炼铁掌掌法。\n");

        if ((int)me->query_skill("strike", 1) < 150)
                return notify_fail("你的基本掌法火候不够，难以修炼铁掌掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tie-zhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的铁掌掌法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
            if (level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("tie-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 50, level)];
}

int practice_skill(object me)
{
        int cost;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练铁掌掌法必须空手。\n");

        if ((int)me->query("qi") < 150)
                return notify_fail("你的体力太低了。\n");

        cost = me->query_skill("tie-zhang", 1) / 5 + 80;

        if ((int)me->query("neili") < cost)
                return notify_fail("你的内力不够练铁掌掌法。\n");

        me->receive_damage("qi", 120);
        me->add("neili", -cost);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("tie-zhang", 1);

        if (damage_bonus < 120 || lvl < 150)
                return 0;

        if (damage_bonus / 5 > victim->query_con()
            && random(2) == 1)
        {
                victim->receive_wound("qi", (damage_bonus - 75) / 3, me);

                return random(2) ? HIR "只听$n" HIR "前胸「咔嚓」一声脆响，竟像是"
                                   "肋骨断折的声音。\n" NOR:

                                   HIR "$n" HIR "一声惨叫，胸前「咔嚓咔嚓」几声脆"
                                   "响，口中鲜血狂喷。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"tie-zhang/" + action;
}
