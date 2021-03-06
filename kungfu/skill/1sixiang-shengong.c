// 基本指法及特殊武功数种。
// 打怪随机生成道具"四象卷", 与四种7c丹分别合成“朱雀卷”“白虎卷”“青龙卷”“玄武卷”，均为一次性道具，有7成几率读成四象四诀。
// 四诀要求为对应的先天>=30，四诀各有一pfm。
// 各180级后演练为：
// sixiang-shengong.c 四象神功。 类似九剑无招，但特效必须身上有内气凝聚的暗器才能展现。另任一天赋大于36，可使用终极pfm。

#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("sixiang-shengong", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

string *parry_msg = ({
        "只见$n力聚双臂，拳上白虎之气闪现，硬将$P来招逼退。\n",
        "$n以攻为守，借力打力，以青龙之型向$P反缠过去。\n",
        "$n吐气扬声，混身气劲爆发，凭玄武真气守得水泄不通，$P一时无法下手。\n",
        "$n功运脚底，如翩翩起舞之凤凰，与$P保持适当距离，令其欲攻无从。\n"
      });

string *dodge_msg = ({
        "只见$n力聚双臂，拳上白虎之气闪现，硬将$P来招逼退。\n",
        "$n以攻为守，借力打力，以青龙之型向$P反缠过去。\n",
        "$n吐气扬声，混身气劲爆发，凭玄武真气守得水泄不通，$P一时无法下手。\n",
        "$n功运脚底，如翩翩起舞之凤凰，与$P保持适当距离，令其欲攻无从。\n"
});


mapping *action = ({
([      "action": "$N十指互锁，大开大合，气势刚猛，合「"NOR + HIW "白虎劲" NOR "」与"
                  "「" NOR + HIB "玄武势" NOR "」于一体，顿时一股罡风直射$n",
        "force" : 440,
        "attack": 220,
        "parry" : 60,
        "dodge" : 60,
        "damage": 220,
        "weapon" : HIR "四象气劲" NOR,
        "damage_type" : "刺伤"
]),
([      "action": "$N左指右掌，一挡一推，是为「" HIG "左青龙" NOR "」「" HIW "右白"
                  "虎" NOR "」，一攻一守，令$n进退两难",
        "force" : 380,
        "attack": 220,
        "parry" : 220,
        "dodge" : 60,
        "damage": 220,
        "weapon" : HIG "四象气劲" NOR,
        "damage_type" : "刺伤"
]),
([      
        "action": "只见$N十指箕张，于虚空中乱舞，将「" HIW "白虎劲" NOR "」及"
                  "「" HIR "朱雀舞" NOR "」的精巧融合，\n顿时劲气纵横，飞"
                  "砂走石，逼向$n而去",
        "force" : 380,
        "attack": 280,
        "parry" : 60,
        "dodge" : 220,
        "damage": 220,
        "weapon" : HIW "四象气劲" NOR,
        "damage_type" : "刺伤"
]),
([      
        "action": "只见$N丁字步一立，双手拟太极之型，待$n来攻时，\n将「" HIG "青龙破" NOR "」及"
                  "「" HIB "玄武势" NOR "」爆发，将其震飞",
        "force" : 460,
        "attack": 220,
        "parry" : 185,
        "dodge" : 65,
        "damage": 200,
        "weapon" : HIB "四象气劲" NOR,
        "damage_type" : "刺伤"
]),
([      "action": "$N十指连弹，陡见四色气团由指尖飞快射出，，\n已「" HIG "青龙破" NOR "」之准引"
                  "「" HIR "朱雀舞" NOR "」之快，向$n身上连环击去",
        "force" : 360,
        "attack": 220,
        "parry" : 230,
        "dodge" : 225,
        "damage": 180,
        "weapon" : HIR "四象气劲" NOR,
        "damage_type" : "刺伤"
]),
([      "action": "只见$N身随气走，以「" HIG "玄武" NOR "」之气护体，\n以"
                  "「" HIR "朱雀" NOR "」之步游身，向$n身上狠狠撞去",
        "force" : 460,
        "attack": 120,
        "parry" : 110,
        "dodge" : 225,
        "damage": 210,
        "weapon" : HIR "四象气劲" NOR,
        "damage_type" : "刺伤"
]),
([      "action": "$N气势磅礴，身现左青龙、右白虎、前玄武、后朱雀之象，\n以"
                  "四兽之型，围着$n狂轰滥炸",
        "force" : 560,
        "attack": 300,
        "parry" : 200,
        "dodge" : 300,
        "damage": 400,
        "weapon" : HIR "四象气劲" NOR,
        "damage_type": "刺伤"
])
});

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

string main_skill() { return "sixiang-shengong"; }

mapping sub_skills = ([
        "qinglong-po"  : 180,
        "baihu-jing"   : 180,
        "xuanwu-shi"   : 180,
        "zhuque-wu"    : 180,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if (me->query_skill("literate", 1) < 1800)
        {
                tell_object(me, "你觉得四象神功极其深奥，看来多研究一下学问可能更有帮"
                                "助。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 180)
        {
                tell_object(me, "你发现自己的武学修养尚待提高，暂且无法演练成功。\n");
                return 0;
        }

        if (me->query_skill("force", 1) < 200)
        {
                tell_object(me, "你发现自己的内功根基不够，暂且无法演练成功。\n");
                return 0;
        }

        if ((int)me->query("max_neili") < 3500)
        {
                tell_object(me, "你觉得自己真气不继，无法合成四象神功神功。\n");
                return 0;
        }

        if (random(10) < 7)
        {
                tell_object(me, "你觉得有所感悟，或许再演练一次就能融会贯通。\n");
                return 0;
        }

        tell_object(me, HIY "\n霎那间，你将自身所修炼的四种气劲运用法门脑海中交替呈\n"
                            "现，真气随心运转，左现青龙，右现白虎，前出玄武，后突朱雀\n"
                            "恰现四象之型，真气外现。你终于练成了四象神功。\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
	return usage == "unarmed" || usage == "parry" || usage == "dodge"|| usage == "force"|| usage == "throwing";
}

int double_attack()
{
	return 1;
}

int valid_force(string force) { return 1; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练四象神功必须空手。\n");

        if ((int)me->query("int") < 30)
                return notify_fail("你的先天悟性太低，无法领会四象神功。\n");

        if ((int)me->query("dex") < 30)
                return notify_fail("你的先天身法孱弱，无法修炼四象神功。\n");

        if ((int)me->query("con") < 30)
                return notify_fail("你的先天根骨太低，无法领会四象神功。\n");

        if ((int)me->query("str") < 30)
                return notify_fail("你的先天臂力孱弱，无法修炼四象神功。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的内功火候不够，无法修炼四象神功。\n");

        if ((int)me->query("max_neili") < 3500)
                return notify_fail("你的内力太弱，无法修炼四象神功。\n");
            
        if (me->query_skill("martial-cognize", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你的武学修养尚待提高，暂且无法修炼四象神功。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你的基本拳脚水平有限，无法领会更高深的四象神功。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你的基本轻功水平有限，无法领会更高深的四象神功。\n");

        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你的基本招架水平有限，无法领会更高深的四象神功。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你的基本内功水平有限，无法领会更高深的四象神功。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你的基本暗器水平有限，无法领会更高深的四象神功。\n");
        return 1;
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        object anqi;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("sixiang-shengong", 1) < 200 ||
            ! living(me) || (int)me->query("neili") < 250 ||
            me->query_skill_mapped("parry") != "sixiang-shengong" ||
            me->query_skill_mapped("dodge") != "sixiang-shengong" ||
//            ob->query_temp("weapon") ||
            (! objectp(anqi = me->query_temp("handing"))) ||
            anqi->query("id") != "qi jing"  || (anqi->query_amount() < 1))
                return;

        cost = damage / 2;

      anqi->add_amount(-1);

        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("sixiang-shengong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$N" HIW "一招击中$n" HIW "的护体真气，只觉落手内劲"
                                            "浑厚无比，力道竟被$n" HIW "以白虎之势给反弹回来。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIB "$N" HIB "一招攻出，$n" HIB "怒喝一声，玄武"
                                            "真气爆发，竟硬吃$N" HIB "这招而毫发未伤。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIR "$N" HIR "远远发出数招，但$n" HIR "脚下朱雀"
                                            "真气连连爆开，借势飘开。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "真气化青龙，盘旋体外，已将$N" HIG "所"
                                            "有进攻招式全部封死。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIW "$n" HIW "默运四象神功，以白虎之势反抗。\n谁知$N" HIW       
                                 "劲力深厚无比，长叹一声，一招竟结实地打在$n" HIY
                                 "身上。\n" NOR;
                        break;

                case 1:
                        result = HIB "$N" HIB "一招攻出，$n" HIB "怒喝一声，玄武"
                                            "真气爆发，竟硬吃$N" HIB "这招，\n谁知$N" HIB       
                                            "劲分三重，连招竟结实地打在$n" HIY "身上。\n" NOR;
                        break;

               case 2:
                        result = HIR "$N" HIR "遥遥攻出数招，$n" HIR "脚下朱雀真气"
                                            "真气连连爆开，\n正借势飘开，但$N" HIR "招式陡然一变\n"
                                            "竟将$n" HIR "打个正着。\n" NOR;
                        break;

                default:
                        result = HIG "$N" HIG "真气化青龙，盘旋体外，欲将$n" HIG "所有进攻路线封死\n"
                                     "但$n" HIG "招式一变，连消带打，将青龙破去。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon, weapon2, anqi;
        int i, ap, ap2, dpp, dpd, dpf, dpu, ap1, lvl;
        string type, msg;
        anqi = me->query_temp("handing");
        if ((me->query("neili") < 200)
           || me->query_skill_mapped("force") != "sixiang-shengong"
           || me->query_skill_mapped("unarmed") != "sixiang-shengong"
           || me->query_skill_mapped("throwing") != "sixiang-shengong"
           || (objectp(weapon = me->query_temp("weapon")))
           || (! objectp(anqi))
	   || (string)anqi->query("id") != "qi jing"
           || anqi->query_amount() < 1)
                return;

        ap = me->query_skill("force");
        dpp = victim->query_skill("parry");
        dpd = victim->query_skill("dodge");
        dpf = victim->query_skill("force");  
        dpu = victim->query_skill("unarmed");  
        ap1 = ap + random(ap/2);    
        me->add("neili", -20);
        me->interrupt_me();

        switch(random(4))
        {
           case 1: 
                if (ap1 > dpp || ap1 > dpd || ap1 > dpf || ap1 > dpu)
                {        
                 
                  me->add("neili", -20);
                  anqi->add_amount(-1);
                  victim->receive_wound("qi", ap * 2 + 300, me);
                  
                 message_vision(HIW "\n$N" HIW "集四象神功如出笼猛虎"
                            HIW "，单拳直取$n" HIW "，轰个正着！\n" NOR, me, victim);

                }        
               break;

           case 2:
		message_vision(HIG "\n$N" HIG "眼观六路，四象神功化青龙"
                            HIG "，直取$n" HIG "招式中的破绽！\n" NOR, me, victim);
		
		if (! me->is_busy())
		{
			weapon2 = victim->query_temp("weapon");
			if ( ap1 >= dpp && weapon2 )
			{
				msg = HIG "$n" HIG "觉得眼前青龙盘绕，手中"
					"的" + weapon2->name() + HIG "竟被"
					"真龙气一荡，脱手而出！\n" NOR;
				weapon2->move(environment(me)); 
				anqi->add_amount(-1);
				me->add("neili", -20);   
				if ( ap1 > dpp ) 
				{
					msg +=  HIG "只见青龙张口一咬，将" + weapon2->name() + HIG "带向"
						"空中，竟向$n" HIG "狠狠劈下，顿时血花四溅！\n" NOR;
					anqi->add_amount(-1);
					victim->receive_wound("qi", ap * 2 + 300, me);
				}
			} else
			{
				msg = HIY "$n" HIY "只得运足内力与青龙搏斗，"
					"一时间却也无力反击。\n" NOR;
				me->add("neili", -20);
				anqi->add_amount(-1);
				victim->start_busy(4 + random(5));
			}
		}else 
		if (ap1 > dpd)
		{
			msg = HIY "$n" HIY "连忙闪避青龙气，一时也腾不开手反击。\n" NOR;
			anqi->add_amount(-1);
			victim->start_busy(4 + random(5));
		}else
		{
			msg = HIG "\n$N" HIG "眼观六路，四象神功化青龙"
				HIG "，直取$n" HIG "招式中的破绽！\n但$n" HIG "凝神"
				HIG "聚气，挥舞手中兵器，与青龙气遥遥相斗，不落下风。\n" NOR;
			anqi->add_amount(-1);
			victim->start_busy(2);
		}
		message_combatd(msg, me, victim);
		break;          

            case 3:
                 msg = HIB "\n$N" HIB "先气运丹田，再大喝一声，把"
                       HIB "四象真气化玄武之势，向$n" HIB "罩去。"
                       HIB "\n$n" HIB "见避无可避，只得催动内劲，硬挡一招！\n" NOR;
                 message_combatd(msg, me, victim);

                   if ( ap1> dpu )
        
                  { msg = HIB + "但见" + anqi->name() + HIB "绿芒一闪，一道气劲"
                          HIB + "透体已入，$n" HIB " 顿时气血上涌，满脸通红。\n" NOR;
                    victim->receive_damage("qi", ap1, me);
                    }  else 
                   {  msg = HIB "$n" HIB "气贯双臂，凝神以对，竟将$N" HIB "之力卸去。\n" NOR;
                    }
            message_combatd(msg, me, victim);
             me->add("neili", -50);
            anqi->add_amount(-1);

                  if ( ap1 > dpp)
        
                  { msg = HIB + "却见玄武真气又闪，一重更猛的冲劲"
                          HIB + "爆发而至，$n" HIB " 胸闷难忍，喉头一甜。\n" NOR;
                    victim->receive_damage("qi", ap1, me);
                    }  else 
                   {  msg = HIB "$n" HIB "再提内气，运劲一敲，竟将$N" HIB "之力打消。\n" NOR;
                    }
            message_combatd(msg, me, victim);
            me->add("neili", -50);
             anqi->add_amount(-1);

                 if ( ap1 > dpd)
        
                  { msg = HIB + "忽然玄武真气绿芒再现，$n" HIB "急忙再度提气一格，"
                          HIB + "谁知绿芒却是虚劲，$n" HIB "劲力无处宣泄，内力乱串，喷出一口鲜血。\n" NOR;
                    victim->receive_damage("qi", ap1, me);
                    }  else 
                   {  msg = HIB "$n" HIB "身气合一，竟将绿芒化为无形。\n" NOR;
                    }
            message_combatd(msg, me, victim);
            anqi->add_amount(-1);
            me->add("neili", -50);

            if ( ap1 * 3 / 2 > dpf )
        
                  { msg = HIB + "未几玄武真气绿芒大盛，现压顶之势，"
                          HIB + "$n" HIB "已是无力抵抗，被轰得抛跌出去，七孔流血。\n" NOR;
                    victim->receive_damage("qi", ap1, me);
                    }  else 
                   {  msg = HIB "$n" HIB "气运下盘，生生被绿芒轰出五丈，但竟未受伤。\n" NOR;
                    }
            anqi->add_amount(-1);
            me->add("neili", -50);
            message_combatd(msg, me, victim);

               break;

          default :        
             if ( ! me->query_temp("sixiang-shengong/lian") && 
                  (ap1 > dpp || ap1 > dpd || ap1 > dpf || ap1 > dpu ) )
             {  
                 message_sort(HIY "\n$N" HIY "气吞天下，四象真气寄朱雀之身，" 
                             "若凤舞九天，向$n" HIY "连连轰去，一时四象之型变化万千。\n" NOR, me, victim);
                me->add("neili", -50);
                me->set_temp("sixiang-shengong/lian", 1);
                for (i = 0; i < 10; i++)
                {
                    if (! me->is_fighting(victim))
                            break;
                   
                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, anqi, i * 2);
                     anqi->add_amount(-1);

                }
                me->delete_temp("sixiang-shengong/lian");
                
             }
             break;                        
       }
}

int query_effect_parry(object attacker, object me)
{
        object anqi;
        int lvl;

        if  (! objectp(anqi = me->query_temp("handing")) || 
            anqi->query("id") != "qijing"|| (anqi->query_amount() < 1) )  
                return 0;

        lvl = me->query_skill("sixiang-shengong", 1);
        if (lvl < 200) return 50;
        if (lvl < 225) return 60;
        if (lvl < 250) return 70;
        if (lvl < 275) return 80;
        if (lvl < 325) return 90;
        if (lvl < 350) return 100;
        return 120;
}

int query_effect_dodge(object attacker, object me)
{
        object anqi;
        int lvl;

        if  (! objectp(anqi = me->query_temp("handing")) || 
            anqi->query("id") != "qijing"|| (anqi->query_amount() < 1) )  
                return 0;

        lvl = me->query_skill("sixiang-shengong", 1);
        if (lvl < 200) return 50;
        if (lvl < 225) return 60;
        if (lvl < 250) return 70;
        if (lvl < 275) return 80;
        if (lvl < 325) return 90;
        if (lvl < 350) return 100;
        return 120;
}

int difficult_level()
{
        return 500;
}

int practice_skill(object me)
{
        return notify_fail("四象神功内外兼修，无法简单的通过练习进步。\n");
}

string perform_action_file(string action)
{
        return __DIR__"sixiang-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"sixiang-shengong/exert/" + action;
}
