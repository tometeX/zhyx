#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY+BLINK"挑战擂台"NOR);
        set("long", HIC@LONG
这里是专门设来接受外国挑战的擂台。
LONG );
        set("no_clean_up", 0);
        set("exits",([
                "down" : __DIR__"guangchang",
        ]));

        setup();
        replace_program(ROOM);
}

