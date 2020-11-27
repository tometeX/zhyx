#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIY"九转金丹"NOR, ({"jin dan", "jindan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "这是一颗九转金丹。\n");
		set("value", 50000);
set("no_pawn",1);
	}
	setup();
}

int do_eat(string arg)
{
	int exp,pot,score;
        object me = this_player();
 	if (!id(arg))
	return notify_fail("你要吃什么？\n");

        if ( (int)me->query_condition("medicine") > 0 )
	{
		me->add("max_neili", -1);
		message_vision(HIR "$N吃下一颗九转金丹，只觉得头重脚轻，摇摇欲倒，原来服食太急太多，药效适得其反！\n" NOR, me);
	}
	else
	{
	exp = 2100+random(2000);
	             pot = exp/3;
             score = random(200)+100;
             me->add("combat_exp",exp);
             me->add("potential",pot);
             me->add("score",score);
tell_object(me,HIY"你被奖励了：50点内力上限\n" +
             chinese_number(exp) + "点实战经验\n"+
             chinese_number(pot) + "点潜能\n" +
            chinese_number(score)+"点江湖阅历\n"NOR);
        me->add("max_neili", 50);
        message_vision(HIY "$N吃下一颗九转金丹，只觉得体内真力源源滋生，你好像变了一个人似的!\n" NOR, me);
	}

        me->apply_condition("medicine", 60);
	
	destruct(this_object());
	return 1;
}