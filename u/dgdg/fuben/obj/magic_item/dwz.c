
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
        set_name(HIG "东皇钟" NOR, ({ "donghuang zhong","zhong" }));
        set_weight(15000);        
        set("special", 1);
        set("unit", "件");        
        set("long", "[1;32m这是一口透着古意的铜钟，却坚硬无比，通体散发着淡淡的霞光。
上面隐约还画着许多神秘符号，散发着无形的力量，却给人一种安全感。[2;37;0m\n");   
        set("point", 560);
        set("no_sell", 1 ); 
        set("value",1000000); 
        set("no_steal", 1);      
        set("material", "tian jing");
      /*  set("wear_msg", HIG "玄音纱横空出世，霞光四射，宛如百鸟朝凤般飞至$N，\n"
                            "刹时便与$N合而为一。\n" NOR);
        set("remove_msg", HIC "$N" HIC "一声轻叹，但见玄音纱随风轻摆，顿时消失于无形。\n" NOR);  */
      /*  if (! check_clone()) return;
        restore(); */
        set("armor_prop/dodge", 100);
        set("armor_prop/parry", 100);
        set("armor_prop/armor", 200);
        setup();
}

 //string long() { return query("long") + item_long(); }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  

        if ((int)me->query_skill("force", 1) < 260
           || (int)me->query("neili") < 500
           || ! living(me) || random(4) != 1)
                return;

        cost = damage / 2;

        if (cost > 300) cost = 300;

        ap = ob->query_skill("force") * 12 + ob->query("max_neili");
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "轻轻一叹，身上" HIC "玄音纱" HIR "叮呤"
                                            "做响，$N" HIR "只觉心头一阵凄苦。这一招居然打不下去。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "只见$n" HIM "身上" HIC "玄音纱" HIM "一颤，有"
                                            "若凤鸣。" HIM "$N" HIM "你只感头晕目眩，居然一招打在空处。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "一招打中$n" HIW "，顿觉毫不受力。定睛一看，原来是"
                                            "的" HIC "玄音纱" HIW "幻化出来的幻象。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "身上" HIC "玄音纱" HIY "一阵霞光闪过，$N" HIY "这一"
                                            "招被霞光牢牢挡住，伤不了$n" HIY "分毫。\n" NOR]);
                        break;
                }
                return result;
        }
}

/*
void init()
{
    add_action("do_canwu", "canwu");  
    add_action("do_linghui", "linghui");      
}

int do_canwu( string arg )
{
   object me;
   int s_skill, t_skill;

   me = this_player();

   if ( ! arg || arg != "xuanyin")
      return notify_fail("你要参悟什么?\n");

   if ( ! me->query("special_skill/queen") )
      return notify_fail("你对着玄音纱端详了半天，"
                         "发现普通人似乎难以从中领会到任何玄机。\n");


   s_skill = (int)me->query_skill("sword", 1);
   t_skill = (int)me->query_skill("xuannv-jian", 1);

        if (s_skill < t_skill)
        {
                message_vision("$N对基本剑法的了解太低，无"
                               "法领悟玄音纱上的内容。\n", me);
                return 1; 
        }

        if (me->query("jing")< 90)
        {
                message_vision("$N太累了，现在无法领悟玄音纱上的内容。\n",me);
                return 1; 
        }

        if (t_skill >= 180)
        {
                message_vision("$N觉得玄音纱上的内容太肤浅了。"
                               "试试(linghui 绝招)吧\n", me);
                return 1;
        }

        message_vision("$N仔细参悟玄音纱上所载的密籍，对玄女"
                       "剑法似有所悟。\n", me);
        me->improve_skill("xuannv-jian", 1 + random(me->query("int")));
        me->receive_damage("jing", 75);
    return 1;
}

int do_linghui( string arg )
{
    object me = this_player();
    

    if ( ! me->query("special_skill/queen") )
        return 0;    
  
    if (me->is_busy())
          return notify_fail("你现在正忙着呢。\n");

    if (me->is_fighting())
          return notify_fail("你还是先打完架再说吧！\n");

    if ( ! arg || ( arg != "微风轻拂面" && arg != "人面桃花红") )
          return notify_fail("你要领会什么绝招？格式为(linghui 绝招)。\n");

    if ( arg == "微风轻拂面" 
        && me->query("can_perform/xuannv-jian/qingfu"))
          return notify_fail("这招你不是已经会了吗？\n");
  
    if ( arg == "人面桃花红" 
        && me->query("can_perform/xuannv-jian/taohua"))
          return notify_fail("这招你不是已经会了吗？\n");

    if ((int)me->query("jing") < 100)
          return notify_fail("你的精力无法集中，无法领会绝招！\n");
 
    me->receive_damage("jing", 90);

    me->start_busy(2 + random(4));

    if (random(10) == 1 && arg == "微风轻拂面" )
    {
        me->add("xuannv-jian/qingfu/count", 1);

        if (me->query("xuannv-jian/qingfu/count") >= 10)
        {
            write(HIM "猛然间，你胸中豁然贯通，再无疑虑。\n" NOR);
            write(HIC "你终于通晓了绝学「微风轻拂面」。\n" NOR);

            me->set("can_perform/xuannv-jian/qingfu", 1);
            me->delete("xuannv-jian/qingfu/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("xuannv-jian"))
                    me->improve_skill("xuannv-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "你对「微风轻拂面」这招有了新的认识，但是仍有许多不解之处。\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }

    if (random(15) == 1 && arg == "人面桃花红")
    {
        me->add("xuannv-jian/taohua/count", 1);

        if (me->query("xuannv-jian/taohua/count") >= 20)
        {
            write(HIM "猛然间，你胸中豁然贯通，再无疑虑。\n" NOR);
            write(HIC "你终于通晓了绝学「人面桃花红」。\n" NOR);

            me->set("can_perform/xuannv-jian/taohua", 1);
            me->delete("xuannv-jian/taohua/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("xuannv-jian"))
                    me->improve_skill("xuannv-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "你对「人面桃花红」这招有了新的认识，但是仍有许多不解之处。\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }
        return notify_fail("你试图从玄音纱上领会有关「" + arg + "」的内容，\n"
                           "但是这次没什么效果，看来得再来过！\n");

}
*/



void owner_is_killed()
{
        destruct(this_object());
} 
