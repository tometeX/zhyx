// nodie.c 不死金身
// by xiner 03/3/2009
#include <ansi.h>

inherit F_CLEAN_UP;

#define NODIE "「"HIY"不死金身" NOR "」"

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        if ((int)me->query_skill("yinyang-shiertian", 1) < 200)
                return notify_fail("你的阴阳十二重天神功等级不够。\n");

        if (target != me)
		return notify_fail("你只能用阴阳十二重天来保护自己。\n");

	if (! me->query("reborn"))        
		return notify_fail("你尚未转世重生，无法使用此技能！\n");

	if ((int)me->query_temp("no_die"))
		return notify_fail("你已经在运功中了。\n");

       if ( time() - me->query("la_sp_tm/nodie") < 3600 )        
		return notify_fail("你要过些时候才能再用此技能！\n");

	message_vision(YEL "$N" YEL "脸色一沉，运起" NODIE YEL "体内真气疾速运转十二周天，"
			"全身散发出一阵金光，如转世罗汉一般。\n" NOR, me);      
      
	me->set_temp("no_die",1);
	me->set("la_sp_tm/nodie", time());        
	me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 60);
	return 1;
}

void remove_effect(object me, int amount)
{
     me->delete_temp("no_die");
     tell_object(me, "你施展完"NODIE"，松了一口气。\n");
}
