// never-defeated.c 不败神功
//updated by kasumi
//updated by xiner 2009-07-30 强化平招攻击效果，威力比9j无招略高

#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("never-defeated", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *action_default = ({
([      "action" : "$N攻势忽缓而不疏，似剑法又似刀法，捉摸不定向$n慢慢推去",
        "force" : 450,
        "attack": 180,
        "dodge" : 180,
        "parry" : 180,
        "damage": 250,
        "damage_type":  "震伤"
]),
([      "action":"$N手中的$w突焕气象森严，便似千军万马奔驰而来，横扫$n",
        "force" : 460,
        "attack": 180,
        "dodge" : 190,
        "parry" : 180,
        "damage": 250,
        "damage_type":  "擦伤"
]),
([      "action":"$N举起手中的$w，对着$n乱砍乱砸，没有半点章法",
        "force" : 470,
        "attack": 190,
        "dodge" : 200,
        "parry" : 190,
        "damage": 250,
        "damage_type":  "割伤"
]),
([      "action":"$N运用$w幻化做一个一个圆圈，似乎要将$n包围",
        "force" : 480,
        "attack": 190,
        "dodge" : 210,
        "parry" : 190,
        "damage": 260,
        "damage_type":  "内伤"
]),
([      "action":"$N含笑回转$w，伸手一指，颇得拈花指之意，点向$n的$l",
        "force" : 490,
        "attack": 200,
        "dodge" : 220,
        "parry" : 190,
        "damage": 250,
        "damage_type":  "刺伤"
]),
([      "action":"$N长叹一声，将$w随手递出，连自己也不知道也攻向哪里",
        "force" : 500,
        "attack": 200,
        "dodge" : 180,
        "parry" : 180,
        "damage": 250,
        "damage_type":  "割伤"
]),
([      "action":"$N神色凝重，$w上劈下切左右横扫，挟雷霆万钧之势逼往$n",
        "force" : 510,
        "attack": 210,
        "dodge" : 190,
        "parry" : 190,
        "damage": 260,
        "damage_type":  "内伤"
]),
([      "action":"$N运起$w，就如狂风暴雨，霍霍亮光中反攻$n的$l，尝试逼$n自守",
        "force" : 520,
        "attack": 220,
        "dodge" : 250,
        "parry" : 190,
        "damage": 270,
        "damage_type":  "内伤"
]),
([      "action":"$N突然如痴如狂，手中的$w猛然向$n周身乱刺乱削",
        "force" : 530,
        "attack": 250,
        "dodge" : 260,
        "parry" : 200,
        "damage": 280,
        "damage_type":  "割伤"
]),
([      "action":"$N将$w随手一摆，$n反而自己向$w撞将上来，神兵之威，实人所难测",
        "force" : 540,
        "attack": 250,
        "dodge" : 170,
        "parry" : 210,
        "damage": 300,
        "damage_type":  "瘀伤"
]),
([      "action":"$N手中的$w忽起剑势，却似或刀法，又夹杂棍杖之意，令$n眩目",
        "force" : 550,
        "attack": 260,
        "dodge" : 250,
        "parry" : 280,
        "damage": 300,
        "damage_type":  "刺伤"
]),
});

mapping *action_whip = ({
([      "action" : "$N攻势忽缓而不疏，$w变化无常，捉摸不定向$n慢慢卷去",
        "force" : 480,
        "attack": 180,
        "dodge" : 75,
        "parry" : 215,
        "damage": 225,
        "damage_type": "擦伤"
]),
([      "action":"$N手中的$w突焕气象森严，便似千军万马奔驰而来，$w就如棍棒一般横扫$n",
        "force" : 450,
        "attack": 190,
        "dodge" : 85,
        "parry" : 225,
        "damage": 210,
        "damage_type": "擦伤"
]),
([      "action":"$N卷起手中的$w，就如铁锤一般对着$n乱砍乱砸，没有半点章法",
        "force" : 480,
        "attack": 195,
        "dodge" : 180,
        "parry" : 125,
        "damage": 205,
        "damage_type": "割伤"
]),
([      "action":"$N运用$w幻化做一个一个圆圈，似乎要将$n团团包围",
        "force" : 465,
        "attack": 190,
        "dodge" : 165,
        "parry" : 125,
        "damage": 290,
        "damage_type": "内伤"
]),
([      "action":"$N含笑回转$w，伸手一指，颇得拈花指之意，点向$n的$l",
        "force" : 510,
        "attack": 210,
        "dodge" : 180,
        "parry" : 120,
        "damage": 200,
        "damage_type": "刺伤"
]),
});

string *usage_skills = ({ "sword", "blade", "dagger",
                          "staff", "hammer", "club", "whip",  
                          "parry", "force", "throwing" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
        return combo == "never-defeated";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        switch (weapon ? weapon->query("skill_type") : "default")
        {
        case "whip":
                return action_whip[random(sizeof(action_whip))];
        default:
                return action_default[random(sizeof(action_default))];
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp;
        object m_weapon;

        if ((int) me->query_skill("never-defeated", 1) < 120
           || ! (m_weapon = me->query_temp("weapon"))
           || ! living(me) 
           )
                return;
        
        ap = ob->query_skill("parry");
        dp = me->query_skill("parry", 1) / 2 + me->query_skill("never-defeated", 1);       
             if (ap / 2 + random(ap) < dp)
             {
                        result = ([ "damage": -damage ]);
                        result += (["msg" : HIG "$n" HIG "不理会$N" HIG "的攻势，"
                                    "随意挥出一招，反攻向$N" HIG "。\n" NOR]);            
                        ob->start_busy(2);
             }             
             return result;
             
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (! objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("never-defeated", 1);
        if (lvl < 200) return 10;
        if (lvl < 400) return 60;
        if (lvl < 600) return 90;
        return 120;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{	
	object weapon;
	if (damage_bonus > 150 && objectp(weapon = me->query_temp("weapon")) && random(8) > 0)
        {
		me->add("neili", -30);			    
		victim->receive_wound("qi", (damage_bonus - 100) / 2, me);          
                return random(2) ? HIM "$N" HIM "默运内劲在" NOR + weapon->name() + HIM "上攻出一招，霎时间只见气劲层层叠叠如波浪般汹涌而起杀向$n" HIM "！\n" NOR:
				   HIW "但见$N" HIW "凝神聚气，运转手中" NOR + weapon->name() + HIW"，刹那间犹如狂风骤起，气劲猛地卷向$n" HIW "！\n" NOR;
        }     
}


int valid_learn(object me)
{
        int level;
        int i;
	int lvl1, lvl2, lvl3;

        if ((int)me->query("combat_exp") < 3000000)
                return notify_fail("你觉得不败神功深奥之极，"
                                   "凭自己的战斗经验一时间难以领会。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("你觉得不败神功过于深奥，以"
                                   "自己的武学修养全然无法明白。\n");

        if (me->query("character") != "狡黠多变")
                return notify_fail("你学了半天，发现不败神功古怪的"
                                   "紧，不合常理，根本无法领会。");

        if (me->query("int") < 39)
                return notify_fail("你觉得不败神功过于深奥，绝"
                                   "非自己的智力所能理解。\n");

	if (me->query("gender") == "无性" &&
	    (int)me->query_skill("never-defeated", 1) > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的不败神功。\n");

        level = me->query_skill("never-defeated", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你觉得自己的武学修养有限，难以领会更高深的不败神功。\n");

        if (me->query_skill("force", 1) < level)
                return notify_fail("你对基本内功的理解还不够，无法继续"
                                   "领会更高深的不败神功。\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("你对基本招架的理解还不够，无法继续"
                                   "领会更高深的不败神功。\n");   

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("不败神功博大精深，无法简单的通过练习进步。\n");
}

int difficult_level()
{
	object me;
	int lvl1, lvl2, lvl3;
	if(me = this_player())
	{
		lvl1 = (int)me->query_skill("never-defeated", 1);
		lvl2 = (int)me->query_skill("dugu-jiujian", 1);
		lvl3 = (int)me->query_skill("xuantie-jian", 1);
		if (lvl1 > lvl2 && lvl1 < lvl3)
			return 700;
		else
			return 800;
	}
	return 1100;
}

string perform_action_file(string action)
{
        return __DIR__"never-defeated/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"never-defeated/exert/" + action;
}


