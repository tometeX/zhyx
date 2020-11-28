// story:lonely 天煞孤星

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

nosave mixed *story = ({
        "花旗国,纽约,自由女神像之颠……",
        "华英雄与无敌的决斗已近尾声……",
        "揉合了无敌一生刀意所在的一式“刀中不二”已把华英雄的“剑气长江”压下。",
        "华英雄握回赤剑，但已身中数刀，无数的血从身上流下……",
        "无敌：老子的刀中不二举世无双，你输定了！",
        "华英雄：我还未……败。无敌，接我最后一式中华傲诀吧！",
        "无敌：哈哈哈哈……那又能奈我何?",
        "华英雄：“中华傲诀”一式乃是“剑”“气”“意”三势融汇贯通而成的旷世奇招。",
        "华英雄：我命犯天煞孤星，孤寂一世方使练成。",
        "无敌：死到临头还大言不惭！受死吧！",
        "华英雄一声怒喝，右掌轰击赤剑剑柄，赤剑顷刻化成一条烈焰火龙，向无敌吞噬过去。",
        "隆……华英雄双掌已击在无敌面上。无敌吐血飞出丈外。",
        "四处一片孤寂，唯有躺在地上的无敌喃喃呻吟：“我败了…我败了…为什么你不杀我…”",
        "华英雄喃喃自语：“你败了……你败了……你败了……”",
        "然而天煞孤星又有何所得呢？",
        "杀了这么多人…压抑了这么多感情…容忍了这么久的孤寂…到了最后只剩下了这些…",
        "是一无所有，唯有这天下第一的虚名！",
        "华英雄仰天长叹：天啊，为何偏偏是我！难道我注定要为这天下第一的虚名而孤寂一世？",
        "天帝：哎，看来华英雄这天煞孤星当得太久，承受不了压力，再这样下去要精神崩溃了！",
        "天帝：来人，速速去下界找寻合适人选，接替华英雄天煞孤星之位",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return CYN "【天煞孤星】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob;
        string msg;
        mapping my;
        int select;

        select = 0;
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                               //  environment($1)->query("outdoors") &&
                                                 ! $1->query("special_skill/emperor") &&
                                                 ! $1->query("special_skill/lonely") &&
                                                 ! $1->query("special_skill/queen") &&
                                                 ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];

        if (random( 5200 -  ob->query("kar") * 100 ) > 0 )
        {
                msg = HIC "天帝：" + ob->name(1) +
                      HIC "此人虽好，但精神承受力太差，不适合接替天煞孤星之位。" NOR;
                ob->add("kar", 1+random(2));
                if ( ob->query("kar") >= 50 ) ob->set("kar",50);


        } else
        {
                msg = HIY "天帝：不错不错，" + ob->name(1) +
                      HIY "此人确实可以接替天煞孤星之位！" NOR;
                ob->set("special_skill/lonely", 1);
                ob->delete("family");
                ob->delete("class");
                log_file("static/tianzi", sprintf("%s(%s) 获得天煞孤星属性 at %s.\n",
                         ob->name(1), ob->query("id"), ctime(time())));
                select = 1;

        }
        remove_call_out("announce");
        call_out("announce",1,select,ob);
        return msg;
}

void announce(int select, object ob)
{
      if (select == 0 )
      CHANNEL_D->do_channel(this_object(), "rumor",
         "听说目前找不到合适人选接替天煞孤星之位,但" + ob->name() + "受天帝恩惠加了福缘。\n");
      else
      CHANNEL_D->do_channel(this_object(), "rumor",
           "听说" + ob->name() + "被天帝选中，继任华英雄成为新一代天煞孤星。\n");
}
