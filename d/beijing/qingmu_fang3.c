#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂");
        set("long", @LONG
这里是一间看似很普通的民居，不过却要比通常的民居大了数倍。房间正
中一张长桌，天地会的青木堂的群豪围桌而坐，大声喧谈。
LONG );
        set("exits", ([
                "east" : __DIR__"qingmu_dayuan",
        ]));

        set("objects", ([
                __DIR__"npc/qibiaoqing" : 1,
                __DIR__"npc/fangang" : 1,
                __DIR__"npc/fengjizhong" : 1,
        ]));
        set("outdoors", "beijing");
        set("coor/x",-40);
	set("coor/y",950);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

