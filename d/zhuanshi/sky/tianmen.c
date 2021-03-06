#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY "【南天门】" NOR);
        set("long", HIW @LONG
你来到这里，发现这里茫茫一片云海。眼前一座宏伟的敞开的大
门，大门的柱子旁依偎着一位男子，似乎对你的到来毫不在意。这里
也有一座云梯(yunti)，据说过了这里就到达传说中的极乐世界了。
LONG NOR );
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/li": 1,
        ]));
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
                if ( objectp(present("li xunhuan", environment(me))))
                {
                        write(CYN "只听李寻欢说道：“这位" +
                              RANK_D->query_respect(me) + CYN
                              "，你还是下来吧。”\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "顺着云梯轻轻一"
                               "纵，身体便随着气流飘了上去……\n"
                               NOR, this_player());
                me->move(__DIR__"heaven"); 
                return 1;
        }
        return 0;
}


