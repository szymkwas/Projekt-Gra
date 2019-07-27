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
class ostrze:public sf::Sprite
{
private:
    float vx=0;
    float vy=-200;
    float angle=0;

public:
    ostrze():sf::Sprite(){}

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
    void setangle(float ang)
    {
        angle=ang;
    }
    void stepk(float d)
    {
        move(vx*d,vy*d);
        rotate(angle*d);
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
    void step(float d,player &p)
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
    int lvl = 0;
    int licznik = 0;


    sf::RenderWindow window(sf::VideoMode(800, 600), "The hardest game");
    sf::Clock clock;

    sf::Texture texture;
    if (!texture.loadFromFile("hero.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Texture texture1;
    if (!texture1.loadFromFile("Meta.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Texture texture2;
    if (!texture2.loadFromFile("ostrze.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }


    vector<kulka> sc;
    vector<kulka> sc1;
    vector<ostrze> os;
    vector<sf::RectangleShape> kolce;

    kulka s1;
    ostrze o1;
    o1.setTexture(texture2);



    for(int i=0;i<8;i++)
    {
        s1.setRadius(15);
        s1.setPosition(200+i*80,100);
        s1.setFillColor(sf::Color(10,20,200));
        sc.emplace_back(s1);
    }

    for(int i=0;i<6;i++)
    {

        s1.setvxs(200);
        s1.setvys(0);
        s1.setRadius(15);
        s1.setPosition(-50,180+i*70);
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
    winsquare.setTexture(texture1);
    winsquare.setPosition(720,520);


    sf::RectangleShape tlogry;
    tlogry.setSize(sf::Vector2f(1000,1000));
    tlogry.setFillColor(sf::Color(150,255,0));

    sf::RectangleShape przeszkoda_z_kolcami;





    while (window.isOpen()) {
        float delta=clock.getElapsedTime().asSeconds();
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
                licznik++;
                gracz.setPosition(0,0);
            }
        }
        for (int i=0;i<sc1.size();i++)
        {
            if(sc1[i].getGlobalBounds().intersects(gracz.getGlobalBounds())==true)
            {
                licznik++;
                gracz.setPosition(0,0);
            }
        }
        for (int i=0;i<os.size();i++)
        {
            if(os[i].getGlobalBounds().intersects(gracz.getGlobalBounds())==true)
            {
                licznik++;
                gracz.setPosition(0,0);
            }
        }
        for (int i=0;i<kolce.size();i++)
        {
            if(kolce[i].getGlobalBounds().intersects(gracz.getGlobalBounds())==true)
            {
                licznik++;
                gracz.setPosition(0,0);
            }
        }

        gracz.step(delta,gracz);


        for(int i=0;i<sc.size();i++)
        {
            window.draw(sc[i]);
            sc[i].stepk(delta);
        }
        for(int i=0;i<sc1.size();i++)
        {
            window.draw(sc1[i]);
            sc1[i].stepk(delta);
        }
        for(int i=0;i<os.size();i++)
        {
            window.draw(os[i]);
            os[i].stepk(delta);
        }
        for(int i=0;i<kolce.size();i++)
        {
            window.draw(kolce[i]);
        }



        if(winsquare.getGlobalBounds().intersects(gracz.getGlobalBounds()))
        {
            lvl++;
            gracz.setPosition(0,0);
            sc.clear();
            sc1.clear();
            os.clear();
            kolce.clear();
            if(lvl==1)
            {
                winsquare.setPosition(720,0);

                przeszkoda_z_kolcami.setSize(sf::Vector2f(100,100));
                przeszkoda_z_kolcami.setFillColor(sf::Color(0,0,250));
                przeszkoda_z_kolcami.setPosition(300,0);
                kolce.emplace_back(przeszkoda_z_kolcami);

                for(int i=0;i<9;i++)
                {
                    s1.setRadius(20);
                    s1.setPosition(0,0);
                    s1.setFillColor(sf::Color(10,20,200));
                    s1.setvxs(500);
                    s1.setvys(0);
                    s1.setPosition(0,100+i*90);
                    sc.emplace_back(s1);
                }
                for(int i=0;i<7;i++)
                {
                    s1.setRadius(20);
                    s1.setPosition(150,0);
                    s1.setFillColor(sf::Color(10,20,200));
                    s1.setvxs(500);
                    s1.setvys(0);
                    s1.setPosition(170,135+i*100);
                    sc1.emplace_back(s1);
                }
            }

            if(lvl==2)
            {
                winsquare.setPosition(720,0);

                for(int i=0;i<6;i++)
                {
                    o1.setangle(300);
                    o1.setScale(0.3,0.3);
                    o1.setPosition(90+i*150,400);
                    os.emplace_back(o1);
                }
                for(int i=0;i<6;i++)
                {
                    o1.setangle(300);
                    o1.setScale(0.3,0.3);
                    o1.setPosition(90+i*150,100);
                    os.emplace_back(o1);
                }

                for(int i=0;i<12;i++)
                {
                    s1.setRadius(15);
                    s1.setPosition(0,0);
                    s1.setFillColor(sf::Color(10,20,200));
                    s1.setvxs(0);
                    s1.setvys(600);
                    s1.setPosition(50+i*90,0);
                    sc.emplace_back(s1);
                }
            }
            if(lvl==3)
            {
                winsquare.setPosition(720,520);

                for(int i=0;i<7;i++)
                {
                    o1.setvxs(0);
                    o1.setvys(0);
                    o1.setangle(250);
                    o1.setScale(0.3,0.3);
                    o1.setPosition(750-i*115,370);
                    os.emplace_back(o1);
                }
                for(int i=0;i<7
                    ;i++)
                {
                    o1.setvxs(0);
                    o1.setvys(0);
                    o1.setangle(250);
                    o1.setScale(0.3,0.3);
                    o1.setPosition(750-i*115,550);
                    os.emplace_back(o1);
                }
                for(int i=0;i<3;i++)
                {
                    o1.setvxs(0);
                    o1.setvys(0);
                    o1.setangle(250);
                    o1.setScale(0.3,0.3);
                    o1.setPosition(200,50+i*120);
                    os.emplace_back(o1);
                }
                for(int i=0;i<3;i++)
                {
                    o1.setvxs(0);
                    o1.setvys(0);
                    o1.setangle(250);
                    o1.setScale(0.3,0.3);
                    o1.setPosition(400,50+i*120);
                    os.emplace_back(o1);
                }
                for(int i=0;i<3;i++)
                {
                    o1.setvxs(0);
                    o1.setvys(0);
                    o1.setangle(250);
                    o1.setScale(0.3,0.3);
                    o1.setPosition(600,50+i*120);
                    os.emplace_back(o1);
                }
            }
            if(lvl==4)
            {
                window.close();
            }

        }
        window.display();
    }
    std::cout<<"Podczas gry zginales: "<<licznik<<" razy"<<std::endl;
    if(licznik<10)
    {
        std::cout<<"WOW! Jestes naprawde dobry!";
    }
    if(licznik>10&&licznik<30)
    {
        std::cout<<"Stac cie na wiecej!";
    }
    if(licznik>30)
    {
        std::cout<<"Musisz jeszcze troche pocwiczyc!";
    }

    return 0;
}
