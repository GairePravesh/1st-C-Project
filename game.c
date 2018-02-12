# include <stdio.h>
# include <stdlib.h>
# include<conio.h>
# include <dos.h>
# include <graphics.h>

# define NULL 0
# define YES 1
# define NO 0

int maxx, maxy, midx, midy ;
int bri[5][20] ;

void load();
void bricks();
void erasebrick();
void drawbrick();
void music();

void main()
{
    union REGS ii, oo ;
    int ballx, bally, paddlex, paddley, dx = 1, dy = -1, oldx, oldy, playerlevel ;
    int gm = CGAHI, gd = CGA;
    int i, flag = 0, speed = 25, welldone = NO, score = 0, chance = 4, area ;
    int layer[5] = { 10, 20, 30, 40, 50 }, limit = 50, currentlayer = 4 ;
    char *p1, *p2 ;
    initgraph ( &gd, &gm, "C:\\TURBOC3\\BGI" ) ;
    maxx = getmaxx() ;
    maxy = getmaxy() ;
    midx = maxx / 2 ;
    midy = maxy / 2 ;
    load();
    playerlevel = mainscreen() ;
    switch ( playerlevel )
    {
        case 'N' :
        case 'n' :
            speed=30
            break;
        case 'A' :
        case 'a' :
            speed = 15 ;
            break ;
        case 'E' :
        case 'e' :
            speed = 5 ;
            break;
    }
    rectangle ( 0, 0, maxx, maxy - 12 ) ;
    bricks() ;
    rectangle ( midx - 25, maxy - 7 - 12, midx + 25, maxy - 12 ) ;
    floodfill ( midx, maxy - 1 - 12, 1 ) ;
    circle ( midx, maxy - 13 - 12, 12 ) ;
    floodfill ( midx, maxy - 10 - 12, 1 ) ;
    area = imagesize ( midx - 12, maxy - 18, midx + 12, maxy - 8 ) ;
    p1 = malloc ( area ) ;
    area = imagesize ( midx - 25, maxy - 7, midx + 25, maxy - 1 ) ;
    p2 = malloc ( area ) ;
    getimage ( midx - 12, maxy - 7 - 12 - 12 + 1, midx + 12, maxy - 8 - 12, p1 ) ;
    getimage ( midx - 25, maxy - 7 - 12, midx + 25, maxy - 1 - 12, p2 ) ;
    paddlex = midx - 25 ;
    paddley = maxy - 7 - 12 ;
    ballx = midx - 12 ;
    bally = maxy - 7 - 12 + 1 - 12 ;
    gotoxy ( 45, 25 ) ;
    printf ( "Balls Remaining:" ) ;
    for ( i = 0 ; i < 3 ; i++ )
    {
        circle ( 515 + i * 35, maxy - 5, 12 ) ;
        floodfill ( 515 + i * 35, maxy - 5, 1 ) ;
    }
    gotoxy ( 1, 25 ) ;
    printf ( "Your Score: %4d", score ) ;
    settextjustify ( CENTER_TEXT, CENTER_TEXT ) ;
    settextstyle ( SANS_SERIF_FONT, HORIZ_DIR, 4 ) ;
    while ( 1 )
    {
        flag
        bally = bally + dy ;
        if ( bally > 40 )
        {
            limit = 50 ;
            currentlayer = 4 ;
        }
        else
        {
            if ( bally > 30 )
            {
                limit = 40 ;
                currentlayer = 3 ;
            }
            else
            {
                if ( bally > 20 )
                {
                    limit = 30 ;
                    currentlayer = 2 ;
                }
                else
                {
                    if ( bally > 10 )
                    {
                        limit = 20 ;
                        currentlayer = 1 ;
                    }
                    else
                    {
                        limit = 10 ;
                        currentlayer = 0 ;
                    }
                }
            }
        }
        if ( ballx < 1 )
        {
            music ( 4) ;
            ballx = 1 ;
            dx = -dx ;
        }
        if ( ballx > ( maxx - 24 - 1 ) )
        {
            music ( 4 ) ;
            ballx = maxx - 24 - 1 ;
            dx = -dx ;
        }
        if ( bally < 1 )
        {
            music ( 4) ;
            bally = 1 ;
            dy = -dy ;
        }
        if ( bally < limit )
        {
            if ( bri[currentlayer][ ( ballx + 10 ) / 32 ] == 1 )
            {
                for ( i = 1 ; i <= 6 ; i++ )
                {
                    if ( bri[currentlayer][ ( ballx + i + 10 ) / 32 ] == 0 )
                    {
                        ballx = ballx + i ;
                        flag = 1 ;
                        break ;
                    }
                    if ( bri[currentlayer][ ( ballx - i + 10 ) / 32 ] == 0 )
                    {
                        ballx = ballx - i ;
                        flag = 1 ;
                        break ;
                    }
                }
                if ( !flag )
                {
                    if ( bally < layer[currentlayer - 1] )
                    {
                        currentlayer-- ;
                        limit = layer[currentlayer] ;
                    }
                    putimage ( oldx, oldy, p1, OR_PUT ) ;
                    putimage ( oldx, oldy, p1, XOR_PUT ) ;
                    putimage ( ballx, bally, p1, XOR_PUT ) ;
                    delay ( speed ) ;
                    continue ;
                }
            }
            music ( 3 ) ;
            erasebrick ( ( ballx + 10 ) / 32, currentlayer ) ;
            if ( ( ballx + 10 ) / 32 == 19 )
                line ( maxx, 0, maxx, 50 ) ;
            if ( ( ballx + 10 ) / 32 == 0 )
                line ( 0, 0, 0, 50 ) ;
            if ( currentlayer == 0 )
                line ( 0, 0, maxx, 0 ) ; /* redraw top boundary */
            bri[currentlayer][ ( ballx + 10 ) / 32 ] = 1 ;
            bally = bally + 1 ;
            dy = -dy ; score += 5 ;
            gotoxy ( 16, 25 ) ;
            printf ( "%4d", score )
            if ( welldone == NO )
                welldone = YES ;
            else
            {
                outtextxy ( midx, midy, "Well done!" ) ;
                delay(10);music ( 3 ) ;
            }
        }
        if ( bally > 50 && welldone == YES )
        {
            setviewport ( midx - 32 * 2.5, midy - 32 / 2, midx + 32 * 2.5, midy + 32 / 2, 1 ) ;
            clearviewport() ;
            setviewport ( 0, 0, maxx, maxy, 1 ) ;
            welldone = NO ;
        }
        if ( bally > 180 - 12 )
        {
            welldone = NO ;
            if ( ballx < paddlex - 20 || ballx > paddlex + 50 )
            {
                while ( bally < 177 )
                {
                    putimage ( oldx, oldy, p1, XOR_PUT ) ;
                    putimage ( ballx, bally, p1, XOR_PUT ) ;
                    delay ( speed ) ;
                    oldx = ballx ;
                    oldy = bally ;
                    ballx = ballx + dx ;
                    bally = bally + dy ;
                }
                chance-- ;
                score -= 20 ;
                gotoxy ( 16, 25 ) ;
                printf ( "%4d", score ) ;
                music ( 2 ) ;
                if ( chance )
                    putimage ( 515 + ( chance - 1 ) * 35 - 12 , maxy - 10, p1, XOR_PUT ) ;
                if ( chance == 1 )
                {
                    gotoxy ( 45, 25 ) ;
                    printf ( "Your last ball... Be careful!" ) ;
                }
                if ( !chance )
                {
                    gotoxy ( 45, 25 ) ;
                    printf ( "Press any key... " ) ;
                    outtextxy ( midx, midy, "I warned you! Try again" ) ;
                    music ( 2) ;
                    closegraph() ;
                    restorecrtmode() ;
                    exit ( 0 ) ;
                }
            }
            music ( 4) ;
            bally = 180 - 12 ;
            dy = -dy ; }
            putimage ( oldx, oldy, p1, OR_PUT ) ;
            putimage ( oldx, oldy, p1, XOR_PUT ) ;
            putimage ( ballx, bally, p1, XOR_PUT ) ;
            if ( score == 500 - ( ( 4 - chance ) * 20 ) )
            {
                outtextxy ( midx, midy, "You win !!!" ) ;
                if ( score < 500 )
                    outtextxy ( midx, midy + 30, "Try scoring 500" ) ;
                else
                    outtextxy ( midx, midy + 30, "You are simply GREAT!" ) ;
                music ( 2) ;
                closegraph() ;
                restorecrtmode() ;
                exit ( 0 ) ;
            }
            delay ( speed ) ;
            if ( kbhit() )
            {
                ii.h.ah = 0 ;
                int86 ( 22, &ii, &oo ) ;
                putimage ( paddlex, paddley, p2, OR_PUT ) ;
                putimage ( paddlex, paddley, p2, XOR_PUT ) ;
                /* if Esc key has been pressed */
                if ( oo.h.ah == 1 )
                    exit ( 0 ) ;
                if ( oo.h.ah == 75 )
                        paddlex = paddlex - 20 ;
                if ( oo.h.ah == 77 )
                    paddlex = paddlex + 20 ;
                if ( paddlex < 0 )
                    paddlex = 0 ;
                if ( paddlex > 589 )
                    paddlex = 589 ;
                putimage ( paddlex, paddley, p2, XOR_PUT ) ;
            }
    }
}

mainscreen()
{
    int ff[12][40] =
    {
        1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,
        1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
        1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,
        1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,
        1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,
        1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,
        1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,
        1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,1,
        1,1,1,1,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,1,1,1,1,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    } ;
    int i, j, lx = 0, ly = 0, ch ;
    setviewport ( 0, 0, maxx, maxy, 1 ) ;
    rectangle ( 0, 0, maxx, maxy ) ;
    for ( i = 0 ; i < 12 ; i++ )
    {
        for ( j = 0 ; j < 40 ; j++ )
        {
            if ( ff[i][j] )
                rectangle ( lx, ly, lx + 15, ly + 9 ) ;
            lx = lx + 16 ;
        }
        lx = 0 ;
        ly = ly + 10 ;
    }
    line ( 0, maxy - 12, maxx, maxy - 12 ) ;
    setfillstyle ( XHATCH_FILL, WHITE ) ;
    floodfill ( 2, maxy - 2, WHITE ) ;
    setfillstyle ( SOLID_FILL, WHITE ) ;
    rectangle ( midx - 25, maxy - 7 - 12, midx + 25, maxy - 12 ) ;
    floodfill ( midx, maxy - 1 - 12, 1 ) ;
    circle ( midx, maxy - 13 - 12, 12 ) ;
    floodfill ( midx, maxy - 10 - 12, 1 ) ;
    outtextxy ( 15, 178, "Enter any key to continue" ) ;
    music ( 1 ) ;
    getch();
    while ( 1 )
    {
        clearviewport();
        outtextxy ( 50, 50, "Select any of the following:" ) ;
        rectangle(40,45,275,60);
        rectangle(40,85,85,100);
        outtextxy ( 50, 90, "Play " ) ;
        rectangle(40,105,150,120);
        outtextxy ( 50, 110, "Instructions " ) ;
        rectangle(40,125,130,140);
        outtextxy ( 50, 130, "Credits " ) ;
        rectangle(40,145,90,160);
        outtextxy ( 50, 150, "Exit " ) ;
        ch = 0 ;
        while ( ! ( ch == 'E' || ch == 'I' || ch == 'P' || ch=='D') )
        {
            fflush ( stdin ) ;
            if ( ( ch = getch() ) == 0 )
                getch() ;
            else
                ch = toupper ( ch ) ;
        }
        if ( ch == 'P' )
            break ;
        switch ( ch )
        {
            case 'I' :
                clearviewport() ;
                setviewport ( 0, 0, maxx, maxy, 1 ) ;
                settextstyle ( DEFAULT_FONT, HORIZ_DIR, 1 ) ;
                outtextxy ( 50, 15, " Instructions " ) ;
                settextstyle ( DEFAULT_FONT, HORIZ_DIR, 0 ) ;
                outtextxy ( 50, 40, "Use left and right arrow keys to move paddle." ) ;
                outtextxy ( 50, 60, "If you don't collect the ball on the paddle, you lose the ball." ) ;
                outtextxy ( 50, 80, "On loosing a ball you loose 20 points." ) ;
                outtextxy ( 50, 100, "On taking a brick you gain 5 points." ) ;
                outtextxy ( 50, 180, "Press any key to go back" ) ;
                fflush ( stdin ) ;
                if ( getch() == 0 )
                    getch() ;
                break ;
            case 'D' :
                clearviewport();
                setviewport ( 0, 0, maxx, maxy, 1 ) ;
                settextstyle ( DEFAULT_FONT, HORIZ_DIR, 1 ) ;
                outtextxy ( 50, 15, "Developer" ) ;
                settextstyle ( DEFAULT_FONT, HORIZ_DIR, 0 ) ;
                outtextxy ( 50, 50, "Pravesh Gaire ") ;
                outtextxy ( 50, 70, "073 / BEX / 427" ) ;
                outtextxy ( 50, 180, "Press any key to go back" ) ;
                fflush ( stdin ) ;
                if ( getch() == 0 )
                    getch() ;
                break ;
            case 'E' :
                closegraph() ;
                restorecrtmode() ;
                exit ( 0 ) ;
        }
    }
    clearviewport() ;
    setviewport ( 0, 0, maxx, maxy, 1 ) ;
    outtextxy ( 50, 50, "Select any of the following levels:" ) ;
    outtextxy ( 50, 70, "Novice" ) ;
    outtextxy ( 50, 90, "Advanced" ) ;
    outtextxy ( 50, 110, "Expert" ) ;
    fflush ( stdin ) ;
    if ( ( ch = getch() ) == 0 )
    getch() ;
    clearviewport() ;
    return ( ch ) ;
}

void bricks()
{
    int i, j, lx = 0, ly = 0 ;
    for ( i = 0 ; i < 5 ; i++
    {
        for ( j = 0 ; j < 20 ; j++ )
        {
            drawbrick ( lx, ly ) ;
            Mini Project Breaker
            lx = lx + 32 ;
        }
        lx = 0 ;
        ly = ly + 10 ;
    }
}

void drawbrick ( int lx, int ly )
{
    rectangle ( lx, ly, lx + 31, ly + 9 ) ;
    rectangle ( lx + 2, ly - 2, lx + 31 - 2, ly + 9 - 2 ) ;
    floodfill ( lx + 1, ly + 1, 2 ) ;
}

void erasebrick ( int b, int l )
{
    setcolor ( BLACK ) ;
    rectangle ( b * 32, l * 10, ( b * 32 ) + 31 , ( l * 10 ) + 9 ) ;
    rectangle ( b * 32 + 1, l * 10, ( b * 32 ) + 31 - 1, ( l * 10 ) + 9 - 1 ) ;
    rectangle ( b * 32 + 2, l * 10, ( b * 32 ) + 31 - 2, ( l * 10 ) + 9 - 2 ) ;
    setcolor ( WHITE ) ;
}

void music ( int type )
{
    float octave[7] = { 130.81, 146.83, 164.81, 174.61, 196, 220, 246.94 } ;
    int n, i ;
    switch ( type )
    {
        case 1 :
            for ( i = 0 ; i<100; i++ )
            {
                if(i==7) i=0;
                    sound ( octave[i] ) ;
                delay ( 500 ) ;
                if(kbhit()) break;
            }
            nosound() ;
            break;
        case 2 :
            for ( i = 0 ; i < 15 ; i++ )
            {
                n = random ( 7 ) ;
                sound ( octave[n] * 4 ) ;
                delay ( 100 ) ;
            }
            nosound() ;
            break ;
        case 3:
            for ( i = 4 ; i >= 0 ; i-- )
            {
                sound ( octave[i] * 4 ) ;
                delay ( 15 ) ;
            }
            nosound() ;
            break ;
        case 4:
            sound ( octave[6] * 2 ) ;
            delay ( 50 ) ;
            nosound() ;
    }
}

void load()
{
    int x=20;
    moveto(200,160);
    outtextxy("Loading, please wait...");
    rectangle(10,maxy-100,maxx-10,maxy-75);
    setcolor(WHITE);
    while(x<maxx-20)
    {
        bar(20,maxy-95,x,maxy-80);
        x++;
        delay(10);
    }
    clearviewport();
}
