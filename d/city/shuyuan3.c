inherit ROOM;
int is_chat_room()
{
	return 1;
}
void create()
{
        set("short", "三味书屋一号屋");
        set("long", @LONG

    这里是三味书屋，大家可以在这里读各种书籍，但是不能
带走。

LONG);
        set("no_fight1", 1);
        set("no_fire", 1);
       // set("sleep_room",1);        
        set("exits", ([
            "down" : __DIR__"shuyuan2",
            "up" : __DIR__"shuyuan4",
        ]));
	 set("no_clean_up", 0);
	 setup();
        //replace_program(ROOM);
}





