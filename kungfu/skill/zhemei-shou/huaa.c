#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

#define HUA "「" HIR "化妖功" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp, p;
        int lv, cost_neili;

        if (userp(me) && ! me->query("can_perform/zhemei-shou/hua"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail(HUA "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUA "只能空手施展。\n");
                
        if (me->query("int") < 34)
                return notify_fail("你先天悟性不足，无法施展灵巧的终极绝招。\n");
                
        if ((int)me->query_skill("beiming-shengong", 1) < 250)
                return notify_fail("你的北冥神功火候不够，难以施展" HUA "。\n");

        if (lv = (int)me->query_skill("zhemei-shou", 1) < 250)
                return notify_fail("你逍遥折梅手等级不够，难以施展" HUA "。\n");

        if (me->query("max_neili") < 4500)
                return notify_fail("你的内力修为不足，难以施展" HUA "。\n");

        if (me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你没有激发北冥神功，难以施展" HUA "。\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("你没有激发逍遥折梅手，难以施展" HUA "。\n");

        if (me->query_skill_prepared("hand") != "zhemei-shou")
                return notify_fail("你没有准备逍遥折梅手，难以施展" HUA "。\n");

        if (me->query("neili") < 500)
                return notify_fail("你现在真气不足，难以施展" HUA "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY"                       真   *   化       妖        功!!!!!!!!!!\n\n"HIM "$N" HIM "深深吸进一口气，将北冥神功运至极限,单手挥出，掌缘顿时霞光万道，漾出"
              "七色虹彩向$n" HIM "席卷而至。\n\n" NOR;

        ap = me->query_skill("dodge", 1) + me->query_skill("hand")+me->query_skill("beiming-shengong",1);
        dp = target->query_skill("dodge", 1) + target->query_skill("parry")+target->query_skill("martial-cognize",1);

        if (target->is_bad() || ! userp(target))
                ap += ap / 10;

        if (ap * 2 / 3 + random(ap) + random(20) > dp)
        {
                damage = 0;
                lv = me->query_skill("zhemei-shou", 1);
                if (lv >= 220)cost_neili = -250;
                if (lv >= 260)cost_neili = -220;
                if (lv >= 300)cost_neili = -190;
                if (lv >= 360)cost_neili = -160;
                
                if ( me->query("max_neili") > target->query("max_neili") * 2
                     && me->query("neili") > 500 )
                {
                        msg += HIM "只听$n" HIM "一声尖啸，$N" HIM "的七色掌"
                               "劲已尽数注入$p" HIM "体内，顿时将$p" HIM "化"
                               "为一滩血水。\n" NOR "( $n" RED "受伤过重，已"
                               "经有如风中残烛，随时都可能断气。" NOR ")\n";
                        damage = -1;
                        me->add("neili", cost_neili);
                        me->start_busy(3);
                } else
                {
                        damage = ap;
                        damage += me->query_temp("apply/unarmed_damage");
                        damage += random(damage);

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage / 2, me);
                        target->receive_damage("jing", damage / 4, me);
                        target->receive_wound("jing", damage / 8, me);
                        p = (int)target->query("qi") * 100 / (int)target->query("max_qi");

                        msg += HIM "$n" HIM "只是微微一愣，$N" HIM "的七色掌劲已破体而"
                               "入，$p" HIM "便犹如身置洪炉一般，连呕数口鲜血。\n\n" NOR;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        
                                     
                        
                        me->add("neili", cost_neili);
                        me->start_busy(3);
                }
        } else
        {
                msg += CYN "$p" CYN "见状大惊失色，完全勘破不透$P"
                       CYN "招中奥秘，当即飞身跃起丈许，躲闪开来。\n" NOR;
                me->add("neili", -200);
                me->start_busy(4);
        }
       
       msg +=HIY"$N连连崔动北冥神功,脸上寒光四射!突然五指连拂,点向$n\n\n"NOR;
       
       
        if (ap * 2 / 3 + random(2*ap) > dp)          
              {          
                    damage=ap+me->query_skill("beiming-shengong",1)*2;
                    
	                   me->add("neili", -200);
        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                   HIG "只听“扑哧”一连五声，$N" HIG "五指正点在$n" HIG "身上的要穴上，$n"
                                   HIG "一声惨叫，血射五步。\n"  NOR);    
        
      } else
      	
      	  {
                msg += CYN "$p" CYN "见状不慌不忙，看破了$N$P"
                       CYN "招中奥秘，当即飞身跃起丈许，躲闪开来。\n" NOR;
                me->add("neili", -200);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        if (damage < 0)
        {      //  target->die(me);
            target->set("eff_qi", -1);
            target->set("eff_jing", -1);
        }
        return 1;
}
