#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
void draw_board();
char take_input();
void process_input(char ch);
void go_left();
void go_up();
void go_down();
void go_right();
void clear_board();
void swap(int x1,int y1,int x2,int y2);
int check_win();
int* get_board(int level); //Function that takes in the user's choice of level and returns the chosen board 

int (*board)[4]; //A pointer to point to the 2D array with each row containing 4 elements

//Below are the three different level boards
int easy_board[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,0,13,14,15} ;
int medium_board[4][4] = {1,2,3,4,5,6,7,8,11,0,15,12,14,10,9,13} ;
int hard_board[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,15,14,0};

//The position of 0 is initialized as per the user selected level in a function called 'get_board' 
int zero_pos_first_index;
int zero_pos_seond_index;
//Initial move count
int move_count=0;

int main()
{

    //Intitially draw the board
      int select_level;
      printf(" 1 : Easy  2 : Medium  3 : Hard \nSelect the level : ");
      scanf("%d",&select_level);
      fflush(stdin);
      //Assigning the board as per the selected level
      board = get_board(select_level);
      draw_board();
    //Loop till check_win is not equal to 1
        while(check_win() != 1)
        {
            //Take input and store in ch
             char ch;
             ch = take_input();
             process_input(ch);//Process input (ch)
             clear_board(); //Clear the board
             printf("\n\n");//Draw the board again
             draw_board();
             if(ch != 'w' && ch != 'a' && ch != 's' && ch != 'd')printf("\n\tInvalid Move !\n");
             move_count++;//Increase move count
        }
    //End Loop
    free(board);
    //Print You have won with ___ Moves
    printf("Won with %d moves !\n",move_count);
}

int* get_board(int option)//Function takes in user's choice and accordingly returns the selected board
{
    if(option == 1)
    {
       //easy_board[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,0,13,14,15} ;
       zero_pos_first_index = 3;
       zero_pos_seond_index = 0;
       return easy_board;
    }
    else if(option == 2)
    {
        //medium_board[4][4] = {1,2,3,4,5,6,7,8,11,0,15,12,14,10,9,13} ;
        zero_pos_first_index = 2;
        zero_pos_seond_index = 1;
        return medium_board;
    }
    else if(option == 3)
    {
        //hard_board[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,15,14,0};
        zero_pos_first_index = 3;
        zero_pos_seond_index = 3;
        return hard_board;
    }
}
void draw_board()
{
   int row_index , col_index;
   row_index = -1;
   while(++row_index < 4)
   {
       col_index = -1;
       while(++col_index < 4)
       {
           printf("\t%d\t",board[row_index][col_index]);
       }
       printf("\n");
   }

}
void clear_board(){
    //Clear the board
    system("cls");
}
char take_input()
{
/*
Take input and return it ,Use Fflush if scanf is being used

*/
   char user_input;
   scanf("%c",&user_input);
   fflush(stdin);
   return user_input;
}

void process_input(char ch)
{

/*
Handle the input char ch ,which is either w,a,s,d ,for up,left,down and right
Use a switch case and call go_left(),go_right()etc respectively
*/
    switch(ch)
    {
        case 'w': go_up();
                  break;
        case 'a': go_left();
                  break;
        case 's': go_down();
                  break;
        case 'd': go_right();
                  break;
        default : move_count--;
    }
}

void go_left()
{
//move 0 tile left
  if(zero_pos_seond_index-1 >= 0)
  {
      swap(zero_pos_first_index,zero_pos_seond_index,zero_pos_first_index,zero_pos_seond_index-1);
      zero_pos_seond_index = zero_pos_seond_index-1;
  }
}
void go_right()
{
//move 0 tile right
  if(zero_pos_seond_index+1 < 4)
  {
      swap(zero_pos_first_index,zero_pos_seond_index,zero_pos_first_index,zero_pos_seond_index+1);
      zero_pos_seond_index = zero_pos_seond_index+1;
  }
}
void go_up()
{
//Move 0 tile up
  if(zero_pos_first_index-1 >= 0)
  {
      swap(zero_pos_first_index,zero_pos_seond_index,zero_pos_first_index-1,zero_pos_seond_index);
      zero_pos_first_index = zero_pos_first_index-1;
  }
}
void go_down()
{
//Move 0 tile down
  if(zero_pos_first_index+1 < 4)
  {
      swap(zero_pos_first_index,zero_pos_seond_index,zero_pos_first_index+1,zero_pos_seond_index);
      zero_pos_first_index = zero_pos_first_index+1;
  }
}

void swap(int x1,int y1,int x2,int y2)
{
//Swap board[x1][y1] and board[x2][y2];
    int temp;
    temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;
}

int check_win(){
//Return 1 , if current board has all tiles perfectly places ,or 0 otherwise
    int count = 0 , check = 0;
    int row , col;
    row = -1;
    while(++row < 4)
    {
        col = -1;
        while(++col < 4)
        {
            if(board[row][col] == ++check && check <= 15)count++;
        }
    }
    if(count == 15)return 1;
    else return 0;
}
