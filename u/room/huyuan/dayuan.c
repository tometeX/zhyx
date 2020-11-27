// File(/data/room/huyuan/dayuan.c) of huyuan's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "天剑山庄大院");
	set ("long", @LONG
这是一个宽阔的院落，种着各种树木，阳光照下来透过树荫投下
层层影子。一条大路通向里面，踩得非常平滑的，看来是经常有人来
往。 
LONG );

	set("exits", ([
		"north"  : __DIR__"qianting",
                "out"    : "/d/huanghe/caodi1",
	]));

        set("outdoors", "huanghe");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);
        setup();

        set("room_owner", "胡渊");
        set("room_name", "天剑山庄");
        set("room_OWNER_id", "huyuan");
        set("room_id", "tianjian");
        set("room_owner_id", "huyuan");
        set("room_position", "草地");
}
