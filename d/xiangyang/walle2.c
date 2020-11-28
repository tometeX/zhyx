// Room: /d/xiangyang/walle2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
    set("short", "石阶");
    set("long", @LONG
这是登向城头的石阶，因为城墙很高，所以很陡。石阶两
侧有可供拉车上下的斜坡道。
LONG );
    set("outdoors", "xiangyang");
    set("exits", ([
        "northup"   : __DIR__"walle4",
        "southdown" : __DIR__"eastgate1",
    ]));
    set("coor/x",-465);
    set("coor/y",-390);
    set("coor/z",5);
    setup();
}

int valid_leave(object me, string dir)
{
    int c_skill;

    // me = this_player();
    if (interactive(me) && sscanf(dir, "%*sup") == 1)
    {
        c_skill = me->query_skill("dodge", 1);
        if (me->query("qi") > 40)
        {
            me->receive_damage("qi", 20 + random(20));
            if (me->can_improve_skill("dodge") && c_skill < 100)
                me->improve_skill("dodge", 1 + random(me->query("dex")));
        }
        else
        {
            me->set("qi", 0);
            return notify_fail("你太累了，还是休息一会儿吧。\n");
        }
    }
    return 1;
}
