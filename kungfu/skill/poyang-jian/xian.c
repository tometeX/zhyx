//updated by kasumi
#include <ansi.h>
#include <combat.h>

#define XIAN "「" HIY "神光再现" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int level,ap,dp,count,i;

        if (userp(me) && ! me->query("can_perform/poyang-jian/xian"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" XIAN "。\n");      

        level = me->query_skill("poyang-jian", 1);

        if (level < 160)
		return notify_fail("你破阳冷光剑不够娴熟，难以施展" XIAN "。\n");

        if (me->query_skill_mapped("sword") != "poyang-jian")
                return notify_fail("你没有激发破阳冷光剑，难以施展" XIAN "。\n");

	if ((int)me->query_skill("force") < 240)
		return notify_fail("你的内功火候不足，难以施展" XIAN "。\n");

        if (me->query("neili") < 250)
                return notify_fail("你现在的真气不够，难以施展" XIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


	msg = HIG "\n$N" HIG "长啸一声，使出破阳冷光剑绝招「" HIY "神光再"
              "现" HIG "」，手中" + weapon->name() + HIG "光芒瀑涨，刺眼"
              "眩目，犹如神光降世，刹那间只见天地为之失辉，光芒已盖"
              "向$n。\n" NOR;
        

		  ap = me->query_skill("sword");
    	dp = target->query_skill("dodge");
		
      if (ap * 3 / 5 + random(ap) > dp)
	    {
		   msg += HIY "$n" HIY "见$P" HIY "剑势汹涌，寒意顿生，竟"
                           "被逼得连连后退，狼狈不已。\n" NOR;
		   count = me->query_skill("poyang-jian", 1) / 3;
      } else
      {
      msg += HIC "$n" HIC "见$N" HIC "这几剑来势迅猛无比，毫"
                 "无破绽，只得小心应付。\n" NOR;
		   count = 0;
      }

         me->add_temp("apply/attack", count);
         message_sort(msg, me, target);
		
		 for (i = 0; i < 6; i++)
         {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);               
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
         me->add("neili", -200);
		 me->add_temp("apply/attack", -count);
		 me->start_busy(1 + random(4));
	return 1;
}