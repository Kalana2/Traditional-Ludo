player players[NUMBEROFPLYERS];

void printLudoHeading() {
    printf("\n");
    printf(Red "\t\t  _       _    _   ____   ____   \n" RESET);
    printf(Green "\t\t | |     | |  | | |  _ \\ |  _ \\  \n" RESET);
    printf(Blue "\t\t | |     | |  | | | | | || | | | \n" RESET);
    printf(Yellow "\t\t | |___  | |__| | | |_| || |_| | \n" RESET);
    printf(Red "\t\t |_____|  \\____/  |____/ |____/  \n" RESET);
    printf("\n");

    printf("\t\t\tby Kalana Jinendra\n\n\n\n");
}

void playerSetup(){
    strcpy(players[0].name, "Red");
    strcpy(players[1].name, "Green");
    strcpy(players[2].name, "Blue");
    strcpy(players[3].name, "Yellow");

    short int pos = 1;
    for(int i=0;i<4;i++){
        players[i].isplayerPlay=false;
        players[i].homeCount=0;
        players[i].startingPoint=pos;
        players[i].approch=(pos+50)%52;

        players[i].p1.name =1;
        players[i].p2.name =2;
        players[i].p3.name =3;
        players[i].p4.name =4;  

        players[i].p1.inCom =false;
        players[i].p2.inCom =false;
        players[i].p3.inCom =false;
        players[i].p4.inCom =false;
              
        pos+=13;
    }
    //The red player has four (04) pieces named R1, R2, R3, and R4.
    for(int i=0; i<4;i++){
        printf(">>\tThe %s player has Four picese named ",players[i].name);
        for(int j=0;j<4;j++){
            printf("%c%d ",players[i].name[0],j);
        }
        printf("\n\n");
    }
    for(int i=0;i<4;i++){
        printf(">>\t%s players starting cell is %d & approch cell is %d\n",players[i].name,players[i].startingPoint,players[i].approch);
    }
    printf("\n");
}

void colour(int index){
	switch (index)
	{
	case 0:
		printf(Red);
		break;
	case 1:
		printf(Green);
		break;
	case 2:
		printf(Blue);
		break;
	case 3:
		printf(Yellow);
		break;
	}
}

short int diceRolling(char name[]){
    
    int val = (1 + (rand() % 6));
	printf(">>\t%s Rolls %d\n",name,val);
	return val;

}

int  getFirstplayer(player players[4]){

    short int curruntPlayer=0,pre=0,temp;
    int count=0;
    for (int  i = 0; i < 4; i++){   
        short int val= diceRolling(players[i].name);
        if(pre<val){
            curruntPlayer=i;
            pre=val;
        }
    }
    printf("\n>>\t%s player has the highest roll and will begin the game.\n",players[curruntPlayer].name); 
    printf(">>\tThe order of a single round is ");
    for(int i=0;i<4;i++){
        printf("%s ",players[(curruntPlayer+i)%4].name);
        if(i==2) printf("and ");
    }
    printf("\n\n");
    return curruntPlayer;
}
 
bool capture(player *currentPlayer, short int steps){
    for (int i = 0; i < 4; i++){
        player *tempPlayer = &players[i];
        if (tempPlayer == currentPlayer) continue;

        piece *pieces[] = {&tempPlayer->p1, &tempPlayer->p2, &tempPlayer->p3, &tempPlayer->p4};
        for (int j = 0; j < 4; j++) {
            piece *tempPiece = pieces[j];

            if (tempPiece->inCom && !tempPiece->inStringht){

                short int newComPos = (currentPlayer->p1.comPos + steps) % 52;

                if (tempPiece->comPos == newComPos){
                    tempPiece->inCom = false;
                    tempPiece->relPos = 0;
                    tempPiece->comPos = 0;
                    printf(">>\t"Underline"%s player captures %s's piece %d and move to %d "RESET"\n" , currentPlayer->name, tempPlayer->name, tempPiece->name, newComPos);
                    return true;
                }
            }
        }
    }
    return false; 
}

void movePiece(player *player, short int steps){
    
    piece *pieces[] = {&player->p1, &player->p2, &player->p3, &player->p4};

    for(int i=0; i<4;i++){
        piece *p =pieces[i] ;
        if (player->isWin) {
        return;
        }
        else{
            if(p->inStringht){
                short int newStrPos = p->Strpos + steps;
                
                if(p->Strpos>=6 && !p->isHome){
                    printf(">>\t%s player piece %d comes to home\n", player->name, p->name);
                    p->isHome=true;
                    player->homeCount++;
                    return;
                }
                else if(!p->isHome){
                    if(newStrPos<6)
                    printf(">>\t%s moves piece %d from location %d to %d by %d in home stright \n", player->name, p->name, p->Strpos, newStrPos, steps);
                    p->Strpos = newStrPos;
                    return;
                }
            }                
    }
    for (int i = 0; i < 4; i++) {
        piece *p =pieces[i];
        if (!p->inCom && steps == 6){
            p->inCom = true;
            p->relPos = 1;
            p->comPos = player->startingPoint;
            player->isplayerPlay = true;
            printf(">>\t%s player moves piece %d to the starting point.\n", player->name, p->name);
            return;
        }
    }
    for (int i = 0; i < 4; i++) {
        piece *p =pieces[i];
        p->relPos += steps;
        if (p->inCom && !p->inStringht ){
            if(p->relPos < 51){
                if (capture(player, steps)) {
                    return;
                }
                int newComPos = (p->comPos + steps) % 52;
                printf(">>\t%s moves piece %d from location %d to %d by %d\n", player->name, p->name, p->comPos, newComPos, steps);
                p->comPos = newComPos;
                return;
            }
            if (p->relPos >= 51 && p->inStringht==false){
                    p->inStringht = true;
                    p->Strpos = p->relPos - 51;
                    printf(">>\t%s player %d piece on the approach cell\n", player->name, p->name);
                    if(p->Strpos>=1){
                        printf(">>\t%s moves piece %d moves to %d by %d in home stright \n", player->name, p->name, p->Strpos,steps);
                    }
                    return;
            }
            
        }
    }
}
}

void logic(){
   short int count = getFirstplayer(players);
    do{   
        short int playingPlayer= count%4, sixCount=0 ;
        colour(playingPlayer);
        if(players[playingPlayer].homeCount!=4){
            short int val = diceRolling(players[playingPlayer].name);
            movePiece(&players[playingPlayer],val);
            if(players[playingPlayer].homeCount==4 && players[playingPlayer].isWin == false){
                players[playingPlayer].isWin=true;
                numOfWiner++;
                if(numOfWiner==1){
                    printf(">>\t"BgWhite" %s player win the game "RESET"\n", players[playingPlayer].name);
                    continue;
                }
                else{
                    printf(">>\t%s player end the game %d place\n", players[playingPlayer].name,numOfWiner);   
                }    
            }
                if(val==6){
                    sixCount++;
                    if (sixCount<2)
                        continue ;
            }
        }
        count++;
       // sleep(1);
        
    }while(numOfWiner<4);
}
