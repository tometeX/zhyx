/// who.c
// Modified by Yu Jue@JY
// Modify by Yu Jue@SJ 1999-06-24
// Modified by Numa@Sj 1999-11-18 门派重新排列 (不准覆盖了， bite. 4.23.2000)
// Modified by snowman@SJ 14/11/2000.  玩家按游戏时间排列。
// Modified by Looklove@SJ 增加查看在线工匠功能
inherit F_CLEAN_UP;


mapping party=([
        "emei":         "峨嵋派",
        "zaixian":      "在线人员",
        "gaibang":      "丐帮",
        "gumu":         "古墓派",
        "huashan":      "华山派",
        "kunlun":       "昆仑派",
        "mingjiao":     "明教",
        "murong":       "姑苏慕容",
        "quanzhen":     "全真教",
        "shaolin":      "少林派",
        "shenlong":     "神龙教",
        "songshan":     "嵩山派",
        "taohua":       "桃花岛",
        "tianlong":     "天龙寺",
        "tiezhang":     "铁掌帮",
        "wudang":       "武当派",
        "xingxiu":      "星宿派",
        "xueshan":      "大轮寺",
        "lingjiu":      "灵鹫宫",
        "xiaoyao":      "逍遥派",
        "riyue":        "日月神教",
        "ouyang":       "欧阳世家",
]);

int sort_user(object,object);

void create() {
        string *pname = values(party)
        int i = sizeof(pname)

        seteuid(getuid())
        while (i--) partypname = pnamei
}

string opt_party

void remove_busy(object me)
{
        if( me)delete_temp(command_busy, me)
}

mixed main(object me, string arg, int remote)
{
        string str, *option, fname = 
        object *list
        int i, ppl_cnt, cnt, count, wcnt = 0
        int opt_long, opt_id, opt_wiz, opt_wizall, opt_career, opt_zhuanzhan

        if (!remote) {
                if( query_temp(command_busy, me) )
                        return notify_fail(你正忙着呢。\n)
set_temp(command_busy, 1,             me)
                call_out(remove_busy, 3, me)
        }


        if( arg ) {
                option -= ({  })
                while( i-- )
                        switch(optioni) {
                                case -l: opt_long = 1
break
                                case -i: opt_id = 1
break
                                case -wizall: opt_wizall = 1
                                case -w: opt_wiz = 1
break
                                case -c: opt_career = 1
break
                                case -z: opt_zhuanzhan = 1
break
                                case -f:
                                case-p:opt_party=query(family/family_name, me)
break
                                default:
                                        if( optioni0=='@' ) {
                                                notify_fail(网路精灵并没有被载入。\n)
                                                if (find_object(DNS_MASTER) && RWHO_Q->send_rwho_q(optioni1..<1,
                                                        me, opt_long & wizardp(me), opt_wiz, opt_party )) {
                                                        // 只有工作人员才允许 who @xx -l，Yu Jue@SJ 19990624
                                                        write(网络讯息已送出，请稍候。\n)
                                                        return 1
                                                return 0
                                        }
                                        if (optioni0 == '-' && !undefinedp(partyoption))
                                        else return notify_fail(指令格式：who [-l|-i|-w|-p|-c]\n)
                        }
        }
/*
        if (!remote && opt_wizall && find_object(DNS_MASTER)) {
                string *mud = sort_array(keys(DNS_MASTER->query_muds()), -1)
                int m = sizeof(mud)

                while (m--) RWHO_Q->send_rwho_q(mudm, me, 0, 1, opt_party)
        }
*/
        if( opt_long && !remote && !wizardp(me)) {
                if( query(jing, me)<50 )
                        return notify_fail(你的精神太差了，没有办法得知所有玩家的详细资料。\n)
                me->receive_damage(jing, 50)
        }

                + 在线 + (opt_wiz?工作人员:opt_career?工匠:opt_zhuanzhan?转站人员:玩家) + ：\n
        str += repeat_string(━, 40) + \n
        if (opt_party != (null))
                        opt_party :))
        if ( opt_career )
        if ( opt_zhuanzhan && wizardp(me) )

        if( opt_long || opt_wiz ) {
                while( i-- ) {
                        if( remote && wizardp(listi) && query(env/invisibility, listi))continue
                        if (!remote && !me->visible(listi) ) continue
                        if (opt_wiz && !wizardp(listi) ) continue
                        if (interactive(listi)) ppl_cnt++
                        else cnt++
                        if( !wiz_level(listi) && fname != query(family/family_name, listi) )
                        if (!wcnt && wiz_level(listi)) {
                        }
                        str += sprintf(%12s%s%s\n,
                                RANK_D->query_rank(listi),
                                interactive(listi)?
                                        (query_idle(listi) > 120?HIM+NOR: )
                                        :HIG*NOR,
                                listi->short(1)
                        )
                }
        } else {
                string name

                while( i-- ) {
                        // Skip those users in login limbo.
                        if( remote && wizardp(listi) && query(env/invisibility, listi))continue
                        if (!remote && !me->visible(listi)) continue
                        if( !wiz_level(listi) && fname != query(family/family_name, listi)){
                                if (count % (opt_id?4:8)) str += \n
                                str += sprintf(HIY %-*s NOR, opt_id?20:10, (fname?fname:普通百姓) + ：)
                        }
                        if (!wcnt && wiz_level(listi)) {
                                if (count % (opt_id?4:8)) str += \n
                                str += sprintf(HIY %-*s NOR, opt_id?20:10, 工作人员：)
                        }
                        str += sprintf( %-*s%s,
                                opt_id?19:9,
                                interactive(listi)?
                                        (query_idle(listi) > 120 ? HIM++name+NOR :  +name)
                                        : HIG*+name+NOR,
                                ++count % (opt_id?4:8) ?  : \n
                        )
                        if (interactive(listi)) ppl_cnt++
                        else cnt++
                }
                if( count % (opt_id?4:8) ) str += \n
        }
        str += repeat_string(━, 40) + \n
        str += sprintf(
                "有 %d 位%s连线中，%d 位%s断线中，"HIG"*"NOR" 表示断线中  "HIM"+"NOR" 表示发呆中\n",
                ppl_cnt, opt_wiz?工作人员:玩家, cnt, opt_wiz?工作人员:玩家, query_load_average()
        )

        if( remote ) return str

        me->start_more(str)
        return 1
}

int sort_user(object ob1, object ob2)
{
        string name1, name2
        int l1 = wiz_level(ob1), l2 = wiz_level(ob2)

        if (l1 != l2) return l2 - l1

        if (l1) {

                if (intp(name1)) name1 = 
                if (intp(name2)) name2 = 
                if (name1 > name2) return -1
                if (name1 < name2) return 1
                return 0
        }

        reset_eval_cost()

        if (intp(name1)) name1 = 
        if (intp(name2)) name2 = 
        if (name1 > name2) return -1
        if (name1 < name2) return 1

        if (l1 != l2) return l1 - l2

        // sort by playing time.
        return query(online_total, ob2) - query(online_total, ob1)
        //query(combat_exp, return ob2)-query(combat_exp, ob1)
}

int help(object me)
{
        string *p
        int i,j

        write(@HELP
指令格式 : who 0

这个指令可以列出所有在线上的玩家及其等级。

-l 选项列出较长的讯息。
-i 只列出玩家的英文代号。
-p 只列出同门的玩家。
-f 同上
-w 只列出线上所有的工作人员。
-c 只列出在线工匠
-英文代号 只列出该门派的玩家。

HELP)
        write(sprintf(   %-12s%-12s    %-12s%-12s\n,英文代号,门派名,英文代号,门派名))
        write(----------------------------------------------------------\n
        for (i=0;i<j/2;i++
        
                if (i==(j/2-1)
                
                        write(sprintf(   %-10s：%-12s\n, pi, partyp)
                        continu
                
                if (i/2*2==i
                        write(sprintf(   %-10s：%-12s|, pi, partyp)
                els
                        write(sprintf(   %-10s：%-12s\n, pi, partyp)
        
        write(----------------------------------------------------------\n
        write(@HEL
相关指令： finge
HELP
        return 
