//paiyun-zhang.c 排云掌
//By dream@rx
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「重云深锁」双掌前后拍出，以极巧妙的手法连续击向$n",
        "force"  : 300,
        "attack" : 220,
        "dodge"  : 100,
        "parry"  : 100,
        "damage" : 150,
        "lvl" : 0,
        "damage_type": "震伤"
]),
([      "action" : "$N一招「云海波涛」双掌大开大合，内力一波接着一波涌向$n",     
        "force"  : 330,
        "attack" : 250,
        "dodge"  : 130,
        "parry"  : 130,
        "damage" : 180,
        "lvl" : 50,
        "damage_type": "震伤"
]),
([      "action" : "$N一招「云莱仙境」，内力经过转化奇异般形成一片雾气罩向$n",
        "force"  : 360,
        "attack" : 280,
        "dodge"  : 160,
        "parry"  : 160,
        "damage" : 210,
        "lvl" : 100,
        "damage_type": "震伤"
]),
([      "action" : "$N神情悲愤，一招「愁云惨淡」以讯雷不及掩耳之势攻向$n",
        "force"  : 390,
        "attack" : 310,
        "dodge"  : 190,
        "parry"  : 190,
        "damage" : 240,
        "lvl" : 100,
        "damage_type": "震伤"
]),
([      "action" : "$N忽然凌空跃起，一招「殃云天降」对着$n当头击去",
        "force"  : 420,
        "attack" : 340,
        "dodge"  : 220,
        "parry"  : 220,
        "damage" : 270,
        "lvl" : 150,
        "damage_type": "震伤"
]),
([      "action" : "$N使出一招「行云流水」，身化无形，围着$n攻个不停",
        "force"  : 450,
        "attack" : 370,
        "dodge"  : 250,
        "parry"  : 250,
        "damage" : 300,
        "lvl" : 200,
        "damage_type": "震伤"
]),
([      "action" : "$N使出「披云带月」，右掌从不可思意的角度劈向$n",
        "force"  : 480,
        "attack" : 400,
        "dodge"  : 280,
        "parry"  : 280,
        "damage" : 330,
        "lvl" : 200,
        "damage_type": "震伤"
]),
([      "action" : "$N迅速窜到$n的面前，一招「乌云蔽日」，注满内力的双掌当头压向$n",
        "force"  : 520,
        "attack" : 430,
        "dodge"  : 310,
        "parry"  : 310,
        "damage" : 360,
        "lvl" : 300,
        "damage_type": "震伤"
]),
([      "action" : HIW"$N使出「撕天排云」，一掌向地，一掌向天，然后双掌向着$n轻轻一推"NOR,
        "force"  : 600,
        "attack" : 500,
        "dodge"  : 350,
        "parry"  : 350,
        "damage" : 400,
        "lvl" : 400, //等级达到400级才能使用此招式
        "damage_type": "内伤" //直接对气血总体值做伤害计算
]),
([      "action" : HIC"$N全身衣襟无风自动，一招「排山倒海」，全身内力如波涛般涌向$n"NOR,
        "force"  : 650,
        "attack" : 550,
        "dodge"  : 400,
        "parry"  : 400,
        "damage" : 450,
        "lvl" : 500, //等级达到500级才能使用此招式
        "damage_type": "内伤"
]),
([      "action" : BLINK HIG"$N一招「翻云覆雨」，双掌仿佛突破了时间和空间的限制，以暗合天理之势击向$n"NOR,  
        "force"  : 700,
        "attack" : 600,
        "dodge"  : 500,
        "parry"  : 500,
        "damage" : 600,
         "lvl" : 600, //等级达到600级才能使用此招式
        "damage_type": "内伤"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}  

int valid_learn(object me)
{

        if ((int)me->query("str") < 30)
                return notify_fail("你的先天膂力孱弱，难以修炼排云掌。\n");

        if ((int)me->query("con") < 30)
                return notify_fail("你的先天根骨孱弱，难以修炼排云掌。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，难以修炼排云掌。\n");

        if ((int)me->query("max_neili") < 3500)
                return notify_fail("你的内力修为不足，难以修炼排云掌。\n");

        if ((int)me->query_skill("strike", 1) < 300)
                return notify_fail("你的基本掌法火候不够，难以修炼排云掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("paiyun-zhang", 1))
                return notify_fail("你的基本掌法水平有限，难以领会更高深的排云掌。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("paiyun-zhang", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 40, level / 8)];
}

int practice_skill(object me)
{
        int cost;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练排云掌必须空手。\n");

        if ((int)me->query("qi") < 500)
                return notify_fail("你的体力太低了。\n");

        cost = me->query_skill("paiyun-zhang", 1) / 5 + 90;

        if ((int)me->query("neili") < cost)
                return notify_fail("你的内力不够练排云掌。\n");

        me->receive_damage("qi", 200);
        me->add("neili", -cost);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("paiyun-zhang", 1);

        if (damage_bonus < 150 || lvl < 150) return 0;

        if (damage_bonus / 6 > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);

                return random(2) ? HIR "只听$n" HIR "一声惨叫，竟是被"
                                   "排云掌的真气透体而过。\n" NOR:

                                   HIR "$n" HIR "面色全白，浑身发颤，排云掌的真气钻入经脉"
                                   "扑的一声，$n口中鲜血狂喷而出。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"paiyun-zhang/" + action;
}

