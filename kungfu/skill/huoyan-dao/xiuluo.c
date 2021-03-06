 // 修罗降世 xiuluo.c

#include <ansi.h>
#include <combat.h>


#define XIULUO "「" HIY "修罗降世" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp, count;
		int damage;

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail(XIULUO "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon"))
           return notify_fail("你拿着武器使不出来" XIULUO "！\n");

        if ( me->query_skill_mapped("unarmed") != "huoyan-dao")
                return notify_fail("你没有激发火焰刀，难以施展" XIULUO "。\n");
        if(me->query_skill("huoyan-dao", 1) < 150 )
                return notify_fail("你的火焰刀火候不够，难以施展" XIULUO "。\n");

        if(me->query_skill("unarmed", 1) < 150 )
                return notify_fail("你的基本拳脚还不够娴熟，难以施展" XIULUO "绝技。\n");


        if(userp(me) && (int)me->query_skill("longxiang-gong", 1) < 100 )
                return notify_fail("你的龙象般若功等级不够高，难以施展" XIULUO "。\n");

        if (me->query("max_neili") < 2000)
           return notify_fail("你的内力修为不够，难以施展" XIULUO "。\n");

       if (me->query("neili") < 500)
           return notify_fail("你的内力不够，难以施展" XIULUO "。\n");

       if (me->query("jing") < 80)
           return notify_fail("你的精力不够，难以施展" XIULUO "。\n");



        msg = HIW "$N" HIW "将手中" + weapon->name() + HIW "缓缓压向$n"
              HIW "，棍体隐隐带着风雷之劲，正是取经棍法杀着「" HIR "震"
              "雷乾坤" HIW "」！\n只见棍端竟全被紫电所笼罩，" +
              weapon->name() + HIW "幻作千百根相似，霹雳间连续向" HIW"$n" HIW"砸出了三招！\n" NOR;			  

        ap = me->query_skill("club") + me->query_skill("force") + me->query_skill("buddhism" ,1) / 2;
        dp = target->query_skill("parry") + target->query_skill("force");
		damage = ap / 2 + random(ap/2);


		msg += HIM "\n       ┏━━━━━┓\n"
               HIM"       ┃大闹阎罗府┃\n"
               HIM"       ┗━━━━━┛\n\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);            
        
		msg += HIR "\n       ┏━━━━━┓\n"
               HIR "       ┃勇斗二郎神┃\n"
               HIR "       ┗━━━━━┛\n\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);     
								   
		msg += HIY "\n       ┏━━━━━┓\n"
               HIY"       ┃千钧澄玉宇┃\n"
               HIY"       ┗━━━━━┛\n\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);     								   
					
        message_combatd(msg, me, target);
        me->start_busy(3 + random(4));
        return 1;
}


