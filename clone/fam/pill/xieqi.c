
//万恶果

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "万恶果" NOR, ({ "wane guo", "guo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIB "这是万恶果，吃了会使你邪气大增!\n" NOR);
                set("unit", "粒");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10); 
                set("can_cun",1);               
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
         me = this_player();
        

        if ( ! arg || ( arg != "wane guo" && arg != "guo"))        
        return 0;
             

         if (me->query("shen") < -1000000)
         {
            tell_object(me, HIR"你的邪气已经够盛了，再吃也没用了!\n"NOR);
            return 1;
         }
       
         message_vision(WHT "$N一口将万恶果吞下了肚子，顿时一股邪气袭上心头!\n" NOR, me);
         tell_object(me, HIB"你的邪气增加了!\n"NOR);

         me->add("shen", - 2000 - random(500));

         destruct(this_object());
         return 1;
}
                
int query_autoload() 
{ return 1; }


        
