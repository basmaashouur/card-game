/*
g++ main.o -o sfml-app -L<sfml-install-path>/lib -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
*/
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;



int main()
{
    RenderWindow window(VideoMode(270, 450), "Cards Game");
    RectangleShape shape(Vector2f(50, 50));
    const sf::Color colorArray[6] = {Color::Cyan, Color::Blue, Color::Green, Color::Red,
                                     Color::Yellow, Color::Magenta
                                    };
    int check[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int fin [12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<pair<double, double > >allpos;
    double incx = 0.0, incy = 0.0;
    int cn = 0, curvis = 0;


    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            allpos.push_back(make_pair(40.f + incx, 40.f + incy));
            incx += 70.0;
        }
        incx = 0.0;
        incy += 70.0;
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

        // clicked on window
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
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
                        cn++;
                        curvis++;
                        // two cards clicked
                        if (curvis == 2)
                        {
                            curvis = 0;
                            for (int ii = 0; ii < 12; ii++)
                            {
                                // check if the two cars are the same
                                if (check[ii] && ii != i )
                                {
                                    if (colorArray[i % 6] != colorArray[ii % 6])
                                        check[i] = 0, check[ii] = 0;
                                    else
                                        fin[i] = 1, fin[ii] = 1;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        window.clear();
        // display shapes on the window
        for (int i = 0; i < 12; i++)
        {
            shape.setPosition(allpos[i].first, allpos[i].second);
            if (check[i] || fin[i])shape.setFillColor(colorArray[i % 6]);
            else shape.setFillColor(Color::White);
            window.draw(shape);

        }

        // game End
        if (cn == 12)
        {


        }

        window.display();

    }

    return 0;
}
