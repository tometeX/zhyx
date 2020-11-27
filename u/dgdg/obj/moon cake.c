
//中秋节礼物

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "月饼" NOR, ({ "moon cake" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "这是巫师大人杨六狼为中秋节特制的“月饼”，据说可以吃好几个，但吃多了就会撑死，小心哦，哈哈。\n" NOR);
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

        if ( ! arg || (arg != "moon cake") )
          return 0;
	
	 me = this_player();

        if (me->query("moon cake/eat") >= 3 )
        {
             write("吃那么多月饼，想被撑死啊?\n");
             return 1;
        }

        message_vision(HIY "$N将月饼一口吞了，哈喇子顺着嘴角就流了出来，\n" +
				"一个劲儿地打着饱嗝!\n\n"NOR, me);


	 me->add("combat_exp",random(5)*10000);
	 me->add("potential",random(5)*10000);

	 mapsk = me->query_skill_mapped("force");
        //	if (me->can_improve_skill("force"))
         //       	me->improve_skill("force", int(random(3000000));
     	if (stringp(mapsk) && me->can_improve_skill(mapsk))
              	me->improve_skill(mapsk,random(500)*10000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry",random(500)*10000);
     //   	if (stringp(mapsk) && me->can_improve_skill(mapsk))
     //           	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", random(500)*10000);
    //    	if (stringp(mapsk) && me->can_improve_skill(mapsk))
      //          	me->improve_skill(mapsk, 1500000);
        me->add("moon cake/eat",1);
tell_object(me, HIG"恭喜你。"
                    "祝你中秋节快乐！\n"NOR);
		destruct(this_object());
      return 1;
}


		


       	