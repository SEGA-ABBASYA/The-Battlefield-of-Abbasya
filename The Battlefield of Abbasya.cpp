#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/window.hpp>
#include <vector>
#include <time.h>
using namespace sf;
using namespace std;

// 0 -> MainMenu
// 1 -> Choose Your Hero 
// 2 -> Options
// 3 -> Credits 
// Esc -> PauseMen
// 4 -> Close



//Global Variables
Clock gameclock;
float Gravity = -20.0f;
float Jumpheight = 150.0f;
float deltatime = 0.0f;
int playerindex = 0;
int Deathindex = 0;
float timer = 0.0f;
float delay = 0.15f;
float roundelay = 5.0f;
int attackindex = 0;
float attacktimer = 0.0f;
float attackdelay = 0.1f;
int index2 = 0;
float timer2 = 0.0f;
float delay2 = 0.15f;
int attackindex2 = 0;
float attacktimer2 = 0.0f;
float attackdelay2 = 0.1f;
float hittimer = 0.0f;
float hittimer2 = 0.0f;
int pagenum = 0;
int page = 0;
int win1 = 0;
int win2 = 0;
bool PAUSE = false;
bool Round_Trans = false;
int volume_ = 90;
bool name__ = false;

Font menufont;
Texture optionButton;
Texture optionButton2;

struct cursor {
    Texture texture;
    Sprite sprite;

    cursor() {
        // Load the cursor texture
        texture.loadFromFile("cursor.png");

        // Create the cursor sprite
        sprite.setTexture(texture);
        sprite.setScale(2, 2);
        sprite.setOrigin(texture.getSize().x / 15, texture.getSize().y / 15);
    }

    void draw(RenderWindow& window) {
        // Set the cursor sprite's position to the mouse position
        sprite.setPosition(Vector2f(Mouse::getPosition(window)));
        // Set the mouse cursor to be hidden
        window.setMouseCursorVisible(false);
        // Draw the cursor sprite
        window.draw(sprite);
    }
}cur;
struct Hitbox
{
    RectangleShape attack;
    RectangleShape player;

    //function for setting the properties of a hitbox
    void sethitbox(Sprite& w, RectangleShape& x, float y, float z, Color l) {
        x.setSize(Vector2f(y, z));
        x.setFillColor(l);
        x.setPosition(w.getPosition().x, w.getPosition().y + 10);
        x.setOrigin(y / 2, -6);
    }
};
struct player {
    string name;
    int health = 100;
    Vector2f velocity{ 0,0 };
    Sprite sprite;
    Hitbox hitbox;
    bool grounded = false, attackbool = false, hitbool = false, timereset = false;

}player1, player2;
struct plates {
    RectangleShape platrec;

    //function for setting the properties of the plates
    void plat_set(Texture& imag, RectangleShape& sh_1, float x1, float x2, int x3, int x4, int x5, int x6) {
        sh_1.setSize(Vector2f(x1, x2));
        sh_1.setPosition(x3, x4);
        sh_1.setTexture(&imag);
        sh_1.setScale(x5, x6);
    }
}plt1, plt2, plt3, plt4, plt5, plt6;

int cursor_select(Text* arr, RectangleShape* Buttonarr, RenderWindow& mywindow)
{
    Mouse mouse;
    for (int i = 1; i < 5; i++)
    {

        if (Buttonarr[i].getGlobalBounds().contains(mouse.getPosition(mywindow).x, mouse.getPosition(mywindow).y))
        {
            if (i == 4)
            {
                Buttonarr[i].setScale(1.6f, 1.6f);
                Buttonarr[i].setTexture(&optionButton);
            }

            else
                Buttonarr[i].setScale(1.05f, 1.05f);
            arr[i].setFillColor(Color::White);

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                Buttonarr[i].setScale(1.f, 1.f);
                arr[i].setFillColor(Color(187, 220, 244));
                return i;
            }
        }
        else
        {
            if (i == 4)
            {
                Buttonarr[i].setScale(1.5f, 1.5f);
                Buttonarr[i].setTexture(&optionButton2);
            }
            else
                Buttonarr[i].setScale(1.f, 1.f);
            arr[i].setFillColor(Color(187, 220, 244));
        }
    }
    return 0;
}

void setTextprop(Text& text) {
    menufont.loadFromFile("Canterbury.ttf");
    text.setCharacterSize(48);
    text.setFillColor(Color(187, 220, 244));
    text.setFont(menufont);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(1);
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
}

int cursor_select_pause(Text* arr, RenderWindow& mywindow)
{
    Mouse mouse;
    for (int i = 0; i < 5; i++)
    {

        if (arr[i].getGlobalBounds().contains(mouse.getPosition(mywindow).x, mouse.getPosition(mywindow).y))
        {
            arr[i].setFillColor(Color::Red);

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                arr[i].setFillColor(Color::White);
                return i;
            }
        }
        else
        {
            arr[i].setFillColor(Color::White);
        }
    }
    return 0;
}

Sprite vol_arr[9];

void MainMenu(RenderWindow& mainwindow)
{
    // Create the menu items

    Texture ButtonTexture;
    Texture Menuback;
    Texture BorderTex;


    ButtonTexture.loadFromFile("Main Menu/silver_button.png");
    BorderTex.loadFromFile("Main Menu/border.png");
    Menuback.loadFromFile("Main Menu/background main menu.png");
    optionButton.loadFromFile("Main Menu/option1.png");
    optionButton2.loadFromFile("Main Menu/option2.png");

    Text select[6];

    RectangleShape buttons[5];

    Sprite Border;
    Sprite Mainmenu_background;
    Mainmenu_background.setTexture(Menuback);
    Border.setTexture(BorderTex);
    Border.setPosition(mainwindow.getSize().x / 2, 200);
    Border.setOrigin(151, 0);

    for (int i = 1; i < 4; i++) {
        buttons[i].setTexture(&ButtonTexture);
        buttons[i].setSize(Vector2f(300.f, 81.f));
        buttons[i].setOrigin(buttons[i].getSize() / 2.f);
    }

    buttons[4].setTexture(&optionButton2);
    buttons[4].setSize(Vector2f(50.f, 50.f));
    buttons[4].setOrigin(buttons[4].getSize() / 2.f);
    buttons[4].setPosition(mainwindow.getSize().x - 60.f, 650);
    

    buttons[1].setPosition(640, 319);

    buttons[2].setPosition(640, 447);

    buttons[3].setPosition(640, 575);

    select[0].setCharacterSize(96);
    select[0].setString("The Battlefield of\n     Abbasya");
    select[0].setFillColor(Color(187, 220, 244));
    select[0].setFont(menufont);
    select[0].setOutlineColor(Color::Black);
    select[0].setOutlineThickness(2);
    // select[5].setOrigin(select[5].getLocalBounds().left + select[5].getLocalBounds().width / 2, select[5].getLocalBounds().top + select[5].getLocalBounds().height / 2);
    select[0].setPosition(mainwindow.getSize().x / 4, 10);

    select[1].setString("Fight!");
    select[1].setPosition(buttons[1].getPosition().x, buttons[1].getPosition().y);

    select[2].setString("Credits");
    select[2].setPosition(buttons[2].getPosition().x, buttons[2].getPosition().y);

    select[3].setString("Exit");
    select[3].setPosition(buttons[3].getPosition().x, buttons[3].getPosition().y);

    for (int i = 1;i < 5;i++) {
        setTextprop(select[i]);
    }

    while (mainwindow.isOpen())
    {
        // Handle events
        sf::Event event;
        while (mainwindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainwindow.close();
            }

        }

        // select which window
        pagenum = cursor_select(select, buttons, mainwindow);

        if (pagenum != 0) { return; }

        // Clear the window
        mainwindow.clear();

        //Draw Background Main Menu
        mainwindow.draw(Mainmenu_background);

        // Draw the buttons
        for (int i = 1;i < 5;i++) {
            mainwindow.draw(buttons[i]);
        }

        // Draw Border
        mainwindow.draw(Border);

        // Draw the menu items
        for (int i = 0; i < 6; i++)
        {
            mainwindow.draw(select[i]);
        }

        // Draw the cursor sprite in the struct;
        cur.draw(mainwindow);

        // Display the window
        mainwindow.display();

    }
}

void Credits(RenderWindow& creditswindow) {
    Font Credits;
    Credits.loadFromFile("ArcadeClassic.ttf");

    Text select[8];
    select[0].setFont(Credits);
    select[0].setFillColor(Color::White);
    select[0].setString("Main Menu");
    select[0].setCharacterSize(60);
    select[0].setPosition(100, 620);

    select[1].setFont(Credits);
    select[1].setString("Abd ElRahman Mustafa");
    select[1].setCharacterSize(40);
    select[1].setFillColor(Color::White);
    select[1].setPosition(20, 20);

    select[2].setFont(Credits);
    select[2].setFillColor(Color::White);
    select[2].setString("Abd ElRahman Osama");
    select[2].setCharacterSize(40);
    select[2].setPosition(20, 100);

    select[3].setFont(Credits);
    select[3].setFillColor(Color::White);
    select[3].setString("Mahmoud Emad");
    select[3].setCharacterSize(40);
    select[3].setPosition(20, 180);

    select[4].setFont(Credits);
    select[4].setFillColor(Color::White);
    select[4].setString("Yousef Ashraf");
    select[4].setCharacterSize(40);
    select[4].setPosition(20, 260);

    select[5].setFont(Credits);
    select[5].setFillColor(Color::White);
    select[5].setString("Yousef Ahmed");
    select[5].setCharacterSize(40);
    select[5].setPosition(20, 340);

    select[6].setFont(Credits);
    select[6].setFillColor(Color::White);
    select[6].setString("Yousef Khataan");
    select[6].setCharacterSize(40);
    select[6].setPosition(20, 420);

    select[7].setFont(Credits);
    select[7].setFillColor(Color::White);
    select[7].setString("Ziad Khaled ");
    select[7].setCharacterSize(40);
    select[7].setPosition(20, 520);

    while (creditswindow.isOpen())
    {
        sf::Event event2;
        while (creditswindow.pollEvent(event2))
        {
            if (event2.type == sf::Event::Closed)
            {
                creditswindow.close();
            }
        }
        RectangleShape backtomain;
        backtomain.setSize(Vector2f(300.f, 100.f));
        backtomain.setPosition(110, 620);
        backtomain.setFillColor(Color::Transparent);

        Mouse mouse;
        if (backtomain.getGlobalBounds().contains(mouse.getPosition(creditswindow).x, mouse.getPosition(creditswindow).y))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                return;
            }
        }
        creditswindow.clear();
        //pagenum = cursor_select(select, creditswindow);


        for (int i = 0; i < 8; i++) {
            creditswindow.draw(select[i]);
        }


        cur.draw(creditswindow);
        creditswindow.draw(backtomain);
        creditswindow.display();
    }
}

void game(int win1, int win2, RenderWindow& window);

void Volume(RenderWindow& volumewindow)
{
    Font volumefont;
    volumefont.loadFromFile("ArcadeClassic.ttf");
    Text volume[3];
    volume[0].setFont(volumefont);
    volume[0].setString("The Battlefield of Abbasya");
    volume[0].setCharacterSize(60);
    volume[0].setFillColor(Color{ 255,204,0 });
    volume[0].setPosition(300, 100);

    volume[1].setFont(volumefont);
    volume[1].setString("Resume");
    volume[1].setCharacterSize(60);
    volume[1].setFillColor(Color{ 255,204,0 });
    volume[1].setPosition(600, 600);

    volume[2].setFont(volumefont);
    volume[2].setString("Mute");
    volume[2].setCharacterSize(60);
    volume[2].setFillColor(Color{ 255,204,0 });
    volume[2].setPosition(600, 550);


    Texture vol80;
    Texture vol70;
    Texture vol60;
    Texture vol50;
    Texture vol40;
    Texture vol30;
    Texture vol20;
    Texture vol10;
    Texture vol0;

    vol80.loadFromFile("Volume Bar/XP Bar Animated Yellow 1.png");
    vol70.loadFromFile("Volume Bar/XP Bar Animated Yellow 2.png");
    vol60.loadFromFile("Volume Bar/XP Bar Animated Yellow 3.png");
    vol50.loadFromFile("Volume Bar/XP Bar Animated Yellow 4.png");
    vol40.loadFromFile("Volume Bar/XP Bar Animated Yellow 5.png");
    vol30.loadFromFile("Volume Bar/XP Bar Animated Yellow 6.png");
    vol20.loadFromFile("Volume Bar/XP Bar Animated Yellow 7.png");
    vol10.loadFromFile("Volume Bar/XP Bar Animated Yellow 8.png");
    vol0.loadFromFile("Volume Bar/XP Bar Animated Yellow 9.png");

    vol_arr[8].setTexture(vol80);
    vol_arr[7].setTexture(vol70);
    vol_arr[6].setTexture(vol60);
    vol_arr[5].setTexture(vol50);
    vol_arr[4].setTexture(vol40);
    vol_arr[3].setTexture(vol30);
    vol_arr[2].setTexture(vol20);
    vol_arr[1].setTexture(vol10);
    vol_arr[0].setTexture(vol0);

    for (int i = 0; i < 9; i++) {
        vol_arr[i].setScale(7, 7);
        vol_arr[i].setOrigin(vol10.getSize().x / 2, vol10.getSize().y / 2);
        vol_arr[i].setPosition(volumewindow.getSize().x / 2, volumewindow.getSize().y / 2);

    }

    while (volumewindow.isOpen())
    {
        sf::Event event;
        while (volumewindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                volumewindow.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::L) {
                    if (volume_ - 10 >= 0)
                        volume_ -= 10;
                }


                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::H) {
                        if (volume_ + 10 <= 90)
                            volume_ += 10;
                    }

                }
            }
        }
        RectangleShape resume_volume;
        resume_volume.setSize(Vector2f(200.f, 100.f));
        resume_volume.setPosition(600, 600);
        resume_volume.setFillColor(Color::Transparent);

        Mouse mouse;
        if (resume_volume.getGlobalBounds().contains(mouse.getPosition(volumewindow).x, mouse.getPosition(volumewindow).y))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                return;
            }
        }

        volumewindow.clear(Color::White);

        for (int i = 0; i < 2; i++) {
            volumewindow.draw(volume[i]);
        }

        volumewindow.draw(resume_volume);
        int voll = ((volume_ - 1) / 10.0);

        volumewindow.draw(vol_arr[voll]);

        cur.draw(volumewindow);

        volumewindow.display();

    }
}

void Controlls(RenderWindow& controllswindow)
{
    Font controllsfont;
    controllsfont.loadFromFile("ArcadeClassic.ttf");
    Text controlls[9];
    controlls[0].setFont(controllsfont);
    controlls[0].setString("The Battlefield of Abbasya");
    controlls[0].setCharacterSize(60);
    controlls[0].setFillColor(Color{ 255,204,0 });
    controlls[0].setPosition(300, 100);

    while (controllswindow.isOpen())
    {

        Event event;
        while (controllswindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                controllswindow.close();
            }

        }

        controllswindow.clear();

        for (int i = 0;i < 9;i++)
            controllswindow.draw(controlls[i]);

        cur.draw(controllswindow);

        controllswindow.display();
    }
}

void Options(RenderWindow& optionwindow)
{
    Font optionfont;
    optionfont.loadFromFile("ArcadeClassic.ttf");
    Text option;
    option.setFont(optionfont);
    option.setString("The Battlefield of Abbasya");
    option.setCharacterSize(60);
    option.setFillColor(Color{ 255,204,0 });
    option.setPosition(300, 100);

    while (optionwindow.isOpen())
    {


        // Handle events
        sf::Event event;
        while (optionwindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                optionwindow.close();
            }

        }

        // select which window
       // pagenum = cursor_select(select, optionwindow);

        if (pagenum != 2) { return; }

        // Clear the window
        optionwindow.clear();

        // Draw the menu items
        optionwindow.draw(option);
        // Draw the cursor sprite in the struct;
        cur.draw(optionwindow);

        // Display the window
        optionwindow.display();
    }
}

int PauseMenu(RenderWindow& pausewindow) {
    Font pausefont;
    pausefont.loadFromFile("Canterbury.ttf");
    Text Pause[5];
    Pause[0].setFont(pausefont);
    Pause[0].setString("The Battlefield of Abbasya");
    Pause[0].setCharacterSize(60);
    Pause[0].setFillColor(Color{ 255,204,0 });
    Pause[0].setPosition(300, 100);

    Pause[1].setFont(pausefont);
    Pause[1].setString("Volume");
    Pause[1].setCharacterSize(60);
    Pause[1].setFillColor(Color{ 255,204,0 });
    Pause[1].setPosition(300, 200);

    Pause[2].setFont(pausefont);
    Pause[2].setString("Resume");
    Pause[2].setCharacterSize(60);
    Pause[2].setFillColor(Color{ 255,204,0 });
    Pause[2].setPosition(300, 250);

    Pause[3].setFont(pausefont);
    Pause[3].setString("Back To MainMenu");
    Pause[3].setCharacterSize(60);
    Pause[3].setFillColor(Color{ 255,204,0 });
    Pause[3].setPosition(300, 300);

    Pause[4].setFont(pausefont);
    Pause[4].setString("Exit");
    Pause[4].setCharacterSize(60);
    Pause[4].setFillColor(Color{ 255,204,0 });
    Pause[4].setPosition(300, 350);


    while (pausewindow.isOpen())
    {
        gameclock.restart();
        Event event;
        while (pausewindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                pausewindow.close();
            }

        }
        page = cursor_select_pause(Pause, pausewindow);
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            PAUSE = false;
            return 1;
        }
        else if (page == 1) { Volume(pausewindow); }//volume
        else if (page == 2) {
            PAUSE = false;
            return 1;
        }
        else if (page == 3) {
            Round_Trans = false;
            win1 = 0;
            win2 = 0;
            PAUSE = false;
            return 0;
        }//main menu
        else if (page == 4) { pausewindow.close(); }//exit

        pausewindow.clear();

        for (int i = 0; i < 5; i++) {
            pausewindow.draw(Pause[i]);
        }
        cur.draw(pausewindow);

        pausewindow.display();
    }
}

void name(struct player, RenderWindow& namewindow) {

    string name1,name2;
    Mouse mouse;


    Texture nameback;
    nameback.loadFromFile("name enternce.png");
    Sprite namebackground;
    namebackground.setTexture(nameback);

    Texture frames[5];
    frames[0].loadFromFile("Name Entry/Game_text_boxes.png");
    frames[1].loadFromFile("Name Entry/name-box.png");
    frames[2].loadFromFile("Name Entry/_Idle1 1.png");
    frames[3].loadFromFile("Name Entry/_Idle2 1.png");
    frames[4].loadFromFile("Name Entry/start1.png");

    RectangleShape start[3];

    //Start Button
    start[0].setSize(Vector2f(316.f, 106.f));
    start[0].setOrigin(151.f, 53.f);
    start[0].setPosition(namewindow.getSize().x / 2, 400);
    start[0].setTexture(&frames[4]);

    //Player 1 name entry button
    start[1].setSize(Vector2f(300.f, 92.f));
    start[1].setPosition(250, 416);
    start[1].setOrigin(150.f, 46.f);
    start[1].setTexture(&frames[1]);

    //Player 2 name entry button
    start[2].setSize(Vector2f(300.f, 92.f));
    start[2].setPosition(1070, 416);
    start[2].setOrigin(150.f, 46.f);
    start[2].setTexture(&frames[1]);

    Sprite frame[3];

    //Player 1 Picture
    frame[0].setTexture(frames[2]);

    //Player 2 Picture
    frame[1].setTexture(frames[3]);

    //Enter Your name 
    frame[2].setTexture(frames[0]);

    frame[0].setPosition(150, 350);
    frame[1].setPosition(930, 340);
    frame[2].setOrigin(240, 70);
    frame[2].setPosition(namewindow.getSize().x / 2, 100);
    
    bool name_ = false;

    Font font;
    font.loadFromFile("Canterbury.ttf");

    Text text1("Bakr", font);
    Text text2("Fat7allah", font);

    text1.setPosition(150, 385);
    text1.setCharacterSize(42);
    text2.setPosition(970, 385);
    text2.setCharacterSize(42);

    Text text[4];

    text[0].setString("Player 1");
    text[0].setCharacterSize(80);
    text[0].setPosition(start[1].getPosition().x, 270);

    text[1].setString("Player 2");
    text[1].setCharacterSize(80);
    text[1].setPosition(start[2].getPosition().x, 270);

    text[2].setString("Enter Your Name");
    text[2].setCharacterSize(42);
    text[2].setPosition(frame[2].getPosition().x, frame[2].getPosition().y + 5);

    text[3].setString("Start");
    text[3].setCharacterSize(60);
    text[3].setPosition(start[0].getPosition().x, start[0].getPosition().y - 5);

    for (int i = 0;i < 4;i++) {
        text[i].setFont(font);
        text[i].setFillColor(Color{ 101,154,171 });
        text[i].setOutlineColor(Color::Black);
        text[i].setOutlineThickness(2);
        text[i].setOrigin(text[i].getLocalBounds().left + text[i].getLocalBounds().width / 2, text[i].getLocalBounds().top + text[i].getLocalBounds().height / 2);
    }



    Clock clock;

    while (namewindow.isOpen())
    {
        gameclock.restart();
        Event event;
        while (namewindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
                namewindow.close();

            if (start[2].getGlobalBounds().contains(mouse.getPosition(namewindow).x, mouse.getPosition(namewindow).y))
            {
                start[2].setScale(1.1, 1.1);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    name_ = true;

                }
            }
            else
            {
                start[2].setScale(1, 1);
            }

            if (start[1].getGlobalBounds().contains(mouse.getPosition(namewindow).x, mouse.getPosition(namewindow).y))
            {
                start[1].setScale(1.1, 1.1);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    name_ = false;

                }
            }
            else
            {
                start[1].setScale(1, 1);
            }

            //Start Button
            if (start[0].getGlobalBounds().contains(mouse.getPosition(namewindow).x, mouse.getPosition(namewindow).y))
            {
                start[0].setScale(1.1, 1.1);
                text[3].setFillColor(Color::White);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    name__ = false;
                    return;
                }
            }
            else {
                text[3].setFillColor(Color{ 101,154,171 });
                start[0].setScale(1, 1);

            }


            if (!name_) {
                if (event.type == Event::TextEntered) {
                    if (isprint(event.text.unicode))
                        name1 += event.text.unicode;
                }
                else if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::BackSpace) {
                        if (!name1.empty())
                            name1.pop_back();
                    }
                    /*if (event.key.code == Keyboard::Right) {
                        name_ = true;
                    }*/

                }
            }
            if (name_) {

                if (event.type == Event::TextEntered) {
                    if (isprint(event.text.unicode))
                        name2 += event.text.unicode;
                }
                else if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::BackSpace) {
                        if (!name2.empty())
                            name2.pop_back();
                    }
                   /* if (event.key.code == Keyboard::Left) {
                        name_ = false;
                    }*/
                    /*if (event.key.code == Keyboard::Return) {
                        name__ = false;
                        return;
                    }*/
                }

                
               
                
            }
        }

        static Time text_effect_time;
        static bool show_cursor;

        text_effect_time += clock.restart();

        if (text_effect_time >= seconds(0.5f))
        {
            show_cursor = !show_cursor;
            text_effect_time = Time::Zero;
        }
        if(!name_)
        text1.setString(name1 + (show_cursor ? '_' : ' '));
        if(name_)
        text2.setString(name2 + (show_cursor ? '_' : ' '));
        //cout << player1.name << endl << endl<<player2.name << endl;
        player1.name = name1;
        player2.name = name2;
        namewindow.clear();
        namewindow.draw(namebackground);
        for (int i = 0; i < 3; i++) {
            namewindow.draw(frame[i]);
            namewindow.draw(start[i]);
        }
        namewindow.draw(text1);
        namewindow.draw(text2);
        for (int j = 0; j < 4; j++) {
            namewindow.draw(text[j]);
        }
        cur.draw(namewindow);
        namewindow.display();
    }
}

//function for defining health bar textures
void init_health_bar();

//function for updating health bar according to player's health
int update_healthbar(int health);

//function for setting setting initial properties to a player
void setprop(Sprite&, Texture&, int, int, int);

//function for checking the colliding the hitbox of attack with the hitbox of player
bool intersection(RectangleShape&, RectangleShape&);

//function for checking the colliding the hitbox of player and the plates
bool platecoliode_1(RectangleShape&, RectangleShape&);

Texture hp_bar[6];

int main()
{
    RenderWindow get_window(VideoMode(1280, 720), "The Battlefield of Abbasya");
    get_window.setFramerateLimit(60);

    while (get_window.isOpen())
    {

        MainMenu(get_window);
        if (pagenum == 0) { MainMenu(get_window); }
        else if (pagenum == 1) {
            name__ = true;
            roundelay = 5.0f;
            Round_Trans = false;
            player1.health = 100;
            player2.health = 100;
            player1.sprite.setColor(Color::White);
            player2.sprite.setColor(Color::White);
            Deathindex = 0;
            game(win1, win2, get_window);
        }
        else if (pagenum == 4) { Volume(get_window); }
        else if (pagenum == 2) { Credits(get_window); }
        else if (pagenum == 3) { get_window.close(); }
    }
    return 0;
}

//function definition above

void init_health_bar()
{
    Texture Hp100;
    Texture Hp80;
    Texture Hp60;
    Texture Hp40;
    Texture Hp20;
    Texture Hp00;

    Hp100.loadFromFile("health_bar/health100.png");
    Hp80.loadFromFile("health_bar/health80.png");
    Hp60.loadFromFile("health_bar/health60.png");
    Hp40.loadFromFile("health_bar/health40.png");
    Hp20.loadFromFile("health_bar/health20.png");
    Hp00.loadFromFile("health_bar/health00.png");

    hp_bar[0] = Hp00;
    hp_bar[1] = Hp20;
    hp_bar[2] = Hp40;
    hp_bar[3] = Hp60;
    hp_bar[4] = Hp80;
    hp_bar[5] = Hp100;
}

int update_healthbar(int health)
{
    if (health == 80)
    {
        return 4;
    }
    else if (health == 60)
    {
        return 3;
    }
    else if (health == 40)
    {
        return 2;
    }
    else if (health == 20)
    {
        return 1;
    }
    else if (health == 0)
    {
        return 0;
    }
    return -1;
}

void setprop(Sprite& x, Texture& y, int z, int l, int m) {

    x.setTexture(y);
    x.setOrigin(60, 40);
    x.setPosition(l, m);
    x.setTextureRect(IntRect(0, 0, 120, 80));
    x.setScale(z, 3);
}

bool intersection(RectangleShape& x, RectangleShape& y) {
    if (x.getGlobalBounds().intersects(y.getGlobalBounds()))
        return true;
    else
        return false;
}

bool platecoliode_1(Sprite& player, RectangleShape& player_x, RectangleShape& plat_y1) {
    if (player_x.getGlobalBounds().intersects(plat_y1.getGlobalBounds()) &&
        player_x.getGlobalBounds().top + player_x.getGlobalBounds().height - 20 < plat_y1.getGlobalBounds().top)
    {
        //cout << plat_y1.getGlobalBounds().top << endl;
        player.setPosition(player.getPosition().x, plat_y1.getGlobalBounds().top - player.getGlobalBounds().height / 2);
        return true;
    }
    else {
        return false;
    }
}

void game(int win1, int win2, RenderWindow& window)
{
    int arr_index = 5;

    srand(time(0));

    //Textures
    Texture Floor;
    Texture Jumping;
    Texture Jumping2;
    Texture Running2;
    Texture Running;
    Texture Idle;
    Texture Idle2;
    Texture Fall;
    Texture Fall2;
    Texture Back[3];
    Texture Attacking;
    Texture Attacking2;
    Texture Hit;
    Texture Hit2;
    Texture Death;
    Texture Death2;
    Texture P1_HealthBar_Texture;
    Texture P2_HealthBar_Texture;
    Font ourFont;
    Texture plateform_1;
    Texture plateform_2;
    Texture plateform_3;
    Texture plateform_4;
    Texture plateform_round3;

    // call init_health_bar once in the beginning of the game
    init_health_bar();
    ourFont.loadFromFile("ArcadeClassic.ttf");
    Back[0].loadFromFile("Background.jpg");
    Back[1].loadFromFile("background2.jpg");
    Back[2].loadFromFile("Round3_Background.jpg");
    Idle.loadFromFile("Player 1/_Idle.png");
    Idle2.loadFromFile("Player 2/Idle2.png");
    Running2.loadFromFile("Player 2/Run2.png");
    Running.loadFromFile("Player 1/Running Animation.png");
    Jumping.loadFromFile("Player 1/_Jump.png");
    Jumping2.loadFromFile("Player 2/Jump2.png");
    Fall.loadFromFile("Player 1/_Fall.png");
    Fall2.loadFromFile("Player 2/_Fall2.png");
    Hit.loadFromFile("Player 1/_Hit.png");
    Hit2.loadFromFile("Player 2/Hit2.png");
    Attacking.loadFromFile("Player 1/_Attack.png");
    Attacking2.loadFromFile("Player 2/Attack2.png");
    Death.loadFromFile("Player 1/_Death.png");
    Death2.loadFromFile("Player 2/_Death.png");
    plateform_1.loadFromFile("Plates/firstplate.png");
    plateform_2.loadFromFile("Plates/secondplate.png");
    plateform_3.loadFromFile("Plates/thirdplate.png");
    plateform_round3.loadFromFile("Plates/plate_Round3.png");
    plateform_4.loadFromFile("Plates/fourthplate.png");

    Event e;

    Sprite background(Back[win1 + win2]);

    //setting prop to plates
    plt1.plat_set(plateform_1, plt1.platrec, 150, 50, 1000, 450, 1, 1);
    plt2.plat_set(plateform_2, plt2.platrec, 450, 50, 400, 400, 1, 1);
    plt3.plat_set(plateform_1, plt3.platrec, 150, 50, 100, 450, 1, 1);
    plt5.plat_set(plateform_1, plt5.platrec, 150, 50, 1000, 300, 0, 0);
    plt4.plat_set(plateform_2, plt4.platrec, 1280, 50, 0, 650, 1, 1);
    if (win1 + win2 == 1) {
        plt1.plat_set(plateform_3, plt1.platrec, 150, 50, 1000, 500, 1, 1);
        plt2.plat_set(plateform_4, plt2.platrec, 450, 50, 400, 400, 1, 1);
        plt3.plat_set(plateform_3, plt3.platrec, 150, 50, 100, 500, 1, 1);
        plt4.plat_set(plateform_4, plt4.platrec, 150, 50, 100, 300, 1, 1);
        plt5.plat_set(plateform_3, plt5.platrec, 150, 50, 1000, 300, 1, 1);
    }
    if (win1 + win2 == 2) {
        plt1.plat_set(plateform_1, plt1.platrec, 150, 50, 1000, 450, 0, 0);
        plt2.plat_set(plateform_round3, plt2.platrec, 750, 70, 250, 450, 1, 1);
        plt3.plat_set(plateform_3, plt3.platrec, 150, 50, 100, 450, 0, 0);
        plt4.plat_set(plateform_2, plt4.platrec, 150, 50, 100, 300, 0, 0);
        plt5.plat_set(plateform_3, plt5.platrec, 150, 50, 1000, 300, 0, 0);
    }

    //Player 1 health bar prop
    RectangleShape p1_healthBar(Vector2f(305.f, 100.f));
    p1_healthBar.setScale(0.8f, 0.7f);
    p1_healthBar.setPosition(50, 50);
    p1_healthBar.setOrigin(p1_healthBar.getPosition().x / 2, p1_healthBar.getPosition().y / 2);
    P1_HealthBar_Texture = hp_bar[arr_index];
    p1_healthBar.setTexture(&P1_HealthBar_Texture);

    //Player 2 health bar prop
    RectangleShape p2_healthBar(Vector2f(305.f, 100.f));
    p2_healthBar.setScale(-0.8f, 0.7f);
    p2_healthBar.setPosition(895, 50);
    p2_healthBar.setOrigin(p2_healthBar.getPosition().x / 2, p2_healthBar.getPosition().y / 2);
    P2_HealthBar_Texture = hp_bar[arr_index];
    p2_healthBar.setTexture(&P2_HealthBar_Texture);

    //Players initial prop
    if (win1 + win2 == 0) {
        setprop(player1.sprite, Idle, 3, 320, 480);
        setprop(player2.sprite, Idle2, -3, 960, 480);
    }
    else if (win1 + win2 == 1) {
        setprop(player1.sprite, Idle, 3, 180, 350);
        setprop(player2.sprite, Idle2, -3, 1050, 350);
    }
    else {
        setprop(player1.sprite, Idle, 3, 330, 150);
        setprop(player2.sprite, Idle2, -3, 900, 150);
    }

    //Hitboxes initial prop
    player1.hitbox.sethitbox(player1.sprite, player1.hitbox.attack, 150.f, 40.f, Color::Yellow);
    player2.hitbox.sethitbox(player2.sprite, player2.hitbox.attack, 150.f, 40.f, Color::Yellow);
    player1.hitbox.sethitbox(player1.sprite, player1.hitbox.player, 30.f, 115.f, Color::Blue);
    player2.hitbox.sethitbox(player2.sprite, player2.hitbox.player, 30.f, 115.f, Color::Blue);
    player1.hitbox.attack.setOrigin(0, 0);
    player2.hitbox.attack.setOrigin(0, 0);



    window.setFramerateLimit(60);


    while (window.isOpen()) {
        gameclock.restart();
        if (name__) {
            name(player1, window);
        }
       
        if (!PAUSE) {
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                {
                    window.close();
                }
                if (e.type == Event::KeyPressed)
                {
                    if (e.key.code == Keyboard::Escape) {
                        PAUSE = true;
                        if (!PauseMenu(window))
                        {
                            PauseMenu(window);
                            setprop(player1.sprite, Idle, 3, 320, 480);
                            setprop(player2.sprite, Idle2, -3, 960, 480);
                            return;
                        }
                    }

                    //player 1 Jumping button
                    if (e.key.code == Keyboard::W && player1.grounded == true && !player1.attackbool && !player1.hitbool && !Round_Trans) {
                        timer = 0;
                        playerindex = 0;
                        player1.velocity.y = -10;
                        player1.sprite.move(0, player1.velocity.y - Jumpheight);
                    }

                    //Player 1 Attacking button
                    if (e.key.code == Keyboard::X && player1.grounded == true && !player1.attackbool && !Round_Trans) {
                        player1.attackbool = true;
                        attacktimer = 0;
                        attackindex = 0;
                        //Attacksound.play();
                        if (intersection(player1.hitbox.attack, player2.hitbox.player) && player1.attackbool && !player1.hitbool) {
                            player2.health -= 20;
                            player2.hitbool = true;
                            hittimer2 = 0.3f;
                            arr_index = update_healthbar(player2.health);
                            if (arr_index != -1)
                            {
                                P2_HealthBar_Texture = hp_bar[arr_index];
                                p2_healthBar.setTexture(&P2_HealthBar_Texture);
                            }
                        }
                    }


                    //Death Animation & Round transition
                    if ((player2.health == 0 && win2 < 2 && win1 < 2) || (player1.health == 0 && win2 < 2 && win1 < 2))
                    {
                        Round_Trans = true;
                        if (roundelay < 0 && e.key.code == Keyboard::Enter)
                        {
                            Deathindex = 0;
                            if (player2.health == 0) {
                                cout << "p1 wins this round\n";
                                win1++;
                            }
                            else if (player1.health == 0) {
                                cout << "p2 wins this round\n";
                                win2++;
                            }
                            roundelay = 5.0f;
                            Round_Trans = false;
                            player1.health = 100;
                            player2.health = 100;
                            player1.sprite.setColor(Color::White);
                            player2.sprite.setColor(Color::White);
                            game(win1, win2, window);
                            Round_Trans = false;
                            return;
                        }
                    }

                    //player 2 Jumping button
                    if (e.key.code == Keyboard::Up && player2.grounded == true && !player2.attackbool && !player2.hitbool && !Round_Trans) {
                        timer2 = 0;
                        index2 = 0;
                        player2.velocity.y = -10;
                        player2.sprite.move(0, player2.velocity.y - Jumpheight);
                    }

                    //Player 2 Attacking button
                    if (e.key.code == Keyboard::J && player2.grounded == true && !player2.attackbool && !player2.hitbool && !Round_Trans) {
                        player2.attackbool = true;
                        attacktimer2 = 0;
                        attackindex2 = 0;
                        //Attacksound.play();
                        if (intersection(player2.hitbox.attack, player1.hitbox.player) && player2.attackbool) {
                            player1.health -= 20;
                            player1.hitbool = true;
                            hittimer = 0.3f;
                            arr_index = update_healthbar(player1.health);
                            if (arr_index != -1)
                            {
                                P1_HealthBar_Texture = hp_bar[arr_index];
                                p1_healthBar.setTexture(&P1_HealthBar_Texture);
                            }
                        }
                    }
                }

            }

            //Round Transition & Death
            if ((player2.health == 0 && win2 < 2 && win1 < 2) || (player1.health == 0 && win2 < 2 && win1 < 2))
            {
                roundelay -= deltatime;
                if (player1.health == 0) {
                    player1.sprite.setTexture(Death);
                    player1.sprite.setColor(Color(128, 0, 0));
                    if (timer <= 0) {
                        if (Deathindex != 9)
                            Deathindex++;
                        Deathindex = Deathindex % 10;
                        player1.sprite.setTextureRect(IntRect((Deathindex * 120), 0, 120, 80));
                        timer = delay;
                    }
                    else
                        timer -= deltatime;
                }
                if (player2.health == 0) {
                    player2.sprite.setColor(Color(128, 0, 0));
                    player2.sprite.setTexture(Death2);
                    if (timer2 <= 0) {
                        if (Deathindex != 9)
                            Deathindex++;
                        Deathindex = Deathindex % 10;
                        player2.sprite.setTextureRect(IntRect((Deathindex * 120), 0, 120, 80));
                        timer2 = delay2;
                    }
                    else
                        timer2 -= deltatime;
                }
            }

            //PLAYER 1

            //Gravity movement
            player1.sprite.move(0, player1.velocity.y);

            //Hitboxes live positioning
            player1.hitbox.player.setPosition(player1.sprite.getPosition().x, player1.sprite.getPosition().y);
            player1.hitbox.attack.setPosition(player1.sprite.getPosition().x, player1.sprite.getPosition().y);

            //Return deafult color
            if (!player1.hitbool && player1.health > 0)
                player1.sprite.setColor(Color::White);

            //Death if Fell
            if (player1.hitbox.player.getPosition().y > window.getSize().y)
            {
                player1.health = 0;
                arr_index = update_healthbar(player1.health);
                if (arr_index != -1)
                {
                    P1_HealthBar_Texture = hp_bar[arr_index];
                    p1_healthBar.setTexture(&P1_HealthBar_Texture);
                }
            }

            //Gravity and Plates
            if (((platecoliode_1(player1.sprite, player1.hitbox.player, plt1.platrec))
                || (platecoliode_1(player1.sprite, player1.hitbox.player, plt2.platrec))
                || (platecoliode_1(player1.sprite, player1.hitbox.player, plt3.platrec))
                || (platecoliode_1(player1.sprite, player1.hitbox.player, plt4.platrec))
                || (platecoliode_1(player1.sprite, player1.hitbox.player, plt5.platrec))
                || player1.hitbox.player.getPosition().y > window.getSize().y)
                && player1.velocity.y >= 0)
            {
                player1.timereset = false;
                player1.velocity.y = 0;
                player1.grounded = true;
                if (player1.health > 0 && !player1.attackbool) {
                    player1.sprite.setTexture(Idle);
                    if (timer <= 0) {
                        playerindex++;
                        playerindex = playerindex % 10;
                        player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                        timer = delay;
                    }
                    else
                        timer -= deltatime;
                }
            }
            else if (!PAUSE && player1.hitbox.player.getPosition().y <= window.getSize().y) {
                if (!player1.timereset) {
                    player1.timereset = true;
                    timer = 0;
                    playerindex = 0;
                }
                player1.grounded = false;
                player1.velocity.y -= Gravity * deltatime;
            }



            //Jumping animation
            if (player1.velocity.y < 0) {
                player1.sprite.setTexture(Jumping);
                if (timer <= 0) {
                    playerindex++;
                    playerindex = playerindex % 3;
                    player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                    timer = delay + 0.15f;
                }
                else
                    timer -= deltatime;
            }

            //Falling animation
            if (player1.velocity.y >= 0 && !player1.grounded) {
                player1.sprite.setTexture(Fall);
                if (timer <= 0) {
                    playerindex++;
                    playerindex = playerindex % 3;
                    player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                    timer = delay + 0.15f;
                }
                else
                    timer -= deltatime;
            }

            //Being Hit
            if (player1.hitbool == true) {
                player1.sprite.setTexture(Hit);
                player1.sprite.setColor(Color::Red);
                player1.sprite.setTextureRect(IntRect(0, 0, 120, 80));
                if (hittimer <= 0)
                {
                    player1.hitbool = false;
                }
                else
                    hittimer -= deltatime;
            }

            //I put everything in else so it cannot be done at the same time
            else
            {
                //Attack & Movement
                if (player1.attackbool == true) {
                    player1.sprite.setTexture(Attacking);

                    //Attacking Animation
                    if (attacktimer <= 0) {
                        attackindex++;
                        attackindex = attackindex % 4;
                        player1.sprite.setTextureRect(IntRect((attackindex * 120), 0, 120, 80));
                        attacktimer = attackdelay;
                        if (attackindex == 0)
                            player1.attackbool = false;
                    }
                    else {
                        attacktimer -= deltatime;
                    }
                }
                //I put everything in else so it cannot be done at the same time
                else
                {
                    //Moving right
                    if (Keyboard::isKeyPressed(Keyboard::D) && player1.sprite.getPosition().x < (window.getSize().x - player1.sprite.getGlobalBounds().width / 100) && !Round_Trans) {
                        player1.sprite.setScale(3, 3);
                        player1.hitbox.attack.setScale(1, 1);
                        if (player1.grounded == true) {
                            player1.sprite.setTexture(Running);
                            if (timer <= 0)
                            {
                                playerindex++;
                                playerindex = playerindex % 10;
                                player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                                timer = delay - 0.05f;
                            }
                            else
                                timer -= deltatime;
                        }
                        player1.sprite.move(500 * deltatime, 0);
                    }
                    //Moving left
                    if (Keyboard::isKeyPressed(Keyboard::A) && player1.sprite.getPosition().x > 0 && !Round_Trans) {
                        player1.sprite.setScale(-3, 3);
                        player1.hitbox.attack.setScale(-1, 1);
                        if (player1.grounded == true) {
                            player1.sprite.setTexture(Running);
                            if (timer <= 0)
                            {
                                playerindex++;
                                playerindex = playerindex % 10;
                                player1.sprite.setTextureRect(IntRect((playerindex * 120), 0, 120, 80));
                                timer = delay - 0.05f;
                            }
                            else
                                timer -= deltatime;
                        }
                        player1.sprite.move(-500 * deltatime, 0);
                    }
                }
            }




            //PLAYER 2

            //Gravity movement
            player2.sprite.move(0, player2.velocity.y);

            //Hitboxes live positioning
            player2.hitbox.player.setPosition(player2.sprite.getPosition().x, player2.sprite.getPosition().y);
            player2.hitbox.attack.setPosition(player2.sprite.getPosition().x, player2.sprite.getPosition().y);

            //Return deafult color
            if (!player2.hitbool && player2.health > 0)
                player2.sprite.setColor(Color::White);

            //Death if Fell
            if (player2.hitbox.player.getPosition().y > window.getSize().y)
            {
                player2.health = 0;
                arr_index = update_healthbar(player2.health);
                if (arr_index != -1)
                {
                    P2_HealthBar_Texture = hp_bar[arr_index];
                    p2_healthBar.setTexture(&P2_HealthBar_Texture);
                }
            }

            //player 2 gravity and plates
            if (((platecoliode_1(player2.sprite, player2.hitbox.player, plt1.platrec))
                || (platecoliode_1(player2.sprite, player2.hitbox.player, plt2.platrec))
                || (platecoliode_1(player2.sprite, player2.hitbox.player, plt3.platrec))
                || (platecoliode_1(player2.sprite, player2.hitbox.player, plt4.platrec))
                || (platecoliode_1(player2.sprite, player2.hitbox.player, plt5.platrec))
                || player2.hitbox.player.getPosition().y > window.getSize().y)
                && player2.velocity.y >= 0)
            {
                player2.velocity.y = 0;
                player2.timereset = false;
                player2.grounded = true;
                if (player2.health > 00 && !player2.attackbool) {
                    player2.sprite.setTexture(Idle2);
                    // animation breath player 2
                    if (timer2 <= 0) {
                        index2++;
                        index2 = index2 % 10;
                        player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                        timer2 = delay;
                    }
                    else
                        timer2 -= deltatime;
                }
            }
            else if (!PAUSE && player2.hitbox.player.getPosition().y <= window.getSize().y)
            {
                if (!player2.timereset) {
                    player2.timereset = true;
                    timer2 = 0;
                    index2 = 0;
                }
                player2.grounded = false;
                player2.velocity.y -= Gravity * deltatime;
            }

            //Jumping animation
            if (player2.velocity.y < 0) {
                player2.sprite.setTexture(Jumping2);
                if (timer2 <= 0) {
                    index2++;
                    index2 = index2 % 3;
                    player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                    timer2 = delay2 + 0.15;
                }
                else
                    timer2 -= deltatime;
            }

            //Falling animation
            if (player2.velocity.y >= 0 && !player2.grounded) {
                player2.sprite.setTexture(Fall2);
                if (timer2 <= 0) {
                    index2++;
                    index2 = index2 % 3;
                    player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                    timer2 = delay2 + 0.15;
                }
                else
                    timer2 -= deltatime;
            }

            //Being hit
            if (player2.hitbool == true) {
                player2.sprite.setTexture(Hit2);
                player2.sprite.setColor(Color::Red);
                player2.sprite.setTextureRect(IntRect(0, 0, 120, 80));
                if (hittimer2 <= 0)
                {
                    player2.hitbool = false;
                }
                else
                    hittimer2 -= deltatime;
            }

            //I put everything in else so it cannot be done at the same time
            else
            {
                //Attack & Movement
                if (player2.attackbool == true) {
                    player2.sprite.setTexture(Attacking2);

                    //Attacking Animation
                    if (attacktimer2 <= 0) {
                        attackindex2++;
                        attackindex2 = attackindex2 % 4;
                        player2.sprite.setTextureRect(IntRect((attackindex2 * 120), 0, 120, 80));
                        attacktimer2 = attackdelay2;
                        if (attackindex2 == 0) {
                            player2.attackbool = false;
                        }

                    }
                    else {
                        attacktimer2 -= deltatime;
                    }
                }
                //I put everything in else so it cannot be done at the same time
                else
                {
                    //Moving right
                    if (Keyboard::isKeyPressed(Keyboard::Right) && player2.sprite.getPosition().x < (window.getSize().x - player2.sprite.getGlobalBounds().width / 100) && !Round_Trans) {
                        player2.sprite.setScale(3, 3);
                        player2.hitbox.attack.setScale(1, 1);
                        if (player2.grounded == true) {
                            player2.sprite.setTexture(Running2);
                            if (timer2 <= 0)
                            {
                                index2++;
                                index2 = index2 % 10;
                                player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                                timer2 = delay2 - 0.05f;
                            }
                            else
                                timer2 -= deltatime;
                        }
                        player2.sprite.move(500 * deltatime, 0);
                    }
                    //Moving left
                    if (Keyboard::isKeyPressed(Keyboard::Left) && player2.sprite.getPosition().x > 0 && !Round_Trans) {
                        player2.sprite.setScale(-3, 3);
                        player2.hitbox.attack.setScale(-1, 1);
                        if (player2.grounded == true) {
                            player2.sprite.setTexture(Running2);
                            if (timer2 <= 0)
                            {
                                index2++;
                                index2 = index2 % 10;
                                player2.sprite.setTextureRect(IntRect((index2 * 120), 0, 120, 80));
                                timer2 = delay2 - 0.05f;
                            }
                            else
                                timer2 -= deltatime;
                        }
                        player2.sprite.move(-500 * deltatime, 0);
                    }
                }
            }

            window.clear();
            window.draw(player1.hitbox.attack);
            window.draw(player2.hitbox.attack);
            window.draw(player1.hitbox.player);
            window.draw(player2.hitbox.player);
            window.draw(background);
            window.draw(plt1.platrec);
            window.draw(plt2.platrec);
            window.draw(plt3.platrec);
            window.draw(plt4.platrec);
            window.draw(plt5.platrec);
            window.draw(p1_healthBar);
            window.draw(p2_healthBar);
            window.draw(player1.sprite);
            window.draw(player2.sprite);
            window.display();
            deltatime = gameclock.getElapsedTime().asSeconds();
        }
    }
}