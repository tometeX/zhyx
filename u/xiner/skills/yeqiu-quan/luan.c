//luan 无双乱舞 3单+6连
#include <ansi.h>
#include <combat.h>

#define LUAN "「" HIM "无双乱舞" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage,count,i;
        string msg;
        int ap, dp;

        me = this_player();

        if (userp(me) && ! me->query("can_perform/yeqiu-quan/luan"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUAN "只能在战斗中对对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用"	LUAN "！\n");

        if ((int)me->query_skill("yeqiu-quan", 1) < 500)
                return notify_fail("你的野球拳还不够娴熟，不能使用" LUAN "。\n");

        if (me->query_skill_prepared("unarmed") != "yeqiu-quan"
           && me->query_skill_prepared("finger") != "yeqiu-quan"
           && me->query_skill_prepared("hand") != "yeqiu-quan"
           && me->query_skill_prepared("cuff") != "yeqiu-quan")
                return notify_fail("你没有准备野球拳，无法使用" LUAN "。\n");
                                
        if ((int)me->query("neili", 1) < 1000)
                return notify_fail("你现在内力太弱，不能使用" LUAN "。\n");

/*        if (userp(target))
                return notify_fail(HIW "你不能对玩家使用这招！\n" NOR); */

        if ((int)me->query_skill("force", 1) < 500)
                return notify_fail("你的内功火候不够，难以施展" LUAN "。\n");

        if ((int)me->query("max_neili") < 10000)
                return notify_fail("你的内力修为不足，难以施展" LUAN "。\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("你现在的真气不够，难以施展" LUAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


        msg = HIW "\n$N" HIW "马步一扎，大吼一声“"HIM"必杀·无双乱舞！"HIW"”\n"
	      HIW "双手不断变换出"HIM"『石头』"HIG"『剪刀』"HIW"和"HIB"『布』"HIW"三种招式，轰向$n"HIW"！\n" NOR;

	//石头
        ap = me->query_skill("yeqiu-quan", 1) + me->query_str()*5;
        dp = target->query_skill("force", 1) + target->query_str()*5;
	msg += HIW "\n$N" HIW "使出一招"HIM"『石头』"HIW"，双拳紧握朝着$n"HIW"的两眼挥去！\n" NOR;
	if (ap * 2 / 3 + random(ap) > dp)
	{
        	me->add("neili", -300);
		damage = ap+random(ap/4);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIR "$n一声惨叫，接连退了数步，被打出了两个熊猫眼！\n" NOR);
	} else
	{
        	me->add("neili", -100);
                msg += CYN "$p" CYN "不慌不忙，使出一招铁板桥。让$N"CYN"扑了个空。\n" NOR;
	}

	//剪刀
        ap = me->query_skill("yeqiu-quan", 1) + me->query_dex()*5;
        dp = target->query_skill("dodge", 1) + target->query_dex()*5;
	msg += HIW "\n紧接着$N" HIW "又是一招"HIG"『剪刀』"HIW"，四条气流从双手食指和中指激射而出，射向$n"HIW"胸口！\n" NOR;
	if (ap * 2 / 3 + random(ap) > dp)
	{
        	me->add("neili", -300);
		damage = ap+random(ap/4);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIR "$n闪避不及，顿时被气流击中，胸前留下四个黑糊糊的窟窿！\n" NOR);
	} else
	{
        	me->add("neili", -100);
                msg += CYN "$p" CYN "连忙使出驴打滚，在地上连打了十八个滚才躲开$N"CYN"的劲气。\n" NOR;
	}

	//布
        ap = me->query_skill("yeqiu-quan", 1) + me->query_con()*5;
        dp = target->query_skill("parry", 1) + target->query_con()*5;
	msg += HIW "\n$N" HIW "接着再出一招"HIB"『布』"HIW"，手掌大开，双手交替变幻罩向$n"HIW"的面门！\n" NOR;
	if (ap * 2 / 3 + random(ap) > dp)
	{
        	me->add("neili", -300);
		damage = ap+random(ap/4);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIR "$n避无可避，被$N"HIR"打得鼻青脸肿。\n" NOR);
	} else
	{
        	me->add("neili", -100);
                msg += CYN "$p" CYN "赶紧使出一招“缩头乌龟”，将头一缩险险避开了$N"CYN"的攻击。\n" NOR;
	}
 	//连招

        me->add("neili", -300);
        message_combatd(msg, me, target);

	msg = HIM "\n$N" HIM "使出三招以后，竟然越战越勇，对着$n"HIM"又是一阵穷追猛打！\n" NOR;
        ap = me->query_skill("yeqiu-quan", 1) + me->query_int()*5;
        dp = target->query_skill("literate", 1) + target->query_int()*5;

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 5;
                msg += RED "$n" RED "面对$P" RED "的攻势，完全无法抵挡，唯有退后。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "凝神应战，竭尽所能化解$P" HIC "的招式。\n" NOR;
                count = 0;
        }
        message_vision(msg, me, target);
	me->add_temp("apply/attack", count);
	me->add_temp("apply/unarmed_damage", count / 2);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
	me->add_temp("apply/attack", -count);
	me->add_temp("apply/unarmed_damage", -count / 2);
        me->start_busy(3 + random(6));
        return 1;
}