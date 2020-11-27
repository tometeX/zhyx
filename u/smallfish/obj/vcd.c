#include <ansi.h>
inherit ITEM;
void create()
 {
    set_name("ＶＣＤ机", ({"vcd"}) );
    set_weight(1000);
    if( clonep() )
           set_default_object(__FILE__);
    else {
        set("unit", "台");
        set("long", "一台高级的ＶＣＤ机，可以用来放ＶＣＤ片。\n");
         set("no_get",1);
         set("value",10000);
    }
    setup();
}

int init()
{
       add_action("do_play", "play");
        add_action("do_shut", "shut");
        add_action("do_kala", "kala");
        add_action("do_stop", "stop");
        return 1;       
}

int do_shut()
{
        if (this_object()->query_temp("play")==0) return notify_fail("现在没有播放ＶＣＤ呀。\n");
        message_vision("$N用遥控关了ＶＣＤ机。\n",this_player());
        this_object()->set_temp("play",0);
        remove_call_out("continue_play");
        return 1;
}

int do_play()
{
      // object ob;
        //ob=present("shi nv", environment(this_player())); 
//      if (objectp(ob)) {
                if (this_object()->query_temp("play")==1) return notify_fail("现在正在放着ＶＣＤ呢。\n");
                if (this_object()->query_temp("kala")!=0) return notify_fail("现在正有人唱卡啦ＯＫ呢。\n");
                this_object()->set_temp("play",1);
//              message_vision("$N走到ＶＣＤ机旁，拿起一张故事片放到ＶＣＤ机中。\n",ob);
                call_out("start_play",2);
                return 1;
//      }
//      return 0;
}

int start_play()
{
        tell_room(environment(this_object()),"电视里开始播放ＶＣＤ。\n");
        call_out("continue_play",1,-1); 
        return 1;       
}

int continue_play(int release)
{
        string *strs=({
                "\n\n                   "YEL"大　　话　　西　　游\n\n"NOR,"",
                "观  音：孙悟空，你这个畜牲，你本来答应如来佛祖护送你师傅唐三藏\n"
                "        去取西经，你居然跟牛魔王串通起来要吃你师傅，你知不知道\n"
                "        你犯了弥天大罪？\n",
                "孙悟空：少罗嗦！你追了我三天三夜，因为你是女人我才不杀你，不要\n"
                "        以为我怕了你了！\n",
                "唐  僧：悟空，你怎么可以这样跟观音姐姐讲话呢？\n",
                "悟  空：哗！不要吵！\n",
                "唐  僧：你又在吓我！\n",
                "观  音：你不是怕我又为什么要打伤紫霞仙子抢走她的月光宝盒，你不\n"
                "        就是想躲开我吗？\n",
                "悟  空：既然躲不了那老孙就跟你绝一死战！\n",
                "\n(悟空将月光宝盒随手一抛，正好砸在唐僧头上。)\n\n",
                "唐  僧：又干什么？\n",
                "\n(俩人正要动手，突然……)\n\n",
                "唐  僧：喂喂喂！大家不要生气，生气会犯了嗔戒的！悟空你也太调皮\n"
                "        了，我跟你说过叫你不要乱扔东西，你怎么又…你看我还没说\n"
                "        完你又把棍子给扔掉了！月光宝盒是宝物，你把他扔掉会污染\n"
                "        环境，要是砸到小朋友怎么办？就算砸不到小朋友砸到那些花\n"
                "         花草草也是不对的！\n",
                "\n(悟空一把抓住唐僧手中的月光宝盒)\n\n",
                "唐  僧：干什么？\n",
                "悟  空：放手！\n",
                "唐  僧：你想要啊？悟空，你要是想要的话你就说话嘛，你不说我怎么\n"
                "        知道你想要呢，虽然你很有诚意地看着我，可是你还是要跟我\n"
                "        说你想要的。你真的想要吗？那你就拿去吧！你不是真的想要\n"
                "        吧？难道你真的想要吗？……\n",
                "悟  空：我Kao！\n"
                "\n(悟空一拳将唐僧打倒。)\n\n",
                "观  音：啊？孙悟空！\n"
                "悟  空：大家看到啦？这个家伙没事就长篇大论婆婆妈妈叽叽歪歪，就\n"
                "        好象整天有一只苍蝇，嗡……对不起，不是一只，是一堆苍蝇\n"
             
                "\n(悟空倒地翻滚，异常痛苦。)\n\n",
                "悟  空：所以呢我就抓住苍蝇挤破它的肚皮把它的肠子扯出来再用它的\n"
                "        肠子勒住他的脖子用力一拉，呵－－！整条舌头都伸出来啦！
\n"
                "        我再手起刀落哗－－！整个世界清净了。现在大家明白，为什\n"
                "        么我要杀他！\n",
                "观  音：哼！悟空，你诸多借口，你根本就不想去取西经！\n",
                "悟  空：说那么多干什么，打呀！\n",
                "\n(俩人一番斗法，悟空被观音降服收入甘露瓶。)\n\n"
                "观  音：今天我要替天行道！\n",
                "唐  僧：喂喂喂！徒弟有错做师傅的也有责任，求姐姐放他一条生路吧！\n",
                "观  音：我不消灭他我没法向玉皇大帝交代！\n",
                "唐  僧：请姐姐向玉皇大帝说一声，贫僧愿意一命赔一命！(合十坐地，\n"
                "        将法杖向空中一抛)喃呒阿弥陀佛！\n"
                "\n(法杖将唐僧砸死。)\n\n",
        });
        if (release==0) {
                tell_room(environment(this_object()),"电视放完了ＶＣＤ。\n");
                this_object()->set_temp("play",0);
                return 0;
        }
        if (release==-1) {
                continue_play(sizeof(strs));
                return 1;
        }
        tell_room(environment(this_object()),strs[sizeof(strs)-release]);
        call_out("continue_play",2,release-1);
        return 1;
}

int do_stop()
{
        if (this_object()->query_temp("kala")!=this_player()) return notify_fail("现在你没有唱卡啦ＯＫ呀。\n");
        message_vision("$N停止了唱卡啦ＯＫ。\n",this_player());
        this_object()->set_temp("kala",0);
        remove_call_out("continue_kala");
        return 1;
}

int do_kala()
{
  //     object ob;
        //ob=present("shi nv", environment(this_player())); 
        //if (objectp(ob)) {
                if (this_object()->query_temp("play")==1) return notify_fail("现在正在放着ＶＣＤ呢。\n");
                if (this_object()->query_temp("kala")!=0) return notify_fail("现在正有人唱卡啦ＯＫ呢。\n");
                this_object()->set_temp("kala",this_player());
//              message_vision("$N走到ＶＣＤ机旁，拿起一张卡啦ＯＫ盘放到ＶＣＤ机中，给$n送上了话筒。\n",ob,this_player());
                call_out("start_kala",2,this_player());
                return 1;
//      }
//      return 0;
}

int start_kala(object me)
{
        message_vision("$N开始唱卡啦ＯＫ。\n",me);
        call_out("continue_kala",1,-1, me);     
        return 1;       
}

int continue_kala(int release, object me)
{
        string *strs=({
                "\n\n                   "YEL"新  神  雕  侠  侣\n\n"NOR,
                CYN"$N："+HIM+"这次是我真的决定离开\n"NOR,
                CYN"$N: "+HIM+"远离那些许久不懂的悲哀\n"NOR,
                CYN"$N: "+HIM+"想让你忘却愁绪忘记关怀\n"NOR,
                CYN"$N: "+HIM+"放开这纷纷扰扰自由自在\n"NOR,
                CYN"$N: "+HIM+"那次是你不经意的离开\n"NOR,
                CYN"$N: "+HIM+"成为我这许久不变的悲哀\n"NOR,
                CYN"$N: "+HIM+"于是淡漠了繁华无法再开怀\n"NOR,
                CYN"$N: "+HIM+"于是我守着寂寞不能归来\n"NOR,
                CYN"$N: "+HIM+"啊～　拥起落落余辉任你采摘\n"NOR,
                CYN"$N: "+HIM+"啊～　留住刹那永远为你开\n"NOR,
                CYN"$N: "+HIM+"啊～　拥起落落余辉任你采摘\n"NOR,
                CYN"$N: "+HIM+"啊～　留住刹那永远为你开\n"NOR,
                CYN"$N: "+HIM+"那次是你不经意的离开\n"NOR,
                CYN"$N: "+HIM+"成为我这许久不变的悲哀\n"NOR,
                CYN"$N: "+HIM+"于是淡漠了繁华只为你开怀\n"NOR,
                CYN"$N: "+HIM+"要陪你远离寂寞自由自在\n"NOR,
                CYN"$N: "+HIM+"..............\n"NOR,
                
        });
        if (release==0) {
                message_vision("$N唱完了卡啦ＯＫ。\n",me);
                this_object()->set_temp("kala",0);
                return 0;
        }
        if (release==-1) {
                continue_kala(sizeof(strs),me);
                return 1;
        }
        message_vision(strs[sizeof(strs)-release],me);
        call_out("continue_kala",2,release-1, me);
        return 1;
}

