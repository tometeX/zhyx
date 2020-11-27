inherit F_CLEAN_UP;
int time_period(int timep, object me);
int main(object ob, string arg)
{
        object me;
        int turn;
        string str="当前的挑战任务：\n",name="你";
        if (!wizardp(ob) || arg == "") me = ob;
        else
        {
        if( arg ){
        me = present(arg, environment(ob));
        if (!me) me =  find_player(arg);
        if (!me) return notify_fail("你要察看谁的任务？\n");
                        }
                        else
                                me = ob;
        }
        if (me!=ob) name=me->query("name");
        if(!me->query("mieyao")&&!me->query("mpmieyao"))
               return notify_fail(name+"现在没有挑战任务。\n");
        str=name+str;
        if (name = me->query("mieyao/name"))
           {
           turn=me->query_temp("mieyao/level")+1;
           str+="挑战大使：第"+chinese_number(turn)+"个挑战任务「"+ name +"」";
           if (!me->query("mieyao/done"))
                 str+="没有完成。\n";
           else
                 str+="已经完成。\n";
           }

        write(str);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : kquest
 
这个指令可以显示出你当前的灭妖任务。

HELP
        );
        return 1;
}

