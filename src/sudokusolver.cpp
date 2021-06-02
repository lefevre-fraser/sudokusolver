/***********************************************************************
 *    Copyright 2021 Fraser LeFevre
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 **********************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/************************************************************************
 * Prompts for the filename and test to see if it opens, reprompt if needed.
 ***********************************************************************/
void getFileName(char fileName[])
{
   ifstream fin;
   do
   {
      cout << "Where is your board located? ";
      cin.getline(fileName, 256);
      fin.open(fileName);
   } while (fin.fail());
   fin.close();
}

/************************************************************************
 * Reads the sudoku file into an array.
 ***********************************************************************/
void readFile(char fileName[], char board[][9])
{
   ifstream fin;
   fin.open(fileName);
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         fin >> board[i][j];
      }
   }
   fin.close();
}

/************************************************************************
 * Displays the sudoku in the array on the screen.
 ***********************************************************************/
void displayBoard(char board[][9])
{
   cout << "   A B C D E F G H I" << endl;
   for (int i = 0; i < 9; i++)
   {
      if (i == 3 || i == 6)
         cout << "   -----+-----+-----" << endl;
      cout << i + 1 << " ";
      for (int j = 0; j < 9; j++)
      {
         if (j == 3 || j == 6)
         {
            cout << "|" << ((board[i][j] == '0') ? ' ' : board[i][j]);
         }
         else
            cout << setw(2) << ((board[i][j] == '0') ? ' ' : board[i][j]);
      }
      cout << endl;
   }
}

/************************************************************************
 * Converts column letter "a,b,c,d.." into a number.
 ***********************************************************************/
int determineColumnEquivelent(char change[])
{
   int column;
   if (!isupper(change[0]))
      change[0] = toupper(change[0]);
   column = change[0] - 64;

   return column;
}

/************************************************************************
 * Determines the values available to be entered into a certain square.
 ***********************************************************************/
void findValues(char board[][9], char values[], char change[])
{
   int c = determineColumnEquivelent(change) - 1;
   int r = change[1] - 49;

   for (int i = 0; i < 9; i++)
      values[i] = i + 49;
   for (int i = 0; i < 9; i++)
      if ((board[i][c] - 48) >= 1 && (board[i][c] - 48) <= 9)
         values[board[i][c] - 49] = ' ';
   for (int i = 0; i < 9; i++)
      if ((board[r][i] - 48) >= 1 && (board[r][i] - 48) <= 9)
         values[board[r][i] - 49] = ' ';
   int squareSearchColumn;
   if (c > 5)
      squareSearchColumn = 6;
   else if (c > 2)
      squareSearchColumn = 3;
   else
      squareSearchColumn = 0;
   int squareSearchRow;
   if (r > 5)
      squareSearchRow = 6;
   else if (r > 2)
      squareSearchRow = 3;
   else
      squareSearchRow = 0;
   for (int i = squareSearchRow; i < (squareSearchRow + 3); i++)
      for (int j = squareSearchColumn; j < (squareSearchColumn + 3); j++)
         for (int k = 0; k < 9; k++)
            if ((board[i][j] - 48) == k + 1)
               for (int l = 0; l < 9; l++)
                  if ((values[l] - 48) == k + 1)
                     values[l] = ' ';
}

/************************************************************************
 * Edits the sudoku board based on user input.
 ***********************************************************************/
void editBoard(char board[][9])
{
   char change[256];
   char valueCheck[256];
   bool displayValues = false;
   char values[9];
   int column = 78;
   change[1] = '0';

   cin.ignore();
   cout << "What are the coordinates of the square: ";
   cin.getline(change, 256);

   column = determineColumnEquivelent(change);

   if (!(column >= 1 && column <= 9) ||
       !(change[1] >= '1' && change[1] <= '9'))
      cout << "ERROR: Square '" << change << "' is invalid" << endl;
   else if (board[change[1] - 49][column - 1] != '0')
   {
      cout << "ERROR: Square '" << change << "' is filled" << endl;
   }
   else
   {
      cout << "What is the value at '" << change << "': ";
      cin >> valueCheck;
      findValues(board, values, change);
      int p = 0;
      for (int q = 0; q < 9; q++)
         if (valueCheck[0] == values[q])
         {
            p = 1;
            q = 9;
         }
      if (p == 1)
         board[change[1] - 49][column - 1] = valueCheck[0];
      else
         cout << "ERROR: Value '" << valueCheck << "' in square '"
              << change << "' is invalid" << endl;
   }

   cout << endl;
}

/************************************************************************
 * Tells the user the available values of a square.
 ***********************************************************************/
void showValues(char board[][9])
{
   char values[9];
   char change[256];
   int column;

   cout << "What are the coordinates of the square: ";
   cin.ignore();
   cin.getline(change, 256);

   column = determineColumnEquivelent(change);

   if (!(column >= 1 && column <= 9) ||
       !(change[1] >= '1' && change[1] <= '9'))
      cout << "ERROR: Square '" << change << "' is invalid" << endl;
   else
   {
      cout << "The possible values for '" << change << "' are: ";
                findValues(board, values, change);
                for (int l = 0; l < 9; l++)
                {
                        bool check = false;
                        while (values[l] != ' ' && l < 9)
                        {
                                check = true;
                                cout << values[l];
                                for (int m = l + 1; m < 9; m++)
                                        if (values[m] != ' ')
                                        {
                                                cout << ", ";
                                                m = 9;
                                        }
                                l++;
                        }
                        if (check)
                                l--;
                }

                cout << endl;
        }
}

/************************************************************************
* Solves the board sudoku board.
***********************************************************************/
bool solveRow(char board[][9])
{
   bool changed = false;
   char values[9][9];
   for (int r = 0; r < 9; r++)
   {
      for (int i = 0; i < 9; i++)
         for (int j = 0; j < 9; j++)
            values[i][j] = i + 49;

      for (int c = 0; c < 9; c++)
      {
         if (board[r][c] != '0')
            for (int i = 0; i < 9; i++)
               values[i][c] = ' ';
         else
         {
            char change[256];
            char tempValues[9];
            change[0] = c + 65;
            change[1] = r + 49;
            findValues(board, tempValues, change);
            for (int i = 0; i < 9; i++)
               values[i][c] = tempValues[i];
         }
      }

      for (int c = 0; c < 9; c++)
      {
         int numPossible = 0;
         for (int i = 0; i < 9; i++)
            if (values[c][i] != ' ')
               numPossible += 1;
         if (numPossible == 1)
            for (int i = 0; i < 9; i++)
               if (values[c][i] != ' ')
               {
                  board[r][i] = values[c][i];
                  changed = true;
               }
      }
   }
   if (changed)
      return true;
   else
      return false;
}

bool solveColumn(char board[][9])
{
   bool changed = false;
   char values[9][9];
   for (int c = 0; c < 9; c++)
   {
      for (int i = 0; i < 9; i++)
         for (int j = 0; j < 9; j++)
            values[i][j] = i + 49;

      for (int r = 0; r < 9; r++)
      {
         if (board[r][c] != '0')
            for (int i = 0; i < 9; i++)
               values[i][r] = ' ';
         else
         {
            char change[256];
            char tempValues[9];
            change[0] = c + 65;
            change[1] = r + 49;
            findValues(board, tempValues, change);
            for (int i = 0; i < 9; i++)
               values[i][r] = tempValues[i];
         }
      }

      for (int r = 0; r < 9; r++)
      {
         int numPossible = 0;
         for (int i = 0; i < 9; i++)
            if (values[r][i] != ' ')
               numPossible += 1;
         if (numPossible == 1)
            for (int i = 0; i < 9; i++)
               if (values[r][i] != ' ')
               {
                  board[i][c] = values[r][i];
                  changed = true;
               }
      }
   }
   if (changed)
      return true;
   else
      return false;
}

void solveBoard(char board[][9])
{
   int tempr;
   int tempc;
   char values[9];
   
   for (int r = 0; r < 9; r++)
   {
      for (int c = 0; c < 9; c++)
      {
         int totalValues = 0;
         if (board[r][c] == '0')
         {
            char change[256];
            change[0] = c + 65;
            change[1] = r + 49;
            findValues(board, values, change);
            for (int k = 0; k < 9; k++)
            {
               if (values[k] != ' ')
                  totalValues += 1;
               if (totalValues == 1)
               {
                  tempr = r;
                  tempc = c;
               }
            }
         }
         if (totalValues == 1)
         {
            for (int k = 0; k < 9; k++)
               if (values[k] != ' ')
                  board[tempr][tempc] = values[k];
         }
      }
   }

   bool changed = true;
   while (changed)
   {
      changed = solveRow(board);
      changed = solveColumn(board);
   }
}
/************************************************************************
* Checks the board to see if every square is filled or not.
***********************************************************************/
bool checkBoard(char board[][9])
{
        int numOfOpen = 0;

        for (int r = 0; r < 9; r++)
                for (int c = 0; c < 9; c++)
                        if (board[r][c] == '0')
                                numOfOpen += 1;

        if (numOfOpen == 0)
                return false;
        else
           return true;
}

bool hardCheck(char board[][9])
{
   char values[9];
   for (int r = 0; r < 9; r++)
   {
      for (int c = 0; c < 9; c++)
      {
         if (board[r][c] == '0')
         {
            int numValues = 9;
            char change[256];
            change[0] = c + 65;
            change[1] = r + 49;
            findValues(board, values, change);
            for (int k = 0; k < 9; k++)
               if (values[k] == ' ')
                  numValues -= 1;
            if (numValues == 1)
               return false;
            else if (numValues == 0)
               return true;
         }
      }
   }

   return true;
}

bool possibleCheck(char board[][9])
{
   char values[9];
   for (int r = 0; r < 9; r++)
   {
      for (int c = 0; c < 9; c++)
      {
         if (board[r][c] == '0')
         {
            int numValues = 9;
            char change[256];
            change[0] = c + 65;
            change[1] = r + 49;
            findValues(board, values, change);
            for (int k = 0; k < 9; k++)
               if (values[k] == ' ')
                  numValues -= 1;
            if (numValues == 0)
               return false;
         }
      }
   }

   for (int r = 0; r < 9; r++)
      for (int c = 0; c < 9; c++)
         if (board[r][c] != '0')
            for (int c2 = 0; c2 < 9; c2++)
               if (c != c2)
                  if (board[r][c] == board[r][c2])
                     return false;

   for (int c = 0; c < 9; c++)
      for (int r = 0; r < 9; r++)
         if (board[r][c] != '0')
            for (int r2 = 0; r2 < 9; r2++)
               if (r != r2)
                  if (board[r][c] == board[r2][c])
                     return false;

   int row = 0;
   int column = 0;
   while (row < 9)
   {
      column = 0;
      for (int r = row; r < row + 3; r++)
      {
         for (int c = column; c < column + 3; c++)
            if (board[r][c] != '0')
               for (int r2 = row; r2 < row + 3; r2++)
                  for (int c2 = column; c2 < column + 3; c2++)
                     if (r != r2 && c != c2)
                        if (board[r][c] == board[r2][c2])
                           return false;
         column += 3;
      }
      row += 3;
   }

   return true;
}

void createTempBoard(char board[][9], char tempBoard[][9])
{
   for (int r = 0; r < 9; r++)
      for (int c = 0; c < 9; c++)
         tempBoard[r][c] = board[r][c];
}

void guessAndCheck(char board[][9])
{
   bool solved;
   bool possible;
   bool hard;
   char values[9];
   char tempBoard[9][9];
   createTempBoard(board, tempBoard);

   if (possibleCheck(tempBoard) && checkBoard(tempBoard))
   {
      for (int r = 0; r < 9; r++)
      {
         for (int c = 0; c < 9; c++)
         {
            if (tempBoard[r][c] == '0')
            {
               char change[256];
               change[0] = c + 65;
               change[1] = r + 49;
               findValues(tempBoard, values, change);

               hard = hardCheck(tempBoard);
               possible = possibleCheck(tempBoard);
               solved = !checkBoard(tempBoard);
               while (!hard && possible && !solved)
               {
                  solveBoard(tempBoard);
                  hard = hardCheck(tempBoard);
                  possible = possibleCheck(tempBoard);
                  solved = !checkBoard(tempBoard);
//                  solveRow(tempBoard);
               }

               if (possible)
               {
                  int k;
                  for (k = 0; k < 9; k++)
                  {
                     if (values[k] != ' ')
                     {
#ifdef DEBUG
                        displayBoard(tempBoard);
#endif
                        tempBoard[r][c] = values[k];
                        solved = !checkBoard(tempBoard);
                        possible = possibleCheck(tempBoard);
                        if (possible && !solved)
                        {
                           guessAndCheck(tempBoard);
                           solved = !checkBoard(tempBoard);
                           possible = possibleCheck(tempBoard);
                        }
                        if (solved)
                        {
                           createTempBoard(tempBoard, board);
                           return;
                        }
                     }
                  }
                  if (k == 9)
                     return;
               }
            }
         }
      }
   }
}

/************************************************************************
 * Writes the new sudoku board into a file.
 ***********************************************************************/
void writeToFile(char board[][9])
{
   char fileName[256];
   cin.ignore();
   cout << "What file would you like to write your board to: ";
   cin >> fileName;

   ofstream fout;
   fout.open(fileName);

   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         fout << board[i][j] << ' ';
      }
      fout << "\n";
   }

   fout.close();
   cout << "Board written successfully\n";
}

/************************************************************************
 * Displays the possible options.
 ***********************************************************************/
void displayOptions()
{
   cout << "Options:" << endl
        << "   ?  Show these instructions" << endl
        << "   D  Display the board" << endl
        << "   E  Edit one square" << endl
        << "   S  Show the possible values for a square" << endl
        << "   Q  Save and Quit" << endl;
   //        << "   Solve  solve the sudoku board" << endl;
}

/************************************************************************
 * Prompts for a command from the user.
 ***********************************************************************/
void chooseOption(char board[][9])
{
   char values[9];
   char change[256];
   char option[256];
   bool solved;
   bool hard;

   displayOptions();
   cout << endl;
   displayBoard(board);
   cout << endl;
   option[0] = '\0';

   while (option[0] != 'Q')
   {
      option[0] = '\0';
      while (option[0] != '?' && option[0] != 'D' && option[0] != 'E' &&
             option[0] != 'S' && option[0] != 'Q')
      {
         if (option[0] != '\0')
         {
            cout << "ERROR: Invalid command" << endl;
         }
         cout << "> ";
         cin >> option;
         if (!isupper(option[0]))
            option[0] = toupper(option[0]);
      }
      if (option[0] == '?')
      {
         displayOptions();
         cout << endl;
      }
      else if (option[0] == 'D')
         displayBoard(board);
      else if (option[0] == 'E')
         editBoard(board);
      else if (option[0] == 'S' && option[1] == 'o')
      {
         solved = !checkBoard(board);
         hard = hardCheck(board);

         while (!solved && !hard)
         {
            solveBoard(board);
            solved = !checkBoard(board);
            hard = hardCheck(board);
         }

         guessAndCheck(board);
         solved = !checkBoard(board);
      }
      else if (option[0] == 'S')
         showValues(board);
      if ((option[0] != 'Q') && (option[0] != 'E'))
         cout << endl;
   }

   writeToFile(board);
}

/************************************************************************
 * Main Function - call functions to work on sudokus.
 ***********************************************************************/
int main()
{
   char fileName[256];
   char board[9][9];

   do
   {
      getFileName(fileName);
      readFile(fileName, board);
   } while (!possibleCheck(board));

   chooseOption(board);

   return 0;
}
