// File(/data/room/guoke/xiaoyuan.c) of guoke's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "无尽崖小院");
	set ("long", @LONG
[1;36m这里是一个不大的院子，角落里栽了几棵树，地上零零散散有一
    些碎落叶片。院门虚掩，穿过院子就是一个小屋，非常精致。
    小院前面就是一座悬崖，一条小路蜿蜒而上。
    环顾四周，只见不远处的旧石碑上写着“无尽崖”。[2;37;0m
LONG );

        set("room_key", "1 of guoke");
	setup();

	set("exits", ([
                "out"    : "/d/xiakedao/haibin",
	]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "过客");
        set("room_owner_id", "guoke");
        set("room_name", "无尽崖");
        set("room_id", "forever");
        set("room_position", "南海之滨");
}
