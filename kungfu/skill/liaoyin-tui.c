inherit SKILL;

mapping *action = ({
([      "action": "只见$N身形一矮，大喝声中一个「海底捞月」对准$n的档部呼！地抓了过去",
        "dodge": 15,
        "parry": 15,
        "attack": 20,
        "force": 120,
        "damage_type":  "抓伤"
]),
([      "action": "$N步履一沉，左拳拉开，右拳带风，一招「仙猴摘桃」势不可挡地击向$n的档部",
        "dodge": 25,
        "parry": 25,
        "attack": 30,
        "force": 140,
        "damage_type":  "抓伤"
]),
([      "action": "只见$N拉开架式，一招「声东击西」使得虎虎有风。底下却飞起一脚踢向$n阴部",
        "dodge": 20,
        "parry": 20,
        "attack": 25,
        "force": 160,
        "damage_type":  "抓伤"
]),
([      "action": "$N一个转身，左掌护胸，右掌使了个「枯树盘根」，从后面往$n屁股一脚踢去",
        "dodge": 30,
        "parry": 30,
        "attack": 40,
        "force": 270,
        "damage_type":  "抓伤"
]),
});

int valid_learn(object me)
{

        if( me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练撩阴腿必须空手。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("liaoyin-tui", 1))
                return notify_fail("你的基本拳脚火候不足，无法领会更高深的撩阴腿。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed" || usage=="parry";
}

string query_skill_name(int lvl)
{
        return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 100 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");

        if( (int)me->query("neili") < 80 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 80);
        me->add("neili", -50);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liaoyin-tui/" + action;
}

