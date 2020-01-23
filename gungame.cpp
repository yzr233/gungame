#pragma GCC optimize(2)
#include<cstdio>
#include<windows.h>
#include<ctime>
#define key(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define koy(vk_code) ((GetKeyState(vk_code)&0x8000)?1:0)
#define sj(i,j) (rand()%(j-i+1)+i)
#define for1 for(int i=0;i<n;i++)for(int j=0;j<m;j++)
#define for2 for(int d=0;d<4;d++)
#define abs(i) ((i)>0?(i):-(i))
#define max(i,j) ((i)>(j)?(i):(j))
#define min(i,j) ((i)>(j)?(j):(i))
#define dis(i1,j1,i2,j2) (((i1)-(i2))*((i1)-(i2))+((j1)-(j2))*((j1)-(j2)))
namespace o {
    char buf[100005];int write=0,pfn,pfm;
    void ch(char c){
    	buf[write++]=c;
	}
    void pf(const char *st,...){
        int num=0;bool op=0,lo=0;
        va_list p;
        va_start(p,st);
        int s=strlen(st);
        for(int i=0;i<s;i++){
            if(op){
                if(st[i]>='0'&&st[i]<='9'){
                    num=num*10+st[i]-'0';
                    continue;
                }
                if(st[i]=='d'){
                    int q=va_arg(p,int);
                    if(q<0)ch('-'),q=-q;
                    int j=10,k=1;
                    while(j<=q)j*=10,k++;
                    if(num>0){
                        num-=k;
                        while(num>0)ch(' '),num--;
                    }
                    while(k--)j/=10,ch(q/j+'0'),q%=j;
                }
                if(st[i]=='f'){
                    double q1=va_arg(p,double);
                    int q=int(q1);q1-=q;
                    if(q<0)ch('-'),q=-q;
                    int j=10,k=1;
                    while(j<=q)j*=10,k++;
                    while(k--)j/=10,ch(q/j+'0'),q%=j;
                    k=num>0?num:6;num=0;
                    if(q1>0)ch('.');
                    int l=k;j=1;
                    while(k--)j*=10;
                    while(int(q1*j)>0){
                        int q2=int(q1*10);q1=(q1*10-q2);
                        ch(q2+'0');
                        if((--l)==0)break;
                    }
                }
                if(st[i]=='c'){
                    char q=va_arg(p,int);
                    ch(q);
                }
                if(st[i]=='s'){
                    char* str=va_arg(p,char*);
                    for(int i=0;i<strlen(str);i++)
                        ch(str[i]);
                }
                if(st[i]=='%'){
                    ch('%');
                }
                lo=0;op=0;num=0;continue;
            }
            if(st[i]=='%'&&op==0)op=1;
            if(st[i]!='%'){
//              if(st[i]=='\n'){
//                  int j=8;while(j--)buf[write++]=' ';
//              }
                ch(st[i]);
            }
        }
        va_end(p);
    }
    void out(){
        fwrite(buf,1,write,stdout),write=0;
    }
}
using namespace o;
using namespace std;
const int N=300,xi[4]={-1,0,1,0},yi[4]={0,-1,0,1};
char a[N][N],str[50];
char sc1[6]={87,65,83,68,70,71},sc2[6]={38,37,40,39,96,110};
char mdn[9][9]={"PVP","PVE"};
char wqn[11][9]={"null","mp5","rpg","gun","knife","5","6","7","8","9","drug"};
short wqw[10]={0,35,2,8,1,0,0,0,0,0};
short live[N][N],tmp[N][N],cart[N][N][4];
bool go[N][N][4];
int n,m,t,tar,mode;
clock_t stime,etime;
double ttime,mtime=8;
//mode: 0-pvp 1-pve
struct Player{int x,y,dir,cd,fh,bb,sl;}r,b;
bool stop,dark;
void Hide_cursor();
void jump(int,int);
int atk(int,int,int);
bool went(int,int,int,int&,int&);
void in(Player&,const char*);
void outp(Player);
void cols(int,int);
double sttime();
int main(){
    /*welcome & enter map*/
    pf("Welcome to the gun game 4.2!\n");out();
//    if(freopen("233.cps","r",stdin)==NULL){
//      freopen("233.cps","w",stdout);
//      printf("87 65 83 68 70 71\n73 74 75 76 186 222\n50");
//      freopen("CON","w",stdout);
//  }
//    freopen("233.cps","r",stdin);
//    for(int i=0;i<6;i++)scanf("%d",&sc[0][i]);
//    for(int i=0;i<6;i++)scanf("%d",&sc[1][i]);
//    scanf("%d",&sca[0]);
    freopen("CON","r",stdin);
    do{
    	con1:pf("Please enter the name of the map: ");out();
    	scanf("%s",str);
    	freopen(str,"r",stdin);
    	while(scanf("%s",a[n])!=-1){
        	if(n==0){
        	    m=strlen(a[0]);
        	    mode=a[0][0]-'0';a[0][0]='X';
        	    if(a[0][1]=='Y')dark=1,a[0][1]='X';
    	    }
    	    for(int j=0;j<m;j++){
    	        char &c=a[n][j];
    	        if(c=='.')c=' ';
    	        if(c=='*')tmp[n][j]=1,c=' ';
    	        if(c=='O')live[n][j]=12;
    	        if(c=='R')r.x=n,r.y=j,live[n][j]=20;
    	        if(c=='B')b.x=n,b.y=j,live[n][j]=20;
    	        if(c=='K')live[n][j]=10;
    	        if(c=='E')live[n][j]=20;
    	        if(c=='@'&&mode==1)tar++;
    	    }
    	    n++;
    	}
    	freopen("CON","r",stdin);
    	if(n==0)goto con1;
    }while(0);
    jump(0,0);
    pfm=max(m+2,42),pfn=n+3;
	cols(pfm,pfn);
    /*start game*/
    Hide_cursor();srand(time(0));
    pf("3");out();Sleep(1000);jump(0,0);
    pf("2");out();Sleep(1000);jump(0,0);
    pf("1");out();Sleep(1000);jump(0,0);
    game:t++;
    /*out map*/
    jump(0,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if((dark&&dis(i,j,r.x,r.y)>45&&dis(i,j,b.x,b.y)>45))pf("*");
            else if(tmp[i][j]==1)pf("*");
            else if(cart[i][j][0]||cart[i][j][1])pf(".");
            else if(cart[i][j][2]||cart[i][j][3])pf(".");
            else pf("%c",a[i][j]);
        }
        pf("\n");
    }
    pf("%s time:%d fps:%1f",mdn[mode],t/10,sttime());
    if(mode==1)pf(" target:%d",tar);
    if(stop)pf(" (stoping)");
    else pf("          "); 
    pf("\n");
    pf("player1:");outp(r);
    pf("player2:");outp(b);
    pf("\n");
//    pf("(%d,%d)(%d,%d)",r.x,r.y,b.x,b.y);
    out();
    /*win or lost*/
    if(mode==0){
        if(live[r.x][r.y]<=0){pf("player2 win in time %d!",t/10);goto end;}
        if(live[b.x][b.y]<=0){pf("player1 win in time %d!",t/10);goto end;}
    }
    if(mode==1){
        if(live[r.x][r.y]<=0&&live[b.x][b.y]<=0){
            pf("You lost in time %d!",t/10);goto end;
        }
        if(!tar){pf("You win in time %d!",t/10);goto end;}
    }
    /*read*/
    stop=koy(80);
    if(!stop)in(r,sc1),in(b,sc2);
    /*time*/
    if(stop){t--;goto game;}
    if(r.cd)r.cd--;if(b.cd)b.cd--;
    if(mode==1){
        if(t%36==0){
            if(live[r.x][r.y]>0&&live[r.x][r.y]<4)live[r.x][r.y]++;
            if(live[b.x][b.y]>0&&live[b.x][b.y]<4)live[b.x][b.y]++;
        }
        if((abs(r.x-b.x)+abs(r.y-b.y))==1){
            r.fh=b.fh=r.fh+2;
            if(r.fh>=100){
                if(live[r.x][r.y]<=0)live[r.x][r.y]=4,a[r.x][r.y]='R';
                if(live[b.x][b.y]<=0)live[b.x][b.y]=4,a[b.x][b.y]='B';
            }
        }
        else r.fh=b.fh=max(r.fh-3,0);
    }
    /*ai go*/
    if(t%16==0){
        for1 go[i][j][0]=0;
        for1{
            if(go[i][j][0]||(a[i][j]!='K'&&a[i][j]!='E'))continue;
            for2{
                int xx=i,yy=j;
                do{
                    xx+=xi[d];yy+=yi[d];
                    if(tmp[xx][yy]==1)continue;
                    if(a[xx][yy]=='R'||a[xx][yy]=='B'){
                        cart[i+xi[d]][j+yi[d]][d]=1;
                        goto bre1;
                    }
                }while(a[xx][yy]!='X'&&a[xx][yy]!='K'&&a[xx][yy]!='E');
            }
            if(a[i][j]=='K'){
                int z=0,zz[4],bb,sl;
                for2 if(a[i+xi[d]][j+yi[d]]==' ')zz[z++]=d;
                if(z>0)z=sj(0,z-1),went(i,j,zz[z],bb,sl);
                go[i+xi[z]][j+yi[z]][0]=1;
            }
            bre1:;
        }
    }
    /*Fcart*/
    for1 for2 go[i][j][d]=0;
    for1 for2{
        if(cart[i][j][d]==0||go[i][j][d])continue;
        if(atk(i,j,0)==1){
            if(cart[i][j][d]==1)atk(i,j,3);
            if(cart[i][j][d]==2)
                for(int ii=i-2;ii<=i+2;ii++)
                    for(int jj=j-2;jj<=j+2;jj++)
                        if(ii>0&&ii<n&&jj>0&&jj<m)
                            atk(ii,jj,12);
            if(cart[i][j][d]==3)atk(i,j,10);
        }
        else if(atk(i,j,0)==0){
            int xx=i+xi[d],yy=j+yi[d];
            cart[xx][yy][d]=cart[i][j][d];
            go[xx][yy][d]=1;
        }
        else{

        }
        cart[i][j][d]=0;
    }
    goto game;
    end:out();
    Sleep(1e9);
    return 0;
}
void Hide_cursor(){
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void cols(int x,int y){
    char st[100]="mode con cols=";int stn=strlen(st);
    int a=1,b=1;
    while(a*10<=x)a*=10,b++;
    while(b--)st[stn++]=(x/a)%10+'0',a/=10;
    const char st1[]=" lines=";
    for(int i=0;i<7;i++)st[stn++]=st1[i];
    a=1,b=1;
    while(a*10<=y)a*=10,b++;
    while(b--)st[stn++]=(y/a)%10+'0',a/=10;
    system(st);
}
void jump(int x,int y){
    HANDLE hout;COORD coord;
    coord.X=x;coord.Y=y;
    hout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout,coord);
}
int atk(int x,int y,int k){
    char &c=a[x][y];
    if(c!='R'&&c!='B'&&c!='K'&&c!='E'&&c!='O'){
        if(c=='X')return -1;
        else return 0;
    }
    live[x][y]-=k;
    if(live[x][y]<=0)c=(c=='R'||c=='B')?'T':' ';
    return 1;
}
void outp(Player p){
    if(live[p.x][p.y]>0)pf("%d",live[p.x][p.y]);
    else pf("%d%%",p.fh);
    if(live[p.x][p.y]>0&&live[p.x][p.y]<4)pf("!");
    pf("(%sx%d)",wqn[p.bb],p.sl);
}
void in(Player& p,const char *f){
    if(a[p.x][p.y]=='T')return;
    for2 if(key(f[d])){
        if(went(p.x,p.y,d,p.bb,p.sl))
            p.x+=xi[d],p.y+=yi[d];
        p.dir=d;
    }
    int xx=p.x+xi[p.dir],yy=p.y+yi[p.dir];
    if(key(f[4])&&p.cd<=0)cart[xx][yy][p.dir]=1,p.cd+=4;
    if(key(f[5])&&p.cd<=0&&p.bb>0){
        if(p.bb>=1&&p.bb<=3)cart[xx][yy][p.dir]=p.bb;
        if(p.bb==4){
            for2 atk(p.x+xi[d],p.y+yi[d],2);
            p.cd-=1;p.sl++;
        }
        if(p.bb==10){
            if(a[xx][yy]=='R'||a[xx][yy]=='B')live[xx][yy]+=8;
            else live[p.x][p.y]+=8;
        }
        p.cd+=2;p.sl--;
        if(p.sl==0)p.bb=0;
    }
}
bool went(int x,int y,int d,int& bb,int& sl){
    int xx=x+xi[d],yy=y+yi[d];
    if(a[xx][yy]=='H')live[x][y]=max(live[x][y],16);
    else if(a[xx][yy]=='@')tar--;
    else if(a[xx][yy]=='O'){
        int x3=xx+xi[d],y3=yy+yi[d];
        if(a[x3][y3]!=' '&&a[x3][y3]!='N'&&a[x3][y3]!='H')return 0;
        if(tmp[x3][y3]==1)tmp[x3][y3]=0;
        if(a[x3][y3]!='N')a[x3][y3]='O',live[x3][y3]=live[xx][yy];
        else a[x3][y3]=' ';
    }
    else if(a[xx][yy]==' '){

    }
    else if(a[xx][yy]=='+')bb=10,sl=1;
    else if(a[xx][yy]>'0'&&a[xx][yy]<'9'){
        bb=a[xx][yy]-'0',sl=wqw[bb];
    }
    else return 0;
    a[xx][yy]=a[x][y];a[x][y]=' ';
    live[xx][yy]=live[x][y];
    return 1;
}
double sttime(){
    etime=clock();
    ttime=(double)(etime-stime)/CLOCKS_PER_SEC;
    if((1.00/mtime)-ttime>0)Sleep(((1.00/mtime)-ttime)*1000);
    ttime=1.0/((double)(etime-stime)/CLOCKS_PER_SEC);
    stime=etime;
    return ttime;
}
