//By baqukq for 2004.08.28

#include <ansi.h>
#include <combat.h>
#define SHA "「" HIR "晴天无悔" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, number, *limbs;
        string ba;
        int ap, dp, a, b, i, lmt;
        int damage, extra, skill, forcee;
        int count, times;
        int lvl, num;
 
 
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/baqukq-sword/sha"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" SHA "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的内功修为不够，难以施展" SHA "。\n");

        if (me->query_skill("baqukq-sword", 1) < 180)
                return notify_fail("你的晴天剑法修为不够，难以施展" SHA "。\n");

        if (me->query_skill_mapped("sword") != "baqukq-sword")
                return notify_fail("你没有激发晴天剑法，难以施展" SHA "。\n");

        if (me->query("neili") < 500)
                return notify_fail("你的真气不够，难以施展" SHA "。\n");

        /*if (! me->query("aaaa"))
                return notify_fail("你学都没学，怎么施展" SHA "。\n");*/

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        a = me->query("aaaa");
        b = random(a);
//第一招 剑伤       
        if (b == 0)
         {
         msg = HIR "$N" HIR "凝神沉履，积聚全身功力于剑，携着雷霆之势奋力向$n"
              HIR "胸前夺去。\n" NOR;

        if (random(me->query_skill("sword")) > target->query_skill("parry") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("sword");
                damage = damage / 2 + random(damage);
                me->add("neili", -250);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "结果$p" HIR "招架不及，被$P" HIR
                                           "一剑刺在胸口，接连刺断了数根肋骨，喷出"
                                           "一大口鲜血！\n" NOR);
        } else
        {
                me->start_busy(3);
                me->add("neili", -100);
                msg += CYN "可是$p" CYN "奋力招架，不露半点破绽，将$P"
                       CYN "这一招驱之于无形。\n" NOR;
        }
        message_combatd(msg, me, target);
        	
         return 0;	
}
//第二招 十三剑
        if (b == 1)
         {
        extra = me->query_skill("baqukq-sword",1);
        msg = HIR  "$N轻描淡写，挥尘如意，一瞬间就已使出夺命十三式，手中的"+ weapon->name()+  NOR+HIR"轻灵流动.\n就像是河水般的向$n刺出,天地间彷佛充满了杀气！\n\n" NOR;
        message_vision(msg,me,target);
	me->add_temp("apply/attack",extra/10);
	me->add_temp("apply/damage",extra/10);
	lmt = random(13)+1;
	for(i=1;i<=lmt;i++)
	{
        message_vision(BLINK HIR"------>>>>>>第"HIC+chinese_number(i)+HIR"剑<<<<<<------"NOR,me,target);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
	}
        msg = CYN "\n\n$N的第"+chinese_number(i-1)+"剑刺出后，所有的变化都已穷尽，又像是流水已到尽头，剑势也慢了，很慢。\n\n"NOR;
	message_vision(msg,me,target);
        me->add_temp("apply/attack",-extra/10);
        me->add_temp("apply/damage",-extra/10);
	me->start_busy(2);

        return 0;
}
//第三招 破内力
        if (b == 2)
         {
        skill = me->query("neili");
        forcee = target->query("neili")/5-50;
        if (forcee < 50) forcee = 50;
        me->add("neili", -400);

        me->start_busy(random(3));
	message_vision(HIR "\n$N飞身而上，屏气凝神，手个宝剑对天一指，引动出九天灵气归于己用！\n顿时天昏地暗，日月无光，天地颠倒！\n好一招灭绝众生的「倒转乾坤」！\n\n"
        NOR, me);
        if( skill +random(skill) > target->query("max_neili"))
        {
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));


        lvl = me->query("eff_qi")/(3+random(4));
	me->receive_damage("qi", 50);
//        lvl->receive_damage("qi",lvl,me,"perform"); 
//        target->receive_wound("qi", lvl,me,"perform");
	target->add("neili",-(forcee));
	me->add("neili", -100);
	message_vision(HIW"$n翻倒在地。受伤严重，全身内力顿失！\n"NOR,me, target);
	target->start_busy(1);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
         }
         }
         else 	message_vision(HIY"可是$p看破了$P的企图，并没有上当。\n" NOR, me, target);

        return 0;
}
//第四招
        if (b == 3)
         {
        msg = HIR "$N" HIR "仰天清啸，手中" + weapon->name() +
              HIR "斜划出一道半弧，整个剑身顿时腾起凛冽无比的"
              "杀气，直贯$n" HIR "而去！\n" NOR;

        ap = me->query_skill("sword") + me->query_str() * 10;
        dp = target->query_skill("force") + target->query_con() * 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                me->add("neili", -200);
//                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "只听$n" HIR "一声惨叫，$N" HIR +
                                           weapon->name() + HIR "剑锋一闪，竟已嵌"
                                           "入$p" HIR "体内尺许，带出一蓬血雨。\n"
                                           NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(4);
                msg += CYN "$n" CYN "见$P" CYN "来势汹涌，不敢轻易抵"
                       "挡，连忙飞身腾挪，躲闪开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 0;
}
//第五招
        if (b == 4)
         {
        skill = (int)me->query_skill("baqukq-sword", 1);
        if(skill < 60)
                return notify_fail("你的晴天剑法级别还不够。\n");
        else 
            if(skill <60){
                times = 1;        
                number = "一";}
            else
                if (skill <80){
                    times = 2;
                    number = "二";}
                else
                    if(skill <120 ){
                           times = 3;
                           number = "三";}
                else
                    if(skill <160 ){
                           times = 4;
                           number = "四";}
                else
                    if(skill <200 ){
                           times = 5;
                           number = "五";}
                     else{ 
                           times = 6;
                           number = "六";}

        me->delete("env/brief_message");
        target->delete("env/brief_message");
        damage = random((int)me->query_skill("sword")/3);

       message_vision(HIM"\n$N突然剑招一变，手中的"+ weapon->query("name")+ HIB"无影无踪，浑身喷薄出凌厉的剑气。闪电般向$n攻出了"+number+"剑！\n"NOR,me,target, "");

        for(int q=1;q<=times;q++)
        COMBAT_D->do_attack(me, target, weapon);
        COMBAT_D->report_status(target, 0);
        me->receive_damage("jing", 20,target);
        me->add("neili", -(times*30+10));

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }
        if(me->is_fighting() && target->is_fighting() &&
        environment(me) == environment(target) && times>5)
        {

        target->receive_damege("jing", damage,me,"pfm");
        target->receive_wound("jing", random(damage),me,"pfm");
        target->receive_damege("qi", damage+1,me,"pfm");
        target->receive_wound("qi", random(damage),me,"pfm");
        message_vision(HIR"\n结果$n被$N的『晴天』剑气穿心，眼前一黑，身子向后飞出丈许！！\n\n $n身上剑痕鲜血涌出......\n" NOR,me,target,"");
                COMBAT_D->report_status(target, 0);
        }
        me->start_busy(1+random(2));
        me->set_temp("sky_end",time());

        return 0;
}
//第六招
        if (b == 6)
         {
        me->add("neili", -60);
        msg = WHT"使出最后一招〖兽变〗！虎！虎！虎！虎！虎！虎！虎！虎！虎！虎！虎！虎！\n"NOR;
        message_combatd(msg,me,target,"");
        me->start_busy(1+random(1));

        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/8 ) 
        {
                        
                limbs=target->query("limbs");                   
                lvl=(int)(me->query_skill("baqukq-sword")/5);
                damage=random(lvl)+lvl;
                damage=damage+me->query_str()+random(me->query_temp("apply/damage"));
                num=random(lvl/2)+lvl/2;
                for(i=0;i<=num;i++)
                {
                        msg =HIR"$N突然变成一只白虎咬向$p"+limbs[random(sizeof(limbs))]+"！\n"NOR;
                        message_combatd(msg,me,target,"");
                   target->receive_damage("qi",damage,me,"pfm");
                   target->receive_wound("qi",damage,me,"pfm");
                   
                }
                COMBAT_D->report_status(target);
                
        }

        return 0;
}
        if (b == 5)
         {
        msg = HIC "$N大喝一声，全场四处游动，$n只看到$N化做数团身影，漫天剑光席卷而来，\n $n奋力一架，但$N剑分数路，$n只架住一剑！\n"NOR;
    if (random(me->query_skill("force")) > target->query_skill("force")/3||
   random((int)target->query("combat_exp")) < (me->query("combat_exp")) )
    {
   //me->start_busy(2);
  // target->start_busy(random(3));
   damage = (int)me->query_skill("baqukq-sword", 1);
   damage = damage + random(damage);
   target->receive_damage("qi", damage);
   target->receive_wound("qi", damage/3);
   target->add("eff_qi", -damage);
   target->receive_damage("jing", damage);
   target->add("eff_jing", -damage);
   msg += HIC"$n根本没法躲避，顿时几剑都夺在$n肩头！\n"+HIR"$n鲜血溅起，$n自觉眼前一片鲜红，遮住视线！\n"NOR;
   me->add("neili", -damage/5);
     me->start_busy(random(3));
   if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
                                  } 
    }else
    {
   me->start_busy(2);
   msg += HIY"可是$p早以看出那是虚招，毫不在意地坦然面对，果真只有架住的是实招。\n"NOR;
    }
    message_vision(msg, me, target);

        return 1;
}
        return 1;

}
