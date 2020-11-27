
//双层大侠汉堡包

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "双层大侠汉堡包" NOR, ({ "double hanbao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一层是鸡腿，一层是牛扒，最上面还盖着一块红橙橙的西红杮，冒着香气的双层大汉堡。\n" NOR);
                set("unit", "个");
                set("value", 10);
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
	 string mapsk;	 
	 object me;

        if ( ! arg || (arg != "double hanbao") )
          return 0;
	
	 me = this_player();

        if (me->query("gift2010_yd/eat") >= 2 )
        {
             write("吃这么多汉堡,你想饱死啊?\n");
             return 1;
        }

        message_vision(HIY "$N将汉堡一口吞了，哈喇子顺着嘴角就流了出来，\n" NOR, me);


	 me->add("combat_exp",60000);
	 me->add("potential",100000);

	 mapsk = me->query_skill_mapped("force");
        //	if (me->can_improve_skill("force"))
         //       	me->improve_skill("force", 1500000);
     	if (stringp(mapsk) && me->can_improve_skill(mapsk))
              	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
     //   	if (stringp(mapsk) && me->can_improve_skill(mapsk))
     //           	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
    //    	if (stringp(mapsk) && me->can_improve_skill(mapsk))
      //          	me->improve_skill(mapsk, 1500000);
        me->add("gift2010_yd/eat",1);
tell_object(me, HIG"恭喜你增加了经验和潜能。"
                    "祝你元旦快乐！\n"NOR);
		destruct(this_object());
      return 1;
}


		


       	