// 稍微增加了威力
//负神越高，攻击越高。说攻击低的同学请加加负神
//2亿负神封顶
// buy gentl
//update 2012.11.29

#include <ansi.h>
#include <combat.h>

#define MOQI "「" HIR "魔气血杀" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping prepare;
        string msg, wp;
        int skill, ski_value;        
        int damage;       
        int ap, dp, p, str, amount, jj;
        object weapon;


        skill = me->query_skill("xuedao-dafa", 1);

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(""MOQI" 只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你所使用的武器不对，难以施展" MOQI "。\n");
  
        if( me->query_skill("xuedao-dafa", 1) < 400 )
                return notify_fail("你的血刀大法功力不足。 \n");

        if( me->query_skill("force", 1) < 400 )
                return notify_fail("你的内功不够好。 \n");
        
        if(me->query("neili") < 1000)
                return notify_fail("你的内力不够。\n");
        
        if (me->query_skill_mapped("force") != "xuedao-dafa") 
                return notify_fail("你现在没有激发血刀大法为内功，难以施展"MOQI"。\n"); 

        if (me->query_skill_mapped("blade") != "xuedao-dafa")
                return notify_fail("你没有激发刀法为血刀大法，难以施展" MOQI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


        msg = HIR "$N" HIR "左手猛力一拍胸膛，顿时一股鲜血喷在" + weapon->name() + HIR"上，只见一片血光"HIR "裹住刀影向$n" HIR "当头劈落。\n" NOR;

        ap = me->query_skill("blade")+me->query_skill("force")+me->query_skill("dodge")+me->query_skill("parry");
        dp = target->query_skill("force") + target->query_skill("parry") + target->query_skill("dodge");     
        ski_value=0;
        ski_value=(int)me->query("shen") / -8000000;
        if (ski_value<=0) ski_value=1;
        if (ski_value>10) ski_value=10;
        damage = 600 + skill * ski_value / 4;
        amount = ski_value * 50;
        ap += amount;
        me->add_temp("apply/damage", amount);
       

       

       // 第一招
	    msg += HBWHT "\n「魔魇懵懵」\n" NOR ; 
       
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "血雾中，" HIR"$N的身影突然出现，" + weapon->name() + HIR "已在$n的腰间对穿而出，鲜血溅得满地！ \n" NOR);
        } else
        {
                msg += CYN "可是$n" CYN "侧身避让，不慌不忙，躲过了$N"
                       CYN "的必杀一刀。\n"NOR;
        }

        // 第二招

	    msg += HBYEL "\n「魔心穹隆」\n"NOR; 
       
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "血雾中，" + weapon->name() + HIR "疾闪，鲜血飞溅，$n" HIR"只觉眼前一阵血红，不禁惨声大嚎！\n" NOR);

        } else
        {
                msg += CYN "$n" CYN "使出浑身解数，终于将$N"
                       CYN "这一刀躲开，丝毫无损。\n" NOR;
        }

        //// 第三招

	    msg += HBGRN "\n「魔光旖旎」 \n"NOR; 
       
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "血雾中，" + weapon->name() + HIR "疾闪，鲜血飞溅，$n" HIR"只觉眼前一阵血红，不禁惨声大嚎！\n" NOR);

        } else
        {
                msg += CYN "可是$n" CYN "侧身避让，不慌不忙，躲过了$N"
                       CYN "的必杀一刀。\n"NOR;
        }

        //// 第四招

	    msg += HBCYN "\n「魔冲霄汉」\n"NOR; 
       
		 if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                          HIR "只见溅满鲜血、泛着血光的刀身却又仿佛化成一片血海，笼罩住" HIR"$n的身影。\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "使出浑身解数，终于将$N"
                       CYN "这一刀躲开，丝毫无损。\n" NOR;
        }
      
          


if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("xuedao-dafa", 1) > 499 && !userp(target))    //修改1499为499，请确认。
        	 {
                    ap = me->query_skill("blade");
                    dp = target->query_skill("force"); 
					ap += amount;

        msg += HIY "\n紧接着$N自残己身，以血气转换成杀气。\n
            ……$N身上发出一股强大的杀气……\n
    ■$N身上杀气逐渐地聚集,在" + weapon->name() + HIY "上形成团魔气■\n
            $N倏地大喝一声－－魔 气 血 杀－－\n\n" NOR;
			
		target->receive_damage("qi", amount, me);	//保底伤害最高500

        
        if( ap * 2 / 3 + random(ap) > dp)  
        {
                msg += HIR  "$N突然喉头一动～～　只见$N口中喷出一道血柱往$n射去～～\n
此乃血刀大法之
            最终杀招 『魔 血 气 杀』\n\n
$n遭到前所未有的打击,但$N也受伤不轻。\n" NOR;

                damage = 600 + skill * ski_value;
                damage += random(damage/2);
                
                target->start_busy(5 + random(ski_value));
                target->receive_damage("qi", damage, me);
				target->receive_wound("qi", damage/2, me);
                me->receive_wound("qi", me->query("qi")* 1 /100);
        }
        else if( random(3) > 2 )
        {
                msg += HIR BLINK"$N真气所转换的杀气不够大,对敌人毫无影响。\n" NOR;
                me->receive_wound("qi", me->query("qi")*1/100);
        }
        else
        {
                msg += HIR BLINK"$n受到强大的杀气伤害，动弹不得。\n" NOR;
                me->receive_wound("qi", me->query("qi")* 1 /100);
                target->receive_damage("qi", (int)me->query_skill("xuedao-dafa", 1), me);
                target->start_busy(3 + random(ski_value));
        }
           }   

	    message_combatd(msg, me, target);
	    me->add("neili", -ski_value * 500);
          me->add_temp("apply/damage", -amount);
          me->start_busy(3 + random(4));

        return 1;
}

