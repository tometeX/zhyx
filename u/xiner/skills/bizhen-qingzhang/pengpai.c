// bizhen-qingzhang  碧针清掌 澎湃
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/bizhen-qingzhang/pengpai"))
                return notify_fail("你还不会使用这一招！\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须空手才能施展「澎湃」这一招！\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("「澎湃」只能对战斗中的对手使用。\n");
 
        if (me->query_skill("bizhen-qingzhang", 1) < 180)
                return notify_fail("你的碧针清掌还不够娴熟，还不能用掌力伤人！\n");

        if (me->query_skill_mapped("strike") != "bizhen-qingzhang")
                return notify_fail("你没有激发碧针清掌，无法使用「澎湃」这一招！");

        if (me->query_skill_prepared("strike") != "bizhen-qingzhang")
                return notify_fail("你没有准备碧针清掌，难以施展「澎湃」。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你内功的修为不够，无法用掌力伤人！\n");

        if (me->query("max_neili") < 3000)
                return notify_fail("你的内力修为不够，无法用掌力伤人！\n");

        if (me->query("neili") < 500)
                return notify_fail("你的内力不够，无法用掌力伤人！\n");
 
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "一声轻哼，双掌挥舞出一个大圈，"
              "横推而出，顿时一股汹涌澎湃的劲气如波浪一般向$n"
              HIW "涌来。\n" NOR;
 
        ap = me->query_skill("strike") + me->query_skill("martial-cognize",1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize",1); 
	damage = ap * 2 / 3 + random(ap);

        me->add("neili", -300);

        if (ap * 2 / 3 + random(ap) < dp)
        {
                msg += HIY "只见$n" HIY "不慌不忙，轻轻一闪，躲过了$N" HIY "这一击！\n"NOR;
        } else
        {
                me->add("neili", -300);
                damage = ap / 2 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(5),
                                           HIR "只见$n" HIR "无法何挡这汹涌澎湃的气流，喷出一大口鲜血，身子直线飞出！\n" NOR);
		if (me->query("reborn"))
        	{
        		if (ap * 3 / 5 + random(ap) > dp) 
	        	{
			me->add("neili", -300);
			damage =ap / 2 + random(ap * 2 / 3);
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(5),
						HIW "$N"+HIW"见状飞身而起，隔空再出一掌，汹涌澎湃的气流将$n卷向空中！\n"
						HIR "$n已完全无法招架，鲜血伴随着嚎声四处飞溅。\n" NOR);
				if (me->query("breakup"))
				{
					if (ap / 2 + random(ap) > dp)
					{
					me->add("neili", -400);
					damage =ap / 2 + random(ap);
					msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(5),
						HIW "紧接着"+HIW"$N"+HIW"空中一个翻腾，跃至$n上方再出一掌，汹涌澎湃的气流将$n拍向地面！\n"
						HIR "$n被$N一掌拍中，鲜血狂喷惨叫一声撞向地面。\n" NOR);
					}
				}
			}
			me->start_busy(2 + random(5));	
        	}
        }
        message_combatd(msg, me, target);
        return 1;
}

