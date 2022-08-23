#include "History.h"
#include "Mesa.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
    : m_rows(nRows), m_cols(nCols)
{
      for(int i = 0; i < nRows; i ++)
      {
            for(int j = 0; j < nCols; j ++)
            {
                  grid[i][j] = '.';
            }
      }
}

bool History::record(int r, int c)
{
      if(grid[r-1][c-1] == ' ')
      {
            return false;
      }
      else if(grid[r-1][c-1] == '.')
      {
            grid[r-1][c-1] = 'A';
            return true;
      }
      else if(grid[r-1][c-1] == 'Z')
      {
            return true;
      }
      else
      {
            grid[r-1][c-1] += 1;
            return true;
      }
}

void History::display() const
{
      clearScreen();
      for(int i = 0; i < m_rows; i ++)
      {
            for(int j = 0; j < m_cols; j ++)
            {
                  cout << grid[i][j];
            }
            cout << endl;
      }
      cout << endl;
}