#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <ctime>


using namespace std;

class kulka:public sf::CircleShape
{
private:
    float vx=0;
    float vy=-200;

public:
    kulka():sf::CircleShape(){}

    sf::FloatRect get_bounds(){
        return getGlobalBounds();
    }
    void setvxs(float vx1)
    {
        vx=vx1;
    }
    void setvys(float vy1)
    {
        vy=vy1;
    }
    void stepk(float d)
    {
        move(vx*d,vy*d);
        if(get_bounds().top+get_bounds().height>600)
        {
            vy=-abs(vy);

        }
        else if(get_bounds().top<0)
        {
            vy=abs(vy);

        }
        else if(get_bounds().left<0)
        {
            vx=abs(vx);
        }
        else if(get_bounds().left+get_bounds().width>800)
        {
            vx=-abs(vx);

        }
    }
};

class player:public sf::Sprite
{
private:
    float v_y_;
    float v_x_;
    vector<kulka> s;
public:
    player():sf::Sprite(){}

    void setvx(float vx)
    {
        v_x_=vx;
    }
    void setvy(float vy)
    {
        v_y_=vy;
    }
    void step(float d,player &p,vector<kulka>&s)
    {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& p.getGlobalBounds().top+p.getGlobalBounds().height<600)
                {
                    p.move(0,v_y_*d);

                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&p.getGlobalBounds().top>0)
                {
                    p.move(0,-v_y_*d);

                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&p.getGlobalBounds().left>0)
                {
                    p. move(-v_x_*d,0);

                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&p.getGlobalBounds().left+p.getGlobalBounds().width<800)
                {
                    p.move(v_x_*d,0);

                }
            }
};



int main()
{
    int lvl =0;



    sf::RenderWindow window(sf::VideoMode(800, 600), "The hardest game");
    sf::Clock clock;
    sf::Texture texture;
    if (!texture.loadFromFile("hero.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Texture texture2;
    if (!texture2.loadFromFile("Meta.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }


    vector<kulka> sc;

    kulka s1;



    for(int i=0;i<8;i++)
    {
        s1.setRadius(15);
        s1.setPosition(200+i*80,100);
        s1.setFillColor(sf::Color(10,20,200));
        sc.emplace_back(s1);
    }

    for(int i=0;i<8;i++)
    {

        s1.setvxs(200);
        s1.setvys(0);
        s1.setRadius(15);
        s1.setPosition(-50,200+i*80);
        s1.setFillColor(sf::Color(10,20,200));
        sc.emplace_back(s1);
    }






    player gracz;
    gracz.setTexture(texture);
    gracz.setPosition(0,0);
    gracz.setScale(0.7,0.7);
    gracz.setvx(300);
    gracz.setvy(300);

    sf::Sprite winsquare;
    winsquare.setTexture(texture2);
    winsquare.setPosition(720,520);


    sf::RectangleShape tlogry;
    tlogry.setSize(sf::Vector2f(1000,1000));
    tlogry.setFillColor(sf::Color(150,255,0));



    while (window.isOpen()) {
        float delta=(clock.getElapsedTime().asSeconds());
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);


        window.draw(tlogry);
        window.draw(winsquare);
        window.draw(gracz);
        for (int i=0;i<sc.size();i++)
        {
            if(sc[i].getGlobalBounds().intersects(gracz.getGlobalBounds())==true)
            {
                gracz.setPosition(0,0);
            }
        }
        gracz.step(delta,gracz,sc);


        for(int i=0;i<sc.size();i++)
        {
            window.draw(sc[i]);
            sc[i].stepk(delta);
        }



        if(winsquare.getGlobalBounds().intersects(gracz.getGlobalBounds()))
        {
            lvl++;
            gracz.setPosition(0,0);
            sc.clear();

            if(lvl==1)
            {
                winsquare.setPosition(720,0);
                for(int i=0;i<3;i++)
                {
                    s1.setvxs(20);
                    s1.setvys(10);
                    s1.setRadius(35);
                    s1.setPosition(-50+i*20,200+i*80);
                    s1.setFillColor(sf::Color(10,20,200));
                    sc.emplace_back(s1);
                }
                for(int j=0;j!=sc.size();j++){
                    sc[j].setvxs(200);
                    sc[j].setvys(0);
                    sc[j].setPosition(-50+j*80,0+j*80);

                }

            }
        }

        if(lvl==2)
        {
            window.close();
        }









        window.display();
    }

    return 0;
}
