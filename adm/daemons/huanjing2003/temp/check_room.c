#include <ansi.h>
#include <errs_func.h>
#include <max_min.h>
inherit ROOM;


#define        LOG_WHERE        "/clone/allall/loglog.c"


void create()
{
    set("short", HIY"幻境活动积分查询处"NOR);
    set("long", "


             输入  <check>  指令获得帮助。

\n");

    set("invalid_startroom",1);
    set("exits", ([
        "up": __DIR__"room_door_hj",
        ]));

    setup();
}

void init()
{
    add_action("do_ts", "check");
}

int shi, fen, miao;

int do_ts(string arg)
{
    string t, *tt, *plers;
    int i,j, t1,t2,t3,times,all, *temp;


    if( !arg ) return errs("输入参数。

 high          -- 所有玩家 各自的成功单局最高分(用于奖项1)

 xiaolv        -- 最高效率的得分(人名请看TOP 公告版)

 oktimes       -- 所有玩家 各自的总成功次数

 playtime      -- 所有玩家 各自的总游戏时间(无论成败)

 failtimes     -- 所有玩家 各自的总失败次数(100+得分才算)

 okscore       -- 所有玩家 各自的总成功得分\n");

    t = read_file ( LOG_WHERE );
    if( !t || !sizeof(t) ) return errs("无法读取文件 "+LOG_WHERE+" \n");

    t = replace_string( t, " ", "" );
    tt = explode( t, "\n" );

    plers = ({
      "addda",
      "anycall",
      "beeee",
      "chengfs",
      "fffjj",
      "jsxm",
      "kickyou",
      "lidaopao",
      "meir",
      "naihe",
      "net",
      "vsvic",
      "szcztzki",
      "xare",
      "xiaobc",
      "xiaxue",
      "xiuxiu",
      "xsmarter",
      "zll",
        });


if( arg == "high" )
{
// 每人选出自己最高分的那个
    write("每位玩家自己的单局成功最高分：\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        temp = ({ });
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "。(效率：" ) != -1
             && strsrch( tt[i], plers[j] ) != -1 )
            {
                if( sscanf( tt[i], "%*s得分%d。(效率：%*s", t1 ) )
                    temp += ({ t1 });
            }
        }
        if( !temp || !sizeof(temp) )
        {
            write(sprintf("      %-8s          ---- 无\n",plers[j]) );
            continue;
        }
        write( sprintf("      %-8s          ---- %d\n", plers[j], max_min(temp, "max")));
    }

    return 1;
}

if( arg == "xiaolv" )
{
    temp = ({ });
    for( j=0;j<sizeof(plers);j++ )
    {
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "。(效率：" ) != -1
             && strsrch( tt[i], plers[j] ) != -1 )
            {
                if( sscanf( tt[i], "%*s(效率：%d%*s", t1 ) )
                    temp += ({ t1 });
            }
        }
    }

    if( !temp || !sizeof(temp) )
        return errs("无任何人成功，没有效率记录。\n");
    
    write("最高效率是："+max_min( temp, "max" ) +" 点。\n");
    return 1;
}

if( arg == "oktimes" )
{
    write("每位玩家的成功总次数：\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        times = 0;
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "。(效率：" ) != -1
             && strsrch( tt[i], plers[j] ) != -1 )
                times ++;
        }
        t = sprintf( "      %-8s          ---- %2d 次\n",
            plers[j], times );
        if( !times ) t = replace_string( t, "0 次", "  无" );
        write( t );
    }
    return 1;
}

if( arg == "playtime" )
{
    write("每位玩家总游戏时间(无论成败)：\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        shi=0;fen=0;miao=0;all=0;
        t1=0;t2=0;t3=0;

        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "游戏" ) != -1 && strsrch( tt[i], plers[j] ) != -1 )
            {
                t1=0;t2=0;t3=0;
                if( sscanf( tt[i], "%*s游戏%d时%d分%d秒%*s", t1,t2,t3 ) )
                    shi += t1; fen += t2; miao += t3;
            }
        }

        all = shi * 3600 + fen * 60 + miao;
        write( sprintf( "      %-8s          ---- %2d:%2d:%2d\n",
            plers[j], all/3600, (all%3600)/60, all%3600%60 ) );
    }

    return 1;
}


if( arg == "failtimes" )
{
    write("每位玩家的总失败次数（100分及以上的回合才计入有效统计）：\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        times=0;
        t1 = 0;
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], plers[j] ) != -1
             && strsrch( tt[i], "失败，得分作废") != -1 )
            {
                if( sscanf( tt[i], "%*s得分%d(失败，得分作废)。", t1 ) )
                    if( t1 > 99 ) times++;
            }
        }
        t = sprintf( "      %-8s          ---- %2d 次\n",
            plers[j], times);
        if( !times ) t = replace_string( t, "0 次", "  无");
        write( t );
    }
    return 1;
}

if( arg == "okscore" )
{
    write("每位玩家的总成功得分：\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        times = 0;
        t1 = 0;
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "。(效率：" ) != -1
             && strsrch( tt[i], plers[j] ) != -1 )
            {
                if( sscanf( tt[i], "%*s得分%d。%*s", t1 ) )
                {
                    times += t1;
                }
            }
        }
        write( sprintf("      %-8s          ---- %8d\n",
            plers[j], times));
    }
    return 1;
}

    write("参数不正确。请直接输入 <check> 指令查询。\n");
    return 1;
}

