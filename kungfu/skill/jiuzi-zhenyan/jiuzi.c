#include <ansi.h>
#include <combat.h>

#define JIUZI "「" HIY "九字真言" NOR "」"
inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg, sub_msg;

	/*if (userp(me) && ! me->query("can_perform/jiuzi-zhenyan/jiuzi"))
                return notify_fail("你所使用的外功中没有这种功能。\n");*/

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIUZI "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("JIUZI只能空手使用。\n");
                
        if (me->query("max_neili") < 6000)
                return notify_fail("你的内力修为还不够，无法施展JIUZI。\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query("qi") < 1000)
                return notify_fail("你的体力现在不够！\n");

        if ((int)me->query_skill("jiuzi-zhenyan", 1) < 300)
                return notify_fail("你的九字真言火候不够，无法使用JIUZI！\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("你的内功修为不够，无法使用JIUZI！\n");

        if (me->query_skill_prepared("hand") != "jiuzi-zhenyan")
              return notify_fail("你现在没有准备使用九字真言，无法使用JIUZI！\n");

        if ((me->query("int") < 35) && (me->query_skill("xuanming-shengong", 1) < 501) 
           || (me->query("int") > 14) && (me->query_skill("xuanming-shengong", 1) > 500)) 
                return notify_fail("你的先天悟性不对，无法使用此招。\n");   

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


        msg = HIY "$N" HIY "倏地升至空中，十指作出连串印结，周身金光闪华，"
		 	"放射出出无边金光，将$n" HIY "牢牢罩住！\n" NOR;   
	
        ap = me->query_skill("buddhism", 1) + me->query_skill("lamaism", 1);
        damage = (int)me->query_skill("jiuzi-zhenyan", 1);

        if ( me->query_skill("jiuzi-zhenyan", 1) > 799 ) damage += random(ap / 2);

	if ( ap > 600 ) damage = damage + ap / 3;

	if ( ap > 800 ) damage = damage * ap / 800;
	
        msg += HIW "\n“临！”$N眼中金光一闪，双手一撑，高举于顶，施出「" HIY "不动根本印" HIW "」\n" NOR;
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n奋力招架，怎奈功力有限，登时受了内伤，吐出一口鲜血。\n" NOR);
	if ( ap > 400 )
	{
	msg += HIW "\n$N" HIW "按捏「" HIR "日轮印" HIW "」手掌交错之间，四周已是热浪翻滚，几阵内劲朝$n" HIW "涌去！\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n一声惨嚎，接连退了数步，“哇”的呕出一大口鲜血。\n" NOR);
	msg += HIW "\n$N" HIW "一无所惧，长笑一声，左手拍向$n，同时右手暗捏「" HIY "狮子印" HIW "」沉喝一声“咄”！\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n轻功尚欠火候，一不留神已然中招。\n" NOR);
	}
	if ( ap > 500 )
	{
	msg += HIW "\n$N" HIW "右手暗捏「" HIR "内狮子印" HIW "」左手一挥，只见一股气墙朝$n拍去！\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n连忙格挡，可哪里抵挡得住？只被打得吐血三尺，连退数步！\n" NOR);
	
	msg += HIW "\n$N" HIW "按捏「" HIG "智拳印" HIW "」突然拳法突变，宛如漫天流星，朝$n" HIW "周身要害打去！\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n只觉气息窒滞，立足不稳，登时应印而横飞出去。\n" NOR);
	}
	if ( ap > 600 )
	{
	msg += HIW "\n$N" HIW "使出「" HIR "内缚印" HIW "」体内脉道真气交替，早严阵以待的真气猛然涌向$n！\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "结果$n躲闪不及，真气窜入体内，顿时口中鲜血狂喷。\n" NOR);

	msg += HIW "\n$N" HIW "由「" HIR "内缚印" HIW "」改为「" HIY "外缚印" HIW "」拇指改置外侧，劲气疾吐，击向$n！\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n急忙抽身后退，可动作稍慢，全身已多了数个伤口，鲜血飞溅。\n" NOR);
	}
	if ( ap > 800 )
	{
	msg += HIW "\n$N" HIW "手捏「" HIM "大金刚轮印" HIW "」脸上红光闪现，只见一股热浪朝$n涌去！\n" NOR;
      	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n内力不济，顿时被$N这招震伤。\n" NOR);
	}
	if ( ap > 900 )
	{
	msg += HIW "\n$N" HIW "按捏「" HIR "宝瓶印" HIW "」气劲再非高度集中的一团，而是像一堵墙般直朝$n压过去！\n" NOR;
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 10,
                                   HIR "$n已然放弃抵抗，任凭气流摧袭，鲜血不断从口中喷出。\n" NOR);
	}

        message_combatd(msg, me, target);
        me->start_busy(3 + random(5));
        me->add("neili", -900);
	

        return 1;
}

        
