#include <ansi.h>
inherit ROOM;

       void create() 
       { 
                   set("short", HIY "\n\n中 华 购 物 中 心" NOR);
                   set("long", HIG "这里是中华会员购物中心，只见这里"
                               "四周宽敞明亮，不远处\n整齐地摆放着很多"
                               "自动售货机(ASM)。\n" NOR
                   );
                   set("exits", ([
                          "west"  :  "/u/yuchang/center/dating",
                   ]));

                   set("no_fight", 1); 
                   set("item_desc", ([ 
                          "asm"  :    "机器屏幕上显示：" HIM + BLINK" 请插入(insert)你的会员卡 " NOR 
                                      "的字样，机器上\n布满着各种奇怪的按扭。\n",
                   ]));

                   setup();     
       } 


void init()
{
        add_action("do_insert", "insert");
        add_action("do_pull", "pull");
        add_action("do_list", "list");
        add_action("do_buy", "want");
        
}
int do_insert(string arg)
{
        object me, ob;
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "card" || arg == "zhyx card")
        {
                if (! ob = present("zhyx card", me)) return 0;

                if (me->query("temp/insert"))
                        return notify_fail("卡还没取呢!\n");

                if (me->is_busy())
                {
                        return notify_fail("你正忙着呢。\n");
                        return 1; 
                }
                destruct(ob);
                write(HIW "你将卡片插入自动售货机...\n" NOR);
                write(HIY "中华自动售货机正在读取你卡上的数据，请稍后...\n" NOR);
                me->set("temp/insert", 1);
                call_out("show", 4 + random(2));
                return 1;
        }
}

//数据读取完毕，允许购物
int show()
{  
   int rmb;
   object me = this_player();
   rmb = this_player()->query("rmb");
   tell_object(me, HIC "你目前的存款为" + chinese_number(rmb) + "圆人民币。\n" NOR);
   write(HIG "数据读取成功，请输入(list)显示可以购买的物品，输入(want)购买物品。\n" NOR);
   this_player()->set("temp/can_pull", 1);
     
   return 1; 
}

int do_list()
{
   string msg;
   if (! this_player()->query("temp/insert"))
   {
           write("请先插入会员卡。\n");
           return 1;
   }
  msg = HIC "【名称】                           \t【作用】            【成功率】                【价格】\n\n" NOR;
  msg +=HIG "真命天子(zhenming tianzi)              特殊先天属性            100%                   ￥1000.00\n";
  msg +=HIG "九天玄女(jiutian xuannv)               特殊先天属性            100%                   ￥1000.00\n";
  msg +=HIG "天煞孤星(tiansha guxing)               特殊先天属性            100%                   ￥1000.00\n";
  msg +=HIG "十级神兵(shiji shenbing)               自制    武器            100%                   ￥500.00\n";
  msg +=HIG "寰宇天晶(tian jing)                    武器    材料            100%                   ￥500.00\n";
  msg +=HIG "返老还童丹(huantong dan)               降低    年龄            100%                   ￥500.00\n";
  msg +=HIG "绝世好剑(jiushi haojian)               转世    物品            100%                   ￥200.00\n";
  msg +=HIG "麒 麟 臂(qinlin bi)                    转世    物品            100%                   ￥200.00\n";
  msg +=HIW "女 娲 石(nvwa shi)                     转世    物品            100%                   ￥200.00\n";
  msg +=HIW "金 刚 圈(jingang quan)                 转世    物品            100%                   ￥200.00\n";NOR;

  write(msg);
  return 1;

}

int do_pull(string arg)
{
        object me,ob;
        int rmb;
        me = this_player();

        if (! arg || (arg != "card" && arg != "zhyx card"))
                return 1;

        if (me->is_busy())
        {
                return notify_fail("你正忙着呢。\n");
        }
        // 判断卡片是否未取出
        if (me->query("temp/insert") && me->query("temp/can_pull"))
        {      
                rmb = me->query("rmb");
                tell_object(me, HIC "你目前的存款为" + chinese_number(rmb) + "圆人民币。\n" NOR);
                write(HIW "你将卡片从中华自动售货机中取出。\n" NOR);
                ob = new("/clone/gift/hycard.c");
                ob->move(me);
                me->delete("temp/insert");
                return 1;
        }
        write(HIR "操作错误!\n" NOR);
        return 1;
}


int do_buy(string arg)
{
    object me, ob;
    int rmb, feng,sun,lighting,water;
    
    me = this_player();
    rmb = me->query("rmb");
    
    if (! arg || arg == "") return 1;
    
    if (arg == "tian jing")
    {
          if (rmb < 500)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/d/death/obj/tianjing");
          ob->move(me);
          me->add("rmb", -500); 
          write(HIG "你买下一块寰宇天晶！\n" NOR);       
    } 
  else  if (arg == "zhenming tianzi")
    {
          if (rmb < 1000)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          me->set("special_skill/youth", 1);
          me->set("special_skill/emperor", 1);
          me->add("rmb", -1000);  
          write(HIG "你买下真命天子特殊属性！\n" NOR);
    }    
    else  if (arg == "jiutian xuannv")
    {
          if (rmb < 1000)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          me->set("special_skill/youth", 1);
          me->set("special_skill/queen", 1);
          me->add("rmb", -1000);  
          write(HIG "你买下九天玄女特殊属性！\n" NOR);
    }      
    else  if (arg == "tiansha guxing")
    {
          if (rmb < 1000)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          me->set("special_skill/youth", 1);
          me->set("special_skill/lonely", 1);
          me->add("rmb", -1000);  
          write(HIG "你买下天煞孤星特殊属性！\n" NOR);
    } 
    else if (arg == "huantong dan")
    {
          if (rmb < 500)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/huantong");
          ob->move(me);
          me->add("rmb", -500);  
          write(HIG "你买下一颗返老还童丹！\n" NOR);
    }    
    else if (arg == "jiushi haojian")
    {
          if (rmb < 200)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/jiushi");
          ob->move(me);
          me->add("rmb", -200);  
          write(HIG "你买下一把绝世好剑！\n" NOR);
    }        
    else if (arg == "麒 麟 臂")
    {
          if (rmb < 200)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/qilin");
          ob->move(me);
          me->add("rmb", -200);  
          write(HIG "你买下一个麒麟臂！\n" NOR);
    }        
    else if (arg == "nvwa shi")
    {
          if (rmb < 200)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/shi");
          ob->move(me);
          me->add("rmb", -200);        
          write(HIG "你买下一块女娲石！\n" NOR);
    }        
    else if (arg == "tian jing")
    {
          if (rmb < 200)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/quan");
          ob->move(me);
          me->add("rmb", -200);        
          write(HIG "你买下一个金刚圈！\n" NOR);
    }        
    else if (arg == "shiji shenbing")
    {
          if (rmb < 500)
          { 
              write("对不起,你的卡上余额已不足,请尽快充值!\n" NOR);
              return 1;
          }   
          write(HIG "请和在线WIZ联系，WIZ将帮你办理购买程序！\n" NOR);      
    }                
    else{
          write(HIR "操作错误！\n" NOR);
          return 1;
    }
    write(HIG "操作完成! 离开前请记得取出(pull)卡片。\n");
    rmb = me->query("rmb");
    tell_object(me, HIC "你目前的存款为" + chinese_number(rmb) + "圆人民币。\n" NOR);
    if (me->query("rmb") < 10) 
          write(HIY "你的余额已不多，为避免给你带来的不便，请及时充值。\n" NOR);
    return 1;
}



