#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "主殿");
	set("long", @LONG
惊雁宫的主殿较雁翔殿高出八丈，巍然耸
立于整个建筑之上，左右两个偏殿虽较雁翔殿
为低，亦高出其他建筑物两丈有余，各由一二
十丈的长廊相连主殿，整个大殿象一只狰狞的
野兽，虎伏在黑夜里。山雨欲来风满楼。
LONG
        );
            
        set("outdoors", "qianhuigu");
        set("exits", ([ 
		"south" : __DIR__"migong1",
		"east" : __DIR__"migong3",
		"west" : __DIR__"migong4",
		"down" : __DIR__"migong5",
        ]));
        setup();
      //  replace_program(ROOM);
}

