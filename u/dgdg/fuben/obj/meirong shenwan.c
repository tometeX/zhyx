
//美容神丸，加一点容貌

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "美容神丸" NOR, ({ "meirong shenwan","mrsw" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "\n比美容丸效果更好，狼氏美容连锁机构出品，信心保证。\n" NOR);
                set("unit", "个");
                set("value", 10);
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

        if ( ! arg || (arg != "meirong shenwan") )
          return 0;
	
	 me = this_player();

       /* if (me->query("gf09tangyuan/eat") >= 3 )
        {
             write("吃这么多汤圆,你想饱死啊?\n");
             return 1;
        } */
 if (me->query("per")>34)  
 	         {
 	         	 write("你已经够很漂亮了啊，还要整容？"); 
 	         	 return 1;
 	         	 }
 	         
        message_vision(HIY "你将美容丸一口吞了，哈喇子顺着嘴角就流了出来。\n" NOR, me);

 	if (random(3)==1) 
  		{
  		tell_object(me,HIG"\n你人品不好，这次吃丹失败了，未能提升容貌。加油吧!\n"NOR);
  		return 1;
  	}
   	 

		
			 me->add("per",1);
       tell_object(me, HIG"恭喜你,加了一点容貌。你真是人见人爱，车见车载的俊哥美女。维护世界和平的任务就交给你了!\n" NOR);
		  destruct(this_object());
       return 1;
}


		       	