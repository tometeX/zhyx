// top.c

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;
int top_list(object ob1,object ob2);
int get_score(object ob);

int main(object me, string arg)
{
        
        object *list,*ob;
        int i;
        string msg;

        if (!wizardp(me))
        return notify_fail("目前暂不对玩家开放。\n");

        ob = filter_array(objects(), (: userp($1) && !wizardp($1) :));
        list = sort_array(ob, (: top_list :));
        msg =  "\n                ┏ "+BCYN HIW+"中华英雄在线高手排行榜"NOR" ┓\n";
        msg += "┏━━━━━┯━┻━━━━━━━━┯━━━┯━━━━┯━┻━━┯━━━━━┓\n";
        msg += "┃   名次   │    高        手    │ 年龄 │ 门  派 │ 内  力 │  经  验  ┃\n";
        msg += "┠─────┴──────────┴───┴────┴────┴─────┨\n";

        if (arg == "80") {
        for (i = 0 ;i < 80 ; i++) {
        if( i >= sizeof(list)) msg += "┃暂时空缺。 \n";
                else {
                if(list[i] == me) msg += BBLU HIY;
//              msg += sprintf("┃    %-7s %-22d%-4d %-10d %7d  ┃\n"NOR,
                msg += sprintf("┃    %-7s", chinese_number(i+1));
                msg += sprintf("%-22s", (list[i]->query("name")?list[i]->query("name"):"连线中")+"("+((list[i]->query("id"))?(list[i]->query("id")):"un known")+")"),
                msg += sprintf("   %-4d", list[i]->query("age"));
                msg += sprintf("     %-10s ", list[i]->query("family")?list[i]->query("family/family_name"):"普通百姓");
                msg += sprintf("%-6d   ", list[i]->query("max_neili"));
                msg += sprintf("%7d  ┃\n", get_score(list[i]));
                }
                         }
       msg += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

//     reset_eval_cost();
       msg += "  " + NATURE_D->game_time() + "记。\n";
       write(msg);
       return 1;
        }
        if (arg == "50") {
        for (i = 0 ;i < 50 ; i++) {
        if( i >= sizeof(list)) msg += "┃暂时空缺。 \n";
                else {
                if(list[i] == me) msg += BBLU HIY;
//              msg += sprintf("┃    %-7s %-22d%-4d %-10d %7d  ┃\n"NOR,
                msg += sprintf("┃    %-7s", chinese_number(i+1));
                msg += sprintf("%-22s", (list[i]->query("name")?list[i]->query("name"):"连线中")+"("+((list[i]->query("id"))?(list[i]->query("id")):"un known")+")"),
                msg += sprintf("   %-4d", list[i]->query("age"));
                msg += sprintf("     %-10s ", list[i]->query("family")?list[i]->query("family/family_name"):"普通百姓");
                msg += sprintf("%-6d   ", list[i]->query("max_neili"));
                msg += sprintf("%7d  ┃\n", get_score(list[i]));
                }
                         }
       msg += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

//     reset_eval_cost();
       msg += "  " + NATURE_D->game_time() + "记。\n";
       write(msg);
       return 1;
        }
        if (arg == "30") {
        for (i = 0 ;i < 30 ; i++) {
        if( i >= sizeof(list)) msg += "┃暂时空缺。 \n";
                else {
                if(list[i] == me) msg += BBLU HIY;
//              msg += sprintf("┃    %-7s %-22d%-4d %-10d %7d  ┃\n"NOR,
                msg += sprintf("┃    %-7s", chinese_number(i+1));
                msg += sprintf("%-22s", (list[i]->query("name")?list[i]->query("name"):"连线中")+"("+((list[i]->query("id"))?(list[i]->query("id")):"un known")+")"),
                msg += sprintf("   %-4d", list[i]->query("age"));
                msg += sprintf("     %-10s ", list[i]->query("family")?list[i]->query("family/family_name"):"普通百姓");
                msg += sprintf("%-6d   ", list[i]->query("max_neili"));
                msg += sprintf("%7d  ┃\n", get_score(list[i]));
                }
                         }
       msg += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

//     reset_eval_cost();
       msg += "  " + NATURE_D->game_time() + "记。\n";
       write(msg);
       return 1;
        }
    else
        for (i = 0 ;i < 10 ; i++) {
        if( i >= sizeof(list)) msg += "┃暂时空缺。 \n";
                else {
                if(list[i] == me) msg += BBLU HIY;
//              msg += sprintf("┃    %-7s %-22d%-4d %-10d %7d  ┃\n"NOR,
                msg += sprintf("┃    %-7s", chinese_number(i+1));
                msg += sprintf("%-22s", (list[i]->query("name")?list[i]->query("name"):"连线中")+"("+((list[i]->query("id"))?(list[i]->query("id")):"un known")+")"),
                msg += sprintf("   %-4d", list[i]->query("age"));
                msg += sprintf("     %-10s ", list[i]->query("family")?list[i]->query("family/family_name"):"普通百姓");
                msg += sprintf("%-6d   ", list[i]->query("max_neili"));
                msg += sprintf("%7d  ┃\n", get_score(list[i]));
                }
                         }
       msg += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

//     reset_eval_cost();
       msg += "  " + NATURE_D->game_time() + "记。\n";
       write(msg);
       return 1;
}
int top_list(object ob1, object ob2)
{
      int score1,score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

      return score2 - score1;
}

int get_score(object ob)
{
        int tlvl,i,score;
        string *ski;
        mapping skills;

      reset_eval_cost();
        skills = ob->query_skills();
        if (!sizeof(skills)) return 1;
        ski  = keys(skills);
        for(i = 0; i<sizeof(ski); i++) {
                        tlvl += skills[ski[i]];
                        }  // count total skill levels
/*
        score = tlvl/10;
        score += ob->query("max_neili")/10;
        score += ob->query_str() + ob->query_int() + ob->query_dex() + ob->query_con();
        score += (int)ob->query("combat_exp")/2500;
*/
        score = ob->query("combat_exp");
        return score;
}

int help(object me)
{
write(@HELP
指令格式 : top

这个指令可以让你知道在线的高手。 

用例：

top 30     查看在线前30位高手
top 50     查看在线前50位高手
top 80     查看在线前80位高手
 
HELP
    );
    return 1;
}
