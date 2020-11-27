// File(/data/room/guoke/dulewu.c) of guoke's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "无尽崖小屋");
	set ("long", @LONG
[1;36m屋子不大，中间是一幅山水画，靠窗的地方摆了一张床，
    屋中一张桌，几只椅，非常简单。
    抬头仔细看看那画中山水，乃是旭日东升下的无尽崖，
    旁边用柳书写着：
    “[1;31m游戏一生，来去匆匆；千金散尽，涅磐重生！[1;36m”，
    落款“[33m一个过客[1;36m”。[2;37;0m
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
    
        set("room_owner", "过客");
        set("room_name", "无尽崖");
        set("room_id", "forever");
        set("room_owner_id", "guoke");
        set("room_position", "南海之滨");
}

