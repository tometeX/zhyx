inherit ROOM;

void create()
{
        set("short", "三味书屋六号屋");
        set("long", @LONG

    这里是三味书屋，大家可以在这里读各种书籍，但是不能
带走。

LONG);
        set("no_fight1", 1);
        set("no_fire", 1);
        set("sleep_room",1);        
        set("exits", ([
            "down" : __DIR__"shuyuan7",
           // "up" : __DIR__"shuyuan9",
        ]));
      /*  set("objects", ([ 
                "/u/sanben/yuanxiao/lottery": 1, 
                "/u/sanben/npc/dumb": 1, 
        ]));  */
	 set("no_clean_up", 0);
	 setup();
        //replace_program(ROOM);
}





