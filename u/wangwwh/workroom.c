#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",
NOR""+BLINK HIM"* 秋水小筑 *" NOR
            );
        set("long",
"　　\n"
""HIR"                 痴情最无聊"NOR"\n"
"　　\n"
""HIW"　　    这就是传说中神仙秋水的家了，在阳光的沐浴\n"
"    下，丝丝阳光透进窗内，顿时整个房间显得恍若仙\n"
"    境一般，你看着着人间的美景，一下子呆了，不由\n"
"    地放慢了脚步，放轻了呼吸，心旷神怡间，你竟在\n"
"    不知不觉中迈进了小院。\n"
"         突然，“你是谁？” 简简单单的三个字冷得\n"
"    如冰锥一样，从后背直刺心底。你不由地猛然一颤，\n"
"    回过头去，映入眼帘的，是一张如梨花般纯净的脸\n"
"    庞。你傻傻的站在那里........"NOR"\n"
"　　\n"
        );


        set("exits", ([
                "east" : "/d/city/kedian",
                "wm" : "/d/city/wumiao",
            ]));

     set("sleep_room", 1);
        setup();
        replace_program(ROOM);       
}


