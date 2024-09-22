#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>
#include <vector>
#include <cassert>
#include <iostream>
#include <vector>
#include <string_view>
#include <bits/stdc++.h>
#include "random.h"
#include <algorithm>
#include <algorithm>        // for std::copy()
#include <cassert>          // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>
#include <exception>
#include <functional>
#include <iostream>
#include <numeric> // for std::gcd
#include <limits>
constexpr int g_consoleLines{ 25 };
class Direction{
  
  public:
  enum Type{
    up,
    down,
    left,
    right,
    maxDirections,
  };
  private:
  Type m_direction{};
  public:
  Direction(Type direction): m_direction{direction}{

  }
  Direction operator-(){
    switch (m_direction)
        {
        case up:    return Direction{ down };
        case down:  return Direction{ up };
        case left:  return Direction{ right };
        case right: return Direction{ left };
        default:    break;
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
  }
  friend std::ostream& operator<<(std::ostream&, Direction);
  static Direction getRandomDirection(){
     Direction random{ static_cast<Type>(Random::get(0, Type::maxDirections - 1)) };
     return random;
  }
  Type getDirection(){
    return m_direction;
  }
};
std::ostream& operator<<(std::ostream& out, Direction d){
  using direction = Direction::Type;
  std::string_view directionString{"Invalid Direction!"};
  switch (d.m_direction)
        {
        case Direction::Type::up:    directionString="up"; break;
        case direction::down:  directionString="down"; break;
        case direction::left:  directionString="left"; break;
        case direction::right: directionString="right"; break;
        default:    break;
        }
  out<<directionString;
  return out;
}
struct Point{
  int x{0};
  int y{0};
  Point(int xCrd, int yCrd): x{xCrd}, y{yCrd}
  {

  }
  friend bool operator==(Point point1, Point point2){
    return point2.x==point1.x&&point2.y==point1.y;
  }
  friend bool operator!=(Point point1, Point point2){
    return !(point2==point1);
  }
  Point getAdjacentPoint(Direction d){
    using direction = Direction::Type;
  switch (d.getDirection())
        {
        case direction::up:    return Point{x,y-1};
        case direction::down:  return Point{x,y+1};
        case direction::left:  return Point{x-1,y};
        case direction::right: return Point{x+1,y};
        default:    return Point{x,y};
        }
  }
};
class Tile{
  int m_num{};
  public:
  Tile(int num){
    assert(num>=0&&num<=15);
    m_num=num;
  }
  bool isEmpty(){
    return m_num==0;
  }
  int getNum(){
    return m_num;
  }
  friend std::ostream& operator<<(std::ostream&, Tile);
};
std::ostream& operator<<(std::ostream& stream, Tile tile)
{
    if (tile.getNum() > 9) 
        stream << " " << tile.getNum() << " ";
    else if (tile.getNum() > 0) 
        stream << "  " << tile.getNum() << " ";
    else if (tile.getNum() == 0) 
        stream << "    ";
    return stream;
}
class Board{
  static constexpr int size{4};
  std::vector<std::vector<Tile>> board{
   {{1},{2},{3},{4}}
  ,{{5},{6},{7},{8}}
  ,{{9},{10},{11},{12}}
  ,{{13},{14},{15},{0}}
  };
  public:
  Board()=default;
  friend std::ostream& operator<<(std::ostream& stream, const Board& board)
    {
        
        for (int i = 0; i < g_consoleLines; ++i)
            std::cout << '\n';

        for (int y = 0; y < size; ++y)
        {
            for (int x = 0; x < size; ++x)
                stream << board.board.at(y).at(x);
                
            stream << '\n';
        }

        return stream;
    }
    bool isValid(Point& point){
      return point.x<0||point.x>=size||point.y<0||point.y>=size;
    }
    Point findEmptyTile(){
      for (int y = 0; y < size; ++y)
        {
            for (int x = 0; x < size; ++x)
                if(board.at(y).at(x).isEmpty()){
                  return Point{x,y};
                }
        }
        return Point{0,0};
    }
    void swapTwoPoints(Point point1, Point point2){
      
      std::swap(board.at(point1.y).at(point1.x),board.at(point2.y).at(point2.x));
     
    }
    static bool isValidTilePos(Point& p){
      return p.x>=0&&p.y>=0&&p.x<size&&p.y<size;
    }
    bool moveTile(Direction dir){
      
       Point emptyTile{findEmptyTile()};
       Point adjacent{emptyTile.getAdjacentPoint(-dir)};
       
  if(isValidTilePos(adjacent)){
    swapTwoPoints(emptyTile,adjacent);
    return true;
  }
        return false;
  }
  void randomize(){
    for(int i {0};i<1000;i++){
      do{
        
        if(moveTile(Direction::getRandomDirection())) break;
      }while(true);
    }
    
  }
    friend bool operator==(Board& f1, Board& f2)
    {
        for (int y = 0; y < size; ++y)
            for (int x = 0; x < size; ++x)
                if (f1.board.at(y).at(x).getNum() != f2.board.at(y).at(x).getNum())
                    return false;

        return true;
    }
    bool isSolved(){
      Board temp{};
      return *this==temp;
    }
};
namespace UserInput{
  char getCommand(std::string_view prompt="")
{
    char attempt{};
    bool isFirstAttempt{true};
    do
    {
        if (!isFirstAttempt)
        {
            std::cin.clear();
            std::cout << "That wasn't a valid input.  Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            isFirstAttempt = false;
        }
        std::cout << prompt;
        std::cin >> attempt;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (!std::cin || (attempt != 'w' && attempt != 's'&& attempt != 'q'&& attempt != 'a'&& attempt != 'd') );
    
    return attempt;
}
  Direction charToDirection(char character){
    if(character=='w'){
      return Direction{Direction::Type::up};
    }
    if(character=='s'){
      return Direction{Direction::Type::down};
    }
    if(character=='a'){
      return Direction{Direction::Type::left};
    }
    if(character=='d'){
      return Direction{Direction::Type::right};
    }
    return Direction{Direction::Type::up};
  }
}
int main()
{
    
     Board board{};
     board.randomize();
    std::cout << board;

    std::cout << "Enter a command: ";
    bool won{false};
    while (!won)
    {
        char ch{ UserInput::getCommand() };

        // Handle non-direction commands
        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        // Handle direction commands
        Direction dir{ UserInput::charToDirection(ch) };

        bool userMoved { board.moveTile(dir) };
        if (userMoved){
            std::cout << board;
        }
        won=board.isSolved();
    }

  std::cout << "\n\nYou won!\n\n";
  return 0;
}