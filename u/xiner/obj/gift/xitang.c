
//喜糖 (基本force,force,dodge,parry)各加1级


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "囍糖" NOR, ({ "xi tang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "这是二○○九年五一离子结婚发的囍糖。\n" NOR);
                set("unit", "包");
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
        {
                add_action("do_eat","eat");
        }
                

int do_eat( string arg )
{       
        if (arg == "xi tang")

        {
         string mapsk;   
         object me;
        
         me = this_player();

        if ( me->query("liwu/20090501/eat") )
        {write(HIR"你已经吃过囍糖了还想要么！\n"NOR);return 1;}

        message_vision(HIY "$N将囍糖一口吞了，对着离子一个劲儿连说:“恭喜！恭喜！\n祝：新 婚 快 乐！\n" NOR, me);

	message("vision", HIM"【喜报喜报】" + me->query("name") + "祝福离子夫妻二人：郎才女貌！花好月圆！相亲相爱！白头偕老！\n"NOR, users());

	log_file("static/wuyi", sprintf("%s(%s) eat 囍糖 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

	me->set("liwu/20090501/eat", 1);

	me->add("combat_exp", 50000);
        me->add("potential",  50000);

	if (me->can_improve_skill("force"))
		me->improve_skill("force", 1500000);
	if (me->can_improve_skill("parry"))
		me->improve_skill("parry", 1500000);
	if (me->can_improve_skill("dodge"))
		me->improve_skill("dodge", 1500000);

	destruct(this_object());
	return 1;
        }
	else
	{return 0;}
}

int query_autoload() { return 1; }
