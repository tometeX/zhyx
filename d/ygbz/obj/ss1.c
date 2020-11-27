#include <ansi.h>   
inherit ITEM;
void create()
{
        set_name(HIW"圣舍利"NOR, ({ "sheng sheli","sheli"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIB"这颗圣舍利又名为邪帝舍利,听说内含大秘密!
您碰到他的时候感到里面似乎有股力量,你不禁生出吸吸(xi)看的念头\n"NOR);
                set("unit", "颗");
}
    setup();
}
void init()
{
    if (query("zhuren")!=this_player()->query("id"))
return 0;
        add_action("do_xi", "xi");
}
int do_xi(string arg)
{
  object me = this_player();
  int maxneili,neili;
    neili = me->query("neili");
    maxneili = me->query("max_neili");
    
  if(!id(arg)) return 0;
  if(me->is_busy()) return notify_fail("你上一个动作还没有完成。\n");

if ((int)me->query("neili") > (int)me->query("max_neili") * 2)
                 return notify_fail("你的内力已经到达了极限，再吸收下去会走火入魔\n");

     if( environment(me)->query("no_fight"))
                return notify_fail("这里不适合吸毒。\n");

  if(!me->query("zjbygbz_max"))
{
 if(!query("bei_eat"))
{
   me->add("max_neili",me->query("max_neili")/10);

 write(HIC "你猛的一颤,感觉一股奇怪的内劲源源不断的从"HIW"圣舍利"NOR"里传
到了自己的体内,你感觉自己的内力值有了明显的增加!\n" + NOR);

     me->set("zjbygbz_max",1);
   set("bei_eat",1);
}
}
if(me->query_temp("ssl_xi"))
{
 if(me->query_temp("ssl_zjb")+5 > time())
  return notify_fail("您正在吸取圣舍利的内力呢。\n");
}
me->set_temp("ssl_xi",1);
me->set_temp("ssl_zjb",time());
    
    me->add("neili",maxneili/3);  
    
 write("你定了定神,双手按到"HIW"圣舍利"HIG"上,感到一股内劲从
"HIW"圣舍利"NOR"中传到了自己的体中\n" + NOR);

if (!me->query("zjbygbz_ssl"))  { 
  if (random(6)>=3) 
  me->set("zjbygbz_ssl","daoxin");
 else 
 me->set("zjbygbz_ssl","zhanshen");
}
  switch(me->query("zjbygbz_ssl"))
  {
  case "daoxin":   
    call_out("on_daoxin", 1);
    break;
    case "zhanshen":
    call_out("on_zhanshen", 1);
    break;
  }
return 1;
}
void on_zhanshen(object me)
{
  me = this_player(); 
me->improve_skill("zhanshen-lu", random((int)me->query_int() * 8 - 9));
 me->delete_temp("ssl_xi");
  if (random(10)>8)    me->start_busy(1);

message_vision(MAG"\n"+me->name()+"的战神录进步了!\n"NOR, this_player());
   write("在吸取圣舍利内力的时候,突然脑中出现了!一些奇怪的画面,
感到自己的"HIM"战神录"NOR"一些不明白的地方突然想通了!\n" + NOR);

return;
}
void on_daoxin(object me)
{
  me = this_player(); 
  me->improve_skill("daoxin-zhongmo", random((int)me->query_int() * 8 - 9));
 me->delete_temp("ssl_xi");
  if (random(10)>8)    me->start_busy(1);

message_vision(WHT"\n"+me->name()+"的道心种魔大法进步了!\n"NOR, this_player());
   write("在吸取圣舍利内力的时候,突然脑中出现了!一些奇怪的画面,
感到自己对"HIW"道心种魔大法"HIB"一些不明白的地方突然想通了!\n" + NOR);
  
return;
}
