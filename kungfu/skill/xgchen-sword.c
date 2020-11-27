// 这是玩家自创武功程序 原由maxim@nju_fengxue编写，现由xgchen@zzfy修改
// xgchen
// 长孙无情
// 布衣平民
// 6000001
// 男性
// sword
// 无情剑





inherit SKILL;

////////////////////////////////

mapping *action = ({

// ZHAOSHI :0

([
"action" :"$N纵身一跃，手中$w一招「无情无意」对准$n的$l斜斜刺出一剑",
"force" :50,
"dodge" :20,
"damage_type": "刺伤",
"parry" : 50,
"lvl" : 0,
"skill_name" : "无情无意"
]),
// ZHAOSHI :1

([
"action" :"$N运起神功，身体不停转动，一招「无花无假」,手中$w犹如银蛇出动直刺$n的$l",
"force" :80,
"dodge" :10,
"damage_type": "刺伤",
"parry" : 80,
"lvl" : 12,
"skill_name" : "无花无假"
]),
// ZHAOSHI :2

([
"action" :"$N的$w一闪，一招「无色无味」,在极快的速度下，朝$n的$l攻去",
"force" :100,
"dodge" :10,
"damage_type": "刺伤",
"parry" : 100,
"lvl" : 20,
"skill_name" : "无色无味"
]),
 });
// ZHAOSHI :3
int valid_learn(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon"))
     || (string)weapon->query("skill_type") != "sword") return notify_fail("你使用的武器不对。\n");
        if( (int)me->query("max_neili") < 50 )
                return notify_fail("你的内力太弱，无法练"+"无情剑"+"。\n");
        return 1;
}
int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
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
    level = (int)me->query_skill("xgchen-sword",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword") return notify_fail("你使用的武器不对。\n");    if( (int)me->query("qi") < 25 )
                return notify_fail("你的体力不够了，休息一下再练吧。\n");
        if( (int)me->query("neili") < 3 )
                return notify_fail("你的内力不够了，休息一下再练吧。\n");
        me->receive_damage("qi", 25);
        me->add("neili", -3);
        return 1;
} //total 34 lines!
