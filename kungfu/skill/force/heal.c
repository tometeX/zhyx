// heal.c
// modified by roland 2004

#include <ansi.h>

int exercising(object me);
int halt_exercise(object me);

int exert(object me, object target)
{
        string force;
                mapping msg; 
        //int recover_points;

        if (me->is_fighting())
                return notify_fail("战斗中运功疗伤？找死吗？\n");

        if (me->is_busy())
                return notify_fail("等你忙完了手头的事情再说！\n");

        force = me->query_skill_mapped("force");
        if (! stringp(force))
                return notify_fail("先激发你的特殊内功。\n");

        if ((int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("你现在气血充盈，不需要疗伤。\n");

        if ((int)me->query_skill(force, 1) < 20)
                return notify_fail("你的" + to_chinese(force) + "修为还不够。\n");

        if ((int)me->query("neili") < 50)
                return notify_fail("你的真气不够。\n");

        if (!me->query("special_skill/divine") && (int)me->query("eff_qi") < (int)me->query("max_qi") / 5)
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");
/*
        message_vision(HIW "$N" HIW "全身放松，坐下来开始运功疗伤。\n"
                       HIY "$N" HIY "吐出一口瘀血，脸色看起来好多了。\n" NOR,
                       me);

        recover_points = 10 + (int)me->query_skill("force") / 3;
        if (me->query("breakup"))
                recover_points *= 3;
        me->receive_curing("qi", recover_points);
        me->add("neili", -50);
        me->start_busy(1);
*/
        msg = SKILL_D(force)->exercise_msg(me);
    if (!msg || undefinedp(msg["heal_msg"]))
                message_vision(HIW"$N盘膝坐下，开始运功疗伤。\n"NOR,me);
    else message_vision(msg["heal_msg"],me);

        me->set_temp("pending/heal", 1);
        me->set_temp("period", 1);
        me->start_busy((: exercising :), (:halt_exercise:));
        return 1;

}

int exercising(object me)
{
        int period = me->query_temp("period");
        int recover_points;
        int eff = me->query("eff_qi");
        int max = me->query("max_qi");
        string force;
        mapping msg;

        if (!living(me) || !(force = me->query_skill_mapped("force"))) {
                me->delete_temp("pending/heal");
                me->delete_temp("period");
                return 0;
        }
        
        if( eff >= max ){
                tell_object(me, "良久，你感觉通过自己的内息运行，身上的伤势已经全好了。\n");
                if (!msg || undefinedp(msg["heal_finish_msg"]))
                        message_vision(HIY"$N运功完毕，吐出一口瘀血，脸色看起来好多了。\n"NOR,me);
                else message_vision(msg["heal_finish_msg"],me);
                me->delete_temp("pending/heal");
                me->delete_temp("period");
                return 0;
        }

        if( me->query("neili") < 50 ){
                tell_object(me, "你正在运功疗伤，却发现自己所剩的内力不够了。\n");
                if(eff < max)
                        tell_object(me, HIY"你呼出一口气站了起来，可惜伤势还没有完全恢复。\n"NOR);
                if (!msg || undefinedp(msg["heal_unfinish_msg"]))
                        message_vision(HIY"$N运功完毕，缓缓站了起来，脸色看起来好了许多。\n"NOR,me);
                else message_vision(msg["heal_unfinish_msg"],me);
                me->delete_temp("pending/heal");
                me->delete_temp("period");
                return 0;
        }
        
        recover_points = 10 + (int)me->query_skill("force") / 3;
    if (me->query("breakup"))
                recover_points *= 3;
        me->receive_curing("qi", recover_points);
        me->add("neili", -50);

        switch(period) {
        case 5:
        case 100:
        case 150:
                tell_object(me, "你双手互握，气凝丹田，不停地催动内息疗伤。\n");
                break;
        case 10:
        case 40:
        case 80:
        case 110:
        case 160:
                message_vision("$N开口吐出一口瘀血，脸色看起来好了一点。\n",me);
                break;
        case 20:
        case 120:
        case 170:
                tell_object(me, "你将双掌掌心相对，内息顺势缓缓运转，通行于全身伤脉。\n");
                break;
        case 30:
        case 130:
        case 180:
                tell_object(me, "你真气在体内转三转，呕出两口瘀血，稍去了点胸口闭塞之气。\n");
                me->improve_skill("force", 1);
                break;
        case 60:
        case 90:
        case 140:
        case 190:
                message_vision("$N打坐运气，调息了大半个时辰，精神为之一振。\n", me);
                me->improve_skill("force", me->query("int")/10, 1);
                break;
        case 50:
        case 70:
        case 200:
                tell_object(me, "你体内真气逐步贯通，四肢渐渐开始复有力气了。\n\n");
                me->improve_skill("force", 1);
                break;
        }
        me->add_temp("period", recover_points);
        return 1;
}

int halt_exercise(object me)
{
        string force;
        mapping msg;
        
        force = me->query_skill_mapped("force");
        if (force) msg = SKILL_D(force)->exercise_msg(me);
        me->delete_temp("pending/heal");
        me->delete_temp("period");
        me->add("jing", -50);
        me->add("jingli", -50);
        tell_object(me, "你心头一动，急忙吐气纳息，硬生生将内息压了下去。\n");
        if (!msg || undefinedp(msg["heal_halt_msg"]))
                message_vision("$N一震，吐出一口瘀血，缓缓站了起来。\n", me);
        else    message_vision(msg["heal_halt_msg"], me);    
        me->start_busy(1+random(5));
        return 1;
}

