


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "剩蛋" NOR, ({ "christmas egg"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "小虾做的剩蛋礼物，祝大家圣诞快乐。\n" NOR);
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

        if ( ! arg || (arg != "christmas egg") )
          return 0;
	
	 me = this_player();

        if (me->query("gift2007/christmas/eat"))
        {
            write(HIR"你已经吃过今年的圣诞礼物了!\n"NOR);
            return 1;
        }

        message_vision(HIY "$N将剩蛋一口吞了，哈喇子顺着嘴角就流了出来，\n" +
				"还一个劲儿连说:味道好极了哟，还有吗？再来一个!\n" NOR, me);


	 me->add("combat_exp", 50000);

	 mapsk = me->query_skill_mapped("force");
        	if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);	

           if (me->can_improve_skill("sword"))
                	me->improve_skill("sword", 1500000);		
    if (me->can_improve_skill("sword"))
                	me->improve_skill("sword", 1500000);	
    if (me->can_improve_skill("sword"))
                	me->improve_skill("sword", 1500000);	
    if (me->can_improve_skill("sword"))
                	me->improve_skill("sword", 1500000);	
    if (me->can_improve_skill("sword"))
                	me->improve_skill("sword", 1500000);						

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


		


       	