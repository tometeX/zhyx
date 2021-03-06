//考虑到特防，命中并不高
//攻击命中均有提高
//buy gentl
//update 2012.11.29

#include <ansi.h>
#include <combat.h>

#define BAGUA "「" HIY "八卦" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg, wp;
        int skill;        
        int damage;       
        int ap, dp , p, str, cp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BAGUA "只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你所使用的武器不对，难以施展" BAGUA "。\n");

        if ((int)me->query_skill("bagua-dao", 1) < 350)
                return notify_fail("你的八卦刀法不够娴熟，难以施展" BAGUA "。\n");

        if ((int)me->query_skill("wai-bagua", 1) < 350)
                return notify_fail("你的外八卦神功不够娴熟，难以施展" BAGUA "。\n");

        if ((int)me->query_skill("nei-bagua", 1) < 350)
                return notify_fail("你的内八卦神功不够娴熟，难以施展" BAGUA "。\n");

        if (me->query_skill_mapped("force") != "nei-bagua")
                return notify_fail("你没有激发内八卦神功，难以施展" BAGUA "。\n");

        if (me->query_skill_mapped("parry") != "wai-bagua")
                return notify_fail("你没有激发外八卦神功，难以施展" BAGUA "。\n");

        if ((int)me->query("max_neili") < 6000)
                return notify_fail("你的内功修为不足，难以施展" BAGUA "。\n");

        if ((int)me->query("neili") < 1200)
                return notify_fail("你现在真气不够，难以施展" BAGUA "。\n");

        if (me->query_skill_mapped("blade") != "bagua-dao")
                return notify_fail("你没有激发八卦刀法，难以施展" BAGUA "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "蓦地一振手中" + weapon->name() +  HIY "，发出万千龙吟，霎时刀光滚滚，向四面涌出，笼罩$n" HIY "全身。\n\n" NOR;
        ap = me->query_skill("bagua-dao", 1) + me->query_skill("nei-bagua", 1) + me->query_skill("wai-bagua", 1);
        dp = target->query_skill("parry", 1) + target->query_skill("force", 1) + target->query_skill("dodge", 1);
        cp = me->query_skill("bagua-bu", 1) + me->query_skill("bagua-quan", 1) + me->query_skill("bagua-zhang", 1);
        ap += cp/6;		
        damage = ap / 2 + random(ap/2);
		
		        me->add("neili", -600);
		
// 第一招
        msg += HIM "『乾』字诀．．．．．．．．．．【奇门八卦】\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           GRN"$N口中念道：乾生天，坤生地，八卦无形，周转复始。\n"
                                           GRN"$n只觉得四周有无形之力向自己压来，身形顿时慢了下来。\n" NOR);
        } else
        {
                msg += CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }

        msg += HIC "\n『坤』字诀．．．．．．．．．．【神勇无敌】\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           GRN"$N一刀比一刀快，当真是有万夫莫敌之气势，\n"
                                           "将八卦刀发挥得淋漓尽致，直朝着$n而去。\n" NOR);
        } else
        {
                msg += CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }

        msg += HIW "\n『巽』字诀．．．．．．．．．．【横刀立马】\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                          GRN"$N将手中" + weapon->name() + GRN"斜斜举起，向$n劈去．只见"+ weapon->name() + GRN"折射着落日的余晖，\n"
                                           "朝着$n卷去,$n慑于$N的气势，顿时脑子一边空白。\n" NOR);
        } else
        {
                msg += CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }

        msg += HIG "\n『震』字诀．．．．．．．．．．【百战百胜】\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           "$N刀指苍穹，大吼一声，携百战百胜之势杀向$n。\n"
                                           "$n被你强大的战意所制，只觉神志一阵迷糊。\n" NOR);
        } else
        {
                msg += CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }

        msg += HIY "\n『坎』字诀．．．．．．．．．．【四海平生】\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           "$N手使八卦刀，脚踏八卦步，顿时好似有无数个$N攻向$n。\n" 
                                            "$n只觉眼花缭乱，根本分不清哪个是真身，惨叫一声，已身中数刀。\n" NOR);
        } else
        {
                msg += CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }

        msg += HIR "\n『兑』字诀．．．．．．．．．．【百步穿杨】\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           GRN"$N一声长啸，凝运八卦神功，"+ weapon->name() + GRN"陡然发出一道刀芒，破空飞向$n。\n"
                                           "只听$n一声惨叫，已被刀芒划过丹田。\n"NOR);
        } else
        {
                msg += CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }
// 最后两招需要高悟性
     if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("bagua-dao", 1) > 499 
     	    && (int)me->query_skill("nei-bagua", 1) > 499 && me->query("int") > 35)
      {           
	              me->add("neili", -600);
				  
                  ap += cp/6;		      
                  damage += cp/2;

          msg += CYN "\n『离』字诀．．．．．．．．．．【力劈山河】\n" NOR;

        if (ap + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           GRN"$N用八卦神功运转"+ weapon->name() + GRN"，刀式大开大阖，攻向$n。\n" 
                                            "$n受不了此攻击，只觉底烦躁不已，无法运功相抗，元气大损。\n" NOR);
        } else
        {
                msg += CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }

        msg += WHT "\n『艮』字诀．．．．．．．．．．【横扫千军】\n" NOR;
        if (ap + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           GRN"你举起" + weapon->name() + GRN"，以雷霆万钧之势向$n砸去，这招刀法看似大拙，实则大巧，\n"
                                           "尽显刀中狂霸之本色。$n在漫天刀风中飘零，顿时不知所措，受伤颇重。\n" NOR);
        } else
        {
                msg += CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }
      }

///后续还有八卦合一，暂时没写。



        me->start_busy(3 + random(3));
        message_combatd(msg, me, target);
        return 1;

}

