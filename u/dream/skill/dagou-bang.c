// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// dagou-bang.c

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
        "$p$W扬起，竟不理会$P的招式，用缠字诀一绊一挑，巧妙异常，去势全在旁人万难料到之处，\n"
        "$P轻跃相避，哪知$W猛然翻转，击$P的脚胫。$P一个踉跄，感紧跃开。\n",
        "$p当即横棒掠地，直击不回。这一棒去势古怪，正巧搭上$P$w。$P这一招尚未使足，已知不妙，急忙跃起相避。\n",
        "$p立感不支，当下移动脚步，使个「封」字诀挡住$P$w攻势。\n",
        "但终究还是慢了一步，$p$W回转，忽地刺向$P的右股。这一招後发而先至，$P$w未及$p身体，\n"
        "手腕先得被棒端刺中，$P急忙收$w变招。\n",
        "$p却将内力慢慢传到$W上。$P只觉$p手里这根$W中竟有一股极强吸力，牵引得$P$w歪歪斜斜，$w所向不是偏左，便是偏右。\n",
        "$p眼见危急，挥棒护住身前，棒端即又疾送，使招" + HIG "「按狗低头」" NOR + "，向$P$w捺落。\n",
        "$p这时和$P站得甚近，闪避不及，急忙回转$W，把$P招式一一拨开。\n",
});

string query_parry_msg(object weapon)
{
        object ob;
        object victim = this_player();

        if (! objectp(ob = victim->query_temp("weapon"))
        ||  ob->query("skill_type") != "staff" 
        ||  victim->query_skill("dagou-bang", 1) < 100)
                return SKILL_D("parry")->query_parry_msg(weapon);
        else
                return replace_string(parry_msg[random(sizeof(parry_msg))], "$W", ob->name());
}

string *action_msg = ({
        "$N使出一招"+HIG"「棒打双犬」"+NOR"，手中$w化作两道青光砸向$n的$l",
        "$N手中$w左右晃动，一招"+HIG"「拨草寻蛇」"+NOR"向$n的$l攻去",
        "$N举起$w，居高临下使一招"+HIG"「打草惊蛇」"+NOR"敲向$n的$l",
        "$N施出"+HIG"「拨狗朝天」"+NOR"，$w由下往上向$n撩去",
        "$N手中$w变招横扫，一招"+HIG"「反截狗臀」"+NOR"，棒夹风声，来势迅猛，攻击$n要害",
        "$N突使一招"+HIG"「斜打狗背」"+NOR"，棒招精妙无比，$w一幌，已击向$n的$l",
        "$N提起$w，一招"+HIG"「棒打狗头」"+NOR"，往$n$l击去，出手狠辣，正是"+HIG"「打狗棒法」"+NOR"中的高招",
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        if (me->query("dex") < 26)
                return notify_fail("你的先天身法太差，无法学习打狗棒法。\n");

        if ((int)me->query("max_neili") < 1500)
                return notify_fail("你的内力修为不足，无法学习打狗棒法。\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("你的基本杖法不够，无法学习打狗棒法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("dagou-bang", 1))
                return notify_fail("你的基本杖法水平有限，无法领会更高深的打狗棒法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "dodge" : 80 + random(10),
                "parry" : 80 + random(10),
                "damage": 120 + random(50),
                "attack": 80 + random(10),
                "damage_type": "挫伤",
        ]);
}

/*
mixed hit_ob(object me, object victim, int damage)
{
        string msg;
        int ap, dp, zhencost;
        string result;
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")))
                return 0;
        
        zhencost = sqrt(weapon->weight() / 10) + 10;
        if (me->query("neili") < zhencost || me->query("jing") < zhencost)
                return 0;
                
        ap = me->query_skill("stick", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        dp = victim->query_skill("dodge", 1) / 2 +
              victim->query_skill("parry", 1) / 4;
        dp += victim->query_skill("martial-cognize", 1);
        

        
        if (random(ap+dp) > ap) 
        {
                result = HIG "突然青光闪动，棒招来势神妙无方，" + (string)weapon->query("name") + HIG "击中了$n。\n" NOR;
                damage = weapon->query("weapon_prop/damage") * 3;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(3));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else if (random(ap + 2 * dp) > ap) 
        {
                result = HIG "$N猛地递出一招，这一棒迅捷无伦，直取$n眉心，$p「啊」的一声，连退出数尺！\n" NOR;
                damage = weapon->query("weapon_prop/damage") * 2;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(2));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else
        {
                result = weapon->name()+ HIG "幌动，霎眼之间竟已转到$n身后，拍的一声，在$p臀上抽了一下。！\n" NOR;
                damage = weapon->query("weapon_prop/damage");
                if (! victim->is_busy())
                        victim->start_busy(1+random(1));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
}
*/

int query_effect_parry(object attacker, object me)
{
        int lvl;
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return 0;

        lvl = me->query_skill("dagou-bang", 1);
        if (lvl < 80)  return 50;
        if (lvl < 200) return 100;
        if (lvl < 280) return 160;
        if (lvl < 350) return 200;
        return 240;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int) me->query_skill("dagou-bang", 1) < 100
           || ! me->query_temp("feng_zijue")
           || ! (weapon = me->query_temp("weapon"))
           || ! living(me)
           || weapon->query("skill_type") != "staff")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "巧妙的施展打狗棒「" HIY "封"
                                            HIG "」字诀，手中" + weapon->name() + HIG
                                            "左封右闭，使得$N" HIG "的攻势全然落空。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "急转手中" + weapon->name() +
                                            HIG "，打狗棒「" HIY "封" HIG "」字诀发挥"
                                            "得淋漓尽致，顿将$N" HIG "的招式驱于无形。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "蓦地施展出打狗棒「封」字"
                                 "诀，可是$N" HIY "理也不理，当即挥招直"
                                 "入，进袭$n" HIY "。\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "急转手中" + weapon->name() +
                                 HIY "，左封右闭，然而$N" HIY "却是精演"
                                 "天数，丝毫不受$n" HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "staff")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 90)
                return notify_fail("你的体力不够练打狗棒法。\n");

        if ((int)me->query("neili") < 90)
                return notify_fail("你的内力不够练打狗棒法。\n");

        me->receive_damage("qi", 80);
        me->add("neili", -80);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dagou-bang/" + action;
}
