#pragma pack(1)

//
#define NUMBEROFPLYERS 4

//terminal colours
#define Underline "\033[4m" 
#define Red "\033[31m" 
#define Green "\033[32m"
#define Yellow "\033[33m"
#define Blue "\033[34m"
#define Black "\033[30m"
#define BgWhite "\033[47m"
#define RESET "\033[0m"

typedef struct {
    bool inCom;
    bool inStringht;
    bool isHome;
    short int comPos;
    short int relPos;
    short int Strpos;
    short int name;

}piece;
typedef struct {
    char name[10];
    bool isplayerPlay;
    short int homeCount;
    bool isWin;
    short int startingPoint;
    short int approch;
    piece p1, p2, p3, p4;

}player;

//player players[NUMBEROFPLYERS]; // store the pl

short int numOfWiner=0;