#include <ansi.h>

inherit SKILL;

mapping *action = ({
([   "action" : "$N面露微笑，手中$w一抖，剑光暴长，洒向$n的$l",
     "force"  : 50,
     "attack" : 15,
     "dodge"  : 10,
     "parry"  : 25,
     "damage" : 10,
     "lvl"    : 0,
     "damage_type":  "刺伤"
]),
([   "action" : "$N身形突闪，剑招陡变，手中$w从一个绝想不到的方位斜刺向$n的$l",
     "force"  : 70,
     "attack" : 25,
     "dodge"  : 25,
     "parry"  : 30,
     "damage" : 5,
     "lvl"    : 10,
     "damage_type":  "刺伤"
]),
([   "action" : "$N暴退数尺，低首抚剑，随后手中$w骤然穿上，刺向$n的$l",
     "force"  : 75,
     "attack" : 33,
     "dodge"  : 22,
     "parry"  : 32,
     "damage" : 20,
     "lvl"    : 20,
     "damage_type":  "刺伤"
]),
([   "action" : "$N身形一晃，疾掠而上，一招「神驼骏足」，手中$w龙吟一声，对准$n的$l连递数剑",
     "force"  : 90,
     "attack" : 39,
     "dodge"  : 40,
     "parry"  : 35,
     "damage" : 25,
     "lvl"    : 30,
     "damage_type":  "刺伤"
]),
([   "action" : "$N神色微变，一招「风卷长草」，剑招顿时变得凌厉无比，手中$w如匹链般洒向$n的$l",
     "force"  : 180,
     "attack" : 71,
     "dodge"  : 30,
     "parry"  : 52,
     "damage" : 40,
     "lvl"    : 70,
     "damage_type":  "刺伤"
]),
([   "action" : "$N缓缓低首，接着一招「举火燎天」，手中$w中宫直进，迅捷无比地往$n的$l刺去",
     "force"  : 200,
     "attack" : 85,
     "dodge"  : 20,
     "parry"  : 54,
     "damage" : 35,
     "lvl"    : 80,
     "damage_type":  "刺伤"
]),
([   "action" : "$N矮身侧步，一招「大漠孤烟」，手中$w反手疾挑而出，“唰”的一声往$n的$l刺去",
     "force"  : 240,
     "attack" : 91,
     "dodge"  : 65,
     "parry"  : 65,
     "damage" : 58,
     "lvl"    : 100,
     "damage_type":  "刺伤"
]),
([   "action" : "$N蓦地疾退一步，又冲前三步，一招「平沙落雁」，手中$w化为一道弧光往$n的$l刺去",
     "force"  : 265,
     "attack" : 93,
     "dodge"  : 40,
     "parry"  : 68,
     "damage" : 72,
     "lvl"    : 110,
     "damage_type":  "刺伤"
]),
([   "action" : "$N纵身跃起，一招「雪中奇莲」，不见踪影，接着却又从半空中穿下，$w直逼$n的$l",
     "force"  : 290,
     "attack" : 97,
     "dodge"  : 60,
     "parry"  : 72,
     "damage" : 78,
     "lvl"    : 120,
     "damage_type":  "刺伤"
]),
([   "action" : "$N一招「千里流沙」，手中$w遥指苍空，猛然划出一个叉字，往$n的$l刺去",
     "force"  : 310,
     "attack" : 100,
     "dodge"  : 45,
     "parry"  : 75,
     "damage" : 86,
     "lvl"    : 130,
     "damage_type":  "刺伤"
]),
([   "action" : "$N一招「冰河倒泻」，左手虚击，右手$w猛的自下方挑起，激起一股劲风反挑$n的$l",
     "force"  : 330,
     "attack" : 105,
     "dodge"  : 50,
     "parry"  : 82,
     "damage" : 95,
     "lvl"    : 140,
     "damage_type":  "刺伤"
]),
});

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 700)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法火候不够，无法学习三分剑术。\n");

        if ( me->query("dex") < 45 && me->query_skill("sanfen-jianshu", 1) > 150) 
                return notify_fail("你的身法灵动性不够，难以继续修炼三分剑术。\n"); 

        if ( me->query("gender") == "无性" ) 
                return notify_fail("你无根无性，难以修炼三分剑术。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("sanfen-jianshu", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的三分剑术。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("sanfen-jianshu",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 150)
                return notify_fail("你的体力目前没有办法练习三分剑术。\n");

        if ((int)me->query("neili") < 360)
                return notify_fail("你的内力不够，无法练习三分剑术。\n");

        if (me->query("dex") < 45 && me->query_skill("sanfen-jianshu", 1) > 150) 
                return notify_fail("你的身法灵动性不够，难以继续修炼三分剑术。\n"); 

        if ( me->query("gender") == "无性" ) 
                return notify_fail("你无根无性，难以修炼三分剑术。\n");
        
        me->add("qi", -120);
        me->add("neili", -250);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i;

        lvl = me->query_skill("sanfen-jianshu", 1);

        if (damage_bonus < 120
           || me->query("neili") < 500
           || me->query_skill_mapped("sword") != "sanfen-jianshu")
                     return 0;

        switch(random(3))
        {
           case 1:
              if (damage_bonus > victim->query_con())
              {
                  me->add("neili", -20);
                  victim->receive_wound("qi", (damage_bonus - 80) / 2, me);
                  
                  return random(2) ? MAG "$N" MAG "悠悠刺出一剑，$n" MAG
                                     "疏于防备，顿时中招。\n" NOR:
                                     MAG "$N" MAG "轻叹一声，缓缓施出一剑，$n" MAG ""
                                     "刚要躲闪，却早已中招，连连惨叫。\n" NOR;
             }
             break;

          case 2:
             if (random(lvl / 2) + lvl > victim->query_skill("dodge",1))
             {
                  weapon = me->query_temp("weapon");
                  victim->start_busy(2);
                  return   HIG "$N" HIG "娇喝一声，手中" + weapon->name() + HIG "化出一道道剑光,"
                           "$n" HIG "一时疏忽，被剑光划得鲜血淋漓。\n" NOR;
             }
             break;

          case 3:
             if (lvl > 250 && random(lvl / 2) + lvl > victim->query_skill("parry", 1)
                  && ! me->query_temp("perform_sanfenjian/lian"))
             {
                weapon = me->query_temp("weapon");
                message_sort(HIR "\n$N" HIR "一声轻呼，手中" + weapon->name() + HIR"顿时"
                             "幻化出万道金龙，金龙携狂风暴雨之势"
                             "向$n" HIR "齐齐攻去。\n" NOR, me, victim);
                me->set_temp("perform_sanfenjian/lian", 1);

                for (i = 0; i < 5; i++)
                {
                    if (! me->is_fighting(victim))
                            break;
                   
                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, weapon, 0);
                } 
                me->delete_temp("perform_sanfenjian/lian");     
                me->add("neili", -50);          
                
             }
             break;     
          	                        
          default:
                return 0;
       }
}

string perform_action_file(string action)
{
        return __DIR__"sanfen-jianshu/" + action;
}