// yuchang
#include <ansi.h>
inherit ROOM;
int do_zhuan(string arg);
int do_an(string arg);
void create()
{
        set("short", "地室");
        set("long", @LONG
这是个宽约二十步的正方形地室，空气流畅，令你觉 
得找对地方。墙壁上有一盏油灯，看上去有点异样！

LONG
        );
        set("exits", ([
                      ]));
        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("do_zhuan", "zhuan");
        add_action("do_an", "an");
}
int do_zhuan(string arg)
{
        object me;
        me = this_player();
      if( !arg || arg=="" ) return notify_fail("你要转什么东西!\n");
            if( arg=="deng" ) {
             write(
           "你转了转油灯，居然可以转动,你可以试试按进去看看!\n");
             this_player()->set_temp("tiwall", 1);
             return 1;
       }
}
int do_an(string arg)
{
        object me;
        object room; 
        me = this_player();
      if( !arg || arg=="" ) return notify_fail("你要按什么东西!\n");
  if( arg=="deng" ) {
        if (me->query_temp("tiwall") ) {
            message("vision", me->name() + "试着把油灯按了一按,
四周墙壁发出了「轧轧」声响，在这个空间份外触耳。\n",
                    environment(me), ({me}) ); 
 message("vision","左面墙壁突然闪出一个出口，露出仅可容一人通过的入
口。 \n",
                    environment(me), ({me}) );
           if(!( room = find_object("/d/ygbz/dishi")) )
                  room = load_object("/d/ygbz/dishi"); 
        if(objectp(room)) 
            { 
  me->move(__DIR__"langdao0");
message("channel:chat", HBRED"【宝藏】"+me->query("name")+"成功进入杨公宝库密道!\n"NOR,users());
}
                            this_player()->delete_temp("tiwall");
            return 1;
        }
}
        else {
            write("你想按什么东西?!\n");
     return 1;
        }
}
