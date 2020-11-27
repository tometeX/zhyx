// File(/data/room/tntb/xiaoyuan.c) of tntb's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "浮云轩小院");
	set ("long", @LONG
[35m这是一个不大的院子，但绿树假山，十分别致。[2;37;0m
LONG );

        set("room_key", "1 of tntb");
	setup();

	set("exits", ([
                "out"    : "/d/hangzhou/yuhuangsj",
	]));

        set("outdoors", "hangzhou");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "黄金二号");
        set("room_owner_id", "tntb");
        set("room_name", "浮云轩");
        set("room_id", "fyx");
        set("room_position", "玉皇山脚");
}
