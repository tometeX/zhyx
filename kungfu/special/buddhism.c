// buddhism.c 九转灵童
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "九转灵童" NOR; }

int perform(object me, string skill)
{        	
	int lvl1, lvl2, lvl3, lvl4;

	if (! me->query("reborn"))        
		return notify_fail("你尚未转世重生，无法使用此技能！\n");
      
	lvl1 = me->query_skill("buddhism", 1);
	lvl2 = me->query_skill("lamaism", 1);
	lvl3 = me->query_skill("mahayana", 1);
	lvl4 = me->query_skill("taoism", 1);

	message_vision(HIY "$N" HIY "闭目端坐，冥神思索，试图与"
                       "天地万物融为一体。\n" NOR, me);   

	me->set_short_desc("正端坐在地上冥想，似乎想与天地万物融为一体");
	me->delete_temp("pending/buddhism");   

	if (lvl1 >= 500 && lvl2 >= 500 && lvl3 >= 500 && lvl4 >= 400)
	{
		if (me->is_busy())
			return notify_fail("等你忙完了手头的事情再说！\n");

		if (me->is_fighting())
			return notify_fail("你边打架一边冥想？真有你的。\n");

		if (me->query("potential") - me->query("learned_points") < 10000)
			return notify_fail("你现在潜能不足以完成一次冥想！\n");

		me->set_short_desc("盘膝而坐，正在瞑目修炼。");

		me->start_busy((:call_other, __FILE__, "check2" :),
				(:call_other, __FILE__, "halt2" :));
	}else
		me->start_busy((:call_other, __FILE__, "check" :),
				(:call_other, __FILE__, "halt" :));

	return 1;
}

int check(object me)
{
    if ( me->add_temp("pending/buddhism", 1) < (40 + random(10)) )
        return 1;
   
     message_vision(HIY "$N" HIY "缓缓睁开双目，"
                    "结束了这次修行。\n" NOR, me);

     if (random(5) != 0 )
        tell_object(me, "\n你感到这次修行并无多大进展，"
                        "无法回忆起以前的佛学和道学知识。\n\n");
     else
     {
        tell_object(me, HIG"\n突然你感到心智顿开，"
                         "无数世前的佛学和道学刹那间印入脑海。\n\n"NOR);
        tell_object(me, HIW"\n你对佛学和道学顿悟了。\n\n"NOR);

        me->set_skill("buddhism", 500);
        me->set_skill("lamaism", 500); 
        me->set_skill("mahayana", 500);
	me->set_skill("taoism", 400);
     }
    me->set_short_desc(0);  
    me->delete_temp("pending/buddhism");
    return 0;
}

int halt(object me)
{            
	message_vision(HIG"$N睁开双眼，结束了这此冥想。\n"NOR, me);        
	me->set_short_desc(0);  
	me->delete_temp("pending/buddhism");     
	return 1;
}

int check2(object me)
{
	if ((int)me->query("potential") - (int)me->query("learned_points") > 50)
	{
		me->add("learned_points", 20 + random(30));
		switch (random(9))
		{
		case 0:
			tell_object(me, HIW "你对禅宗心法有了新的领悟。\n" NOR);
			if (me->query_skill("buddhism",1) < 800)
				me->improve_skill("buddhism", 6000 + random(3000));
			break;
		case 1:
			tell_object(me, HIW "你对密宗心法有了新的领悟。\n" NOR);
			if (me->query_skill("lamaism",1)< 800)
				me->improve_skill("lamaism", 6000 + random(3000));
			break;
		case 2:
			tell_object(me, HIW "你对大乘涅盘功有了新的领悟。\n" NOR);
			if (me->query_skill("mahayana",1)< 800)
				me->improve_skill("mahayana", 6000 + random(3000));
			break;
		case 3:
			tell_object(me, HIW "你对道学心法有了新的领悟。\n" NOR);
			if (me->query_skill("taoism",1)< 800)
				me->improve_skill("taoism", 6000 + random(3000));
			break;
		default:
			//tell_object(me, HIW "你安坐不动，整个人似梦似醒。\n" NOR);
		}
		return 1;
	}
	message_vision(HIY "$N" HIY "缓缓睁开双目，结束了这次修行。\n" NOR, me);
	me->set_short_desc(0);  
	return 0;
}

int halt2(object me)
{            
	message_vision(HIG"$N睁开双眼，结束了这此冥想。\n"NOR, me);
	me->add("potential", (me->query("learned_points") - me->query("potential")) / 2);
	me->set_short_desc(0);
	me->delete_temp("pending/buddhism");
	return 1;
}


