// dragon-strike.c 降龙十八掌 羝羊触蕃 

inherit SKILL; 

mapping *action = ({ 
([      "action" : "$N使出「羝羊触蕃」，双掌由下往上击向$n的$l",     
        "dodge"  : 90, 
        "parry"  : 90, 
        "attack" : 90,
        "force"  : 190, 
        "damage" : 100, 
        "damage_type": "震伤" 
]), 
}); 

string main_skill() { return "dragon-strike"; } 

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }   

int valid_learn(object me) 
{ 
       if (me->query_skill("dragon_strike", 1) > 0) 
               return notify_fail("你已经学全十八掌了，不必再单独学习。\n"); 

       if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 

       if ((int)me->query("str") < 30) 
               return notify_fail("就你这身子骨还练降龙十八掌？小心弄折了胳膊。\n"); 

       if ((int)me->query_skill("force") < 90) 
               return notify_fail("你的内功火候不够无法学习降龙十八掌。\n"); 

       if ((int)me->query("max_neili") < 600) 
               return notify_fail("你的内力太差无法学习降龙十八掌。\n"); 

       if ((int)me->query_skill("strike", 1) < 30) 
               return notify_fail("你的基本掌法火候不够，无法学习降龙十八掌。\n"); 

       if ((int)me->query_skill("strike", 1) < (int)me->query_skill("feilong-zaitian", 1)) 
               return notify_fail("你的基本掌法水平有限，无法领会更高深的降龙十八掌。\n"); 

       return 1; 
} 

mapping query_action(object me, object weapon) 
{ 
        return action[random(sizeof(action))]; 
} 

int practice_skill(object me)  
{ 
       if ((int)me->query("qi") < 110)  
               return notify_fail("你的体力太低了。\n"); 

       if ((int)me->query("neili") < 100) 
               return notify_fail("你的内力不够练降龙十八掌。\n"); 

       me->receive_damage("qi", 90); 
       me->add("neili", -80); 
       return 1; 
} 

string perFORM_action_file(string action) 
{ 
       return __DIR__"diyang-chufan/" + action; 
} 



