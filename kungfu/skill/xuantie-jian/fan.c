// updated by kasumi 2007/3/30
#include <ansi.h>
#include <combat.h>

#define FJDH "「" HIG "翻江倒海" NOR "」"
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;

        int ap, dp, p, damage, i, count;
        string wp, msg,str;
      

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FJDH "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" FJDH "。\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("你的内功火候不够，难以施展" FJDH "。\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 250)
                return notify_fail("你的玄铁剑法不够娴熟，难以施展" FJDH "。\n");

        if ((string)weapon->query("material") != "xuantie" && ! environment(me)->query("biwutai") )                                                            
                return notify_fail("只有用玄铁铸成的兵器才能使出" FJDH "。\n");         

        if ((int)me->query("neili") < 600)
                return notify_fail("你现在的内力不足，难以施展" FJDH "。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你没有激发玄铁剑法，难以施展" FJDH "。\n");                  
       
        
        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "突然闭目凝神，剑锋望天一指，转瞬间已经腾空而起，"
              "手中" + wp + HIW "\n顺势一挥，搅动得滚滚气浪如潮水般涌来"
              "，所施正是玄铁剑法「" HIG "翻江倒海" HIW "」。\n"NOR;


        ap = me->query_skill("sword") + me->query_str() * 5;
        dp = target->query_skill("dodge") + target->query_dex() * 5;
		
		damage = me->query_skill("sword") + me->query_skill("surge-force",1) + me->query_str()*2;
		damage = damage*2 + random(damage*2);
        
       
	    msg += YEL "\n$N忽然猛一吸气，全身内力汹涌彭湃而出压向$n。\n"NOR;
        msg += HIB "$n眼前已经是一片茫茫气浪，所有的景象都已经扭曲。\n"NOR;


        if (ap * 2/3 + random(ap) > dp)
        {
		     msg +=  HIR "结果$n" HIR "只觉得全身已被气流桎梏，再也无法应付这漫漫无边的剑雨气浪，口中鲜血狂喷而出。\n" NOR;
		     target->receive_wound("qi", damage, me);
			 str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));			
			 msg += "($n"+str+")\n";
             me->add("neili", -400);               
             count = ap /10;
		}
		else
		{  
		       msg += CYN "$n使出浑身解数勉力抵挡着$N的重重气浪，脸色愈来愈红。\n"NOR;
			   count = ap /14;
	    }
		message_combatd(msg, me, target);

        msg = HIY"\n$N手中" + wp + HIY"一闪，万丈光芒射向$n！\n"NOR;
        msg += HIC "初时似乎出手不重，但其波浪状的剑气后浪击前浪，一浪高过一浪，连绵不尽！\n"NOR;
        msg += HIR "～～～～～翻～～～江～～～倒～～～海～～～～～\n"NOR;
        message_combatd(msg, me, target);
          
        me->add_temp("apply/attack", count);
        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) == 1 && !target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(3 + random(4));
        msg = HIC "$N使完"NOR"" FJDH HIC"，周围的一切又恢复了平静！\n"NOR;
        message_combatd(msg, me, target);
        me->add_temp("apply/attack", -count);
                         
        return 1;

}



