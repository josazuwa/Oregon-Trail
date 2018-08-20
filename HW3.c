#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node
{
    enum ThreatType {COLD, FLU, DYSENTERY, GRIZZLY, BOAR, ELK, HARE, OCEAN, START, FINISH, NONE, RIVER} threattype;
    int XLocation;
    int YLocation;
    char letter;
    struct node *up;
    struct node *down;
    struct node *left;
    struct node *right;
    bool Discovered;
    bool DorR;
    
} NODE;

//Function used to create node
//Input: X Location, Y Location, Character Type
//Output: A Node* with the correct data
NODE * CreateNode(int xloc, int yloc, char type){
	
   NODE * newnode;
   newnode = (NODE *) malloc (sizeof(NODE));
   if (newnode == NULL){
   
      printf ("No Memory left !!\n");
      return NULL;
	  
   }
   newnode->XLocation = xloc;
   newnode->YLocation = yloc;
   newnode->up = NULL;
   newnode->down = NULL;
   newnode->left = NULL;
   newnode->right = NULL;
   newnode->Discovered = false;
   newnode->letter = type;
   if(type == 'C' || type == 'F' || type == 'D' || type == 'R'){
       newnode->DorR = true;
   }
   else{
       newnode->DorR = false;
   }

   return newnode;
}

//This is used to print the correct letter after it is changed to the current node
//Input: A Node*
//Output: The letter that corresponds to the Node*
char GetLetter(NODE* newnode){
    if(newnode -> threattype == RIVER){
      return 'R';
    }
    else if(newnode -> threattype == COLD){
      return 'C';
    }
    else if(newnode -> threattype == FLU){
      return 'F';
    }
    else if(newnode -> threattype == DYSENTERY){
      return 'D';
    }
    else{
      return '?';
    }
}

//Used to free memory in the map
//Input: The size of the map and the actual map itself
//Output: None - a freed map
void clearMap(int size, NODE* map[size][size]){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      free(map[i][j]);
    }
  }
}

//Function used to change the map and put player in the correct position
//Input: 2 Node*, where you are and where you are going
//Output: None - Swap information in the Node*
void SwapNode(NODE* start, NODE* finish){
    if(start->threattype != RIVER && start->threattype != COLD && start->threattype != FLU && start->threattype != DYSENTERY && finish->threattype != RIVER && finish->threattype != COLD && finish->threattype != FLU && finish->threattype != DYSENTERY){
        start->threattype = NONE;
        finish->threattype = START;
        start->letter = 'N';
        finish->letter = 'X';
        start->DorR = false;
        finish->DorR = false;
    }
    else{
        if(start->DorR == true && finish->DorR == true){
            start->letter = GetLetter(start);
            finish->letter = 'X';
        }
        else if(start->DorR == true && finish->DorR == false){
            start->letter = GetLetter(start);
            finish->letter = 'X';
            finish->threattype = START;
        }
        else if(start->DorR == false && finish->DorR == true){
            start->letter = 'N';
            finish->letter = 'X';
            start->threattype = NONE;
        }
    }
}

int main(int argc, char *argv[]){
    
    FILE *ptr_file;
    char buf[1000];

    int count = 0;
    int count2 = 0;
    int count3 = 0;

    char mapBufN[1000];
    char viewBufN[1000];
    char foodBufN[1000];
    char MAP[1000];

    ptr_file =fopen(argv[1],"r");
    if (!ptr_file)
      return 1;

    while (fgets(buf,1000, ptr_file)!=NULL){
      int length = strlen(buf);
      for(int i = 0; i < length; i++){
	if(count == 0){
	  mapBufN[count2] = buf[i+8];
	}
	else if(count == 1){
	  viewBufN[count2] = buf[i + 9];
	}
	else if(count == 2){
	  foodBufN[count2] = buf[i + 5];
	}
	else if(count >= 5){
	  if(i != (length - 1)){
	    MAP[count3] = buf[i];
	    count3++;
	  }
	}
	count2++;
      }
      count2 = 0;
      count++;
    }   

    int MapSize = atoi(mapBufN);
    int ViewPort = atoi(viewBufN);
    int Food = atoi(foodBufN);
    int FullSize = MapSize + 2;
    count = 0;

    //This series of lines creates the map
    NODE* map[FullSize][FullSize];
    NODE* view[ViewPort][ViewPort];
    for(int r = 0; r < FullSize; r++){
        for(int c = 0; c < FullSize; c++){
            if(MAP[count] == 'O'){
                map[r][c] = CreateNode(r,c,'O');
                map[r][c]->threattype = OCEAN;
            }
            else if(MAP[count] == 'G'){
                map[r][c] = CreateNode(r,c,'G');
                map[r][c]->threattype = GRIZZLY;
            }
            else if(MAP[count] == 'B'){
                map[r][c] = CreateNode(r,c,'B');
                map[r][c]->threattype = BOAR;
            }
            else if(MAP[count] == 'E'){
                map[r][c] = CreateNode(r,c,'E');
                map[r][c]->threattype = ELK;
            }
            else if(MAP[count] == 'H'){
                map[r][c] = CreateNode(r,c,'H');
                map[r][c]->threattype = HARE;
            }
            else if(MAP[count] == 'C'){
                map[r][c] = CreateNode(r,c,'C');
                map[r][c]->threattype = COLD;
            }
            else if(MAP[count] == 'F'){
                map[r][c] = CreateNode(r,c,'F');
                map[r][c]->threattype = FLU;
            }
            else if(MAP[count] == 'D'){
                map[r][c] = CreateNode(r,c,'D');
                map[r][c]->threattype = DYSENTERY;
            }
            else if(MAP[count] == 'X'){
                map[r][c] = CreateNode(r,c,'X');
                map[r][c]->threattype = START;
            }
            else if(MAP[count] == 'Z'){
                map[r][c] = CreateNode(r,c,'Z');
                map[r][c]->threattype = FINISH;
            }
            else if(MAP[count] == 'N'){
                map[r][c] = CreateNode(r,c,'N');
                map[r][c]->threattype = NONE;
            }
            else if(MAP[count] == 'R'){
                map[r][c] = CreateNode(r,c,'R');
                map[r][c]->threattype = RIVER;
            }
            count++;
        }
    }
    //These series of lines links all of the nodes together
    for(int r = 0; r < FullSize; r++){
        for(int c = 0; c < FullSize; c++){
            if(r == 0 || c == 0 || r == (FullSize - 1) || c == (FullSize - 1)){
                if(r == 0 && c == 0){
                    map[r][c]->right = map[r][c+1];
                    map[r][c]->down = map[r+1][c];
                }
                else if(r == 0 && c == (FullSize - 1)){
                    map[r][c]->left = map[r][c-1];
                    map[r][c]->down = map[r+1][c];
                }
                else if(r == 0){
                    map[r][c]->left = map[r][c-1];
                    map[r][c]->down = map[r+1][c];
                    map[r][c]->right = map[r][c+1];
                }
                else if(r == (FullSize - 1) && c == 0){
                    map[r][c]->right = map[r][c+1];
                    map[r][c]->up = map[r-1][c];
                }
                else if(r == (FullSize - 1) && c == (FullSize - 1)){
                    map[r][c]->left = map[r][c-1];
                    map[r][c]->up = map[r-1][c];
                }
                else if(r == (FullSize - 1)){
                    map[r][c]->left = map[r][c-1];
                    map[r][c]->up = map[r-1][c];
                    map[r][c]->right = map[r][c+1];
                }
                else if(c == 0){
                    map[r][c]->up = map[r-1][c];
                    map[r][c]->right = map[r][c+1];
                    map[r][c]->down = map[r+1][c];
                }
                else if(c == (FullSize - 1)){
                    map[r][c]->up = map[r-1][c];
                    map[r][c]->left = map[r][c-1];
                    map[r][c]->down = map[r+1][c];
                }
            }
            else{
                map[r][c]->up = map[r-1][c];
                map[r][c]->left = map[r][c-1];
                map[r][c]->down = map[r+1][c];
                map[r][c]->right = map[r][c+1];
            }
        }
    }
    char choice;
    char choice2;
    char direct;
    printf("Press S to start game, Q to quit game or D to diplay instructions: ");
    scanf (" %c", &choice);
    if(choice == 's' || choice == 'S'){
        NODE* currentNode = map[FullSize - 2][FullSize - 2];
        //Starts the game and continues while not in the correct area
        while(currentNode->XLocation != 1 || currentNode->YLocation != 1){
            printf("Food: ");
            printf("%d\n", Food);
            //This creates the viewport to be seen
            view[(ViewPort-1)/2][(ViewPort-1)/2] = currentNode;
            int xcount = (currentNode->XLocation) - (ViewPort-1)/2;
            int ycount = (currentNode->YLocation) - (ViewPort-1)/2;
            for(int i = 0; i < ViewPort; i++){
                for(int j = 0; j < ViewPort; j++){
                    if(xcount < 0 || xcount >= FullSize || ycount < 0 || ycount >= FullSize){
                        view[i][j] = CreateNode(i,j,'O');
                        view[i][j]->threattype = OCEAN;
                        printf("%c",view[i][j]->letter);
                        free(view[i][j]);
                    }
                    else{
                        view[i][j] = map[xcount][ycount];
                        if(view[i][j]->Discovered == false && view[i][j]->threattype != RIVER && view[i][j]->threattype != START && view[i][j]->threattype != OCEAN && view[i][j]->threattype != NONE && view[i][j]->threattype != FINISH){
                            printf("U");
                        }
                        else{
                            printf("%c",view[i][j]->letter);
                        }
                    }
                    ycount++;
                }
                xcount++;
                ycount = (currentNode->YLocation) - (ViewPort-1)/2;
                printf("\n");
            }
            //The selection for which direction to go in
            printf("Which direction do you want to go? U for Up, D for Down, L for Left, R for Right, E to Exit: ");
            scanf (" %c", &direct);
            //The selection of up is correct
            if(direct == 'u' || direct == 'U'){
                if((currentNode->up)->threattype == OCEAN){
                    printf("Cannot Pass Ocean Tiles\n");
                }
                else if((currentNode->up)->threattype == FINISH){
		  SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
		  currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
		}
                else if((currentNode->up)->threattype == NONE){
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                    currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                }
                else if((currentNode->up)->threattype == GRIZZLY){
                    printf("You have encountered a Grizzly bear, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food - 10;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                        currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                        printf("You have lost 10 Food due to this encounter.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[(currentNode->XLocation) - 1][currentNode->YLocation] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->up)->threattype == BOAR){
                    printf("You have encountered an Boar, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h'  || choice2 == 'H'){
                        Food = Food - 5;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                        currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                        printf("You have lost 5 Food due to this encounter.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[(currentNode->XLocation) - 1][currentNode->YLocation] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->up)->threattype == ELK){
                    printf("You have encountered an Elk, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                        currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                        printf("Your food supply remains unchanged\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[(currentNode->XLocation) - 1][currentNode->YLocation] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->up)->threattype == HARE){
                    printf("You have encountered a HARE, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food + 5;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                        currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                        printf("You have gained 5 Food due to this encounter\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[(currentNode->XLocation) - 1][currentNode->YLocation] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->up)->threattype == RIVER){
                    printf("You are attempting to ford a river; you may either choose to ford (f) or retreat(r): " );
                    scanf (" %c", &choice2);
                    if(choice2 == 'f' || choice2 == 'F'){
                        Food = Food - 20;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                        currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                        printf("You have lost 20 Food while crossing the river.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        printf("You choose to retreat\n");
                    }
                }
                else if((currentNode->up)->threattype == COLD){
                    printf("You have contracted the common cold, your food storage drops by 5 as you take a day off to recuperate\n" );
                    Food = Food - 5;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                    map[(currentNode->XLocation) - 1][currentNode->YLocation] -> Discovered = true;
                    currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                }
                else if((currentNode->up)->threattype == FLU){
                    printf("You have contracted the Flu, your food storage drops by 10 as you take a day off to recuperate\n" );
                    Food = Food - 10;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                    map[(currentNode->XLocation) - 1][currentNode->YLocation] -> Discovered = true;
                    currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                }
                else if((currentNode->up)->threattype == DYSENTERY){
                    printf("You have contracted Dysentery, your food storage drops by 15 as you take a day off to recuperate\n" );
                    Food = Food - 15;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->up)->XLocation][(currentNode->up)->YLocation]);
                    map[(currentNode->XLocation) - 1][currentNode->YLocation] -> Discovered = true;
                    currentNode = map[(currentNode->XLocation) - 1][currentNode->YLocation];
                }

            }
            //The selection of down is correct
            else if(direct == 'd' || direct == 'D'){
                if((currentNode->down)->threattype == OCEAN){
                    printf("Cannot Pass Ocean Tiles\n");
                }
		else if((currentNode->down)->threattype == FINISH){
                  SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                  currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
                }
                else if((currentNode->down)->threattype == NONE){
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                    currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
                }
                else if((currentNode->down)->threattype == GRIZZLY){
                    printf("You have encountered a Grizzly bear, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food - 10;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                        currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
			printf("You have lost 10 Food due to this encounter.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[(currentNode->XLocation) + 1][currentNode->YLocation] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->down)->threattype == BOAR){
                    printf("You have encountered an Boar, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food - 5;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                        currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
			printf("You have lost 5 Food due to this encounter.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[(currentNode->XLocation) + 1][currentNode->YLocation] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->down)->threattype == ELK){
                    printf("You have encountered an Elk, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                        currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
			printf("Your food supply remains unchanged\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[(currentNode->XLocation) + 1][currentNode->YLocation] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->down)->threattype == HARE){
                    printf("You have encountered a HARE, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h'){
                        Food = Food + 5;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                        currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
			printf("You have gained 5 Food due to this encounter\n");
                    }
                    else if(choice2 == 'r'){
                        map[(currentNode->XLocation) + 1][currentNode->YLocation] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->down)->threattype == RIVER){
                    printf("You are attempting to ford a river; you may either choose to ford (f) or retreat(r): " );
                    scanf (" %c", &choice2);
                    if(choice2 == 'f' || choice2 == 'F'){
                        Food = Food - 20;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                        currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
			printf("You have lost 20 Food while crossing the river.\n");
                    }
                    else if(choice2 == 'r'){
                        printf("You choose to retreat\n");
                    }
                }
                else if((currentNode->down)->threattype == COLD){
                    printf("You have contracted the common cold, your food storage drops by 5 as you take a day off to recuperate\n" );
                    Food = Food - 5;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                    map[(currentNode->XLocation) + 1][currentNode->YLocation] -> Discovered = true;
                    currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
                }
                else if((currentNode->down)->threattype == FLU){
                    printf("You have contracted the Flu, your food storage drops by 10 as you take a day off to recuperate\n" );
                    Food = Food - 10;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                    map[(currentNode->XLocation) + 1][currentNode->YLocation] -> Discovered = true;
                    currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
                }
                else if((currentNode->down)->threattype == DYSENTERY){
                    printf("You have contracted Dysentery, your food storage drops by 15 as you take a day off to recuperate\n" );
                    Food = Food - 15;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->down)->XLocation][(currentNode->down)->YLocation]);
                    map[(currentNode->XLocation) + 1][currentNode->YLocation] -> Discovered = true;
                    currentNode = map[(currentNode->XLocation) + 1][currentNode->YLocation];
                }
            }
            //The selection of left is correct
            else if(direct == 'l' || direct == 'L'){
                if((currentNode->left)->threattype == OCEAN){
                    printf("Cannot Pass Ocean Tiles\n");
                }
                else if((currentNode->left)->threattype == FINISH){
		  SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
		  currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
		}
                else if((currentNode->left)->threattype == NONE){
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                    currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
                }
                else if((currentNode->left)->threattype == GRIZZLY){
                    printf("You have encountered a Grizzly bear, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food - 10;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
			printf("You have lost 10 Food due to this encounter.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[currentNode->XLocation][(currentNode->YLocation) - 1] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->left)->threattype == BOAR){
                    printf("You have encountered an Boar, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food - 5;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
			printf("You have lost 5 Food due to this encounter.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[currentNode->XLocation][(currentNode->YLocation) - 1] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->left)->threattype == ELK){
                    printf("You have encountered an Elk, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
			printf("Your food supply remains unchanged\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[currentNode->XLocation][(currentNode->YLocation) - 1] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->left)->threattype == HARE){
                    printf("You have encountered a HARE, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food + 5;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
			printf("You have gained 5 Food due to this encounter\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[currentNode->XLocation][(currentNode->YLocation) - 1] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->left)->threattype == RIVER){
                    printf("You are attempting to ford a river; you may either choose to ford (f) or retreat(r): " );
                    scanf (" %c", &choice2);
                    if(choice2 == 'f' || choice2 == 'F'){
                        Food = Food - 20;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
			printf("You have lost 20 Food while crossing the river.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        printf("You choose to retreat\n");
                    }
                }
                else if((currentNode->left)->threattype == COLD){
                    printf("You have contracted the common cold, your food storage drops by 5 as you take a day off to recuperate\n" );
                    Food = Food - 5;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                    map[currentNode->XLocation][(currentNode->YLocation) - 1] -> Discovered = true;
                    currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
                }
                else if((currentNode->left)->threattype == FLU){
                    printf("You have contracted the Flu, your food storage drops by 10 as you take a day off to recuperate\n" );
                    Food = Food - 10;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                    map[currentNode->XLocation][(currentNode->YLocation) - 1] -> Discovered = true;
                    currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
                }
                else if((currentNode->left)->threattype == DYSENTERY){
                    printf("You have contracted Dysentery, your food storage drops by 15 as you take a day off to recuperate\n" );
                    Food = Food - 15;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->left)->XLocation][(currentNode->left)->YLocation]);
                    map[currentNode->XLocation][(currentNode->YLocation) - 1] -> Discovered = true;
                    currentNode = map[currentNode->XLocation][(currentNode->YLocation) - 1];
                }

            }
            //The selection of right is correct
            else if(direct == 'r' || direct == 'R'){
                if((currentNode->right)->threattype == OCEAN){
                    printf("Cannot Pass Ocean Tiles\n");
                }
                else if((currentNode->right)->threattype == FINISH){
		  SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
		  currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
		}
                else if((currentNode->right)->threattype == NONE){
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                    currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
                }
                else if((currentNode->right)->threattype == GRIZZLY){
                    printf("You have encountered a Grizzly bear, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food - 10;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
			printf("You have lost 10 Food due to this encounter.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[currentNode->XLocation][(currentNode->YLocation) + 1] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->right)->threattype == BOAR){
                    printf("You have encountered an Boar, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food - 5;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
			printf("You have lost 5 Food due to this encounter.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[currentNode->XLocation][(currentNode->YLocation) + 1] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->right)->threattype == ELK){
                    printf("You have encountered an Elk, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
			printf("Your food supply remains unchanged\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[currentNode->XLocation][(currentNode->YLocation) + 1] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->right)->threattype == HARE){
                    printf("You have encountered a HARE, would you choose to hunt (h) or retreat (r): ");
                    scanf (" %c", &choice2);
                    if(choice2 == 'h' || choice2 == 'H'){
                        Food = Food + 5;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
			printf("You have gained 5 Food due to this encounter\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        map[currentNode->XLocation][(currentNode->YLocation) + 1] -> Discovered = true;
                        printf("You choose to retreat.\n");
                    }
                }
                else if((currentNode->right)->threattype == RIVER){
                    printf("You are attempting to ford a river; you may either choose to ford (f) or retreat(r): " );
                    scanf (" %c", &choice2);
                    if(choice2 == 'f' || choice2 == 'F'){
                        Food = Food - 20;
                        SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                        currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
			printf("You have lost 20 Food while crossing the river.\n");
                    }
                    else if(choice2 == 'r' || choice2 == 'R'){
                        printf("You choose to retreat\n");
                    }
                }
                else if((currentNode->right)->threattype == COLD){
                    printf("You have contracted the common cold, your food storage drops by 5 as you take a day off to recuperate\n" );
                    Food = Food - 5;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                    map[currentNode->XLocation][(currentNode->YLocation) + 1] -> Discovered = true;
                    currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
                }
                else if((currentNode->right)->threattype == FLU){
                    printf("You have contracted the Flu, your food storage drops by 10 as you take a day off to recuperate\n" );
                    Food = Food - 10;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                    map[currentNode->XLocation][(currentNode->YLocation) + 1] -> Discovered = true;
                    currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
                }
                else if((currentNode->right)->threattype == DYSENTERY){
                    printf("You have contracted Dysentery, your food storage drops by 15 as you take a day off to recuperate\n" );
                    Food = Food - 15;
                    SwapNode(map[currentNode->XLocation][currentNode->YLocation], map[(currentNode->right)->XLocation][(currentNode->right)->YLocation]);
                    map[currentNode->XLocation][(currentNode->YLocation) + 1] -> Discovered = true;
                    currentNode = map[currentNode->XLocation][(currentNode->YLocation) + 1];
                }

            }
            //Exit the game
            else if(direct == 'e' || direct == 'E'){
	      clearMap(FullSize, map);
	      exit(0);
            }
            //Loss condition
            if(Food <= 0){
                printf("\nYou have died, Game Over. Press E to try again. Press Q to quit. ");
                scanf(" %c", &choice);
                if(choice == 'Q' || choice == 'q'){
                  clearMap(FullSize, map);
                  fclose(ptr_file);
		  exit(0);
		}
                else if(choice == 'E' || choice == 'e'){
                  main(2, argv);
		}
            }
            //Win condition
            if(currentNode->XLocation == 1 && currentNode->YLocation == 1){
                printf("\nCongratulations! You have survived the Oregon Trail! Food remaining: ");             
                printf("%d", Food);
                printf(" Press E to play again. Press Q to quit.\n");
                scanf(" %c", &choice);
                if(choice == 'q' || choice == 'Q'){
                  clearMap(FullSize, map);
                  fclose(ptr_file);
                  exit(0);
                }
                else if(choice == 'e' || choice == 'E'){
                  main(2, argv);
                }
            }
        }
    }
    else if(choice == 'q' || choice == 'Q'){
      clearMap(FullSize, map);
      fclose(ptr_file);
      return 0;
    }
    else if(choice == 'd' || choice == 'D'){
        printf("\nThis is the game Oregon Trail. Your goal is to get from the bottom right of the map to the top left\n");
        printf("In order to do this you pick a direction: up, down, left or right and choose different outcomes.\n");
        printf("\n");
        main(2, argv);
    }

    return 0;
}
