// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// duoluoye-zhi.c - 少林多罗叶指(极为霸道的武功)
       
inherit SHAOLIN_SKILL;
        
string *action_msg = ({
        "$N身形前倾，右指弹出一屡劲风，飘渺无形的击向$n的$l",
        "$N手捏不动手印，轻轻跃起，双手回旋，将$n笼罩在指风之中",
        "$N揉身而上，右指长驱直入，弛点$n的大穴，一派两败俱伤的打法",
        "$N纵身跃起，居高临下，双手分别点向$n的各大要穴",
        "$N将内力灌注于指间，一指戳出，勇不可挡，硬破入$n的招数中，击向$n的$l",
        "$N跨步上前，突然连环三指击出，一气呵成，射出三屡指风击向$n",
        "$N纵身而上，右手食指点出，缓缓按向$n的$l，似乎毫不着力",
        "$N缓步上前，尽起全身功力，双指弹出数道指风，将$n完全笼罩在攻势之下",
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; } 
      
int valid_learn(object me) 
{ 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("练多罗叶指必须空手。\n"); 
      
        if ((int)me->query_skill("force") < 150) 
                return notify_fail("你的内功火候不够，无法学习多罗叶指。\n"); 
     
        if ((int)me->query("max_neili") < 2000) 
                return notify_fail("你的内力太弱，无法练多罗叶指。\n"); 
      
        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("duoluoye-zhi", 1))
                return notify_fail("你的基本指法水平有限，无法领会更高深的多罗叶指。\n"); 
      
        return 1; 
} 
      
mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 360 + random(120),
                "attack": 80 + random(10),
                "dodge" : 80 + random(10),
                "parry" : 80 + random(10),
                "damage_type" : "刺伤",
        ]);        
}

int practice_skill(object me) 
{ 
        if (me->query_temp("weapon") || 
            me->query_temp("secondary_weapon")) 
                return notify_fail("你必须空手练习！\n"); 
      
        if ((int)me->query("qi") < 90) 
                return notify_fail("你的体力太低了。\n"); 
      
        if ((int)me->query("neili") < 90) 
                return notify_fail("你的内力不够练多罗叶指。\n");
      
        me->receive_damage("qi", 80);
        me->add("neili", -80); 
        return 1; 
} 
      
string perform_action_file(string action) 
{ 
        return __DIR__"duoluoye-zhi/" + action; 
}
