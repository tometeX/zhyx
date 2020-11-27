
//春节汤圆

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "离子的生日蛋糕" NOR, ({ "jakescake" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "为了庆祝离子生日专门连夜赶做的蛋糕.是巫师大人杨六狼做的,意外吗?惊喜吗?\n" NOR);
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

        if ( ! arg || (arg != "jakescake") )
          return 0;
	
	 me = this_player();

        if (me->query("jakescake/eat") >= 1 )
        {
             write("吃这么多蛋糕,你想饱死啊?\n");
             return 1;
        }

        message_vision(HIY "$N将蛋糕一口吞了，哈喇子顺着嘴角就流了出来，\n" +
				"还一个劲儿连说:味道好极了哟，还有吗？再来一个!\n突然远处飘来一阵乐曲\n\n\nHappy BirthDay to You\nHappy BirthDay to You\nHappy BirthDay to You\nHappy BirthDay to 离子.\n\n你听完,不禁一阵失神,感动得不得了.\n"NOR, me);


	 me->add("combat_exp",60000);
	 me->add("potential",99999);

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
        me->add("jakescake/eat",1);
tell_object(me, HIG"恭喜你增加了经验和潜能。"
                    "祝你生日快乐！\n"NOR);
		destruct(this_object());
      return 1;
}


		


       	