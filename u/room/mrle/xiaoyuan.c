// File(/data/room/mrle/xiaoyuan.c) of mrle's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "闲仙居小院");
	set ("long", @LONG
这里是一个不大的院子，角落里栽了几棵树，地上零零散散有一
些碎落叶片。院门虚掩，穿过院子就是一个小屋，非常精致。 
LONG );

        set("room_key", "1 of mrle");
	setup();

	set("exits", ([
                "out"    : "/d/xiakedao/xkroad3",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "慕容珑儿");
        set("room_owner_id", "mrle");
        set("room_name", "闲仙居");
        set("room_id", "xxj");
        set("room_position", "平原小路");
}
