// File(/data/room/tntb/dulewu.c) of tntb's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "浮云轩小屋");
	set ("long", @LONG
[1;33m金子盖的小房，有些俗气，但也十分气派（藏娇的好地方）。[2;37;0m
LONG );

        set("objects", ([
                "/u/sanben/obj/locker" : 1,
        ]));

    setup();

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "黄金二号");
        set("room_name", "浮云轩");
        set("room_id", "fyx");
        set("room_owner_id", "tntb");
        set("room_position", "玉皇山脚");
}

