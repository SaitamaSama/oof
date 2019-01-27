#include<iostream.h>
#include<stdlib.h>
#include<dos.h>
#include<ctype.h>
#include<conio.h>
int us,cs,flag=0;
void bat();
void bowl();
void cbat();
void cbowl();
void main()
{
  start :
  us=cs=flag=0;
  clrscr();
  char toss,name[30];
  int rand;
  randomize();
  cout<<"\n\n\t\tHand Cricket.....\n\n\n\tTOSS\n\t~~~~\n\nHead Or Tail \n\nEnter H / T : ";
  toss=toupper(getch());
  if((toss!='H')&&(toss!='T'))
  {
    cout<<"\a\n\nEnter H Or T : ";
    delay(1000);
    goto start;
  }
  cout<<toss<<"\n\nPress Any key To Stop ! \n\n";
  int i=1;
  while(!kbhit())
  {
    rand=random(2);
    switch(rand)
    {
      case 0 : cout<<" Head ";break;
      case 1 : cout<<" Tail ";break;
    }
    if((i%11)==0)
      cout<<'\n';
    delay(50);
    i++;
  }
  getch();
  redo :
  switch(rand)
  {
    case 0:
      if(toss=='H')
      {
        cout<<"\nYou Won The Toss !!\n\n\nBatting Or Bowling ? \n\nEnter B / L : ";
        toss=toupper(getch());
        cout<<toss;
        if(toss=='B')
          bat();
        else if(toss=='L')
          bowl();
        else
        {
          cout<<"\n\nPlease Enter Correct Option : ";
          sound(700);
          delay(750);
          nosound();
          toss='H';
          goto redo;
        }
      }
      else if(toss=='T')
      {
        cout<<"\n\nComputer Wins The Toss !! \n\n";
        switch(rand)
        {
        case 0 : cout<<"\n\nComputer Choose To Bat ! ";
        getch();
        bowl();
        break;
        case 1 : cout<<"\n\nComputer Choose To Bowl ! ";
        getch();
        bat();
        break;
        }
      }
      break;
    case 1:
      if(toss=='T')
      {
        cout<<"\nYou Won The Toss !!\n\n\nBatting Or Bowling ? \n\nEnter B / L : ";
        toss=toupper(getch());
        cout<<toss;
        if(toss=='B')
          bat();
        else if(toss=='L')
          bowl();
        else
        {
          cout<<"\n\nPlease Enter Correct Option : ";
          sound(700);
          delay(750);
          nosound();
          toss='H';
          goto redo;
        }
      }
      else if(toss=='H')
      {
        cout<<"\n\nComputer Wins The Toss !! \n\n";
        switch(rand)
        {
          case 0 : cout<<"\n\nComputer Choose To Bat ! ";
            getch();
            bowl();
          break;
          case 1 : cout<<"\n\nComputer Choose To Bowl ! ";
            getch();
            bat();
          break;
        }
      }
      break;
  }
  if(us>cs)
  {
    cout<<"\n\n\t\t\t***You Win !! ***";
  }
  else if(cs>us)
  {
    cout<<"\n\n\t\t\t***Computer Win !! ***";
  }
  else
  {
    cout<<"\n\n\t\t\t***Match TIED";
  }
  cout<<"\n\nDo You Want To Play Again ? \n\nEnter Y / N : ";
  toss=toupper(getch());
  cout<<toss;
  if(toss=='N')
  {
    cout<<"\n\nThankYou For Playing This Game !!";
    delay(2000);
  }
  else
    goto start;
    getch();
}

void bat()
{
  clrscr();
  randomize();
  cout<<"\n\n\n\nUser Batting !\n\n";
  int u,c;
do
{
  if(flag!=0)
  {
    if((cs-us)<0)
  {
    cout<<"\n\n\nYou Win !!";
    goto end;
  }
    cout<<"\n\nYou Need "<<(cs-us)<<" Runs To Win ! ";
  }
  cout<<"\n\nEnter Shot 1 to 4 and 6 : ";
  u=getche();
  u-=48;
  if((u>6)||(u==0)||(u==5))
  {
    cout<<"\aInvalid Shot ! ";
    continue;
  }
  c=random(5);
  switch(c)
  {
    case 0 : c=1 ;break;
    case 1 : c=2 ;break;
    case 2 : c=3 ;break;
    case 3 : c=4 ;break;
    case 4 : c=6 ;break;
  }
  if(u!=c)
  {
    us+=u;
    cout<<"\nYou Win "<<u<<" Runs ";
  }
  else
  {
    cout<<"\n\nYou Are OUT \n\nYou Have "<<us<<" Runs ! ";
  }
  } while(u!=c);
  getch();
  if(flag==0)
  {
    flag=1;
    bowl();
  }
  end :
}

void bowl()
{
  clrscr();
  randomize();
  int u,c;
  cout<<"\n\n\n\nUser Bowling !\n\n";
  do
  {
    if(flag!=0)
    {
    if((us-cs)<0)
    {
    cout<<"\n\n\nComputer Wins !! ";
    goto end;
    }
    cout<<"\n\nComputer Needs "<<(us-cs)<<" Runs To Win ! \n\n";
    }
    cout<<"\n\nEnter Style 1 to 4 and 6 : ";
    u=getche();
    u-=48;
    if((u>6)||(u==0)||(u==5))
    {
    cout<<"\aInvalid Style ! ";
    continue;
    }
    c=random(5);
    switch(c)
    {
    case 0 : c=1 ;break;
    case 1 : c=2 ;break;
    case 2 : c=3 ;break;
    case 3 : c=4 ;break;
    case 4 : c=6 ;break;
    }
    if(u!=c)
    {
    //cout<<c<<" "<<cs;
    cs+=c;
    cout<<"\nComputer Win "<<c<<" Runs ";
    }
    else
    {
    cout<<"\n\nYou Have Bowled Out The Computer \n\nComputer Have "<<cs<<" Runs ! ";
    }

  } while(u!=c);
  getch();
  if(flag==0)
  {
    flag=1;
    bat();
  }
  end:
}