// File(/data/room/ultrahell/dulewu.c) of ultrahell's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "火焰居小屋");
	set ("long", @LONG
屋子不大，靠窗的地方摆了一张床，屋中一张桌，几只椅，非常
简单。看来主人是一个甘于平淡寂寞的人。 
LONG );

        set("objects", ([
                "/d/room/obj/storage" : 1,
        ]));

    setup();

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "胡晨曦");
        set("room_name", "火焰居");
        set("room_id", "hyj");
        set("room_owner_id", "ultrahell");
        set("room_position", "南大街");
}

