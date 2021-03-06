// yingxian-bu.c 萦仙步
// By Alf, Last Update 2001.10

// 白锦无纹香烂漫　玉树琼苞堆雪　烂银霞照通彻　冷浸溶溶月
// 万蕊参差谁信道　洞天方看清绝　不与群芳同列　意气殊高洁

inherit SKILL;

mapping *action = ({
([    "action" : "$n足尖发力，一式「白锦无纹香烂漫」，身形后荡而起，轻轻掠向一旁。\n",
    "dodge"  : 10
]),
([    "action" : "$n双脚连点，一式「玉树琼苞堆雪」，全身化为一道白影，急速旋转不休。\n",
    "dodge"  : 20
]),
([    "action" : "$n劲拔腰背，力贯双足，一式「烂银霞照通彻」，身形凭空弹地而起。\n",
    "dodge"  : 30
]),
([    "action" : "$n双足交错，脚尖脚跟相靠，一式「冷浸溶溶月」，如行云流水般滑出丈余。\n",
    "dodge"  : 40
]),
([    "action" : "$n身形连晃，一式「万蕊参差谁信道」，$N只觉眼前一花，不见了$n的身影。\n",
    "dodge"  : 50
]),
([    "action" : "$n身形倒掠，一式「洞天方看清绝」，凌空两个翻转，退出两丈开外。\n",
    "dodge"  : 60
]),
([    "action" : "$n息气上升，意存玉枕，一式「不与群芳同列」，身形飘然而起。\n",
    "dodge"  : 70
]),
([    "action" : "$n全身笔直，一式「意气殊高洁」，拔地而起，在半空中一转，已落至丈许开外。\n",
    "dodge"  : 80
])
});

mapping query_action(object me, object weapon)
{
    int zhaoshu, level;

    zhaoshu = sizeof(action);
    level   = (int) me->query_skill("yingxian-bu",1);

    if (level < 60 )
    zhaoshu--;

    if (level < 50 )
    zhaoshu--;

    if (level < 40 )
    zhaoshu--;

    return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
    return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
    return 1;
}

string query_dodge_msg(string limb)
{
    object me, ob;
    mapping action;

    me = this_player();
    action = query_action(me, ob);

    return action["action"];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 50 )
        return notify_fail("你的体力太差了，不能练萦仙步。\n");
    me->receive_damage("qi", 30);

    return 1;
}


