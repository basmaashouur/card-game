#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

// Game Objects

// sf
const sf::Color colorArray[6] = {Color::Cyan, Color::Blue, Color::Green, Color::Red,
                                 Color::Yellow, Color::Magenta
                                };

RenderWindow window(VideoMode(270, 450), "Cards Game");
RectangleShape shape(Vector2f(50, 50));
Event event;
Text timetext;
Font font;
Clock clockk;


// std
vector<pair<double, double > >allpos;
vector<int>check(12, 0);
vector<int>fin(12, 0);
double incx = 0.0, incy = 0.0;
int numclick = 0, curvis = 0, found = 0, countup = 0;

// Function to Genrate shapes
void gen(int ex, int wy)
{
    for (int x = 0; x < ex; x++)
    {
        for (int y = 0; y < wy; y++)
        {
            allpos.push_back(make_pair(40.f + incx, 40.f + incy));
            incx += 70.0;
        }
        incx = 0.0;
        incy += 70.0;
    }
}

// Function to draw shapes
void drawShape()
{
    for (int i = 0; i < 12; i++)
    {
        shape.setPosition(allpos[i].first, allpos[i].second);
        if (check[i] || fin[i])shape.setFillColor(colorArray[i % 6]);
        else shape.setFillColor(Color::White);
        window.draw(shape);

    }
}

// Function to show the number of clicks and the time
void drawTimeClicks()
{

    const unsigned int seconds = static_cast<unsigned int>(clockk.getElapsedTime().asSeconds());
    string sec = "Time: "+to_string(seconds);

    timetext.setFont(font);
    timetext.setString(sec);
    timetext.setColor(sf::Color::White);
    timetext.setCharacterSize(25);
    timetext.setPosition(40.f, 340.f);
    window.draw(timetext);

}

// Function to trace the cards when clicked on them
void clickOnCard()
{
    double ex = event.mouseButton.x;
    double wy = event.mouseButton.y;
    for (int i = 0; i < 12; i++)
    {
        // the click is on card
        if (ex >= allpos[i].first && ex <= allpos[i].first + 50 &&
                wy >= allpos[i].second <= wy && wy <= allpos[i].second + 50)
        {
            shape.setPosition(allpos[i].first, allpos[i].second);
            shape.setFillColor(colorArray[i % 6]);
            check[i] = 1;
            window.draw(shape);
            numclick++;
            curvis++;
            // two cards clicked
            if (curvis == 2)
            {
                curvis = 0;
                for (int ii = 0; ii < 12; ii++)
                {
                    // check if the two cards are the same
                    if (check[ii] && ii != i )
                    {
                        if (colorArray[i % 6] != colorArray[ii % 6])
                            check[i] = 0, check[ii] = 0;
                        else
                            fin[i] = 1, fin[ii] = 1, found++;
                    }
                    else if (check[ii] && ii == i) check[i] = 0, check[ii] = 0;
                }
            }
            break;
        }
    }
}


void endGame()
{

}


int main()
{
    gen(4, 3);
     if (!font.loadFromFile("font.ttf"))cout<<"erorr"<<endl;
    while (window.isOpen())
    {
        window.clear();
        drawShape();
        drawTimeClicks();
        window.display();
        if (found == 6)endGame();

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed &&
                     event.mouseButton.button == Mouse::Left)
                clickOnCard();
        }
    }

    return 0;
}
