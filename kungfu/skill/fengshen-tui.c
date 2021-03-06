#include <ansi.h> 
inherit SKILL;

string *xue_name = ({ 
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴", "承浆穴", "天突穴", "百会穴",
"幽门穴", "章门穴", "大横穴", "紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", });

string *attack_name = ({
"风神腿劲", "狂风扫落叶劲气", "摩诃无量玄劲", "三合为一的霸烈真气", });

string *parry_msg = ({
       "$n以"+MAG"「风神腿劲」"NOR+"护体，身边竟旋起一阵旋风，让$N目瞪口呆。\n",
      "$n在这刹那间，身体变得柔弱无骨，给在人一种奇异的感觉，这正是来自外域的"+HIM"「瑜珈奇术」\n",
       "$n运起"+CYN"「狂风扫落叶劲气」"NOR+"犹如天神临世,$N的招式再也不使不下去了。\n",
        "$n大喝一声，以"+RED"「摩诃无量玄劲」"NOR+"之威，震慑在场众人。竟无人敢出手了。\n",
});

mapping *action = ({
([      "action" : "$N双手虚晃，左脚猛地飞起，一式[1;36m「风卷楼残」[0m,[1;33m，踢向$n的$l",
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "风神腿劲" NOR,
        "damage_type" : "瘀伤",
        "skill_name"  : "风卷楼残"
]),
([      "action" : "$N左脚顿地，身形猛转，右脚一式[1;36m「风中劲草」[0m,[1;33m，猛踹$n的$l",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIR "狂风扫落叶劲气" NOR,
        "damage_type" : "瘀伤",
        "skill_name"  : "风中劲草"
]),
([      "action" : "$N右脚飞一般踹出，既猛且准，一式[1;36m「雷厉风行」[0m,[1;33m，踢向的$n",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIY "摩诃无量玄劲" NOR,
        "damage_type" : "瘀伤",
        "skill_name"  : "雷厉风行"
]),
([      "action" : "$N双足连环圈转，一式[1;36m「暴风骤雨」[0m,[1;33m，足带风尘，攻向$n的全身",
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "摩诃无量玄劲" NOR,
        "damage_type" : "瘀伤",
        "skill_name"  : "暴风骤雨"
]),
([      "action" : "$N双脚交叉踢起，一式[1;36m「叱咤风云」[0m,[1;33m，脚脚不离$n的面门左右",
        "force" : 850,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "三合为一的霸烈真气" NOR,
        "damage_type" : "瘀伤",
        "skill_name"  : "叱咤风云"
]),
});

string *usage_skills = ({ "unarmed", "parry" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
       return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}
int practice_skill(object me)
{
      return notify_fail("风神腿博大精深，无法简单的通过练习进步。\n");
}

int valid_learn(object me)
{
        int level;

     
        level = me->query_skill("fengshen-tui", 1);

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("你对基本拳脚的理解还不够，无法继续领会更"
                                   "高深的风神腿。\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("你对基本招架的理解还不够，无法继续领会更"
                                   "高深的风神腿。\n");

       if (me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你的武学修养不够，无法继续领会更"
                                   "高深的风神腿。\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
       if ( this_player()->query_skill("fengshen-tui", 1) > 300)
       return 1200;
       else   return 1000;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name1, name2, weapon;
        name1 = xue_name[random(sizeof(xue_name))];
        name2 = attack_name[random(sizeof(attack_name))];

        victim->receive_wound("qi", damage_bonus * 3, me);
        me->add("neili", me->query("jiali") / 3);

        if (victim->query("neili") < 500)
                victim->set("neili", 0);
        else
                victim->add("neili", -300);

        return NOR + HIR "$n" HIR "接下$N" HIR "一招，" + name2 + "顿时破体而"
               "入，全身真气由" + name1 + "狂泻而出。\n" NOR;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, sk1, sk2;
        string msg;

        sk1 = ob->query_skill("paiyun-zhang", 1); 
        sk2 = me->query_skill("fengshen-tui", 1); 
//        ap = ob->query_skill("parry");
        ap = ob->query_skill("fanyun-daofa", 1);
        dp = me->query_skill("fengshen-tui", 1);

/*
        if (dp/2 > ap)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" "以"HIR"「风神腿劲」护体，身边竟旋起一,"
                                                  "阵旋风，让$N目瞪口呆。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" "在这刹那间，身体变得柔弱无骨，给"
                                                  "人一种奇异的感觉，这正是来自外域的"HIM"「瑜珈奇术」。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" "运起"CYN"「狂风扫落叶劲气」，犹如天神临世,"
                                                   "$N的招式再也不敢出手。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" "大喝一声，以"RED"「摩诃无量玄劲」之威，"
                                                     "震慑在场众人。竟吾人敢出手了。\n" NOR]);
                        break;
                }
                return result;
        }
*/

        if (sk1 > 100)
        {
                msg = "$N竟运起排云掌法，将其奥义发挥得淋漓尽致，$n竟一时找不出破绽，处处受制！\n";
                msg = HIY + msg + NOR; 
                COMBAT_D->set_bhinfo(msg); 
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fengshen-tui", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"fengshen-tui/perform/" + action;
}




