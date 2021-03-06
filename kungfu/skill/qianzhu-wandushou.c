#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N身形一晃而至，一招「小鬼勾魂」，双掌带着一缕腥风拍向$n的前心",
        "force" : 400,
        "attack": 125,
        "dodge" : 115,
        "parry" : 120,
        "damage": 110,
        "lvl"   : 10,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形化做一缕轻烟绕着$n急转，一招「天网恢恢」，双掌幻出无数掌影罩向$n",
        "force" : 430,
        "attack": 130,
        "dodge" : 110,
        "parry" : 115,
        "damage": 120,
        "lvl"   : 30,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N怪叫一声，一招「阴风怒号」，双掌铺天盖地般拍向$n的$l",
        "force" : 460,
        "attack": 145,
        "dodge" : 120,
        "parry" : 120,
        "damage": 125,
        "lvl"   : 60,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N一照「凄雨冷风」，双掌拍出满天阴风，忽然右掌悄无声息的拍向$n的$l",
        "force" : 480,
        "attack": 150,
        "dodge" : 120,
        "parry" : 130,
        "damage": 130,
        "lvl"   : 80,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N大喝一声，一招「恶鬼推门」，单掌如巨斧开山带着一股腥风猛劈向$n的面门",
        "force" : 510,
        "attack": 165,
        "dodge" : 125,
        "parry" : 120,
        "damage": 135,
        "lvl"   : 100,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N一声冷笑，一招「灵蛇九转」，身形一闪而至，一掌轻轻拍出，手臂宛若无骨，掌到中途竟连\n"
                   "变九变，如鬼魅般印向$n的$l",
        "force" : 520,
        "attack": 195,
        "dodge" : 125,
        "parry" : 125,
        "damage": 145,
        "lvl"   : 120,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N侧身向前，一招「地府阴风」，双掌连环拍出，一缕缕彻骨的寒气从掌心透出，将$n周围的空\n"
                   "气都凝结了",
        "force" : 540,
        "attack": 210,
        "dodge" : 130,
        "parry" : 130,
        "damage": 160,
        "lvl"   : 140,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N厉叫一声，身形忽的蜷缩如球，飞身撞向$n，一招「黄蜂吐刺」单掌如剑，直刺$n的心窝",
        "force" : 560,
        "attack": 235,
        "dodge" : 130,
        "parry" : 135,
        "damage": 175,
        "lvl"   : 160,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N一个急旋，飞身纵起，半空中一式「毒龙摆尾」，反手击向$n的$l",
        "force" : 580,
        "attack": 250,
        "dodge" : 130,
        "parry" : 175,
        "damage": 190,
        "lvl"   : 180,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N大喝一声，运起五毒神功，一招「毒火焚身」，刹那间全身毛发尽绿，一对碧绿的双爪闪电般的朝\n"
                   "$n的$l抓去",
        "force" : 600,
        "attack": 285,
        "dodge" : 140,
        "parry" : 180,
        "damage": 220,
        "lvl"   : 200,
        "damage_type" : "抓伤"
])
});

int valid_enable(string usage)
{
        return usage=="hand" || usage=="parry";
}

int valid_learn(object me)
{

        if (me->query("character") == "光明磊落")
                return notify_fail("你心中暗想：我为人光明磊落，岂能学习这种害人武功？\n");

        if (me->query("character") == "狡黠多变")
                return notify_fail("你心中暗想：哼，这种武功虽然厉害，但对自身损害极大，学来何用？\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练千蛛万毒手必须空手。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，无法练习千蛛万毒手。\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力太弱，无法练习千蛛万毒手。\n");

        if ((int)me->query_skill("hand", 1) < 80)
                return notify_fail("你的基本手法火候不够，无法练千蛛万毒手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("qianzhu-wandushou", 1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的千蛛万毒手。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("qianzhu-wandushou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{	
	if (damage_bonus < 100 || random(3)==1) return 0;		

        if ((damage_bonus / 5 > victim->query_con()) )
        {
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);
                return HIB "$n" HIB "忽然感到一股莫名的恶心，毒气攻心，全身顿时瘫软。\n" NOR;
        }        
}

int practice_skill(object me)
{
	   if (me->query_skill("qianzhu-wandushou", 1) < 180)
        return notify_fail("千蛛万毒手等级不够，只有通过吸取毒虫的毒素练功来提高。\n");
        
        if ((int)me->query("qi") < 100)
                return notify_fail("你的体力太差了，难以练习千蛛万毒手。\n");

        if ((int)me->query("neili") < 120)
                return notify_fail("你的内力不够了，无法练习千蛛万毒手。\n");

        me->receive_damage("qi", 100);
        me->add("neili", -120);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qianzhu-wandushou/" + action;
}
