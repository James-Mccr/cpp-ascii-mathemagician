#include "lib/game.h"
#include "lib/grid.h"
#include "lib/input.h"

class Number
{
public:
    Number(int _x, int _y, int _value)
    {
        x = _x;
        y = _y;
        if (value < 0 || value > 9)
            value = 0;
        value = _value;
        ascii = value + '0';
    }

    int GetX() { return x; }
    int GetY() { return y; }
    char GetAscii() { return ascii; }
    void Update(int _x, int _y)
    {
        grid.SetTile(x, y);

        x = _x;
        y = _y;

        grid.SetTile(x, y, ascii);
    }
    

private:
    int value{};
    int x{5};
    int y{5};
    char ascii;
};

class Numbers
{
public:
    void Add(Number n)
    {
        numbers.push_back(n);
    }

    void Show()
    {
        for (auto& number : numbers)
            number.Update(number.GetX(), number.GetY());
    }

    void Update(int x, int y, UserInput direction)
    {
        for (auto& number : numbers)
        {
            if (x == number.GetX() && y == number.GetY())
            {
                if (direction == UserInput::Up)
                    number.Update(x, y-1);
                else if (direction == UserInput::Down)
                    number.Update(x, y+1);
                else if (direction == UserInput::Left)
                    number.Update(x-1, y);
                else if (direction == UserInput::Right)
                    number.Update(x+1, y);
                return;
            }
        }
    }

private:
    vector<Number> numbers{};
};

class Player
{
public:
    Player(Numbers _numbers)
    {
        numbers = _numbers;
    }

    void Update()
    {
        grid.SetTile(x, y);
            
        UserInput input = userInput;
        if (userInput == UserInput::Up)
            y -= 1;
        else if (userInput == UserInput::Down)
            y += 1;
        else if (userInput == UserInput::Right)
            x += 1;
        else if (userInput == UserInput::Left)
            x -= 1;

        if (grid.IsOutOfBounds(x, y))
        {
            if (x < 0)
                x = 0;
            else if (x >= grid.GetWidth())
                x = grid.GetWidth()-1;
            if (y < 0)
                y = 0;
            else if (y >= grid.GetHeight())
                y = grid.GetHeight()-1;
        }

        numbers.Update(x, y, input);

        grid.SetTile(x, y, ascii);
    }

    int x{};
    int y{};
    Numbers numbers;
    static constexpr char ascii = '@';
};

class Mathemagician : public Game
{
public:
    Mathemagician() : Game(30) 
    {
        numbers.Add(Number{5,5,3});
        numbers.Add(Number{15,15,7});
        numbers.Add(Number{2,9,5});
        player.numbers = numbers;
        numbers.Show();
    }

protected:
    void Update()
    {
        player.Update();
    }

    Numbers numbers{};
    Player player{numbers};
};

int main()
{
    Mathemagician mathemagician{};
    mathemagician.Start();
    return 0;
}