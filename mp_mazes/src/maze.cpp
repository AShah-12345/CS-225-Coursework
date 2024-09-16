/* Your code here! */
#include "maze.h"
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <random>
#include <utility>
using namespace std;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
SquareMaze::SquareMaze() //done
{
  width_ = 0;
  height_ = 0;
  right_Walls.clear();
  down_Walls.clear();
  sets = DisjointSets();
  sets.addelements(width_*height_);
  maze.resize(width_*height_);
}

SquareMaze::~SquareMaze() //done
{
  width_ = 0;
  height_ = 0;
  right_Walls.clear();
  down_Walls.clear();
  maze.resize(width_*height_);
}

void SquareMaze::makeMaze(int width, int height) //done 
{
    width_ = width;
    height_ = height;
    sets.addelements(width_ * height_);
    right_Walls.resize(width_ * height_, true);
    down_Walls.resize(width_ * height_, true);
    maze.resize(width_ * height_);

    while (sets.size(0) < width_ * height_) 
    {
        int cell = rand() % (width_ * height_);
        bool isRightWall = rand() % 2 == 0;
        int nextCell = isRightWall ? cell + 1 : cell + width_;
        
        if ((isRightWall && cell % width_ != width_ - 1 && sets.find(cell) != sets.find(nextCell)) ||
            (!isRightWall && cell / width_ != height_ - 1 && sets.find(cell) != sets.find(nextCell))) 
        {
            if (isRightWall) 
            {
                right_Walls[cell] = false;
                sets.setunion(cell, nextCell);
            } 
            else 
            {
                down_Walls[cell] = false;
                sets.setunion(cell, nextCell);
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const //done
{
    int index = y * width_ + x;  
    if (dir == 0)
    {
        if (x == width_ - 1 || right_Walls[index])
        {
            return false;
        }
    }
    else if (dir == 1)
    {
        if (y == height_ - 1 || down_Walls[index])
        {
            return false;
        }
    }
    else if (dir == 2)
    {
        if (x == 0 || right_Walls[index - 1])
        {
            return false;
        }
    }
    else if (dir == 3)
    {
        if (y == 0 || down_Walls[index - width_])
        {
            return false;
        }
    }
    return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) //done
{
    int index = y * width_ + x;
    if (dir == 0)
    {
        right_Walls[index] = (exists) ? true : false;
    }
    else if (dir == 1)
    {
        down_Walls[index] = (exists) ? true : false;
    }
}

vector<int> SquareMaze::solveMaze()
{
    vector<int> dist(width_ * height_, -1); 
    vector<int> prev(width_ * height_, -1);
    queue<int> q;
    int start = 0; 
    q.push(start); 
    dist[start] = 0; 
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        int x = curr % width_;
        int y = curr / width_;
        for (int dir = 0; dir < 4; dir++)
        {
            int nextX = x + dx[dir];
            int nextY = y + dy[dir];
            int next = nextY * width_ + nextX;
            if (canTravel(x, y, dir) && dist[next] == -1)
            {
                q.push(next);
                dist[next] = dist[curr] + 1;
                prev[next] = curr; 
            }
        }
    }
    int dest = -1;
    int maxDist = -1;
    for (int x = 0; x < width_; x++)
    {
        int curr = (height_ - 1) * width_ + x;
        if (dist[curr] > maxDist)
        {
            maxDist = dist[curr];
            dest = curr;
        }
    }
    int destX = dest % width_;
    int destY = dest / width_;
    setFinalDestination(destX, destY);
    vector<int> path;
    while (dest != start)
    {
        int curr = prev[dest];
        int dx = dest % width_ - curr % width_;
        int dy = dest / width_ - curr / width_;
        if (dx == 1) 
        {
            path.push_back(0);
        }
        else if (dx == -1) 
        {
            path.push_back(2);
        }
        else if (dy == 1) 
        {
            path.push_back(1);
        }
        else if (dy == -1) 
        {
            path.push_back(3);
        }
        dest = curr;
    }
    reverse(path.begin(), path.end());
    return path;
}

void SquareMaze::setFinalDestination(int x, int y) {
  finalMaze = make_pair(x, y);
}

PNG* SquareMaze::drawMaze() const
{
    int imageWidth = width_ * 10 + 1;
    int imageHeight = height_ * 10 + 1;
    PNG* image = new PNG(imageWidth, imageHeight);
    for (int i = 0; i < imageWidth; i++)
    {
        if (i < 1 || i > 9)
        {
            HSLAPixel& pixel = image->getPixel(i, 0);
            pixel.l = 0;
        }
    }
    for (int j = 0; j < imageHeight; j++)
    {
        HSLAPixel& pixel = image->getPixel(0, j);
        pixel.l = 0;
    }
    for (int x = 0; x < width_; x++)
    {
        for (int y = 0; y < height_; y++)
        {
            int index = y * width_ + x;
            if (right_Walls[index])
            {
                for (int z = 0; z <= 10; z++)
                {
                    HSLAPixel& pixel = image->getPixel((x + 1) * 10, y * 10 + z);
                    pixel.l = 0;
                }
            }
            if (down_Walls[index])
            {
                for (int z = 0; z <= 10; z++)
                {
                    HSLAPixel& pixel = image->getPixel(x * 10 + z, (y + 1) * 10);
                    pixel.l = 0;
                }
            }
        }
    }
    return image;
}

PNG* SquareMaze::drawMazeWithSolution()
{
  PNG* image = drawMaze();
  vector<int> solution = solveMaze();
  int xCoord = 5;
  int yCoord = 5;
  for(size_t i = 0; i < solution.size(); i++)
  {
    int dir = solution[i];
    for(int j = 0; j <= 10; j++)
    {
      HSLAPixel& temp = image->getPixel(xCoord + dx[dir] * j, yCoord + dy[dir] * j);
      temp.h = 0;
      temp.s = 1;
      temp.l = 0.5;
      temp.a = 1;
    }
    xCoord += dx[dir] * 10;
    yCoord += dy[dir] * 10;
  }
  int exitX = finalMaze.first * 10;
  int exitY = (finalMaze.second + 1) * 10;
  for(int z = 1; z <= 9; z++)
  {
    HSLAPixel& temp = image->getPixel(exitX + z, exitY);
    temp.l = 1;
  }
  return image;
}