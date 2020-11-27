// datianlong-zhi.c 大天龙指

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N一指点出，这一招「鲤贯龙门」中宫直进，指气将$n压得揣不过气来",
        "force" : 90,
        "dodge" : 5,
        "damage": 15,
        "lvl"   : 0,
        "weapon"      : "无形指气",
        "damage_type" : "刺伤",
        "skill_name"  : "鲤贯龙门"
]),
([      "action": "$N身形不动，一招「盘龙踞虎」攻出。$n稍一犹豫，$N的中指已刺向自己",
        "force" : 140,
        "attack": 5,
        "parry" : 5,
        "dodge" : 5,
        "damage": 20,
        "lvl"   : 40,
        "weapon"      : "右手中指",
        "damage_type" : "刺伤",
        "skill_name"  : "盘龙踞虎"
]),
([      "action": "只见$N一转身，正是一式「云龙三现」，一指由胁下穿出，疾刺$n的$l",
        "force" : 155,
        "attack": 10,
        "parry" : 7,
        "dodge" : 5,
        "damage": 30,
        "lvl"   : 40,
        "weapon"      : "左手中指",
        "damage_type" : "刺伤",
        "skill_name"  : "云龙三现"
]),
([      "action": "只见$N一招「龙腾四海」，十指如穿花蝴蝶一般上下翻飞，全全笼罩$n",   
        "force" : 170,
        "attack": 20,
        "parry" : 11,
        "dodge" : 9,
        "damage": 40,
        "lvl"   : 60,
        "damage_type" : "点穴",
        "skill_name"  : "龙腾四海"
]),
([      "action": "只见$N面带微笑，负手而立，一招「域外天蛟」，$n顿觉一道指力直扑而来",
        "force" : 190,
        "attack": 30,
        "parry" : 12,
        "dodge" : 10,
        "damage": 50,
        "lvl"   : 80,
        "weapon"      : "无形指气",
        "damage_type" : "刺伤",
        "skill_name"  : "域外天蛟"
]),
([      "action": "忽听$N一声轻叱，一招「天龙神威」，左手划了个半弧，食指闪电般点向$n",
        "force" : 250,
        "attack": 40,
        "parry" : 23,
        "dodge" : 25,
        "damage": 57,
        "lvl"   : 100,
        "weapon"      : "右手食指",
        "damage_type" : "刺伤",
        "skill_name"  : "天龙神威"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已将这种指法融入参合指，不必再分开练习了。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练大天龙指必须空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，无法学大天龙指。\n");

        if ((int)me->query_skill("finger", 1) < 80)
                return notify_fail("你的基本指法火候不够，无法学大天龙指。\n");

        if ((int)me->query("max_neili") < 1200)
                return notify_fail("你的内力太弱，无法练大天龙指。\n");

        if (me->query_skill("finger", 1) < me->query_skill("datianlong-zhi", 1))
                return notify_fail("你的基本指法太差，无法领会更高深的大天龙指。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("datianlong-zhi", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已将这种指法融入参合指，不必再分开练习了。\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力太低了，无法练大天龙指。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够，无法练大天龙指。\n");

        me->receive_damage("qi", 55);
        me->add("neili", -51);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"datianlong-zhi/" + action;
}
