 // 修罗降世 xiuluo.c

#include <ansi.h>
inherit F_SSERVER;
#include <weapon.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>


#define XIULUO "「" HIY "修罗降世" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
      object weapon;
      int damage;
      int i, jiali;
      string msg;

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



        me->add("neili", -500);
        msg =HIR "突然" HIR "$N" HIR "双掌搓了几搓，只听得嗤嗤声响，「火焰刀」在" HIR "$N" HIR "极强内劲的斗然冲击之下\n"
             HIR "威势大盛，激射而出的无形刀气组成了一片刀网，宛如修罗降世，向着" HIR "$n" HIR "直劈而下! \n" NOR;

        i = me->query_skill("force") / 4;
        jiali = me->query("jiali");
	damage = i  + random(i/2);


        msg += BBLU"\n\n～～～～～           刀山火海！           ～～～～～ \n\n"NOR;
        msg += COMBAT_D->do_damage(me,target,msg, WEAPON_ATTACK, damage, 50,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);    


        msg += BRED"   ～～～～～        无尽炼狱！        ～～～～～\n\n"NOR;
        msg += COMBAT_D->do_damage(me,target,msg, WEAPON_ATTACK, damage, 50,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);


        msg += BMAG"       ～～～～～     四方俱灭！     ～～～～～\n\n"NOR;
        msg += COMBAT_D->do_damage(me,target,msg, WEAPON_ATTACK, damage, 50,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);


        message_combatd(msg, me, target);
        me->start_busy(1+random(6));
        return 1;
}

