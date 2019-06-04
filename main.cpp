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
    kulka():sf::CircleShape(){};

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
    float v_y_=20.0;
    float v_x_=20.0;
public:
    player():sf::Sprite(){};

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
        for (int i=0;i<s.size();i++) {


        if(s[i].getGlobalBounds().intersects(p.getGlobalBounds())==false)
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
        else
        {
                p.setPosition(0,0);
        }

        }
    }

    bool win(sf::Sprite &r1)
    {
        if(r1.getGlobalBounds().intersects(getGlobalBounds()))
        {
            return true;
        }
        else {
            return false;
        }
    }
};



int main()
{



    sf::RenderWindow window(sf::VideoMode(800, 600), "The hardest game");
    sf::Clock clock;
    sf::Texture texture;
        if (!texture.loadFromFile("hero.png")) {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
    sf::Texture texture1;
          if (!texture1.loadFromFile("tlo.jpg")) {
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
    kulka s2;


    for(int i=0;i<8;i++)
        {
        s1.setRadius(15);
        s1.setPosition(200+i*80,100);
        s1.setFillColor(sf::Color(10,20,200));
        sc.emplace_back(s1);
        }

    for(int i=0;i<8;i++)
        {

        s2.setvxs(200);
        s2.setvys(0);
        s2.setRadius(15);
        s2.setPosition(-50,200+i*80);
        s2.setFillColor(sf::Color(10,20,200));
        sc.emplace_back(s2);
        }




    player gracz;
    gracz.setTexture(texture);
    gracz.setPosition(0,0);
    gracz.setScale(0.7,0.7);
    gracz.setvx(30);
    gracz.setvy(30);

    sf::Sprite winsquare;
    winsquare.setTexture(texture2);
    winsquare.setPosition(720,520);

    sf::Sprite tlogry;
    tlogry.setTexture(texture1);



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
            for(int i=0;i<sc.size();i++)
            {
                window.draw(sc[i]);
                sc[i].stepk(delta);
                if(gracz.win(winsquare)==true)
                {
                 gracz.setPosition(0,560);
                 winsquare.setPosition(720,0);
                 for(int j=0;j<sc.size();j++){
                 sc[j].setvxs(200);
                 sc[j].setvys(0);
                 sc[j].setPosition(-50+j*80,0+j*80);

                }
                 if(gracz.win(winsquare)==true)
                  {
                      window.close();
                  }
                }

            }



            gracz.step(delta,gracz,sc);



            window.display();
        }

    return 0;
}
