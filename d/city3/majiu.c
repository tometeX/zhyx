#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "马厩");
      set("long", @LONG
这是成都城的马厩，常年供应新鲜草料。成都民风淳朴马
夫们会把马牵到马厩好生照看，将它们喂饱饮足，再洗刷得干
乾净净，一直伺候到客人上路。马厩雨檐下的烂木柱上钉着块
破木牌(paizi)。马厩中堆放著几堆草料。
LONG);
      set("outdoors", "chengdu");
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
                "clone/horse/mapi.c": 1 + random(5),
      ]));
      set("exits", ([
                "west" : __DIR__"kedian",
                "up"   : "/clone/shop/chengdu_shop",
      ]));
      set("coor/x",-482);
      set("coor/y",-194);
      set("coor/z",0);
      setup();
}
