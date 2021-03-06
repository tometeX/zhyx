// 紫金葫芦内部
#include <room.h>
#include <ansi.h>

//inherit ROOM;
inherit CREATE_CHAT_ROOM;
int is_chat_room() { return 1; } 


#define MASTER "sanben"
#define HULU_INSIDE  "/u/sanben/obj/hulu_inside"

string look_paizi();

void create()
{
        set("short",NOR YEL"紫金葫芦内部"NOR);
        set("long", YEL"\n"
"这里是紫金葫芦的内部，四周空荡荡的，使你有种无所适从的感觉。\n"
"你感到很压抑，真想赶快离开这里，但是怎么也找不着出口。听说\n"
"要离开这里唯一的办法就是开动脑筋猜出一个葫芦给你设定的四位\n"
"数。关于规则可以看看牌子。\n"
"    旁边有一个牌子(paizi)。\n"NOR);
        set("no_fight", 1);
        set("item_desc", ([
                "paizi" : (: look_paizi :),
        ]));
}

void init()
{
        object me = this_player();

        if ( me->query("id") != MASTER )
        {
           me->set("startroom", HULU_INSIDE);
        add_action("do_suicide", "suicide");
        add_action("do_drop", "drop");
        add_action("do_give", "give");

        add_action("no_go", "rideto");
        add_action("no_go", "rideto1");
        add_action("no_go", "miss");
        add_action("no_go", "flyup");

        add_action("no_go", "trans");
        add_action("no_go", "recall");

        add_action("do_quit", "quit");
        add_action("do_quit", "exit");
        //wiz的法力也消失了，哈哈
        add_action("no_power", "home");
        add_action("no_power", "goto");
        add_action("no_power", "flyto");

        add_action("no_power", "more");
        add_action("no_power", "edit");
        add_action("no_power", "ls");
        add_action("no_power", "cd");
        add_action("no_power", "rm");
        add_action("no_power", "mv");
        add_action("no_power", "cp");

        add_action("no_power", "kickout");
        add_action("no_power", "purge");
        add_action("no_power", "summon");
        add_action("no_power", "promote");
        add_action("no_power", "throw");
        add_action("no_power", "dest");
        add_action("no_power", "auth");
        add_action("no_power", "free");
        add_action("no_power", "grant");
        add_action("no_power", "update");
        add_action("no_power", "data");
        add_action("no_power", "info");
        add_action("no_power", "call");
        add_action("no_power", "clone");
        add_action("no_power", "dual");

        add_action("do_guess", "guess");
        add_action("do_giveup", "giveup");
        message_vision(HIY"只听“咵啦”一声，$N被装进了葫芦里。\n"NOR,
                                                this_player());
        call_other(HULU_INSIDE, "set_number", me);
        }
}


int do_suicide()
{
        write(HIB"不要这么看不开嘛，何必自寻短剑呢！\n"NOR);
        return 1;
}

int do_give()
{
        write(HIG"这里不能给东西！\n"NOR);
        return 1;
}

int do_drop()
{
        write(HIG"这里不能乱仍东西！\n"NOR);
        return 1;
}

//想借助工具逃跑？

int no_go()
{
        write(YEL"紫金葫芦里面哪能说走就走！\n"NOR);
        return 1;
}


int do_quit()
{
        write(HIR"你现在就是退出游戏下回连线进来还是在这里，"
              "所以还是别quit了吧！\n"NOR);
        return 1;
}

//巫师也跑不了！ 哈哈 (当然除了主人瞎三笨,keke)

int no_power()
{
        write(HIC"到了这里就算是巫师也没法力了！你死定了，哈哈！\n"NOR);
        return 1;
}

string look_paizi()
{
    string msg,*result,*number;
    object me;
    int i;

    me = this_player();

    msg = HIG"\n葫芦的自白：其实我本来是太上老君炼制出来的法宝，但是现\n"
             "在被金角大王胁持，无奈只好听命于他。不过我善心未泯，还\n"
             "是会尽量帮助你的。只要你能猜中我给你设定好的一个随机的\n"
             "四位数就可以出去了。\n"
             "这个四位数的各位上的数字都不重复，且都不为 0。你有八次\n"
             "机会，八次还猜不中的话就会换另一个数字重新开始再猜。方\n"
             "法是guess xxxx 每猜一次我就会给你一次提示。\n"NOR +
             HIR"A"NOR + HIY"表示位数也对，数字也对。" NOR +
             HIR"B"NOR + HIY"表示数字对了但是位数不对。\n"NOR +
             HIR"猜不出的话就只能向金角大王投降(giveup)啦！\n"NOR;

    msg += HIW"\n你现在还有" + chinese_number( 8 - me->query("hulu/guess/time"))
           + "次机会猜这个数字。\n"NOR;

 /*   if ( me->query("hulu/guess/") )
    {
       result = me->query("hulu/guess/result/");
       number = me->query("hulu/guess/number/");

       msg += HIY"你现在猜过的数字记录是：\n"NOR;
       for ( i = 0; i < sizeof(result); i++)
       {
          msg += HIG + me->query("hulu/guess/number/"+ i) + "     ";
          msg += me->query("hulu/guess/result/"+ i) + "\n"NOR;
       }

    }      */
    return msg + "\n";
}

void set_number(object me)
{
   int i,ii,x,y;

   me->delete("hulu");
   for (i = 0; i < 4; i++)
   {
      x = random(9) + 1;
      y = 0;

      if ( sizeof(me->query("hulu/number")) > 0 )
      {
         for (ii = 0; ii < sizeof(me->query("hulu/number")); ii++)
         {
             if (me->query("hulu/number/" + ii) == x)
             {
               y = 1;
             }
         }
      }
      if (y == 0) me->set("hulu/number/" + i,x);
      else i = i - 1;
   }
}

int do_guess(string arg)
{
   int num, num1, num2, num3, num4, i, ii, a, b, *num_arr, exp, pot, tihui;
   object me;
   string number,msg;

   num_arr = allocate(4);
   num = atoi(arg);
   me = this_player();
   number = "";

   if ( time() - me->query("hulu/last_guess") < 5 )
   {
       return notify_fail("你怎么猜得这么快，是不是用机器人的？\n");
   }

   if (! arg )
   return notify_fail("你要猜哪个数字？\n");

   if ( sizeof(arg) != 4 || num == 0 || num < 1000 || num > 9999)
   return notify_fail("请猜一个四位整数！\n");

   num1 = num / 1000;
   num2 = (num - num1 * 1000) / 100;
   num3 = (num - num1 * 1000 - num2 * 100)/ 10;
   num4 = (num - num1 * 1000 - num2 * 100 - num3 * 10);

   if ( num1 == num2 || num1 == num3 || num1 == num4 || num2 == num3 ||
        num2 == num4 || num3 == num4)

   return notify_fail("这个四位数各位都不重复，所以你猜的数字也别重复。\n");

   num_arr[0] = num1;
   num_arr[1] = num2;
   num_arr[2] = num3;
   num_arr[3] = num4;

   for (i = 0; i < 4; i++)                //先判断有几个A
   {
       if (me->query("hulu/number/" + i) == num_arr[i])
       {
          a += 1;
       }

   }

   for (i = 0; i < 4; i++)                //再判断有几个B
   {
       for (ii = 0; ii < 4; ii++)
       {
           if (me->query("hulu/number/" + i) == num_arr[ii])
           {
              b += 1;
           }
       }
   }
   b = b - a;    

   me->set("hulu/guess/result/" + me->query("hulu/guess/time"),a +"A"+ b +"B");
   me->set("hulu/guess/number/" + me->query("hulu/guess/time"),
           num1+""+num2+""+num3+""+num4);
   me->add("hulu/guess/time", 1);
   me->set("hulu/last_guess",time());
   if ( a == 4 )
   {
      me->set("startroom", "/d/city/kedian/");
      tell_object(me,HIW"哇，这么都被你猜中！你太厉害了，没错，答案就是:"NOR
                     HIR + num + NOR HIY
                    "\n有你这样的智力看来连紫金葫芦也困你不住了！\n"NOR);

    /*  exp = 9000 + random(1000);
      pot = 5000 + random (500);
      tihui = 1000 + random(200);  */

      exp = 1000 + random(500);
      pot = 500 + random (300);
      tihui = 200 + random(100);

      me->add("combat_exp", exp);
      me->add("potential", pot);
      me->add("experience", tihui);

      message_vision(HIC"只见葫芦盖突然掀了开来，$N嗖的一声钻了出去。\n"NOR,
                     this_player());

      tell_object( me, HIG"通过这次脱困过程，你获得了"NOR HIR +
                   chinese_number(exp) + HIG"点经验，\n"NOR HIW +
                   chinese_number(pot) + NOR HIG"点潜能以及"HIY +
                   chinese_number(tihui) + HIG"点实战体会。\n"NOR);
      me->delete("hulu");


      me->move("/d/city/kedian");
   }
   else
   {
   if (me->query("hulu/guess/time") < 8 )
      {
        /*   write(HIC"本次你的答案命中："NOR HIR+ a + "A" + b +"B\n"NOR +
                 HIG"你还有"NOR HIY + (8 - me->query("hulu/guess/time")) +
                 NOR HIG"次机会可以猜。\n"NOR);    */

            msg = HIC"本次你的答案命中：\n"NOR;
            msg += call_other(TEXT2PIC_D,"Display",a + "A" + b +"B");
            msg += HIG"\n你还有"NOR HIY + (8 - me->query("hulu/guess/time")) +
                   NOR HIG"次机会可以猜。\n"NOR;
            write(msg);
      }
      else
      {
           for (i=0;i<4;i++)
           {
               number += me->query("hulu/number/"+i);

           }

           me->delete("hulu/guess");
           write(HIR"真可惜，八次了你还是没猜中，答案是:"NOR
                     HIG + number + NOR HIR
                     "\n现在给你换个数字重新开始猜。\n"NOR);
           call_other(HULU_INSIDE, "set_number",me);
      }

   }

   return 1;

}

int do_giveup()
{
    object me;
    me = this_player();

    tell_object( me, HIR"这么就放弃了，真没出息，哈哈！\n");
    message_vision(HIC"$N万般沮丧，垂头丧气得说到，“哎，我认输了，放我出去"
                   "吧！”\n只见葫芦盖突然掀了开来，$N嗖的一声钻了出去。\n"NOR,
                   me);

    me->delete("hulu");
    me->set("startroom", "/d/city/kedian/");
    me->move("/d/city/kedian");

    tell_object(me, HIG"由于受到金角大王的干扰，你的趣味任务被迫取消了。"
                "重新来过吧！\n"NOR);
        if ( me->query("weiwang") > 10000 && me->query("score") > 10000 )
        {
           me->add("weiwang", -100);
           me->add("score", -100);

           tell_object(me, HIR"你的阅历和江湖威望收到了一定损失！\n"NOR);
        }
    me->delete("xquest");
    me->set("xquest_count",0);
    me->set("xquest_last_cancel", time());
    me->add("xquest_total_cancel/total", 1);

    return 1;
}
