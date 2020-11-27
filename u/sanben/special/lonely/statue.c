// 自由女神像

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "自由女神像" NOR, ({ "statue of liberty", "statue"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "这是一坐高耸入云的女神雕像。她左手拿着一本圣经，\n"
                                "右手举着一个火炬，象征着人人渴望获得的自由。雕\n"
                                "像的底部有道门，似乎可以(enter statue)。\n"NOR);
                set("unit", "个");                
                set("no_sell",1);
                set("weight", 10000);
                set("no_get",1);                
             }
        setup();
}

void init()
{
    add_action("do_enter", "enter"); 
    
}

int do_enter(string arg)
{
   object me = this_player();
   
   if ( ! arg || ( arg != "statue" && 
        arg != "statue of liberty" ) )
   return notify_fail("你要进去哪里？\n");

   message_vision("$N从女神像的底部走了进去。\n\n" , me);

   me->move(__DIR__"floor1");
   return 1;
}





