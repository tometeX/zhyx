#include <ansi.h>
#include <combat.h>

#define ZHENWU "「" HIY "真武除邪" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);
string final2(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/taiji-jian/zhenwu"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHENWU "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" ZHENWU "。\n");

        if ((int)me->query_skill("taiji-jian", 1) < 180)
                return notify_fail("你的太极剑法不够娴熟，难以施展" ZHENWU "。\n");

        if (me->query("neili") < 200)
                return notify_fail("你现在真气不够，难以施展" ZHENWU "。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian") 
                return notify_fail("你没有激发太极剑法，难以施展" ZHENWU "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        
msg = HIG "$N" HIG "跨前一步，平平挥出一剑，横扫$n" HIG "而去，毫"
              "无半点花巧可言。\n" NOR;
        
        ap = me->query_skill("sword")+(int)me->query_skill("taoism", 1)*2/3;
        dp = target->query_skill("parry");
        if (target->is_bad()) ap += ap / 8;
		damage = ap*2 + random(ap*2);

		if (me->query_skill_mapped("force") == "taiji-shengong")
		{
			me->add("neili", -100);
			damage+=(int)me->query_skill("taiji-shengong", 1);
		}
		else
		{
			me->add("neili", -50);			
		}

        me->start_busy(3);
        if (ap * 2 / 3 + random(ap) > dp)
        {
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
                                           (: final, me, target, damage :));
        } else
        { msg += HIC "可是$n" HIC "看透$P" HIC "招后更有杀着，镇"
                      "定逾恒，全神应对自如。\n" NOR; 
                      
        	if (ap * 3 / 4 + random(ap) > dp)
             {msg += HIW "$N" HIW "退后一步，再出一剑，横扫$n" HIW "而去，毫"
              "无半点花巧可言。\n" NOR;
            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           (: final, me, target, damage :));
             } 
                 
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("qi", damage / 2, me);
        target->receive_wound("qi", damage / 3, me);
        return  HIY "结果$n" HIY "却丝毫未把这招放在眼里，随手应了一招，却见$N"
                HIY "剑势\n忽然一变，气象万千，变幻无穷，极具王者风范！\n" NOR +
                HIR "$n" HIR "顿时惊慌失措，被$P" HIR "这一剑击中要害，鲜血崩流"
                "，惨不忍睹！\n" NOR;
}
