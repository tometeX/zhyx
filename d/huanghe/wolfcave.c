#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【狼穴】" NOR);
        set("long", HIW @LONG

                杨六狼的狼穴

    这里阴森恐怖，不时传来一阵狼嚎之声，令人害怕。四周吹来阵阵
冷风，风中有一股腥味，令你非常的不舒服。


LONG NOR );

     set("exits", ([
                "out" : "/d/huanghe/shulin2",
                "north" :"/u/dgdg/fuben/room/sncave",
]));
       
        set("sleep_room", 1);
       /* set("objects", ([
                "/u/dgdg/fuben/npc/shennong": 1,
                "/u/dgdg/fuben/npc/shennong dizi":1,
               
        ])); */
      
        setup();
}

void init()
{
        add_action("do_move", "jump");
        add_action("do_move", "move");
        add_action("do_move", "tiao");
        add_action("do_move", "enter");
        add_action("do_move", "up");
}

int do_move(string arg)
{
        object paper,
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "yunti")
        {
                if ( objectp(present("tie chuanjia", environment(me))))
                {
                        write(CYN "只听铁传甲一声暴喝：“这位" +
                              RANK_D->query_respect(me) + CYN
                              "，请停步。”\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "顺着云梯轻轻一"
                               "纵，身体便随着气流飘了上去……\n"
                               NOR, this_player());
                me->move(__DIR__"sky2"); 
                return 1;
        }
        return 0;
}

