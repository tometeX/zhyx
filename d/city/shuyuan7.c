inherit ROOM;

void create()
{
        set("short", "三味书屋五号屋");
        set("long", @LONG

    这里是三味书屋，大家可以在这里读各种书籍，但是不能
带走。

LONG);
        set("no_fight1", 1);
        set("no_fire", 1);
        set("sleep_room",1);        
        set("exits", ([
            "down" : __DIR__"shuyuan6",
            "up" : __DIR__"shuyuan8",
        ]));
	 set("no_clean_up", 0);
	/* set("objects", ([               
              "/u/kasumi/npc/kasumi":1,
        ])); */
	 setup();
        //replace_program(ROOM);
}





