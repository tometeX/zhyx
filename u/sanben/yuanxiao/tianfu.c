
//金帝巧克力 指定一项天赋 加一点

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "金帝巧克力" NOR, ({ "chocolate", "xiao keli"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "想加天赋想疯了吗？先wish再eat，"+
				     "吃完别忘了说声味道好啊！。\n" NOR);
                set("unit", "粒");
                set("value", 10);
                set("weight", 10);                
             }
        setup();
}

void init()
	{	
		add_action("do_wish","wish");
		add_action("do_eat","eat");
	}
		

int do_wish( string arg )

	{	this_player()->set_temp("wish_tianfu1", arg);	
	    if (arg == "臂力")
		{ this_player()->set_temp("wish_tianfu", "str");
		  write("你指定了要加一点"HIY+ arg + NOR"。\n");return 1;}
	    if (arg == "悟性")
		{ this_player()->set_temp("wish_tianfu", "int");
		  write("你指定了要加一点"HIW+ arg + NOR"。\n");return 1;}
	    if (arg == "根骨")
		{ this_player()->set_temp("wish_tianfu", "con");
		  write("你指定了要加一点"YEL+ arg + NOR"。\n");return 1;}
	    if (arg == "身法")
		{ this_player()->set_temp("wish_tianfu", "dex");
		  write("你指定了要加一点"HIR+ arg + NOR"。\n");return 1;}		

	    else { write("你要加哪项天赋？比如wish 臂力\n");}	    
	    return 1;
	}

int do_eat( string arg )
{	
	if (arg == "chocolate" || arg == "qiao keli")

	{	 	 
	 object me;
	
	 me = this_player();

        if (me->query_temp("wish_tianfu") == 0 )
        {write(HIR"请先用wish <天赋> 指定你要加哪项天赋！\n"NOR);return 1;}
	 
	 log_file("static/yuanxiao", sprintf("%s(%s) eat 金帝巧克力 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));
        message_vision(HIY "$N一口将巧克力吞下了肚子，感觉身体有了很奇异的变化。\n" NOR, me);
	 write(HIG"你的先天" + me->query_temp("wish_tianfu1") + "永久增加一点。\n"NOR);

        me->add(me->query_temp("wish_tianfu"), 1);
	        	
	 me->delete_temp("wish_tianfu");
	 me->delete_temp("wish_tianfu1");

	 destruct(this_object());
	 return 1;
	}
else {	return 0;}
}
		


       	