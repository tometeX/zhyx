// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /d/wiz/system.c

inherit ROOM;

void create()
{
   set("short", "宝石炼制房");
   set("long", @LONG
宝石炼制房   
LONG
   );

   set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"dazaoroom",
]));
   set("no_clean_up", 0);
   set("no_fight", 1);
   set("no_magic", 1);
   set("no_bian",1);
   set("objects", 
        ([ 
 	 __DIR__"tai" : 1,
 	 ]));
   setup();


}


int valid_leave(object me, string dir)
{
/*/     if(me->query("id")=="beavis") return ::valid_leave(me, dir);
       //temp access for future wiz.

     if( dir=="east" && !wizardp(me) )
        return notify_fail("那里只有巫师才能进去。\n");
       if( dir=="west" && !wizardp(me) ) {
            if( (int)me->query("combat_exp")>0 ||
             (int)me->query("no_gift")==0 )
          return notify_fail("你感觉被一股强大的气流推了出来。\n");
    }*/
     return ::valid_leave(me, dir);
}


