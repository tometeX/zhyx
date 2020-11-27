#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "武庙");
        set("long",
"这里是扬州岳王庙的正殿，内有岳飞像，像上方悬挂岳飞手书还我河 \n"
"山的横匾。殿两侧壁上嵌着尽忠报国四个大字。武人到此，都放下武 \n"
"器，毕恭毕敬地上香礼拜。旁边似乎有一道侧门。\n\n"
HIW "比武入口(enter) \n"
);
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_sleep_room", 1);

        set("valid_startroom", 1);
	set("objects", ([
            //    "/u/xgchen/xmas/man" : 1,
               "/u/sanben/npc/bobo" : 1,
                __DIR__"obj/box" : 1,

	]));

	set("exits", ([
		"east" : __DIR__"beidajie2",
		"up"   : __DIR__"wumiao2",
            //    "down" : "/d/wizard/herodoor"
	]));
	set("coor/x",-10);
	set("coor/y",19);
	set("coor/z",0);
	setup();
              "/clone/board/wumiao_b"->foo(); 
        //replace_program(ROOM);
}
int valid_leave(object me, string dir) 
{ 
       
    if ( ! me->is_player() && dir == "up" ) return 0;
    
    return 1;
} 

