inherit ROOM;

void create()
{
	set("short", "有间客栈客房");
	set("long", @LONG
这是一间很大的客房，陈设十分简陋。靠墙放了十几张小
木床，不少客人正和衣而卧，满屋子都是呼呼的打酣声。西边
有张床是空的，你蹑手蹑脚地走了过去。
LONG );
	set("sleep_room", 1);
	set("no_fight", 1);      
	set("no_clean_up", 0);
	set("exits", ([
		"up" : __DIR__"kedian",
	]));	
	setup();
}

