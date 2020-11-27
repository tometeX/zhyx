
//儿童节礼物

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "儿童节聪明蛋" NOR, ({ "childgift" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "儿童节才可以吃到的聪明蛋,是巫师大人杨六狼做的，据说可以吃好几个哦。笨蛋吃了变好蛋，好蛋吃了变坏蛋。\n" NOR);
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

        if ( ! arg || (arg != "childgift") )
          return 0;
	
	 me = this_player();

        if (me->query("childgift/eat") >= 3 )
        {
             write("吃这么多聪蛋,你想笨蛋啊?\n");
             return 1;
        }

        message_vision(HIY "$N将聪明蛋一口吞了，哈喇子顺着嘴角就流了出来，\n" +
				"还一个劲儿连说:味道好极了哟，还有吗？再来一个!\n\n"NOR, me);


	 me->add("combat_exp",random(15)*10000);
	 me->add("potential",random(15)*10000);

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
        me->add("childgift/eat",1);
tell_object(me, HIG"恭喜你聪明了。"
                    "祝你儿童节快乐！\n"NOR);
		destruct(this_object());
      return 1;
}


		


       	