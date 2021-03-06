// haishi.c 海市蜃楼

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int delta;
        int i, count;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/sanfen-jianshu/haishi"))
                return notify_fail("你不会使用「海市蜃楼」这一绝技！\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("「海市蜃楼」只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("sword", 1) < 350)
                return notify_fail("你的剑术修为不够，目前不能使用「海市蜃楼」！\n");

        if (me->query_skill("sanfen-jianshu", 1) < 350)
                return notify_fail("你的三分剑术的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("dodge") < 350)
                return notify_fail("你的轻功修为不够，无法使用「海市蜃楼」！\n");

        if ((int)me->query("dex") < 45)
                return notify_fail("你的身法太差，无法施展「海市蜃楼」！\n");
 
        if (me->query("neili") < 1000)
                return notify_fail("你的真气不够！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "狂喝一声，手中" + weapon->name() +
              HIW "将到之际，突然圈转，使出三分剑术的独得之秘"
              "「海市蜃楼」，一招之中\n又另蕴涵三招，招式繁复狠"
              "辣，剑招虚虚实实，霍霍剑光径直逼向$n"
              HIW "！\n\n" NOR;

        ap = me->query_skill("sword") + me->query_skill("force") + me->query_skill("dodge");
        dp = target->query_skill("dodge") + target->query_skill("parry");
        if (ap + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70,
                                           HIR "$n" HIR "完全无法辨清虚实，只感一阵触心的刺痛，一声惨叫，已被$N"
                                           HIR "凌厉的剑招刺中。\n" NOR);

                if (ap / 2 + random(ap) > dp)
                {
                        damage /= 2;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                                   HIR "\n$N" HIR "见$n" HIR "重创之下不禁破绽迭出，"
                                                   HIR "冷笑一声，手中" + weapon->name() +
                                                   HIR "挥洒，又攻出一剑，正中$p" HIR "胸口。\n" NOR);
                }

        } else
        {
                msg += HIC "$n" HIC "见状身形急退，避开了$N"
                       HIC "凌厉的攻击！\n" NOR;
        }

        message_combatd(msg, me, target);

        ap = me->query_skill("parry") + me->query_skill("force");
        dp = target->query_skill("force");

        msg = HBGRN "\n随后，$N" HBGRN "跃向空中，一招「"HBGRN"海市幻境" HBGRN"」，手中" 
                  + weapon->name() + HBGRN "狂舞，无数剑光洋洋洒洒的攻向$n" HBGRN "。\n" NOR;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "完全放弃了反击，"
                       "茫然之中东冲西撞，反而却被剑气划得鲜血淋漓。\n" NOR;
                count = ap / 8;
        } else
        {
                msg += HIC "$n" HIC "眼看剑气袭来，施出浑身解数"
                       "躲闪$N" HIC "发出的数道剑气。\n" NOR;
                count = ap / 20;
        }
        message_sort(msg, me, target);
        me->set_temp("perform_sanfenjian/lian", 1);
        count=me->query_skill("sword") / 6;
        me->add_temp("apply/attack", count);        
        for (i = 0; i < 6; i++)
	      {
		        if (! me->is_fighting(target))
			           break;
			      if (! target->is_busy() && random(2) == 1)
                       target->start_busy(1);
	        COMBAT_D->do_attack(me, target, weapon, 0);
	      }
        me->add_temp("apply/attack", -count);        
        me->delete_temp("perform_sanfenjian/lian");
        me->add("neili", -300 - random(300));
        me->start_busy(1 + random(2));

        return 1;
}