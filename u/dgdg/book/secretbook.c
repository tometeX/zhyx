


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "杨六狼作弊大全" NOR, ({ "cheat miji", "zuobi shu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n一本传说中的神书，据说可以得到mud中至高无尚的技能。你可以通过（use）来使用。\n" NOR);
                set("unit", "本");
                set("value", 10000000);
                set("weight", 100);                
             }
        setup();
}

void init()
	{
		add_action("do_use","use");
	}
		

int do_use( string arg )
{		
	 string mapsk;	 
	 object me;

        if ( ! arg || (arg != "chat miji" && arg != "zuobi shu") )
          return 0;
	
	      me = this_player();
	      
	      	      
        message_vision(HIG "$N"HIG"哈哈哈，，你上当了......\n" NOR, me); 
        
        me->unconcious();

		destruct(this_object());
      return 1;
}

string query_autoload()
{
        if ( ! query("owner") )
                return 0;

        return query("owner");
}

void autoload(string owner)
{       
     if (owner) set("owner", owner);
}


		


       	