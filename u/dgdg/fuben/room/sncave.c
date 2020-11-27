#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【神农草舍】" NOR);
        set("long", HIW @LONG

                     神农氏草舍

    这是一个用草叶搭建的草舍，四周静悄悄的，吹来一股股凉风。
风中飘着一股药香味。这儿是神农尝百草途中临时棲身之所。


LONG NOR );

     set("exits", ([
                "north" : "/u/dgdg/fuben/room/fxcave",
]));
        
        set("sleep_room", 1);
    
        set("objects", ([
                "/u/dgdg/fuben/npc/shennong": 1,
                "/u/dgdg/fuben/npc/shennong dizi":1,
                "/u/dgdg/fuben/npc/tongzi":1,
               
        ]));
      
        setup();
}


void init()
{
        add_action("do_move", "touxi");
        add_action("do_move", "hit");
        add_action("do_yun","yun");
        add_action("do_yun","exert");
        add_action("do_move","guard");
        add_action("do_move","steal");
}


int do_yun(string arg)
{
        object ob = this_player();

        if (arg == "roar")
        {
                message_vision(CYN "\n空中神灵喝道：什么人？圣人之地"
                               "可由不得你嚣张！\n" NOR, ob);
                return 1;
        }
        return 0;
}

 	 int do_move(string arg) 
      { 
              object paper, 
              me = this_player(); 
       
              if (! arg || arg == "") 
                      return 0; 
       if (arg != "") 
            
             { 
                     
                       
                              write(CYN "只听空中一声暴喝：“这位" + 
                                    RANK_D->query_respect(me) + CYN 
                                    "，怎么做这种事情!”\n" NOR); 
                              return 1; 
                      
                    
                   
              } 
              return 0; 
      } 

