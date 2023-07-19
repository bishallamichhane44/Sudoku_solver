#include<raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../../src/raygui.h"
using namespace std;

#define N 9




bool isSafe(int grid[N][N], int row,int col, int num)
{
	
    //Check in Row
	for (int x = 0; x <= 8; x++)
		if (grid[row][x] == num)
			return false;

    //Check in Coloumn
	for (int x = 0; x <= 8; x++)
		if (grid[x][col] == num)
			return false;

    //Check in grid
	int startRow = row - row % 3,
			startCol = col - col % 3;
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (grid[i + startRow][j +
							startCol] == num)
				return false;

	return true;
}


bool solveSudoku(int grid[N][N], int row, int col)
{
	// Check if we have reached the 8th
	// row and 9th column (0
	// indexed matrix) , we are
	// returning true to avoid
	// further backtracking
	if (row == N - 1 && col == N)
		return true;

	// Check if column value becomes 9 ,
	// we move to next row and
	// column start from 0
	if (col == N) {
		row++;
		col = 0;
	}
	
    //ignore the box with non zero value
	if (grid[row][col] > 0)
		return solveSudoku(grid, row, col + 1);

	for (int num = 1; num <= N; num++)
	{
		
        //Check if the number fits in a specific box.
		if (isSafe(grid, row, col, num))
		{
			
            
			grid[row][col] = num;
			
			// Checking for next possibility with next
			// column
			if (solveSudoku(grid, row, col + 1))
				return true;
		}
		
        //back
		grid[row][col] = 0;
	}
	return false;
}














int main(){


    //For Screen
    int screenWidth=900;
    int screenHeight=900;

    //For slider
    int value;
    int valuey;
    
    //To store suduko data
    int arr[9][9]={};
    
    //mouse coordinates
    int mx;
    int my;

    //mouse left pressed
    int mlp=0;

    //color
    int col=150;

    //To check if the number is entered or not
    int gotnum=0;
    int nume=44;   //default number for test
    
    //coordinates of the choosen box
    int stpx=0;
    int stpy=0;
    
    //Entered number
    int numk;
    
    //Coordinate of the text display box
    int codrx=0;
    int codry=0;
    
    int valueBox002Value = 0;
    bool valueBoxEditMode = false;
    
    //Check the status of botton
    int generated=0;
    int generateAnswer=0;
    int enterQuestion=0;
    int done=0;
    int clear=0;

    //For slider(Editing purpose)
    //float GuiVerticalSlider(Rectangle bounds, const char *textTop, const char *textBottom, int value, float minValue, float maxValue);  <<

    //Initialize working window
    InitWindow(screenWidth,screenHeight, "Suduko Solver");

    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        int SW= GetScreenWidth();
        int SH= GetScreenHeight();
        
        Color clr[]={GRAY,DARKGRAY,};
        

        //Starting of suduko table
        int recx=270;
        int recy=200;
        int rech=40;
        int recw=40;
        
        //coordinates of selected box
        int codx;
        int cody;
        
        //Display of mouse coordinates.
        int dxy;
        
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            mx=GetMouseX();
            my=GetMouseY();
            
            
            
            
            
            
            
            for(int i=0;i<9;i++){
                for(int j=0; j<9;j++){
                    Rectangle rec= { (recx+(j*recw)),(recy+(i*rech)),rech,recw};
                    DrawRectangleLinesEx(rec, 2.0, GRAY);
                    DrawText(TextFormat("%0.1d", arr[j][i]), (recx+(j*recw))+10, (recy+(i*rech))+10,20,BLACK);
                    
                    // for designing purpose
                    //value = GuiSlider((Rectangle){ 96, 800, 216, 16 }, TextFormat("%0.2d", value), NULL, value, 0, 800);     <<
                    //valuey = GuiSlider((Rectangle){ 96, 880, 216, 16 }, TextFormat("%0.2d", valuey), NULL, valuey, 0, 800);  <<
                    GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
                    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
                    DrawText("SUDUKO SOLVER", 232, 56,50,BLUE);
                    //DrawText("QUESTION", 260, 600,20,GRAY);
                    //DrawText("ANSWER", 260, 650,20,GRAY);
                    
                        //Determine the coordinates of each box.
                        if ((mx-recx)<1){
                            codx=0;
                           }
                           else{
                           codx=((mx-recx)/recw)+1;
                                }
            
                        if ((my-recy)<1){
                            cody=0;
                            }else{
                            cody=((my-recy)/rech)+1;
                                  }
                       
                       //table outlines
                       //Lines for table
                       DrawLineEx({(recx+3*recw),(recy+0*rech)}, {(recx+3*recw),(recy+9*rech)}, 3.0, BLACK);
                       DrawLineEx({(recx+6*recw),(recy+0*rech)}, {(recx+6*recw),(recy+9*rech)}, 3.0, BLACK);
                       DrawLineEx({(recx+0*recw),(recy+3*rech)}, {(recx+9*recw),(recy+3*rech)}, 3.0, BLACK);
                       DrawLineEx({(recx+0*recw),(recy+6*rech)}, {(recx+9*recw),(recy+6*rech)}, 3.0, BLACK);
                       
                       
                       
                       //Check if a particular box is selected
                       if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT))&& dxy==1){
                            stpx=recx+(codx-1)*recw;
                            stpy=recy+(cody-1)*rech;
                            codrx=codx;
                            codry=cody;
                            
                            mlp=1;
                            //mlp=mlp+1;
                            //mlp=mlp%2;
                        }
                
                       if (mlp==1 && dxy==1){
                           
                           DrawRectangleRec(Rectangle {stpx,stpy,recw,rech}, (Color){ 0, 158, 47, 150 });    
                            valueBoxEditMode=true;
                           DrawText(TextFormat("%0.1d", arr[codrx-1][codry-1]), stpx+10, stpy+10,20,BLACK);             
                       }else{
                           valueBoxEditMode=false;
                       }
                      
            
            
                        if(dxy==1 && enterQuestion==1){
                            DrawRectangleRec(Rectangle {recx+(codx-1)*recw,recy+(cody-1)*rech,recw,rech}, (Color){ 102, 191, 255, 50 });
                        }
                        
                        if(codx<10 && codx>0 && cody>0 && cody<10){
                            dxy=1;
                            DrawText(TextFormat("%0.2d", codx), 15, 15,20,GRAY);
                            DrawText(TextFormat("%0.2d", cody), 15, 30,20,GRAY);
                        }else{
                            dxy=0;
                        }
                                
                    
                    
                    
                    
                    
                    
                    if (GuiValueBox((Rectangle){ 388, 120, 125, 30 }, NULL, &arr[codrx-1][codry-1], 0, 9, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;
                    
                    
                    //Enter question button.
                    if(enterQuestion==1){
                        GuiSetState(STATE_PRESSED);
                    }
                    else{
                        GuiSetState(STATE_NORMAL);
                    }
                    if (GuiButton((Rectangle){ 230, 585, 130, 30 }, "Enter Question")) { 
                    enterQuestion=1;
                    generateAnswer=0;
                    generated=0;
                    }
                    if(enterQuestion==1){
                    DrawText("Now, Enter your suduko question in the table.", 220, 168,20,GRAY);
                    }else{
                        dxy=0;
                    }
                    GuiSetState(STATE_NORMAL);
                    
                    if(GuiButton((Rectangle){ 380, 585, 130, 30 }, "Done")){
                        done=1;
                        enterQuestion=0;
                    }
                    if(GuiButton((Rectangle){ 520, 585, 130, 30 }, "Clear")){
                        clear=1;
                        generateAnswer=0;
                        arr[i][j]=0;
                        enterQuestion=0;
                    }
                    GuiSetState(STATE_NORMAL);


                    //Generate Answer
                    if(GuiButton((Rectangle){ 380, 635, 130, 50 }, "Generate Answer")){
                        generateAnswer=1;
                        done=1;
                        enterQuestion=0;
                    }
                    if(generateAnswer==1 && generated!=1){
                        DrawText("Generating Answer...", 348, 168,20,GRAY);
                        
                        
                        //main logic looop
                        
                       if (solveSudoku(arr, 0, 0)){
                           generated=1;
                       }else{
                           generated=0;
                           generateAnswer=0;
                           DrawText("Answer not possile", 360, 168,20,GRAY);
                       }
                        
                        
                        
                        
                        
                    }else if(generateAnswer==1 && generated==1){
                        DrawText("Answer Generated", 360, 168,20,GRAY);
                    }
                    
                    //if (GuiValueBox((Rectangle){ 270, 700, 40, 40 }, NULL, &arr[i][j], 0, 9, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;
                    
                    //DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color); 
            }}
            
        EndDrawing();
    }

CloseWindow();
return 0;
}









/*
int exist(int arr[10][10],int r,int c,int v){
	int k=0;
    int m=((c/3)*3);
    int n=((c/3)*3+3);
    int o=((r/3)*3);
    int p=((r/3)*3+3);
    
    //check in row
    for (int i=1;i<10;i++){
        if (arr[c][i]==v){
            k=1;
            break;
          
        }
    }
    
    //check in cloumn
    for (int i=1;i<10;i++){
        if (arr[i][r]==v){
            k=1;
            break;
            
        }
    }
    //check in grid
    for (int i=m;i<n;i++){
    	for(int j=o; j<p; j++){
        	 if (arr[i][j]==v){
            k=1;
            break;
           
        }
        }       
    }
    
    return k;
    
}*/
