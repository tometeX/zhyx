// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "山道");
	set("long", @LONG
蜿蜒而上的山道渐渐陡峭，高大的林木后面隐隐约约露出天空中飘荡的飞
絮。野花满径，花香浓浓缭绕在呼吸里。耳畔时而想起潺潺的流水声，环顾翠
绿的山谷，却又找不见溪流的踪影。
LONG );
	set("exits", ([
		"north" : __DIR__"yuanyuan-tai",
		"south" : __DIR__"shandao1",
	]));
	
//	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
