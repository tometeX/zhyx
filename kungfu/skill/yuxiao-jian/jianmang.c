// Code of JHSH
// jianmang.c

/*
卓不凡第二击不中，五分惊讶之外，更增了五分惧怕，身子滴溜溜的打了半个
圈子，长剑一挺，剑尖上突然生出半尺吞吐不定的青芒。群众中有十余人齐声
惊呼：“剑芒，剑芒！”那剑芒犹似长蛇般伸缩不定，卓不凡脸露狞笑，丹田
中提一口真气，青芒突盛，向虚竹胸口刺来。

虚竹从未见过别人的兵刃上能生出青芒，听得群豪呼喝，料想是一门厉害武功，
自己定然对付不了，脚步一错，滑了开去。卓不凡这一剑出了全力，中途无法
变招，刷的一声响，长剑刺入了大石柱中，深入尺许。这根石柱乃极坚硬的花
岗石所制，软身的长剑居然刺入一尺有余，可见他附在剑刃上的真力实是非同
小可，

Maco备注：
剑芒此一perform，本来出处不属桃花岛。然而Kane造出此code，长久以来也
被认定为玉箫剑法标准perform，Maco在此便将错就错，依着前人脚步略加拓
展code变化性，增加些许趣味。

双重剑芒作用，在於将剩余的剑芒有效时间一次用光，合为一剑，威力大幅提
高，然而剑芒效果立刻结束，普通剑也会立刻断裂，这是和平常相同的。剩余
时间越长，威力越大，可说是使尽剑芒余力的一击。

又，“剑意”高低，影响双重剑芒威力至钜。
*/

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
void checking(object me, object weapon,int damage);
void remove_effect1(object me, object weapon, int damage) ;

int perform(object me, object target)
{
        object weapon;
        int i, damage, sword, jianyi;

        weapon = me->query_temp("weapon");
                
        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("剑芒只能对战斗中的对手使用。\n");

        jianyi = (int)me->query("tianmo_jieti/times");
        if (jianyi > 8) jianyi = 8;

        if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
                return notify_fail("你手中无剑，怎能运用「剑芒」？！\n");

        if( me->query_temp("th_jianmang") )
        {
                if( jianyi < 1 )
                        return notify_fail("以你对剑意的领悟，剑芒施展至当下威力，已是极限！\n");
        }

        if( me->query_temp("th_wait_jianmang") && !me->query_temp("th_jianmang") )
                return notify_fail("你气血翻涌，无法运用「剑芒」！\n");

        if( me->query_temp("th_jianzhi") )
                return notify_fail("你正在运用剑指相配的攻势，不能分心运用「剑芒」！\n");

        if( me->query_skill("yuxiao-jian",1) < 200 )
                return notify_fail("你玉箫剑法修为还不够，还未领悟「剑芒」！\n");

        if( me->query_skill("bibo-shengong", 1) < 150 )
                return notify_fail("你的碧波神功修为火候未到，施展剑芒只会伤及自身！\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你所用的内功无法施展玉箫剑法的「剑芒」！\n");

        if( me->query("max_neili") <= 1200 )
                return notify_fail("你的内力修为不足，劲力不足以施展剑芒！\n");

        if( me->query("neili") <= 600 )
                return notify_fail("你的内力不够，劲力不足以施展剑芒！\n");

        if( me->query("jingli") <= 200 )
                return notify_fail("你的精力有限，不足以施展剑芒！\n");

        sword = me->query_skill("yuxiao-jian",1)/10;
        damage = me->query_skill("force") + me->query_skill("qimen-wuxing",1);
        damage = damage/5;

        if(me->query_temp("th_jianmang")) {
                me->add("neili", -150);
                me->add("jingli", -50);
                me->set_temp("final_jianmang", 1); 
                for (i =0;i < jianyi*2;i++)
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
                me->delete_temp("final_jianmang"); 
                me->delete_temp("th_jianmang"); 
                me->start_busy(1);
                checking(me, weapon, damage);
        }
        else {
                me->add("neili", -300);
                me->add("jingli", -100);
                me->add_temp("th_jianmang", sword/3); 
                me->set_temp("th_wait_jianmang", 1);
                me->add_temp("apply/defense",damage); 
                me->add_temp("apply/damage", damage);
                me->add_temp("apply/attack", damage);
                me->start_busy(1);

                message_vision(HIC
                        "$N傲身长笑，手中"+NOR+weapon->name()+HIG"渐渐变成惨碧半透明色，\n"+
                        "一团青碧色豪芒从剑柄处直游至剑尖 ......\n"+NOR+
                        weapon->name()+NOR+HIC"前端蓦地伸出三尺"+HIG"剑芒"NOR+
                        HIC"，忽伸忽缩，吞吐不定，看上去诡异绝伦！！！\n"NOR, 
                me);
                call_out("checking", 1, me, weapon, damage);
                call_out("remove_effect2", sword*2/3, me);
        }
        return 1;
}

void checking(object me, object weapon, int damage)
{
        if (!me) return;
        me->add_temp("th_jianmang", -1);
         
        if( !living(me) || me->is_ghost() )
        {
                remove_effect1(me, weapon, damage);
                return ;
        }
        if( !me->is_fighting() )
        {
                message_vision("\n$N见战局已毕，便即收起了催动剑芒的内力。\n", me);
                remove_effect1(me, weapon, damage);
                return ;
        }
        else if( !weapon || environment(weapon) != me || weapon != me->query_temp("weapon") )
        {
                message_vision("\n$N手中兵器已失，剑芒真力随之瓦解。\n"NOR, me);
                remove_effect1(me, weapon, damage);
                return ;
        }
        else if( me->query_skill_mapped("sword") != "yuxiao-jian"
         || me->query_skill_mapped("force") != "bibo-shengong" )
        {
                remove_effect1(me, weapon, damage);
                message_vision(HIG"\n$N武功路数陡变，"+
                        weapon->name()+HIG"上青芒消逝。\n"NOR, me);
                return ;
        }
        else if( me->query_temp("th_jianmang") <= 0 )
        {
                tell_object(me,HIG"\n剑芒威力已到极限！\n"NOR);
                remove_effect1(me, weapon, damage);
                return; 
        }
        else call_out("checking", 1, me, weapon,damage);
        
        if (random(2))
                message_vision(HIG"$N的"NOR+"$n"+NOR+HIG"顶端青色剑芒忽长忽短，闪烁不定....\n"NOR,me,me->query_temp("weapon"));
        return;
}

void remove_effect1(object me, object weapon, int damage) 
{
        if (!me) return;
        me->add_temp("apply/defense",-damage); 
        me->add_temp("apply/damage", -damage);
        me->add_temp("apply/attack", -damage);
        me->delete_temp("th_jianmang");

        if (!weapon) return;

        if( environment(weapon) != me || weapon != me->query_temp("weapon") )
                return;
        else if (weapon->query("weapon_prop/damage") < 40) {
                message_vision(HIW"\n只听得一声清响，$N手中"+weapon->name()+
                        HIW"经不住内力冲击，已裂成碎片！！\n"NOR,me);
                destruct(weapon);
        }
        else {
                message_vision(HIY"\n$N手中"+weapon->name()+HIY+
                        "“咯”的一声轻响，附在剑上的青芒已消失得无影无踪。\n"NOR, me);
        }
}

void remove_effect2(object me)
{
        if (!me) return;
        me->delete_temp("th_jianmang");
        me->delete_temp("th_wait_jianmang");
        tell_object(me, HIG"\n你经过一段时间调气养息，经脉气血已运转如常。\n"NOR); 
}
