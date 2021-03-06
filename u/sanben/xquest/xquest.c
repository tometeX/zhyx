
//趣味任务主文件   作者：瞎三笨  (根据原宗师任务创意改编)
//生平第一次写任务，所以垃圾了点，哈哈

                      
#include <ansi.h>

#define TAKE_NPC    "/u/sanben/xquest/npc/take_npc.c"//护送任务NPC的原型文件
#define SET_QUEST   "/u/sanben/xquest/set_quest.c" //随机决定任务信息的文件
#define TOTAL_QUEST  8  //从几种任务中随机抽取
#define LETTER      "/clone/misc/letter.c"         //物件书信的路径
#define RECEIPT     "/clone/misc/receipt.c"        //物件回执的路径
#define BAG         "/u/sanben/xquest/obj/bag.c"   //埋宝画图任务中NPC给的包裹
#define SET_ITEM    "/u/sanben/xquest/set_item.c"  //产生奖励item的文件
#define HULU_INSIDE  "/u/sanben/obj/hulu_inside"   //紫金葫芦内部的路径


//问线索，随机抽取任务
int accept_ask(object npc,object me,string topic)
{      
        
         
        int div, add;
         

         if ( me->is_busy() )
          {
                write("你正忙呢，没空跟人打听消息！\n");
                return 1;
         }

         if ( time() - me->query("xquest/last_ask") < 5 )
         {
                write("你老是连着问人家不烦吗?\n");
                return 1;
         }
         if ( time() - me->query("xquest_total_ask/time") > 3600 * 24 )
         {
                me->delete("xquest_total_ask");
                me->set("xquest_total_ask/time", time());
         }
         else
         {
         if ( me->query("xquest_total_ask/total") >= 3000
              && me->query("combat_exp") < 2000000)
         {
            message_vision(CYN "$N" CYN "盯着$n看了看，说道：“对不起，24小时内"
                            "只能做3000个任务！”\n"NOR,
                            npc, me);
                        return 1;
         }
      }
        
          if ( me->query("xquest/mirror") )
         {
            message_vision(CYN "$N" CYN "说道：“请你先完成一个宝镜任务"
                            "我再告诉你线索！”\n"NOR,
                            npc, me);
                        return 1;
         }
        me->set("xquest/last_ask", time() );

        //第七类任务，猜谜语(判断回答是否正确有效)
        if ( me->query("xquest/init_npc") == npc->name() &&
             me->query("xquest/kind") == "guess_riddle" )

        {
           if ( time() - me->query("xquest/time") > 300 )

           {
              message_vision(WHT "$N" WHT "对$n说道：“很抱歉，你已经超过"
                             "回答谜语的时间了！”\n"NOR, npc, me);
              return 1;
           }
           tell_object(me, WHT "你对" + npc->name() + "说道：“"
                       "谜底是不是"NOR HIG + topic + NOR WHT"呢？”\n");

           message("vision",WHT + me->name() + "对" + npc->name() + "说道"
                    "：“谜底是不是"NOR HIG + topic + NOR WHT"呢？”\n"NOR,
                    environment(me),({me}));


           if ( topic != me->query("xquest/answer") )
           {
              message_vision(WHT "$N" WHT "对$n说道：“很抱歉，猜错了哟，"
                             "呵呵！”\n"NOR, npc, me);

              tell_object(me, HIR "你还有" + chinese_number(300 - time() +
                              me->query("xquest/time") ) +
                              "秒钟时间作答。\n"NOR);

              return 1;
           }
           if ( topic == me->query("xquest/answer") )
           {
              message_vision(HIC "$N" HIC "对$n说道：“哇，猜对了，你真聪明"
                             "！”\n"NOR, npc, me);

              div = 4;     //设置猜谜语任务奖励计算的参数
              add = 80;
              call_other(XQUEST,"reward",me, div, add);

              return 1;
           }
        }

        if ( topic != "线索" )
        return 0;

        if ( me->query("xquest/init_npc") == npc->name() )
        {
           message_vision(HIY "$N" HIY "不耐烦地对$n" HIY "说道：“你这人怎么"
                                 "这么啰嗦，我不是已经告诉你要你干啥了吗！”\n"
                                 NOR, npc, me);
           return 1;
        }

        if ( me->query("xquest/target_npc") != npc->name() )
        {  return 0; }

        if ( me->query("xquest/kind") != 0 )
        {
           message_vision(HIY "$N" HIY "对$n" HIY "说道：“嗯......任务"
                                 "要是没法完成就去紫虚道人那里取消吧！“\n"NOR,
                                 npc, me);
           return 1;  
        }


       switch(random(TOTAL_QUEST))
        {    
        case 0 :
                me->start_busy(2);                
                call_other(XQUEST, "send_letter", me, npc);
                break;
        case 1 :
                me->start_busy(2);               
                call_other(XQUEST, "buy_thing", me, npc);
                break;
        case 2 :
                me->start_busy(2);                
                call_other(XQUEST, "buy_thing", me, npc);
                break;

        case 3 :
                me->start_busy(2);               
                call_other(XQUEST, "take_npc", me, npc);
                break;

        case 4 :                
                call_other(XQUEST, "pay_gold", me, npc);
                break;
        case 5 :                
                call_other(XQUEST,"do_drawing", me, npc);
                break;
        case 6 :               
                call_other(XQUEST, "take_npc", me, npc);
                break;
        case 7 :                
                call_other(XQUEST, "guess_riddle", me, npc);
                break;
         default:
                 me->start_busy(2);               
                call_other(XQUEST, "buy_thing", me, npc);
                break;

        } 
        return 1;
}

//第一类任务，送信给指定NPC(先产生信件及目标NPC）
void send_letter(object me, object init)
{
       object ob, letter;
       string npc, place, name;

       
       npc = call_other(SET_QUEST, "set_npc");
       sscanf(npc, "%s/%s", place, name);

       if ( name == 0 || name == "" || name == init->name())
       //如果目标NPC与任务提出NPC为同一个
          {

            call_other(XQUEST,"send_letter", me, init);
            return;
          } //则重新呼叫涵数再次抽取名字

      if ( name != 0 && name != ""  &&  name != init->name() )
        //取出有效的名字以后
       {
           me->set("xquest/kind", "send_letter");  //记录任务种类为送信
           me->set("xquest/init_npc", init->name()); //记录发出任务的NPC的名字
           me->set("xquest/target_npc", name);  //记录目标NPC的名字
           me->set("xquest/place", place);      //记录目标NPC所在的地点
           me->set("xquest/time", time());     //记录任务开始的时间
           letter = new(LETTER);
           letter->set("long", "这是一封" + init->name() + "写给" +
                             name + "的亲笔信函。\n");
           letter->set("init_npc", init->name());
           letter->set("target_npc", name);
           letter->move(me);

           tell_object(me, WHT + init->name() + "悄悄在你耳边说道：“" +
                       "这封信麻烦你尽快帮我送到"NOR HIY + place + WHT"的"HIY +
                       name + NOR WHT"手里，\n"
                       "然后再把回执拿回来，我就告诉你点消息。”\n"NOR  +
                       init->name() + "说着就拿出一封信给你。\n");

            message("vision",WHT + init->name() + "在" + me->name() +
                    "耳边小声吩咐着什么。\n" + me->name() + "一边听，"
                    "一边不住地点头 。\n"NOR +  init->name() +
                    "说完就拿出一封信交给了" +  me->name() + "。\n",
                    environment(init),({me}));
      }
      return;
}


//第三类任务，帮NPC买东西 (产生并发放任务)

void buy_thing(object me, object init)
{
       object item;
       string item_path, item_name,msg;

       item_path = call_other(SET_QUEST, "set_item");
       item = new(item_path);


       if ( item == 0 )
       {
           call_other(XQUEST,"buy_thing", me, init);
           return;
       }
       else  {

             item->move(init);
             item_name = ( find_object(item_path)->name() );
             destruct (item);
          if ( sizeof(filter_color(item_name)) > 0 )
          {
            tell_object( me,WHT + init->name() + "在你耳边悄悄说道：“"
                       "我正愁找不到"NOR + item_name + WHT
                       "你要是能帮我把这东西买来我就告诉你点消息。”\n");
          }
          else
          {
            msg = call_other(TEXT2PIC_D,"Display",filter_color(item_name));
            tell_object( me,WHT + init->name() + "在你耳边悄悄说道：“"
                       "我正愁找不到一样东西,"
                       "你要是能帮我把这东西买来我就告诉你点消息。”\n"NOR);
            write(msg +"\n");
          }

          message("vision",WHT + init->name()
                  + "在" + me->name() +  "耳边小声吩咐着什么。\n" +
                  me->name() + "一边听，一边不住地点头 。\n"NOR,
                  environment(me),({me}));

           me->set("xquest/kind", "buy_thing");  //设置任务种类为买东西
           me->set("xquest/init_npc", init->name()); //设置发出任务的NPC的名字
           me->set("xquest/target_npc", init->name());  //设置目标NPC的名字
           me->set("xquest/item", item_name );
           me->set("xquest/time", time());     //设置任务开始的时间
                                             //买东西任务分发到此完成
                }
           return;

}

//第四类任务，护送NPC去某个地方 (产生并发放任务)
void take_npc(object me, object npc)
{
       object ob;
       string place, place1, place2;

       place = call_other(SET_QUEST, "set_place");
         if ( place == 0 || place == "")
       {
           call_other(XQUEST, "take_npc", me, npc);
           return;
       }

      if ( place != 0 && place != "")   {

        sscanf(place, "%s/%s", place1, place2);
      

        ob = new(TAKE_NPC);
        ob->move(environment(npc));
        ob->set("long", "他是" + npc->name() +
                        "的远房亲戚。\n");
        ob->set("leader",me);
        ob->set_leader(me);
        ob->set("dest", place2);

        me->set("xquest/kind", "take_npc");
        me->set("xquest/init_npc", npc->name());
        me->set("xquest/target_npc", ob->name());
        me->set("xquest/place1", place1);
        me->set("xquest/place2", place2);
        tell_object(me, WHT + npc->name() + "悄悄在你耳边说道：“"HIY +
                   ob->name() + NOR WHT"是我一位远房亲戚。\n"
                   "他年老体衰，行将就木，但是临死前想去趟"HIG + place1 +
                   NOR WHT"的"HIG + place2 + NOR
                   WHT"了却最后一桩心愿，\n我想请你送他一程。"
                   "等到了地头他自然会告诉你你想知道的事情。”\n"NOR);

        message("vision",WHT + npc->name() + "在" + me->name() +
                 "耳边小声吩咐着什么。\n" + me->name() + "一边听，"
                 "一边不住地点头 。\n"NOR,
                environment(ob),({me}));

        
         call_other(XQUEST,"create_npc",ob);
         return;
              }
}

//护送NPC去某地任务，延迟1秒给出NPC出现的描述
void create_npc(object ob)
{

     message_vision(CYN "只见$N" CYN "步履蹒跚地走过来,对" "$n" CYN
                    "做了个揖道：“老汉我时日无多了，咱们这就启程吧。”\n"NOR,
                    ob, this_player());
     //由于玩家意见,这部分取消
     if ( this_player()->query("combat_exp") >500000 && random(30) == -1 )
     {
        message_vision(HIY "$N" HIY "正要举步，突然只见金角大王驾着一朵乌云"
                       "飘了过来，气急败坏地说道：\n“本大王最讨厌你们这种"
                       "乐于助人的伪善之徒，今天看本大王给你点" NOR + HIR"C"NOR
                       HIM"O"NOR HIY"L"NOR HIG"O"NOR HIB"R"NOR HIR" SEE SEE！"
                       HIY"”\n"NOR, this_player());
        message_vision(HIW"只见金角大王举起手中的紫金葫芦，大喝一声“疾！”。"
                       "$N顿时化作一股清烟被收进了葫芦里。。。\n\n"NOR,
                       this_player());
        this_player()->move(HULU_INSIDE);
     }
}

//第五类任务，给NPC黄金换线索(此处发放任务)
void pay_gold(object me, object npc)
{
     
     int amount;

     me->set("xquest/kind","pay_gold");
     me->set("/xquest/init_npc",npc->name());

     amount = random(50) + 1;
     
     me->set("xquest/pay_amount", amount);

     tell_object(me, WHT + npc->name() + "露出一丝尴尬的神情，悄悄在你耳边说"
                     "道：“嗯...这个嘛...我最近手头有点紧，\n你要是能给我"NOR
                     HIY + chinese_number(amount) + "两"NOR + HIW"白银"NOR +
                     WHT"我就告诉你点消息。”\n"NOR);

     message("vision",WHT + npc->name() + "露出一丝尴尬的神情，悄悄在" +
                      me->name() + "耳边说了点什么。\n",
                      environment(npc),({me}));
     return;


}

//第六类任务，帮NPC埋宝贝并画图
void do_drawing(object me, object npc)
{
       object ob;
       string place, place1, place2;

       
       place = call_other(SET_QUEST, "set_place");
                
         if ( place == 0 || place == "")
       {
           call_other(XQUEST,"do_drawing",me, npc);
           return;
       }
        if ( place != 0 && place != "")

       {
           sscanf(place, "%s/%s", place1, place2);
           me->set("xquest/kind", "do_drawing");  //设置任务种类为画图
           me->set("xquest/init_npc", me->query("xquest/target_npc"));
            //设置发出任务的NPC的名字

           me->set("xquest/place1", place1);
           me->set("xquest/place2", place2);  //记录埋宝的地点
           me->set("xquest/buried", 0);    //记录宝物尚未埋藏
           tell_object( me,WHT + me->query("xquest/init_npc") +
                "在你耳边悄悄说道：“我最近发了一笔横财，怕有人来抢。\n"
                "你帮我把它埋到"NOR HIY + place1 + NOR WHT "的" NOR HIY +
                place2 + NOR WHT"去，再把那里的"
                "地形画下来交给我，这样我日后可以去取。\n"
                "一切都办妥后我自有酬谢。”\n");

                message("vision", WHT + me->query("xquest/init_npc") +
                "在" + me->name() +  "耳边小声吩咐着什么。\n" +
                me->name() + "一边听，一边不住地点头 。\n"NOR,
                environment(me),({me}));
           ob = new(BAG);
           ob->move(me,1);
           message_vision(CYN "$N" CYN "拿出一个包裹给$n。\n",
                               npc, me);
               return;
            //至此埋宝画图任务发放完毕
       }
}

//第七类任务，猜谜语 (产生谜语）

void guess_riddle(object me, object init)
{
       object ob;
       string riddle, pro, ans, *space;
       int i;

       space = ({"!","@","#","$","%","^","&","*","_","+","|"});

       riddle = call_other(SET_QUEST, "set_riddle");
       sscanf(riddle, "%s:%s", pro, ans);

       if ( pro == 0 || pro == "" )
       //如果取出的谜语为空
          {
            call_other(XQUEST,"guess_riddle", me, init);
            return;
          } //则重新呼叫涵数再次抽取谜语
        if ( pro != 0 && pro != "" )
        {

       /*    i = random(10);
           if ( i%2 == 0 ) i = i -1;
           pro = pro[0..i] + space[random(sizeof(space))] +
                 space[random(sizeof(space))] + pro[(i+1)..sizeof(pro)];

           i = random(10);
           if ( i%2 == 0 ) i = i -1;
           pro = pro[0..i] + space[random(sizeof(space))] +
                 space[random(sizeof(space))] + pro[(i+1)..sizeof(pro)];

           i = random(10);
           if ( i%2 == 0 ) i = i -1;
           pro = pro[0..i] + space[random(sizeof(space))] +
                 space[random(sizeof(space))] + pro[(i+1)..sizeof(pro)]; */

        message_vision(WHT "$N" WHT "对$n说道：“我今天很无聊，你来和我玩个"
                      "猜谜语的游戏吧，要是猜对了我就告诉你点消息。”\n"NOR,
                      init, me);
         tell_object(me, HIG + pro +
                  NOR HIY"\n指令是 ask npc<id> about 谜底    " NOR +
                  HIR"你得在五分种内回答\n"NOR);
        me->set("xquest/kind", "guess_riddle");
        me->set("xquest/init_npc", init->name() );
        me->set("xquest/riddle", pro);
        me->set("xquest/answer", ans);
        me->set("xquest/time", time());
        return;
        }
}



//接受物件时的反应
int accept_object(object me, object ob, object npc)
{
    int div, add,amount;    //根据不同任务计算奖励的参数
    object receipt, pay;
    string change_npc;

     if ( me->is_busy() )
          {
                write("你正忙呢，没空交东西给别人！\n");
                return 0;
         }

    if ( time() - me->query("xquest/last_give") < 5 )
         {
                write("你老是连着给东西人家不烦吗?\n");
                return 0;
         }
        
        me->set("xquest/last_give", time() );
       

      
  //  if ( npc == 0 ) { npc = this_object();}


    if ( me->query("xquest/target_npc") != npc->name())//若不是目标NPC
       return 0;                                       //则不接受任何物件

    if ( me->query("xquest/kind") == "send_letter")    //如果是送信任务
    {
       if ( ob->query("target_npc") != npc->name() )  /*如果此信件不是给目标
                                                       NPC的 */
       {
           tell_object( me, npc->name() + "看了看信，对你说道："
                        "“这封好像不是给我的信呀！”\n");
                        return 0;
       }
       else
       {
            if ((time() - me->query("xquest/time")) > 600 )//如果超过时间才送到
            {

                message_vision(CYN "$N" CYN "生气地对$n说道：“你怎么"
                               "这么迟才把这封信送来呀！耽误了我的大事了！”\n",
                               npc, me);
                tell_object(me, HIR"你看看" + npc->name() + "那气鼓鼓的样子" +
                            "，想来他是肯定不会再告诉你下一步的线索了。\n"NOR);
                return 1;
            }                  //任务失败，不提供下一步线索


            message("vision",WHT + npc->name() + "接过信看了看，满意地" +
                     "说道：“多谢这位" + RANK_D->query_respect(me)
                     + "把信送到。”\n"NOR,
                    environment(me));     //接受信件的描述
            destruct(ob);                 //销毁掉收到的信件避免积累
            //此处开始第二类任务，送到信后将回执带给原NPC

            me->set("xquest/kind", "bring_receipt");  //设置任务种类为送回执

            change_npc = me->query("xquest/init_npc");//将原任务提出者存到别处

            me->set("xquest/init_npc", me->query("xquest/target_npc"));
            //设置现任务（送回执）发出者为原任务（送信）的目标NPC

            me->set("xquest/target_npc", change_npc);
             //从change_npc中提取出原任务发出者，记为现任务目标NPC

            me->set("xquest/time", time());     //设置任务开始的时间
            receipt = new(RECEIPT);
            receipt->set("long", "这是一封" + me->query("xquest/init_npc") +
                                 "交给" + change_npc + "的回执。\n");
            receipt->set("init_npc", me->query("xquest/init_npc"));
            receipt->set("target_npc", change_npc);
                                          //以上将任务基本信息记录到回执上
            receipt->move(me);

            message_vision(CYN "$N" CYN "拿出一封回执给" "$n。\n"NOR,
                    npc, me);                    //给出回执的描述

              return 1;
        }
    }

    /*开始第二类任务接受回执的判断
     是否是交给目标NPC本涵数开始有判断，此处略过 */

     if ( me->query("xquest/kind") == "bring_receipt")    //如果是送回执的任务
    {
       if ( ob->query("target_npc") != npc->name() )  /*如果此回执不是给目标
                                                       NPC的 */
       {
           tell_object( me, npc->name() + "看了看回执，对你说道："
                        "“这封回执好像不是给我的呀。”\n");
                        return 0;
       }
       else
       {
           if ((time() - me->query("xquest/time")) > 300 )//如果超过时间才送到
            {

                message_vision(CYN "$N" CYN "生气地对$n说道：“你怎么"
                               "这么迟才把回执送来呀！害我担心了这么多天！”\n"
                               "说完就转过头去再也不理睬$n了。\n" NOR,
                               npc, me);
                tell_object(me, HIR"看这情形下一步线索又无望了。\n"NOR);
                return 1;
            }                  //任务失败，不提供下一步线索

            message("vision",WHT + npc->name() + "接过回执看了看，满意地" +
                     "说道：“多谢这位" + RANK_D->query_respect(me)
                     + "帮我这个大忙。”\n"NOR,
                    environment(me));     //接受回执的描述
             destruct(ob);               //销毁掉回执，避免积累
             div = 4;     //设置送回执任务奖励计算的参数
             add = 80;

             message_vision(CYN "$N从怀里掏出一些银子交给$n，说道：“这点是给"
                               "你的跑腿费。”\n" NOR,
                               npc, me);

             pay = new("/clone/money/silver");
             pay->set_amount(5+random(5));
             pay->move(me, 1);

             call_other(XQUEST,"reward",me, div, add);  //呼叫奖励涵数
             return 1;                            //送回执任务到此完成
       }
     }

     if ( me->query("xquest/kind") == "buy_thing")    //如果是买东西任务
    {
        if ( ob->name() != me->query("xquest/item") ) //如果不是NPC要的东西

        { message_vision(CYN "$N" CYN "对$n疑惑地说道：“咦？这个"
                               "好像不是我要的东西呀！”\n" NOR,
                               npc, me);
          return 0; }

        if ((time() - me->query("xquest/time")) > 600 )//如果超过时间才送到
        {
          message_vision(CYN "$N" CYN "不屑一顾地对$n说道：“你这么迟才把"
                               "这东西买来啊？我前几天已经找到了！”\n" NOR,
                               npc, me);
          tell_object(me, HIR"惨了，看来没法继续完成任务了，从头来过吧。\n"NOR);
          return 0;
        }    //找东西任务失败，不提供下一步线索

        else
        {
            message("vision",WHT + npc->name() + "接过"NOR + ob->name()+NOR WHT
                    "看了看，满意地说道：“多谢这位" + RANK_D->query_respect(me)
                     + "帮了我这个大忙。”\n"NOR,
                    environment(me));     //接受购买到物品的描述
            
            message_vision(CYN "$N从怀里掏出一点银子交给$n，说道：“这点是给"
                               "你的跑腿费。”\n" NOR,
                               npc, me);

             pay = new("/clone/money/silver");
             amount = ob->query("value") /100 + 1 + random(6);
             if ( amount < 6 ) amount = 6;
             pay->set_amount(amount);

             pay->move(me,1);             //报酬是原物品的价值 + n silver

              destruct(ob);                 //销毁掉收到的物品避免积累
             div = 4;     //设置找东西任务奖励计算的参数
             add = 100;

             call_other(XQUEST,"reward",me, div, add);  //呼叫奖励涵数
             return 1;                            //找东西任务到此完成

        }
    }

     if ( me->query("xquest/kind") == "pay_gold")    //如果是给钱买线索任务
    {
       if ( ! ob->query("money_id") )  //如果给的不是钱
       {
              message_vision(CYN "$N对$n不满地说道：“你要不就给钱，要不"
                                 "就走路，少拿这些东西来敷衍我！”\n" NOR,
                               npc, me);
              return 0;
       }
       if ( ob->value() / 100 < me->query("xquest/pay_amount") ) //给的钱不够
       {
              message_vision(CYN "$N对$n不满地说道：“你这人怎么这么婆婆妈妈"
                                 "的，\n肯给就爽快点给我"NOR  +
                                 chinese_number(me->query("xquest/pay_amount"))
                                 + "两" + HIW"白银" NOR CYN +
                                 "，要舍不得就趁早滚蛋，少在这儿啰嗦！”\n" NOR,
                                 npc, me);
              return 0;
       }
       else
       {     if ( random(3) == 1 )
             { message_vision(CYN "$N接过$n递上来的黄金，顿时喜上眉梢，"
                                 "连声说道：“好,好,您出手真阔绰，嘿嘿！”\n"
                                 "这一脸的肉麻相，看了真让人想吐。\n"NOR ,
                                 npc, me);
               destruct(ob);         //销毁掉收到的gold避免积累

           call_other(XQUEST,"next_quest",me);  //呼叫next_quest涵数产生新的任务

              return 1;
              }
              else
              {

               tell_object( me,WHT + npc->name() +
                "在你耳边故作神秘地说道：“这位" + RANK_D->query_respect(me) +
                "我和你说实话吧，刚才我只是试试你的人品如何。\n"
                "你出手既然如此大方，看来这件事我可以托你去办了！”\n"NOR);

                //此处呼叫产生第六种任务的涵数，帮NPC埋宝贝再画图

               call_other(XQUEST,"do_drawing", me, npc);

                return 0;
               }
       }
    }
       //此处判断是否接受图画
      if ( me->query("xquest/kind") == "do_drawing")    //如果是埋宝画图任务
    {
        if ( me->query("xquest/init_npc") != npc->name() )//若不是这个NPC发放的
        return 0;

        if ( ! ob->id("paper of drawing") )            //给的不是纸张的话
        return 0;

        if ( me->query("xquest/buried") == 0 )          //如果没有埋宝

        {
           message("vision",WHT + npc->name() + "哼了一声，说道：“" +
                   me->name() + "你以为我是白痴吗？\n这几天我一直派人跟踪你，"
                   "发现你根本没去埋我的宝贝。\n老实交待你是不是把我的宝贝贪污了"
                   "然后随便拿张图画来敷衍我？！”\n"NOR, environment(me));
           return 0;

        }

         if ( ! ob->query("draw/info") )
        {
           message("vision",WHT + npc->name() + "说道：“" + me->name() +
                   "你拿张白纸给我干什么，有病啊!”\n"NOR, environment(me));
           return 0;

        }

     if ( ob->query("draw/info") == "unknow" )
        {
           message("vision",WHT + npc->name() + "说道：“" + me->name() +
                   "你这画的是什么哟！”\n"NOR, environment(me));
           return 0;

        }
        if ((ob->query("draw/info") )->short() != me->query("xquest/place2") )
        {
           message("vision",WHT + npc->name() + "说道：“" + me->name() +
                   "你可看清楚了，我要你把我的宝贝埋在"NOR HIY +
                   me->query("xquest/place2") + NOR WHT"\n再把那里的地形画下"
                   "来，可你这是给我画的哪里呀！”\n"NOR, environment(me));
           return 0;

        }
        destruct(ob);
        message_vision(CYN "$N接过$n递上来的图画看了看，满意地说道：“嗯，不"
                           "错，正是这个地方。这一躺有劳你了。\n"
                           "这点银子是给你的酬劳。说着就从怀里摸出点银子交"
                           "给了$n。\n"NOR, npc, me);

        pay = new("/clone/money/silver");
        pay->set_amount(5 + random(5));
        pay->move(me, 1);                      //给酬劳

        div = 3;
        add = 80;                              //设置奖励系数


        call_other(XQUEST,"reward", me, div, add);  //呼叫奖励涵数
        return 1;                             //埋宝画图任务到此结束

    }
    return 0;
}

void reward(object me, int div, int add)      //计算奖励
{
     int exp, pot, tihui, score, weiwang, num, multi;

     me->set("xquest/kind",0);     //设置现在为没有任务状态
     me->add("xquest_count",1);   //累计完成数量增加一个
     if ( me->query("xquest_count") > 500 )
     { me->set("xquest_count",1); }     //累计超过500则变1

     num = me->query("xquest_count");

   //  if ( me->query("xquest_count") < 20 ) { num = 20;}
     if ( me->query("xquest_count") > 250 ) { num = 250;}

     exp =  ( num / div + random(100) ) * 2 + add;
     pot =   num / div + random(100) + add ;


     tihui = random( num/div ) ;
    // tihui = 1 + random(2);
     tihui += 10;
     
     multi = 2;

     if ( me->query("combat_exp") > 300000 ) multi = 1;

     exp *= multi;
     pot *= multi;
     tihui *= multi;

  
     if ( me->query("combat_exp") > 2000000 )
     {
        exp /= 16;
        pot /= 16;
      //  tihui /= 16;
        tihui = 1;
     } else   
     if ( me->query("combat_exp") > 1000000 )
     {
        exp /= 8;
        pot /= 8;
      //  tihui /= 8;
        tihui = 1;
     } else
     if ( me->query("combat_exp") > 800000 )
     {
        exp /= 4;
        pot /= 4;
        tihui /= 4;
     }
       else
     if ( me->query("combat_exp") > 500000 )
     {
        exp /= 2;
        pot /= 2;
        tihui /= 2;
     }

     if ( me->query("combat_exp") < 1000000 )
     {
        score = random(50) + 10;
        weiwang = random(50) + 10;
     }
else
     {
        score = random(5) + 5;
        weiwang = random(5) + 5;

     }

     if ( me->query("potential") >= me->query_potential_limit() )
     {  pot = 1; }
     if ( me->query("experience") >= me->query_experience_limit() )
     {  tihui = 1; }

     me->add("combat_exp", exp );
     me->add("potential", pot );
     me->add("experience", tihui);
     me->add("score", score);
     me->add("weiwang", weiwang);

     me->start_busy(2);
     tell_object( me, HIG"\n通过这次锻炼，你获得了"NOR HIR + chinese_number(exp) +
                  HIG"点经验，"NOR HIW + chinese_number(pot) + NOR
                  HIG"点潜能以及"HIY +
                  chinese_number(tihui) + HIG"点实战体会。\n" +
                  "江湖阅历以及威望也都有了不同程度的提高。\n" NOR);

     if ( me->query("xquest_count") % 100 == 0 )  //完成整百数任务给予item奖励
     {

        call_other(XQUEST,"item_reward", me);

     }

     call_other(XQUEST,"next_quest",me);  //呼叫next_quest涵数产生新的任务
     return;
}

void next_quest(object me)   //产生下一个任务线索的涵数
{
       string npc, place, name;

       npc = call_other(SET_QUEST, "set_npc");
       sscanf(npc, "%s/%s", place, name);

       me->set("xquest/kind",0);
       me->add("xquest_total_ask/total", 1 );
  //     if ( random(40) == 1 ) me->set("xquest/mirror",1);

       if ( name == "" || name == 0 ||
             name == me->query("xquest/target_npc")
         ||  name == me->query("xquest/init_npc") )  //如果新的
          {                                   //目标NPC与目前发任务NPC为同一个
            call_other(XQUEST,"next_quest", me);
             return;
          }                                     //则重新呼叫涵数再次抽取名字

       if ( name != "" && name != 0 && 
             name != me->query("xquest/target_npc")
         && name != me->query("xquest/init_npc") )
          {
                tell_object( me,WHT + me->query("xquest/target_npc") +
                "在你耳边悄悄说道：“你不妨去找"NOR HIY + place + NOR WHT"的"
                NOR HIY + name + NOR WHT"打听打听，他那里可能有些线索。”\n");

                message("vision",WHT + me->query("xquest/target_npc")
                + "在" + me->name() +  "耳边小声吩咐着什么。\n" +
                me->name() + "一边听，一边不住地点头 。\n"NOR,
                environment(me),({me}));
                me->set("xquest/place", place);
                me->set("xquest/init_npc", me->query("xquest/target_npc") );
                me->set("xquest/target_npc", name);
          }
          return;

}

void item_reward(object me)
{
        object item;
        string gift;

    if ( random(2) > -1 )
    {
        gift = call_other(SET_ITEM, "set_item", me);
        if ( gift == 0 || gift =="" )
        {
           call_other(XQUEST,"item_reward", me);

        }  else

        if ( gift != 0 && gift !="" )
        {

           item = new(gift);
           item->move(me);

           message_vision(HIC"正在这时只见乌有道人匆匆忙忙地跑来对$N说道:“我"
                           "师兄说你现在帮人排忧解难连着做了不少好事，\n因此特"
                           "意让我给你带点礼物来。”\n说着就从怀里摸出点东西"
                           "交给了$N\n"NOR, me);
           if ( item->query("base_unit") )
           {
              tell_object(me,HIG"你获得了一" + item->query("base_unit") + NOR +
              item->name()+ "\n");
           }   else
           {
           tell_object(me,HIG"你获得了一" + item->query("unit") +  NOR +
           item->name()+ "\n");
           }
        }
     }
      else
     {
           message_vision(HIC"正在这时只见乌有道人匆匆忙忙地跑来对$N说道:“嗯,"
                           "你现在帮人做好事干得不错，继续努力\n到时候"
                           "我会给你物质奖励。”\n说完就架着云飞走了。"NOR, me);
     }
}


