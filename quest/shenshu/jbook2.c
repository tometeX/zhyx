#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIW"金庸全集下册"NOR, ({ "jin bookb" }) );
            set("no_put", 1);
            set("value", 0);
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
	        
            set("shenshu",1);
            set("unit", "本");
            set("no_put", 1);
            set("material", "paper");
            set("long", "一本由神书合并成的卷册，你可以用(chayue)来查阅它。\n");
          }

    setup();
}
void init()
{
   add_action("do_cha","chayue");
}
int do_cha(string arg)
{
	object me;
	int exp,pot,score;
	me =this_player();
 	if (!id(arg))
	return notify_fail("你要查什么？\n");

	exp = 2100+random(1000);
	             pot = exp/3;
             score = random(200)+100;
             me->add("combat_exp",exp);
             me->add("potential",pot);
             me->add("score",score);
     	      message_vision("$N仔细地查阅了一遍"+this_object()->query("name")+"。\n", me);
tell_object(me,"你被奖励了：\n" +
             chinese_number(exp) + "点实战经验\n"+
             chinese_number(pot) + "点潜能\n" +
            chinese_number(score)+"点江湖阅历\n");
	destruct(this_object());
return 1;
}
