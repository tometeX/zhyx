#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + WHT "\n\n                人        间        道" NOR);
        set("long", WHT "\n"
"仿佛踏进了嘈杂的闹市，又如闯进了民家大院。欢笑声、哭泣\n"
"声、怒骂声相互交杂。喜怒哀乐、恩怨情仇，世间百态尽集于\n"
"此。尝尽人间种种酸甜苦辣，悲欢离合。于痛苦中诞生，又于\n"
"痛苦中消逝。怜我世人，忧患实多。怜我世人，忧患实多。你\n"
"可以在这里参悟(canwu)。\n\n" NOR);
set("exits", ([ 
            "out"   : "/d/special/taixu",            
        ]));
        setup();
}

void init()
{
        add_action("do_canwu", "canwu");
}


int do_canwu()
{
        object ob;
        int c_skill;

        ob = this_player();

        c_skill = (int)ob->query_skill("lunhui-jian", 1);     

        if (ob->query("can_perform/lunhui-jian/rendao"))
        {
                write("你已经参悟透了人间道。\n");
                return 1;
        }

/*         if (!ob->query("reborn"))
        {
                write("你未修前世，无法参透人间道。\n");
                return 1; 
        } */

        if (c_skill < 600)
        {
                write("你至少要六百级轮回剑，才能参透人间道。\n");
                return 1; 
        }

        if (ob->query("jing") < 80)
        {
                write("你精力不能集中，现在无法参悟。\n",ob);
                return 1; 
        }
      
        if (random(15) != 1)
        {
        
                write("你趺坐静思良久，还是无法参透生死之道。\n", ob);              
                return 1;
        }
		
		if (random(5) == 1)
		{
        message_sort(HIW"\n$N" HIW"趺坐静思，猛然间一声长叹，诸"
                     "多凡尘旧事已涌上心头，$N" HIW "终于将「人间道」"
                     "参悟出来，从此再无疑虑。\n", ob);       
    
          write(HIC "你学会了「人间道」。\n" NOR);
          ob->set("can_perform/lunhui-jian/rendao", 1);
		}
		else 
		{
		 message_sort(HIR"\n$N只觉得人生如梦，生死无意，气血翻涌，一头栽倒在地!\n", ob);    
		 ob->die();
		 return 1;
		}
		
        ob->receive_damage("jing", 75);
        ob->start_busy(2);
        return 1;
}