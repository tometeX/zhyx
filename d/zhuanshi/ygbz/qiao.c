// By yuchang@zhyx
#include <ansi.h> 
inherit ROOM;

void check_longtou();

void create()
{
        set("short", "跃马桥");
        set("long", @LONG  
这里是长安有名的跃马桥,桥中间有六根石柱顶
部给雕成六个俯探桥外的石龙头(shi longtou)，画
龙点睛般为石桥平添无限生气。
LONG); 
        set("item_desc", ([       
"shi longtou" : "你隐见一圈淡淡的圆柱与桥身的接痕，若不是有目标的查察，
必会当是石纹忽略过去,你不禁想顶一顶(ding)圈痕(quan hen)。\n",          
        ]));
        set("exits", ([
               "west" : "/d/changan/ca13",
        ]));
        set("no_clean_up", 0);
        setup();
} 

void init()
{
        add_action("do_ding", "ding");
        add_action("do_ba", "ba"); 
        add_action("do_zhuan", "zhuan");
}

int do_ding(string arg)
{
    object zhu, me = this_player();

    if ( !arg || arg != "quan hen" )  
       return notify_fail("你要顶什么呀？\n");  
                                                  
       message_vision(HIR"$N在龙头下方的圈痕用力往上顶了一下!\n"NOR, me);
       add("longtou",1);
       check_longtou();
       return 1; 
}

void check_longtou()
{
        object me;
        me = this_player();
        if (query("longtou") >= 6)
        {
            message_vision(HIC"$N突然感觉龙头松了很多，"
                         "似乎可以拔(ba)起来了!。\n"NOR, me);
            me->set_temp("ba_longtou",1);
            delete("longtou");
        }
}

int do_ba(string arg)
{
        object me;
        me = this_player(); 
        if( ! me->query_temp("ba_longtou")) return 0;   

        if( !arg || arg != "shi longtou" && 
            arg != "longtou"  ) return notify_fail("你要拔什么东西!\n");
       
        message_vision(HIB"\n$N一把将龙头把了起来。 \n"NOR, me); 
        write(HIC"\n龙头似乎可以往左右转动，到底转哪边好呢? \n\n"NOR); 

        me->delete_temp("ba_longtou");             
        me->set_temp("zhuan_longtou", 1);
        return 1;    
}



int do_zhuan(string dir)
{
    object me; 
    object room;
    me = this_player();

    if (!me->query_temp("zhuan_longtou")) 
        return 0;

    if (!dir || dir =="") 
        return notify_fail("你要向哪个方向转动龙头!\n");
     
    if (dir == "left") 
    {
       message_vision(HIC"$N把龙头往左转了一转。\n"NOR, me); 
       add("zhuanmen", 1); 
       return 1;
    }

    if (dir == "right") 
    {
        if (query("zhuanmen")) 
        {   
           message_vision(HIG"\n$N把龙头又转了回去。\n"NOR, me); 
           message_vision(HIG"\n龙柱座落原位，果然与先前丝毫无异。\n"NOR, me);
           me->delete_temp("zhuan_longtou"); 
           delete("zhuanmen");

           room = find_object(__DIR__"yuanzi");
           if (! room) room = find_object(__DIR__"yuanzi");
 
           room->set("exits/down", __DIR__"jindi");
           message_vision(HIR"龙柱该是连接着钢索轴轮一类的东西，"
                           "$N感到扭动和震荡。\n\n"NOR,me );
           tell_object(me, HIY"不知道西寄园现在有什么动静没有？不妨去看一下。\n"NOR);

           tell_room(room, "突然井里的水位下降了好多，好象可以走下去了。\n");
 
           message("vision", HBRED"【宝藏传闻】" + me->query("name") + 
                          "成功开启了杨公宝藏!\n"NOR,users());
           remove_call_out("close");
           call_out("close", 180, room);
        } else 
        message_vision(HIC"$N把龙头往右转了一转。\n"NOR, me); 

        return 1;
     }
     else {
            write("你要向哪个方向转动龙头?\n");
            return 1;
          }

}

void close(object room)
{     
     if ( room )
     { 
        room->delete("exits/down");
        delete("longtou");  
        message_vision(HIG"突然出现咔咔的响声，水位又上了!\n"NOR, room);
     }
}

