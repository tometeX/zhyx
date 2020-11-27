// File(/data/room/weed/xiaoyuan.c) of weed's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "杂草居小院");
	set ("long", @LONG
这里是一个不大的院子，角落里栽了几棵树，地上零零散散有一
些碎落叶片。院门虚掩，穿过院子就是一个小屋，非常精致。 
LONG );

        set("room_key", "1 of weed");
	setup();

	set("exits", ([
                "out"    : "/d/gumu/hanshuitan",
	]));

        set("outdoors", "quanzhen");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "杂草");
        set("room_owner_id", "weed");
        set("room_name", "杂草居");
        set("room_id", "weed");
        set("room_position", "寒水潭");
}
