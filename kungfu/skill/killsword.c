// killsword.c 天煞剑法
// by yuchang
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : HIW"
$N以气摧剑，神惯剑身，顿悟了『天煞剑法』的绝学「气游百穴连绵不决」\n"NOR+
YEL"$N顿感真气有如大江奔腾，无穷无尽的向着白卉飞流东，$N大喝一声：\n"NOR+
HIY"    『三剑齐发』\n"NOR,

        "force" : 250,
        "dodge" : 15,
        "damage": 100,
        "lvl" : 90,
        "set_name" : "气游百穴",
        "damage_type":  "刺伤"
]),
([      "action" : HIB"
$N仰目长笑，将心中的杀气聚在掌心，用尽全力使出天煞神掌之最终绝技------\n\n"NOR+
HIC"　　　　　　　 　『中 华 傲 决』　　　　　　　　　　　\n\n"NOR+
HIR"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"NOR+    
HIR"WWWWWWWWWWWWWWWWWWWP'dP'dWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWW'VWWWb &'''.o.. .dWWWWWWWWWWWWP~~''_{WWWWWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWWb  '''''''w.     jWWWWWWWP'  ,.--''    .wWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWWWbWWWWF'''''`    WWWWWWP' .-'          {WWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWWWWWWWWLLWP      jWWWWP'               .wwWWWWWWWWW WWWWWWWW\n"NOR+
HIR"WWWWW`W`W`WWWW'      jWWW'                 {WWWWWWWWWWP  `VWWWWWW\n"NOR+
HIR"WWWWWW, dWWWW'      jWWWW                 .wwWWP'.w.'WWP.WWWWWWWW\n"NOR+
HIR"WWWWWW' VWWWW        VWW'               _{WWWW( WWWW. P.WWWWWWWWW\n"NOR+
HIR"::::::':  :::         '                {  `:::::. '' ,.::::::::::\n"NOR+
HIR":::::,:::  ::                                `''''  .::::::::::::\n"NOR+
HIR"::::::::::                                       ..,:::::::::::::\n"NOR+
HIR":::::::::::   .                  ..:.      `:::::::::::::::::::::\n"NOR+
HIR":::::::::::: ::   .: ::::::::   :::::::.          `::::::::::::::\n"NOR+
HIR"::::::::::::::' .::::::::::::.    .::::::::::::::  ::::::::::::::\n"NOR+
HIR":::::::::::::'.:::::::::::::::::  ::::::::::::::'  ::::::::::::::\n"NOR+
HIR":::::::'.....:.. ::::::::'......:. :::::::::'....::.`::::::::::::\n"NOR+
HIR":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"NOR+
HIR":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"NOR,

        "force" : 300,
        "dodge" : 15,
        "damage": 600,
        "lvl" : 100,
        "skill_name" : "中华傲决",
              "damage_type":  "刺伤" 
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
me=this_player();
if(me->query_skill("force")<350)
return notify_fail("你的基本内功修为不够学天煞剑法这种绝技！\n");
if(me->query_skill("strike")<180)
return notify_fail("你的基本掌法不够学天煞剑法这种绝技！\n");
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
        level = (int) me->query_skill("killsword", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/50)];
}

int practice_skill(object me)
{
        object weapon;


        if(this_player()->query_skill("king-of-dragon")<100)
        return notify_fail("你还要在君临天下神功上有所加强！\n");
        if (! objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "sword") 
            return notify_fail("你使用的武器不对。\n"); 

        if ((int)me->query("qi") < 500)
        return notify_fail("你的体力不够练天煞剑法这种绝技！\n");
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"killsword/" + action;
}



