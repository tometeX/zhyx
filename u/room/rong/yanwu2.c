// File(/data/room/rong/yanwu2.c) of rong's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "芙蓉居演武厅");
	set ("long", @LONG
这是芙蓉居的演武厅，有时有些江湖朋友来会，想一试身手，就
在这里比武较量。 
LONG );

	set("exits", ([
                "east" : __DIR__"yishiting",
	]));

        set("objects", ([
                "/clone/weapon/zhubang" : 1,
                "/clone/weapon/zhujian" : 1,
                "/clone/weapon/mudao"   : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "水蓉儿");
        set("room_name", "芙蓉居");
        set("room_id", "rong");
        set("room_owner_id", "rong");
        set("room_position", "南海渔村");
}
