// china-aojue.c 中华傲诀 
// 天煞孤星专用技能
// 可激发为剑法，掌法，招架，轻功和内功。

#include <ansi.h>

inherit FORCE;

string *parry_msg = ({
        "$n身形稳如泰山，轻呼一声，把$N震到一边。\n",
        "$n身形微微一抖，立时将$N迫退几步。\n",
        "$n沉腰立马，$N竟然无法进击，只能勉强自保。\n",
        "$n轻轻一格，将$N的进攻招数全部封死。\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("china-aojue", 1);
        return lvl * lvl * 24 * 15 / 100 / 200;
}



mapping *actionf = ({
([      "action":"$N五指合掌，一股气流自掌间涌出，一掌拍向$n$l",
        "force" : 510,
        "attack": 190,
        "dodge" : 100,
        "parry" : 90,
        "damage": 180,
        "weapon": HIW "中华傲气" NOR,
        "damage_type":  "震伤"
]),
([      "action":"$N双掌齐发，幻化出无数道掌印，齐齐拍向$n的$l",
        "force" : 510,
        "attack": 185,
        "dodge" : 90,
        "parry" : 120,
        "damage": 175,
        "weapon": HIW "中华傲气" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N身形一转，单掌以迅雷不及掩耳之势挥出，击向$n",
        "force" : 530,
        "attack": 175,
        "dodge" : 90,
        "parry" : 110,
        "damage": 200,
        "weapon": HIW "中华傲气" NOR,
        "damage_type":  "刺伤"
]),
([      "action":"$N气沉丹田，一掌缓缓拍向$n的$l，动作虽缓却势不可挡",
        "force" : 525,
        "attack": 185,
        "dodge" : 85,
        "parry" : 115,
        "damage": 185,
        "weapon": HIW "中华傲气" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N身形微晃，双掌凌空劈出，直奔$n的$l处",
        "force" : 530,
        "attack": 165,
        "dodge" : 90,
        "parry" : 115,
        "damage": 200,
        "weapon": HIW "中华傲气" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N双手合掌，微聚真力于掌中，数道掌风已袭向$n的$l",
        "force" : 540,
        "attack": 200,
        "dodge" : 115,
        "parry" : 120,
        "damage": 280,
        "weapon": HIW "中华傲气" NOR,
        "damage_type":  "刺伤"
]),
});

mapping *actionw = ({
([      "action" : "$N攻势忽然加速，手中$w宛如一条赤龙，向$n直奔而去",
        "force" : 470,
        "attack": 180,
        "dodge" : 75,
        "parry" : 115,
        "damage": 225,
        "damage_type": "割伤"
]),
([      "action":"$N手中的$w突似生了眼睛一般，向$n横扫而去$n",
        "force" : 450,
        "attack": 160,
        "dodge" : 85,
        "parry" : 125,
        "damage": 210,
        "damage_type": "擦伤"
]),
([      "action":"$N提起手中的$w，对着$n面门疾刺，毫无章法可言",
        "force" : 460,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 205,
        "damage_type": "刺伤"
]),
([      "action":"$N运用$w幻化做一个一个圆圈，似乎要将$n团团包围",
        "force" : 525,
        "attack": 160,
        "dodge" : 65,
        "parry" : 125,
        "damage": 190,
        "damage_type": "内伤"
]),
([      "action":"$N目光呆滞，面露孤寂之色，回转手中$w，缓缓点向$n的$l",
        "force" : 540,
        "attack": 180,
        "dodge" : 70,
        "parry" : 120,
        "damage": 260,
        "damage_type": "刺伤"
]),
});

int get_ready(object me)
{
        return 1;
}

string *usage_skills = ({ "sword", "strike", "dodge", "parry", "force" });
string *usage_skills2 = ({ "sword", "strike", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}


int valid_force(string force)
{
        return 1;
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("china-aojue", 1);
        if (lvl < 150) return 0;
        if (lvl < 200) return 50;
        if (lvl < 250) return 60;
        if (lvl < 300) return 70;
        if (lvl < 350) return 80;
        if (lvl < 400) return 90;
        return 100;
}

int valid_learn(object me)
{
        int level;
        int i;
     
        level = me->query_skill("china-aojue", 1);

        if ( ! me->query("special_skill/lonely"))
                return notify_fail("你不是天煞孤星，无法修习中华傲诀。\n");

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你的武学修养不够，无法继续领会更高深的中华傲诀。\n");

        for (i = 0; i < sizeof(usage_skills2); i++)
                if (me->query_skill(usage_skills2[i], 1) < level)
                        return notify_fail("你对" + to_chinese(usage_skills2[i]) +
                                           "的理解还不够，无法继续领会更高深的中华傲诀。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("中华傲诀博大精深，无法简单的通过练习进步。\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("china-aojue", 1) < 150 ||
            ! living(me) || (int)me->query("neili") < 150 ||
            me->query_skill_mapped("parry") != "china-aojue")
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("china-aojue", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "默运中华傲诀，护住全身。$N" HIR
                                            "一招击向$n" HIR "前胸，只觉落手处似乎碰到一团"
                                            "棉花，毫无出力之处。 \n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "一招攻出，$n" HIR "怒喝一声，不退"
                                            "反进，竟将$N" HIR "这招逼回。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "$n" HIR "全身不现一处破绽，将$N" HIR "所"
                                            "有进攻招式尽数封死。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIW "$n" HIW "默运中华傲诀，护住全身。但是$N" HIW
                                 "招数精奇，突然变化，一招竟结实地打在$n" HIW
                                 "胸口。\n" NOR;
                        break;
                case 1:
                        result = HIW "$n" HIW "不退反进，试图将$N" HIW "的招式逼回。但是"
                                 "$N" HIW "突然猛提真力，$n" HIW "猝不及防，已然中招。\n" NOR;
                        break;

                default:
                        result = HIW "$n" HIW "全身不现一处破绽，欲将$N" HIW "的进攻"
                                 "招式尽数封死。但是$N" HIW "内力深厚，真气迸出，$N" HIW
                                 "已被其内力击中。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}


mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        if (me->query_temp("weapon"))return 1;

        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || damage_bonus < 120
           || me->query("neili") < 200
           || me->query_skill("china-aojue", 1) < 250)
        	return 0;


        if (damage_bonus / 4 > victim->query_con())
        {
                me->add("neili", -100);
                victim->receive_wound("qi", (damage_bonus - 88) / 2, me);
                victim->add("neili", -((damage_bonus - random(80)) / 2), me);

                return random(2) ? HIR "$N" HIR "出招突然加快，双掌猛然间拍向$n" HIR "丹田。\n" NOR:
                                   HIR "$N" HIR "疾进数步，全身真力贯于掌间，猛地拍向$n" 
                                   HIR "胸口大穴！\n" NOR;
        }        
}

int difficult_level()
{
        return 1600;
}

string perform_action_file(string action)
{
        return __DIR__"china-aojue/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"china-aojue/exert/" + action;
}
