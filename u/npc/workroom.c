// Room of wizard that haven't modify own workroom
// Updated by Lonely

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
          set("short", HIM"【静无悔的桃源仙境】"NOR);
        set("long",HIW @LONG
这是人在江湖巫师静无悔的住处，如今已经被静无悔搬
到纵横天下居住了。一群仙山之间的峡谷翠绿的柳树，簇拥
着碧波荡漾的池塘，阵阵氤氲雾气从池塘袅袅升起，弥漫谷
间。池塘前是一片桃林，粉红色的桃花四季绽放。
LONG NOR);

        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/wizard/wizard_room",
                "down"  : "/d/city/kedian",
        ]));
        set("objects", ([
                "/kungfu/class/sky/npc/hua" : 1,
                "/kungfu/class/sky/npc/kou" : 1,
                "/kungfu/class/sky/npc/xu" : 1,
        ]));
        set("valid_startroom", 1);
        set("no_fight",1);
        set("sleep_room", "1");
        set("no_clean_up", 0);
        setup();
     //    "/clone/board/jing_b"->foo();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && !wizardp(me))
                return notify_fail("那里只有巫师才能进去。\n");

        return ::valid_leave(me, dir);
}

void init()
{
        add_all_action();
        add_action("do_action", "");
        add_action("do_here", "come");
        add_action("do_sanweapon", "sanweapon");
}

int do_action(string arg)
{
        object me, *ob, ob1;
        int i;
        me = this_player();
        ob = all_inventory(environment(me));

        if (this_player()->query("id") != "jing")
        {
                string action = query_verb();

                switch (action)
                {
                case "smash":
                        write(HIW "这里是静无悔的房间，别乱来。\n" NOR);
                        return 1;
                }
        }
        if (arg != "")
        {
                for (i = 0; i < sizeof(ob); i++)
                {
                        ob1 = query_snoop(ob[i]);
                        if (!living(ob[i]))
                                continue;
                        if (objectp(ob1))
                        {
                                snoop(ob1);
                                tell_object(ob[i], HIW + ob1->name(1) + "对你的窃听被中止。\n" NOR);
                        }
                }
        }
        return 0;
}

int do_here(string arg)
{
        object me, *user;

        user = users();
        me = this_player();

        if (me->query("id") != "jing" || arg != "here")
                return notify_fail("What are you doing ?");

        foreach (object player in user)
        {
                if (wizardp(player))
                        player->move("/u/jing/workroom.c");
        }
        return 1;
}

int do_sanweapon(string arg)
{
        object me = this_player();
        object ob;
        if (!arg || !objectp(ob = present(arg, environment(me))))
                return 0;
        if (!ob->is_item_make())
                return 0;
        ob->set("magic/imbue_ok", 1);
        return 1;
}
