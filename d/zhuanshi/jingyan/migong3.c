#include <room.h>
#include <ansi.h>
inherit ROOM;

void random_exit(object room);

void create()
{
        set("short", "右雁殿");
        set("long", @LONG
右雁殿里空无一物，四周墙上刻满浮雕(relievo)。
这些浮雕造型高古，手工细致精雅，工程惊人庞大，内
容令人难解，描绘的都是些奇禽异兽。你虽见识宽广，
但浮雕上的异兽竟是一样也没见过，真是奇怪之极！
LONG);
       set("item_desc", ([       
"relievo" : "你发现浮雕有点凹凸不平，若不是有目标的查察，
必会当是石纹忽略过去,你不禁想按下(press)浮雕!\n",  
       ]));              
       set("exits", ([
                "west" :__DIR__"migong2",                                           
       ]));             
      setup();
} 
void init()
{  
     add_action("do_press", "press");
     add_action("do_pull", "pull"); 
     add_action("do_turn", "turn");
}

 int do_press(string arg)
{
     object me = this_player();

     if( !arg || arg != "relievo" ) 
         return notify_fail("你是不是想按浮雕(press relievo)？\n");
                            
       
     message_vision(HIC"$N把浮雕用力往里按了一下!\n"NOR, me);
     add("press",1);  

    if (query("press") == 6)
    {
       message_vision(HIC"$N这次按下后突然有块浮雕凸了出来!\n\n"NOR, me);
       tell_object(me, HIW"你不妨试试(pull relievo)。\n\n"NOR);       
       set("can_pull", 1);
       remove_call_out("on_del");
       call_out("on_del", 10, me);
    }

    if (query("press") > 6 )
   {
       message_vision(HIG"$N按过头了,浮雕又陷了回去!\n"NOR, me);       
       delete("press");
       delete("can_pull");
   }
   return 1;
}

void on_del(object me)
{
    object ob = this_object();
    ob->delete("press");
    tell_room(ob, HIW"凸起的浮雕重又陷落了下去。\n\n"NOR);
    ob->delete("can_pull");    
}

int do_pull(string arg)
{
        object me;
        me = this_player(); 

        if(!query("can_pull")) return 0;   

        if( !arg || arg != "relievo" ) 
            return notify_fail("你是要拉浮雕(pull relievo)吗？\n");
          
        message_vision(HIB"$N一把将浮雕拉了起来。\n\n"NOR, me);
        tell_object(HIG"你突然发现浮雕似乎可以往左右转动，转哪边好呢? \n\n"NOR);
         
        delete("can_pull");
        set("can_turn", 1);
        return 1;      
}

int do_turn(string dir)
{
    object me; 
    object room;
    
    me = this_player();

    if ( ! query("can_turn")) return 0;

    if (!dir || dir != "right" && dir != "left") 
        return notify_fail("你要往哪个方向转动浮雕，(right还是left)？\n");
    
    if (dir == "left") 
    {
       message_vision(HIC"$N把浮雕往左转了一转。\n"NOR, me); 
       add("turn", 1);        
    }
    if ( dir == "right") 
   {
       message_vision(HIC"$N把浮雕往右转了一转。\n"NOR, me); 
       if (query("turn") > 5) 
       {          
          message_vision(HIC"$N这次转动后，浮雕座落原位，"
                             "竟与先前丝毫无异。\n"NOR, me);                        
          delete("can_turn");      
                        
          if (!objectp (room = find_object(__DIR__"migong5")))
              room = load_object(__DIR__"migong5") ;

          random_exit(room);

          message_vision("浮雕该是连接着一些机关，$N感到扭动和震荡。\n",me );

          tell_room(room, HIB"突然这里出现九个大洞，"
                    "不知道哪个才通往密道。\n\n"NOR);
 
          message("vision", HIW"【惊雁宫传闻】" + me->query("name") + 
                   "成功打开了惊雁宫密道。!\n"NOR,users());
          remove_call_out("close");
          call_out("close", 180);
        }
    }
    return 1;        
}

void close()
{ 
     int i;
     object room;

     if( room = find_object(__DIR__"migong5") ) 
     {
       for(i = 1; i < 10; i++)     
          room->delete("exits/" + i);       
          tell_room(room,HIG"突然出现咔咔的响声，洞口又消失了!\n"NOR);
     }
}

void random_exit(object room)
{  //这里还得改，这么设计会折腾死人的！！！！
   /*  int i;
     int *a = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
     int x = random(9) + 1;
     for(i = 1; i < 10;       
     room->set("exits/" + x , __DIR__"lev1/dong01");
                a -= ({x});
                
     for( i = 0; i < 8;i++)
         room->set("exits/"+a[i], "/d/city/wumiao");    */  
                        
                        //return x;//返回值为通往密道房间的数值
                        return;
}

