
//大侠汉堡包，减一点容貌

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "大侠汉堡包" NOR, ({ "hanbao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "\n吃大侠汉堡包，做真英雄。\n" NOR);
                set("unit", "个");
                set("value", 10000000);
                set("weight", 100);                
             }
        setup();
}

void init()
	{
		add_action("do_eat","eat");
	}
		

int do_eat( string arg )
{		
	 
	 object me;

        if ( ! arg || (arg != "hanbao") )
          return 0;
	
	 me = this_player();

       /* if (me->query("gf09tangyuan/eat") >= 3 )
        {
             write("吃这么多汤圆,你想饱死啊?\n");
             return 1;
        } */
 if (me->query("per")<1)  
 	         {
 	         	 write("你已经够丑了，还吃？"); 
 	         	 return 1;
 	         	 }
 	         
        message_vision(HIY "$N将大侠汉堡包一口吞了，哈喇子顺着嘴角就流了出来，\n" NOR, me);

  
   	 
	 me->add("per",-1);
	

	 
tell_object(me, HIG"恭喜你,减了一点容貌!吃了大侠汉堡包，维护世界和平的任务就交给你了!\n" NOR);
		destruct(this_object());
      return 1;
}


		       	