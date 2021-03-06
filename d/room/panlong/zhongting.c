// zhongting.c 盘龙居中庭

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "中庭");             /* EXAMPLE */
//**    set("short", "ROOM_NAME中庭");
	set("long", @LONG
这是盘龙居之腰：中庭，两旁便是客人居住的厢房，后面通往后
花园和主人居所，前面则是议事厅，一直通往大院。
LONG );

	set("default_long", "这是ROOM_NAME之腰：中庭，两旁便是客人居"  /* EXAMPLE */
                            "住的厢房，后面通往后花园和主人居所，前面" /* EXAMPLE */
                            "则是议事厅，一直通往大院。");             /* EXAMPLE */
                                                                       /* EXAMPLE */

	set("exits", ([
		"north"  : __DIR__"houyuan",
                "south"  : __DIR__"yishiting",
                "east"   : __DIR__"zuoxiang",
                "west"   : __DIR__"youxiang",
	]));

        set("outdoors", "OUTDOORS");

        create_door("east", "木门", "west", DOOR_CLOSED);
        create_door("west", "木门", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

