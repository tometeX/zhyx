//天煞剑法              by yuchang@zhyx 2005 11.28
#include <ansi.h> 
inherit SKILL;

mapping *action = ({
([      "action" : "$N狂啸一声，赤剑如狂风暴雨般疾刺向$n攻去",
        "force" : 510,
        "attack": 180,
        "dodge" : 115,
        "parry" : 125,
        "damage": 325,
        "damage_type": "内伤"
]),
([      "action":"$N立刻变招，剑势由刚转柔，以“戮守诀”剑势纠缠,$n被缠得呆滞无劲，逼于要节节后退。",
        "force" : 510,
        "attack": 188,
        "dodge" : 112,
        "parry" : 115,
        "damage": 310,
        "damage_type": "刺伤"
]),
([      "action":"$N当下使出十成功力，一剑划破长空，灌劲向$n后心刺去",
        "force" : 532,
        "attack": 225,
        "dodge" : 120,
        "parry" : 102,
        "damage": 365,
        "damage_type": "刺伤"
]),
([      "action":"$N舞动手中$w，灌注强横内力暴射，访如神龙吐信，跨越千重山峰，气势之猛，震古烁今。剑气直逼$n",
        "force" : 565,
        "attack": 210,
        "dodge" : 115,
        "parry" : 105,
        "damage": 390,
        "damage_type": "内伤"
]),
([      "action":"$N手腕抖动，剑带柔劲，剑势一收一放,劲透$w剑身暴震，疾刺$n下盘",
        "force" : 550,
        "attack": 248,
        "dodge" : 110,
        "parry" : 120,
        "damage": 420,
        "damage_type": "刺伤"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        int i, level;
level = (int) me->query_skill("lonely-jianfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  
        object m_weapon;

if ((int) me->query_skill("lonely-jianfa", 1) < 150 ||
            ! (m_weapon = me->query_temp("weapon")) ||
            ! living(me) || m_weapon->query("skill_type") != "sword")
                return;


        cost = damage / 2;

        if (cost > 100) cost = 100;

        ap = ob->query_skill("force");
        dp = me->query_skill("parry", 1) / 2 +
me->query_skill("lonely-jianfa", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
result += (["msg" : HIY "$n" HIY "面露克煞魔之相，天上的黑云不断聚厚，瞬间已是灰天黑地……"
                                            "，$N" HIY "只觉$n浑身毫无破绽可寻，" HIY 
                                            "一时间根本无从攻击。\n"NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "$N" HIY "一招击中$n" HIY "上身"
"，可却被$n克煞魔相所慑，招式顿显无力\n" NOR]);

                        break;
                default:
                        result += (["msg" : HIR "但见$n" HIR "动作潇洒致极。"
                                            "随手接下了$N" HIR "这一招，却没有受到"
                                            "半点伤害。\n" NOR]);
                        break;
                }
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon = me->query_temp("weapon");

lvl = me->query_skill("lonely-jianfa", 1);


        if (damage_bonus < 150
           || lvl < 140
           || me->query("neili") < 300 )         
      	    return 0;


             if (objectp(weapon) && weapon->query("skill_type") != "sword")                
                         return 0;
           
             if (objectp(weapon) && weapon->query("skill_type") == "sword"
&& me->query_skill_mapped("sword") != "lonely-jianfa")
                         return 0;

        if (random(2) == 1)return 0;

        if (damage_bonus / 5 > victim->query_con())
        {
                me->add("neili", -100);
                victim->receive_wound("qi", (damage_bonus - 76) / 2, me);
                victim->add("neili", -((damage_bonus - random(70)) / 2), me);
         
return random(2) ? HIY "$N" HIY "一剑挥出，顿时黑雾弥漫整个空间,仿佛时间停止在瞬间，"
                                   "尽数射入$n" HIY "体内！\n" NOR:
                                   HIM "$N" HIM "突然连出数剑，$n" HIM "只感全身一"
                                   "震，登时被刺出数个伤口！\n" NOR;
        }
}

int practice_skill(object me)
{
        int cost;
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        
if ( me->query_skill("lonely-jianfa",1) < 200 )
return notify_fail("你对天煞剑法理解不够纯熟，尚不足以自行锻炼。\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 75)
return notify_fail("你的内力不够练天煞剑法。\n");

cost = me->query_skill("lonely-jianfa", 1) / 2 + 250;

        if ((int)me->query("neili") < cost)
return notify_fail("你的内力不够练天煞剑法。\n");

        me->receive_damage("qi", 150);
        me->add("neili", -cost);
        return 1;

}

int valid_learn(object me)
{
        int level;
        
if ( ! me->query("special_skill/lonely"))
return notify_fail("你不是天煞孤星,无法修习天煞剑法。\n");

        if (me->query("gender") == "无性")
return notify_fail("你无根无性，阴阳不调，难以修习天煞剑法。\n");
     
level = me->query_skill("lonely-jianfa", 1);

        if (me->query_skill("sword", 1) < level)
                return notify_fail("你对基本剑法的理解还不够，无法继续领会更"
"高深的天煞剑法。\n");
       if (me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你的武学修养不够，无法继续领会更"
"高深的天煞剑法。\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
if ( this_player()->query_skill("lonely-jianfa", 1) > 300)
       return 1500;
       else   return 1000;
}

string perform_action_file(string action)
{
        object me = this_player();

if ( ! me->query("special_skill/lonely") )
return "不是天煞孤星无法使用天煞剑法。";

return __DIR__"lonely-jianfa/" + action;
}


