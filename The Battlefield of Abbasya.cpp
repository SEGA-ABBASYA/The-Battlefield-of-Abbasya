#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/window.hpp>
#include <vector>
#include <time.h>
#include <string>
#include <cstdlib>
// #include "ResourcePath.hpp"

using namespace sf;
using namespace std;
// string path = "/Users/yoyo/#COLLEGE/The-Battlefield-of-Abbasya/";
// string path = resourcePath();
 string path = "";

// 0  -> MainMenu
// 1  -> Choose Your Hero
// 2  -> Options
// 3  -> Credits
// ESC  -> PauseMen
// 4  -> Close

//Global Variables
Clock gameclock;
float Gravity = -20.0f;
float Jumpheight = 150.0f;
float deltatime = 0.0f;
int playerindex = 0;
int Deathindex = 0;
float timer = 0.0f;
float delay = 0.15f;
float roundelay = 1.0f;
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
bool Round_Interacting = false;
int volume_ = 100;
bool name__ = false;
Sprite vol_arr[11];
Font menufont;
Texture optionButton;
Texture optionButton2;
string arrayOfInteractions[100];

struct cursor
{
    Texture texture;
    Sprite sprite;

    cursor()
    {
        // Load the cursor texture
        texture.loadFromFile(path + "cursor.png");

        // Create the cursor sprite
        sprite.setTexture(texture);
        sprite.setScale(2, 2);
        sprite.setOrigin(texture.getSize().x / 15, texture.getSize().y / 15);
    }

    void draw(RenderWindow &window)
    {
        // Set the cursor sprite's position to the mouse position
        sprite.setPosition(Vector2f(Mouse::getPosition(window)));
        // Set the mouse cursor to be hidden
        window.setMouseCursorVisible(false);
        // Draw the cursor sprite
        window.draw(sprite);
    }
} cur;
struct Hitbox
{
    RectangleShape attack;
    RectangleShape player;

    // function for setting the properties of a hitbox
    void sethitbox(Sprite &w, RectangleShape &x, float y, float z, Color l)
    {
        x.setSize(Vector2f(y, z));
        x.setFillColor(l);
        x.setPosition(w.getPosition().x, w.getPosition().y + 10);
        x.setOrigin(y / 2, -6);
    }
};
struct player
{
    string name;
    int health = 100;
    Vector2f velocity{0, 0};
    Sprite sprite;
    Hitbox hitbox;
    bool grounded = false, attackbool = false, hitbool = false, timereset = false;
    Text Round_won[3];
}player1, player2;
struct plates {
    RectangleShape platrec;

    // function for setting the properties of the plates
    void plat_set(Texture &imag, RectangleShape &sh_1, float x1, float x2, int x3, int x4, int x5, int x6)
    {
        sh_1.setSize(Vector2f(x1, x2));
        sh_1.setPosition(x3, x4);
        sh_1.setTexture(&imag);
        sh_1.setScale(x5, x6);
    }
} plt1, plt2, plt3, plt4, plt5, plt6;


//powerups

RectangleShape Powers_sp[3];
Texture Powers_tex[3];
Clock timerpow;
void power_draw()
{
    Powers_sp[0].setSize(Vector2f(100, 100));
    Powers_sp[1].setSize(Vector2f(100, 100));
    Powers_sp[2].setSize(Vector2f(100, 100));

    Powers_tex[0].loadFromFile("attack.png");
    Powers_tex[1].loadFromFile("attack.png");
    Powers_tex[2].loadFromFile("heal.png");


    for (int i = 0; i < 3; i++)
    {
        Powers_sp[i].setTexture(&Powers_tex[i]);
    }
    Powers_sp[0].setOrigin(50, 50);
    Powers_sp[1].setOrigin(50, 50);
    Powers_sp[2].setOrigin(50, 50);

}
/*bool powercoliodeattack(Sprite& player, RectangleShape& player_x, Sprite& Powers)
{
    if (player_x.getGlobalBounds().intersects(Powers.getGlobalBounds()))
    {
        toucher=false;
        return true;

    }
    else {
        return false;
    }
}*/
bool powercoliodeheal(Sprite& player, RectangleShape& player_x, Sprite& Powers)
{
    if (player_x.getGlobalBounds().intersects(Powers.getGlobalBounds()))
    {
        Powers.setScale(0, 0);
        return true;

    }
    else {
        return false;
    }
}

// power end


struct interactionWindow 
{
private:
    Vector2f frameScale;
    Sprite frameSprite;
    Texture frameTexture;

    Font arcadeClassic;
    string final_string;
    string displayed_text;
    Text textToBeDisplayed;

    Text pressSpaceToSkip;
    string player_name;

    bool aborted = false;
    void setInteractions(string arr[])
    {
        arr[0] = "el salamo 3alekom wa \nrahmat allah w barakato";
        arr[1] = "Aboos Edak Er7mny";
        arr[2] = "I am delighted to be here";
        arr[3] = "You may not indure the \nslays of my mighty sword";
        arr[4] = "May the odds be in your \nfavor";
        arr[5] = "I'm not a king \nI'm not a god \nI AM WORSE";
        arr[6] = "";
        arr[7] = "";
        arr[8] = "";
        arr[9] = "";
        arr[10] = "";
        arr[11] = "";
    }

public:
    int no_of_interactions = 6;
    int max_letters_per_line = 27;
    float timer_per_letter = 0.1;

    bool finishedInteracting = false;
    bool deletingWindow = false;
    bool isActive = false;
    // constructor
    void interactionSetProp(string interactions[], string plyr_nam, float xPos, float yPos)
    {
        //cout << "constructed" << endl;
        // the constructor initiates the window at a zero size, then it enlarged in the update function

        // initialize the array of text interactions
        setInteractions(interactions);

        // loads textures
        frameTexture.loadFromFile(path + "TextBox.png");
        frameSprite.setTexture(frameTexture);

        // set positions (!!THEY MUST BE SET IN THAT ORDER!!!)
        // frameSprite.setPosition(300, 200);
        frameSprite.setPosition(xPos, yPos);
        textToBeDisplayed.setPosition(frameSprite.getPosition().x - 200, frameSprite.getPosition().y - 60);
        textToBeDisplayed.setFillColor(Color::Black);
        frameSprite.setOrigin(250, 250);

        pressSpaceToSkip.setPosition(310, 633);
        pressSpaceToSkip.setScale(2, 2);

        // set initial scales
        frameSprite.setScale(0, 0);

        // set final scales
        frameScale = {1, 1};

        // loads font and initial/Applications/Visual Studio Code.app/Contents/Resources/app/out/vs/code/electron-sandbox/workbench/workbench.htmlizes text
        arcadeClassic.loadFromFile(path + "Canterbury.ttf");
        textToBeDisplayed.setFont(arcadeClassic);
        pressSpaceToSkip.setFont(arcadeClassic);
        pressSpaceToSkip.setString("Press Space To Skip");
        // pressSpaceToSkip.setColor(Color::White);
        displayed_text = "";

        player_name = plyr_nam;

        // takes a random interaction out of the interactions array
        int randomNumb = rand() % no_of_interactions;
        final_string = plyr_nam + ' ' + ':' + "\n" + interactions[randomNumb];
        // textToBeDisplayed.setString(final_string); 
        textToBeDisplayed.setString(displayed_text);
    }

    // update functions: gradually scales window, then gradually scales icon, then gradually shows text
private:
    int text_index = 0;
    float textTimer = 0.1;
    float pauseTimer = 2.5;
    int lettersPerLine = 0;
    int flutter_timer = 20;
    bool isSkipTextShown = true;

public:
    void update(float deltatime, RenderWindow &window)
    {



        // cout << "update of interaction got called\n";
        float scale_offset = 2;
        float descale_offset = 2;

        // if(finishedInteracting)
        //     cout << "finished interacting\n";
        // else
        //     cout << "not finished interacting\n";

        // if the window isnt big enough yet, it gets scaled
        if (frameSprite.getScale().x < frameScale.x and frameSprite.getScale().y < frameScale.y and !deletingWindow and !aborted)
        {
            // cout << "deltatime: " << deltatime << endl;
            // cout << "frame current scale: " << frameSprite.getScale().x;
            // adds a slight increase to the scale every frame relative to delatatime
            frameSprite.setScale({frameSprite.getScale().x + scale_offset * deltatime, frameSprite.getScale().y + scale_offset * deltatime});
            // cout << "  frame new scale: " << frameSprite.getScale().x << endl;
        }

        // if both window is scaled, we start displaying the text gradually
        else
        {
            // if not all of string have been displayed
            if (text_index < final_string.length() and !aborted)
            {
                if (textTimer <= 0)
                {
                    displayed_text = displayed_text + final_string[text_index];
                    textToBeDisplayed.setString(displayed_text);
                    text_index++;
                    lettersPerLine++;

                    // resets timer
                    textTimer = timer_per_letter;

                }
                else
                    textTimer -= deltatime;
            }
            // if all has been displayed, starts timer, and when it ends, it destroys the window
            else
            {
                if (pauseTimer <= 0 or aborted)
                {
                    deletingWindow = true;
                    // if not , plays reverse animation for shrinking
                    if (frameSprite.getScale().x > 0 and frameSprite.getScale().y > 0 and !finishedInteracting)
                    {
                        frameSprite.setScale({frameSprite.getScale().x - descale_offset * deltatime, frameSprite.getScale().y - descale_offset * deltatime});
                        // cout << "  frame new scale: " << frameSprite.getScale().x << "  delatatime: " << deltatime << endl;

                        // textToBeDisplayed.setScale({textToBeDisplayed.getScale().x - scale_offset * deltatime, textToBeDisplayed.getScale().y - scale_offset * deltatime});
                        textToBeDisplayed.setScale(0, 0);
                    }
                    // if finished shrinking, destroys and marks the bool as true for external use
                    else if (frameSprite.getScale().x <= 0 or frameSprite.getScale().y <= 0)
                    {
                        frameSprite.setScale(0, 0);
                        // playerIconSprite.setScale(0, 0);
                        textToBeDisplayed.setScale(0, 0);
                        finishedInteracting = true;
                    }
                }
                else
                    pauseTimer -= deltatime;
            }
        }

        // window.draw(frameSprite);
        // window.draw(playerIconSprite);
        // window.draw(textToBeDisplayed);
    }
    void draw(RenderWindow &window)
    {
        if (!finishedInteracting)
        {
            // flutters the press to skip text
            if(!aborted)
            {
                if (flutter_timer <= 0)
                {
                    if (isSkipTextShown)
                    {
                        isSkipTextShown = false;
                    }
                    else
                        isSkipTextShown = true;

                    flutter_timer = 20;
                }
                else
                {
                    if (isSkipTextShown)
                    {
                        window.draw(pressSpaceToSkip);
                    }
                    flutter_timer -= deltatime;
                }
            }

            window.draw(frameSprite);
            // window.draw(playerIconSprite);
            window.draw(textToBeDisplayed);
            // window.draw(pressSpaceToSkip);
        }
    }

    void abort()
    {
        aborted = true;
    }
    // destroy window
    void destroyInteractionWindow()
    {
        frameSprite.setScale(0, 0);
        // playerIconSprite.setScale(0, 0);
        textToBeDisplayed.setScale(0, 0);
        // finishedInteracting = true;
    }
}interactionwindow1,interactionWindow2;

int cursor_select(Text *arr, RectangleShape *Buttonarr, RenderWindow &mywindow)
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

void setTextprop(Text& text , int x,int y) {
    menufont.loadFromFile("Canterbury.ttf");
    text.setCharacterSize(x);
    text.setFillColor(Color(187, 220, 244));
    text.setFont(menufont);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(y);
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
}

int cursor_select_pause(Text* arr, RectangleShape* Buttonarr, RenderWindow& mywindow)
{
    Mouse mouse;
    for (int i = 0; i < 4; i++)
    {

        if (Buttonarr[i].getGlobalBounds().contains(mouse.getPosition(mywindow).x, mouse.getPosition(mywindow).y))
        {
            arr[i+1].setFillColor(Color::White);
            Buttonarr[i].setScale(1.1f, 1.1f);


            if (Mouse::isButtonPressed(Mouse::Left))
            {
                Buttonarr[i].setScale(1.f, 1.f);
                arr[i+1].setFillColor(Color{ 245,176,38 });
                return i;
            }
        }
        else
        {
            Buttonarr[i].setScale(1.f, 1.f);
            arr[i+1].setFillColor(Color{ 245,176,38 });
        }
    }
    //return 0;
}

void Controlls(RenderWindow& controllswindow)
{
    Texture controll_back;
    controll_back.loadFromFile("controlls back.png");
    Sprite back;
    back.setTexture(controll_back);
    Texture Pause;
    Pause.loadFromFile("Controlls/pause.png");
    Sprite pause;
    pause.setTexture(Pause);
    pause.setScale(0.1, 0.1);
    pause.setPosition(1000, 320);

    Texture Jumping,Jumping2,Running2,Running,Attacking,Attacking2,idle1,idle2,frames[2],buttons[9];

    frames[0].loadFromFile("Controlls/controlls_banner.png");
    frames[1].loadFromFile("Controlls/controlls_main.png");
    idle1.loadFromFile("Name Entry/_Idle1 1.png");
    idle2.loadFromFile("Name Entry/_Idle2 1.png");
    buttons[0].loadFromFile("Controlls/A.png");
    buttons[1].loadFromFile("Controlls/D.png");
    buttons[2].loadFromFile("Controlls/W.png");
    buttons[3].loadFromFile("Controlls/X.png");
    buttons[4].loadFromFile("Controlls/up.png");
    buttons[5].loadFromFile("Controlls/J.png");
    buttons[6].loadFromFile("Controlls/right.png");
    buttons[7].loadFromFile("Controlls/left.png");
    buttons[8].loadFromFile("Controlls/ESC.png");
    Running2.loadFromFile("Player 2/Run2.png");
    Running.loadFromFile("Player 1/Running Animation.png");
    Jumping.loadFromFile("Player 1/_Jump.png");
    Jumping2.loadFromFile("Player 2/Jump2.png");
    Attacking.loadFromFile("Player 1/_Attack.png");
    Attacking2.loadFromFile("Player 2/Attack2.png");

    Sprite jumping1, attacking1, running1r, jumping2, attacking2, running2r, running2l, running1l, Idle1, Idle2;
    Sprite button[9];
    Sprite frame[2];
    Mouse mouse;

    Idle1.setTexture(idle1);
    Idle2.setTexture(idle2);
    jumping1.setTexture(Jumping);
    attacking1.setTexture(Attacking);
    running1r.setTexture(Running);
    running1l.setTexture(Running);
    jumping2.setTexture(Jumping2);
    attacking2.setTexture(Attacking2);
    running2r.setTexture(Running2);
    running2l.setTexture(Running2);
    frame[0].setTexture(frames[0]);
    frame[1].setTexture(frames[1]);
    for (int i = 0; i < 9; i++) {
        button[i].setTexture(buttons[i]);
    }
    jumping1.setTextureRect(IntRect(0, 0, 120, 80));
    jumping2.setTextureRect(IntRect(0, 0, 120, 80));
    attacking1.setTextureRect(IntRect((3 * 120), 0, 120, 80));
    attacking2.setTextureRect(IntRect((3 * 120), 0, 120, 80));
    running1r.setTextureRect(IntRect(0, 0, 120, 80));
    running1l.setTextureRect(IntRect(0, 0, 120, 80));
    running2r.setTextureRect(IntRect(0, 0, 120, 80));
    running2l.setTextureRect(IntRect(0, 0, 120, 80));

    frame[0].setOrigin(204, 0);
    frame[0].setPosition(controllswindow.getSize().x / 2, 0);
    frame[0].setScale(0.8, 0.8);
    frame[1].setOrigin(201, 0);
    frame[1].setPosition(1150, 500);
    frame[1].setScale(0.75, 0.75);


    button[0].setScale(3.5, 3.5);
    button[0].setPosition(290, 450);
    button[1].setScale(3.5, 3.5);
    button[1].setPosition(290, 360);
    button[2].setScale(3.5, 3.5);
    button[2].setPosition(290, 540);
    button[3].setScale(3.5, 3.5);
    button[3].setPosition(290, 650);
    button[4].setScale(3.5, 3.5);
    button[4].setPosition(710, 540);
    button[5].setScale(3.5, 3.5);
    button[5].setPosition(710, 650);
    button[6].setScale(3.5, 3.5);
    button[6].setPosition(710, 360);
    button[7].setScale(3.5, 3.5);
    button[7].setPosition(710, 450);
    button[8].setScale(3.5, 3.5);
    button[8].setPosition(1140, 345);


    jumping1.setScale(2, 2);
    jumping1.setPosition(100, 450);
    jumping2.setScale(2, 2);
    jumping2.setPosition(520, 450);
    attacking1.setScale(2, 2);
    attacking1.setPosition(70, 550);
    attacking2.setScale(2, 2);
    attacking2.setPosition(490, 550);
    running1r.setScale(2, 2);
    running1r.setPosition(100, 260);
    running1l.setScale(-2, 2);
    running1l.setPosition(325, 350);
    running2r.setScale(2, 2);
    running2r.setPosition(520, 260);
    running2l.setScale(-2, 2);
    running2l.setPosition(750, 350);
    Idle1.setScale(0.7, 0.7);
    Idle1.setPosition(250, 80);
    Idle2.setScale(0.7, 0.7);
    Idle2.setPosition(650, 70);
    
    Font controllsfont;
    controllsfont.loadFromFile("Canterbury.ttf");
    Text controlls[13];

    controlls[0].setFont(controllsfont);
    controlls[0].setString("Controllers");
    controlls[0].setCharacterSize(45);
    controlls[0].setFillColor(Color{ 255,204,0 });
    controlls[0].setPosition((controllswindow.getSize().x / 2)-80, 55);

    controlls[1].setFont(controllsfont);
    controlls[1].setString("Player 1");
    controlls[1].setCharacterSize(60);
    controlls[1].setFillColor(Color{ 255,204,0 });
    controlls[1].setPosition(30, 200);

    controlls[2].setFont(controllsfont);
    controlls[2].setString("Player 2");
    controlls[2].setCharacterSize(60);
    controlls[2].setFillColor(Color{ 255,204,0 });
    controlls[2].setPosition(450, 200);

    controlls[3].setFont(controllsfont);
    controlls[3].setString("Right");
    controlls[3].setCharacterSize(50);
    controlls[3].setFillColor(Color{ 255,204,0 });
    controlls[3].setPosition(30, 350);

    controlls[4].setFont(controllsfont);
    controlls[4].setString("Left");
    controlls[4].setCharacterSize(50);
    controlls[4].setFillColor(Color{ 255,204,0 });
    controlls[4].setPosition(30, 450);

    controlls[5].setFont(controllsfont);
    controlls[5].setString("Jump");
    controlls[5].setCharacterSize(50);
    controlls[5].setFillColor(Color{ 255,204,0 });
    controlls[5].setPosition(30, 550);

    controlls[6].setFont(controllsfont);
    controlls[6].setString("Attack");
    controlls[6].setCharacterSize(50);
    controlls[6].setFillColor(Color{ 255,204,0 });
    controlls[6].setPosition(30, 650);

    controlls[7].setFont(controllsfont);
    controlls[7].setString("Right");
    controlls[7].setCharacterSize(50);
    controlls[7].setFillColor(Color{ 255,204,0 });
    controlls[7].setPosition(450, 350);

    controlls[8].setFont(controllsfont);
    controlls[8].setString("Left");
    controlls[8].setCharacterSize(50);
    controlls[8].setFillColor(Color{ 255,204,0 });
    controlls[8].setPosition(450, 450);

    controlls[9].setFont(controllsfont);
    controlls[9].setString("Jump");
    controlls[9].setCharacterSize(50);
    controlls[9].setFillColor(Color{ 255,204,0 });
    controlls[9].setPosition(450, 550);

    controlls[10].setFont(controllsfont);
    controlls[10].setString("Attack");
    controlls[10].setCharacterSize(50);
    controlls[10].setFillColor(Color{ 255,204,0 });
    controlls[10].setPosition(450, 650);

    controlls[11].setFont(controllsfont);
    controlls[11].setString("Pause");
    controlls[11].setCharacterSize(60);
    controlls[11].setFillColor(Color{ 255,204,0 });
    controlls[11].setPosition(1000, 200);

    controlls[12].setFont(controllsfont);
    controlls[12].setString("Main Menu");
    controlls[12].setCharacterSize(40);
    controlls[12].setFillColor(Color{ 255,204,0 });
    controlls[12].setPosition(1055, 520);


    while (controllswindow.isOpen())
    {

        sf::Event event;
        while (controllswindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                controllswindow.close();
            }

        }

        if (frame[1].getGlobalBounds().contains(mouse.getPosition(controllswindow).x, mouse.getPosition(controllswindow).y)) {

            frame[1].setOrigin(201, 0);
            frame[1].setScale(0.85, 0.85);
            controlls[12].setFillColor(Color::White);

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                return;
            }
        }
        else
        {
            frame[1].setScale(0.75, 0.75);
            controlls[12].setFillColor(Color{ 255,204,0 });

        }

        controllswindow.clear();
        controllswindow.draw(back);
        controllswindow.draw(frame[0]);
        controllswindow.draw(frame[1]);
        controllswindow.draw(pause);
        controllswindow.draw(Idle1);
        controllswindow.draw(Idle2);
        controllswindow.draw(attacking1);
        controllswindow.draw(attacking2);
        controllswindow.draw(jumping1);
        controllswindow.draw(jumping2);
        controllswindow.draw(running1r);
        controllswindow.draw(running2r);
        controllswindow.draw(running1l);
        controllswindow.draw(running2l);
        for (int i = 0; i < 13; i++) {
            controllswindow.draw(controlls[i]);
        }
        for (int j = 0; j < 9; j++) {
            controllswindow.draw(button[j]);
        }

        cur.draw(controllswindow);

        controllswindow.display();
    }
}
void MainMenu(RenderWindow& mainwindow)
{
    // Create the menu items

    Texture ButtonTexture;
    Texture Menuback;
    Texture BorderTex;
    Texture controll1;
    Texture controll2;

    ButtonTexture.loadFromFile("Main Menu/silver_button.png");
    BorderTex.loadFromFile("Main Menu/border.png");
    Menuback.loadFromFile("Main Menu/background main menu.png");
    optionButton.loadFromFile("Main Menu/option1.png");
    optionButton2.loadFromFile("Main Menu/option2.png");
    controll1.loadFromFile("Main Menu/controller_blue.png");
    controll2.loadFromFile("Main Menu/controller_grey.png");


    Text select[6];

    RectangleShape buttons[5];

    Sprite Border;
    Sprite Mainmenu_background;
    Mainmenu_background.setTexture(Menuback);
    Border.setTexture(BorderTex);
    Border.setPosition(mainwindow.getSize().x / 2, 200);
    Border.setOrigin(151, 0);

    for (int i = 1; i < 4; i++)
    {
        buttons[i].setTexture(&ButtonTexture);
        buttons[i].setSize(Vector2f(300.f, 81.f));
        buttons[i].setOrigin(buttons[i].getSize() / 2.f);
    }

    buttons[4].setTexture(&optionButton2);
    buttons[4].setSize(Vector2f(50.f, 50.f));
    buttons[4].setOrigin(buttons[4].getSize() / 2.f);
    buttons[4].setPosition(mainwindow.getSize().x - 60.f, 650);

    Sprite controllbutton;

    
    controllbutton.setTexture(controll1);
    controllbutton.setOrigin(40,0);
    controllbutton.setPosition(70, 620);


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
        setTextprop(select[i],48,1);
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
        Mouse mouse;
        if (controllbutton.getGlobalBounds().contains(mouse.getPosition(mainwindow).x, mouse.getPosition(mainwindow).y))
        {
            controllbutton.setScale(1.1, 1.1);
            controllbutton.setTexture(controll2);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                Controlls(mainwindow);
            }
        }
        else {
            controllbutton.setScale(1, 1);
            controllbutton.setTexture(controll1);

        }
        // Clear the window
        mainwindow.clear();

        //Draw Background Main Menu
        mainwindow.draw(Mainmenu_background);

        // Draw the buttons
        for (int i = 1; i < 5; i++) {
            mainwindow.draw(buttons[i]);
        }

        // Draw Border
        mainwindow.draw(Border);
        mainwindow.draw(controllbutton);
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
void credits_text(Text* arr,RenderWindow& textwindow) {
    Mouse mouse;


    if (arr[1].getGlobalBounds().contains(mouse.getPosition(textwindow).x, mouse.getPosition(textwindow).y))
    {
        arr[1].setFillColor(Color::Blue);
    }
    else {
        arr[1].setFillColor(Color::Black);
    }


    if (arr[2].getGlobalBounds().contains(mouse.getPosition(textwindow).x, mouse.getPosition(textwindow).y))
    {
        arr[2].setFillColor(Color::Cyan);
    }
    else {
        arr[2].setFillColor(Color::Black);
    }

    if (arr[3].getGlobalBounds().contains(mouse.getPosition(textwindow).x, mouse.getPosition(textwindow).y))
    {
        arr[3].setFillColor(Color::Magenta);
    }
    else {
        arr[3].setFillColor(Color::Black);
    }

    if (arr[4].getGlobalBounds().contains(mouse.getPosition(textwindow).x, mouse.getPosition(textwindow).y))
    {
        arr[4].setFillColor(Color::Yellow);
    }
    else {
        arr[4].setFillColor(Color::Black);
    }

    if (arr[5].getGlobalBounds().contains(mouse.getPosition(textwindow).x, mouse.getPosition(textwindow).y))
    {
        arr[5].setFillColor(Color::Green);
    }
    else {
        arr[5].setFillColor(Color::Black);
    }

    if (arr[6].getGlobalBounds().contains(mouse.getPosition(textwindow).x, mouse.getPosition(textwindow).y))
    {
        arr[6].setFillColor(Color{ 255,204,0 });
    }
    else {
        arr[6].setFillColor(Color::Black);
    }
    if (arr[7].getGlobalBounds().contains(mouse.getPosition(textwindow).x, mouse.getPosition(textwindow).y))
    {
        arr[7].setFillColor(Color(187, 220, 244));
    }
    else {
        arr[7].setFillColor(Color::Black);
    }
    
}

void Credits(RenderWindow& creditswindow) {
    Font Credits;
    Credits.loadFromFile("Canterbury.ttf");

    Texture group;
    group.loadFromFile("credit_pic1 1.png");
    Sprite pic;
    pic.setTexture(group);

    Texture frame;
    frame.loadFromFile("main frame1.png");
    Sprite mainframe;
    mainframe.setTexture(frame);

    mainframe.setOrigin(180, 0);
    mainframe.setPosition(1050, 30);
    Text select[8];
    select[0].setFont(Credits);
    select[0].setFillColor(Color::Black);
    select[0].setString("Main Menu");
    select[0].setCharacterSize(60);
    select[0].setPosition(925, 30);

    select[1].setFont(Credits);
    select[1].setString("Abd ElRahman Mustafa");
    select[1].setCharacterSize(40);
    select[1].setFillColor(Color::Black);
    select[1].setPosition(155, 10);

    select[2].setFont(Credits);
    select[2].setFillColor(Color::Black);
    select[2].setString("Abd ElRahman Osama");
    select[2].setCharacterSize(40);
    select[2].setPosition(155, 65);

    select[3].setFont(Credits);
    select[3].setFillColor(Color::Black);
    select[3].setString("Mahmoud Emad");
    select[3].setCharacterSize(40);
    select[3].setPosition(170, 180);

    select[4].setFont(Credits);
    select[4].setFillColor(Color::Black);
    select[4].setString("Yousef Ashraf");
    select[4].setCharacterSize(40);
    select[4].setPosition(600, 10);

    select[5].setFont(Credits);
    select[5].setFillColor(Color::Black);
    select[5].setString("Yousef Ahmed");
    select[5].setCharacterSize(40);
    select[5].setPosition(600, 125);

    select[6].setFont(Credits);
    select[6].setFillColor(Color::Black);
    select[6].setString("Yousef Khataan");
    select[6].setCharacterSize(40);
    select[6].setPosition(600, 65);

    select[7].setFont(Credits);
    select[7].setFillColor(Color::Black);
    select[7].setString("Ziad Khaled Shraf");
    select[7].setCharacterSize(40);
    select[7].setPosition(155, 125);

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
        Mouse mouse;
        if (mainframe.getGlobalBounds().contains(mouse.getPosition(creditswindow).x, mouse.getPosition(creditswindow).y))
        {
            mainframe.setOrigin(180, 0);
            mainframe.setScale(1.1, 1.1);
            select[0].setFillColor(Color::Red);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                return;
            }
        }
        else {
            mainframe.setOrigin(180, 0);
            mainframe.setScale(1, 1);
            select[0].setFillColor(Color::Black);

        }
       
        credits_text(select,creditswindow);
        creditswindow.clear();
       
        creditswindow.draw(pic);
        creditswindow.draw(mainframe);

        for (int i = 0; i < 8; i++) {
            creditswindow.draw(select[i]);
        }

        cur.draw(creditswindow);
    
        creditswindow.display();
    }
}

void game(int win1, int win2, RenderWindow& window);

void game2(int win1, int win2, RenderWindow& game2window);

void Volume(RenderWindow& volumewindow)
{
    Mouse mouse;
    Font volumefont;
    volumefont.loadFromFile("Canterbury.ttf");
    Text volume[2];
    volume[0].setFont(volumefont);
    volume[0].setString("Volume");
    volume[0].setCharacterSize(60);
    volume[0].setFillColor(Color::Black);
    volume[0].setPosition((volumewindow.getSize().x / 2)-85, 20);

    volume[1].setFont(volumefont);
    volume[1].setString("Back");
    volume[1].setCharacterSize(60);
    volume[1].setFillColor(Color::Black);
    volume[1].setPosition(590, 580);

    Texture volume_back;
    volume_back.loadFromFile("Volume Bar/volume background.png");
    Sprite Back;
    Back.setTexture(volume_back);


    Texture buttons[5];
    buttons[0].loadFromFile("Volume Bar/back frame.png");
    buttons[1].loadFromFile("Volume Bar/mute-.png");
    buttons[2].loadFromFile("Volume Bar/volume frame.png");
    buttons[3].loadFromFile("Volume Bar/volume++-.png");
    buttons[4].loadFromFile("Volume Bar/volume--- 1.png");

 
    Sprite button[5];
    for (int i = 0; i < 5; i++) {
        button[i].setTexture(buttons[i]);
    }

    button[0].setOrigin(150, 0);
    button[0].setPosition((volumewindow.getSize().x / 2)+10, 20);
    
    button[1].setOrigin(0, 0);
    button[1].setPosition(volumewindow.getSize().x / 2-50, (volumewindow.getSize().y / 2)+50);

    button[2].setOrigin(140, 0);
    button[2].setPosition(volumewindow.getSize().x / 2, 550);

    button[3].setOrigin(0, 0);
    button[3].setPosition((volumewindow.getSize().x / 2) + 420, (volumewindow.getSize().y / 2) - 90);
    button[3].setScale(0.9, 0.9);

    button[4].setOrigin(44, 0);
    button[4].setPosition((volumewindow.getSize().x / 2) - 500, (volumewindow.getSize().y / 2) - 90);


    Texture vol[11];
    
    vol[10].loadFromFile("Volume Bar/New_HealthBar100.png");
    vol[9].loadFromFile("Volume Bar/New_HealthBar90.png");
    vol[8].loadFromFile("Volume Bar/New_HealthBar80.png");
    vol[7].loadFromFile("Volume Bar/New_HealthBar70.png");
    vol[6].loadFromFile("Volume Bar/New_HealthBar60.png");
    vol[5].loadFromFile("Volume Bar/New_HealthBar50.png");
    vol[4].loadFromFile("Volume Bar/New_HealthBar40.png");
    vol[3].loadFromFile("Volume Bar/New_HealthBar30.png");
    vol[2].loadFromFile("Volume Bar/New_HealthBar20.png");
    vol[1].loadFromFile("Volume Bar/New_HealthBar10.png");
    vol[0].loadFromFile("Volume Bar/New_HealthBar00.png");

    for (int i = 0; i < 11; i++) {
        vol_arr[i].setTexture(vol[i]);
    }

    for (int i = 0; i < 11; i++) {
        vol_arr[i].setScale(1, 1);
        vol_arr[i].setOrigin(vol[i].getSize().x / 2, vol[i].getSize().y / 2);
        vol_arr[i].setPosition(volumewindow.getSize().x / 2, volumewindow.getSize().y / 2-47);

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
            if (button[4].getGlobalBounds().contains(mouse.getPosition(volumewindow).x, mouse.getPosition(volumewindow).y)) {

                button[4].setOrigin(44, 0);
                button[4].setScale(1.1, 1.1);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (volume_ - 10 >= 0)
                        volume_ -= 10;
                }
            }
            else
            {
                button[4].setScale(1, 1);
            }
            
            if (button[3].getGlobalBounds().contains(mouse.getPosition(volumewindow).x, mouse.getPosition(volumewindow).y)) {

                button[3].setOrigin(0, 0);
                button[3].setScale(1, 1);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (volume_ + 10 <= 100)
                        volume_ += 10;
                }
            }
            else
            {
                button[3].setScale(0.9, 0.9);
            }

            if (button[1].getGlobalBounds().contains(mouse.getPosition(volumewindow).x, mouse.getPosition(volumewindow).y)) {

                button[1].setOrigin(0, 0);
                button[1].setScale(1.1, 1.1);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                        volume_ = 0;
                }
            }
            else
            {
                button[1].setScale(1, 1);
                
            }
            if (button[2].getGlobalBounds().contains(mouse.getPosition(volumewindow).x, mouse.getPosition(volumewindow).y)) {

                button[2].setOrigin(140, 0);
                button[2].setScale(1.1, 1.1);
                volume[1].setFillColor(Color::White);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    return;
                }
            }
            else
            {
                button[2].setScale(1, 1);
                volume[1].setFillColor(Color::Black);
            }
        }
        

        volumewindow.clear();

        volumewindow.draw(Back);

        for (int i = 0; i < 5; i++) {
            volumewindow.draw(button[i]);
        }

        for (int i = 0; i < 2; i++) {
            volumewindow.draw(volume[i]);
        }

        int voll = ((volume_) / 10.0);

        volumewindow.draw(vol_arr[voll]);

        cur.draw(volumewindow);

        volumewindow.display();

    }
}



void Options(RenderWindow &optionwindow)
{
    Font optionfont;
    optionfont.loadFromFile(path + "ArcadeClassic.ttf");
    Text option;
    option.setFont(optionfont);
    option.setString("The Battlefield of Abbasya");
    option.setCharacterSize(60);
    option.setFillColor(Color{255, 204, 0});
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

        if (pagenum != 2)
        {
            return;
        }

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

int PauseMenu(RenderWindow &pausewindow)
{
    Font pausefont;
    
    //PAUSE = true;
    pausefont.loadFromFile("Canterbury.ttf");

    Texture Pauseback;
    Texture Pauseborder;
    Texture Buttontex;

    Pauseback.loadFromFile("Pause Menu/Pause Menu Background.png");
    Pauseborder.loadFromFile("Pause Menu/Logo Frame.png");
    Buttontex.loadFromFile("Pause Menu/Gold Button.png");

    RectangleShape buttons[4];

    Sprite Border;
    Sprite Pausemenu_background;
    Pausemenu_background.setTexture(Pauseback);
    Border.setTexture(Pauseborder);
    Border.setOrigin(749 / 2.f, 207 / 2.f);
    Border.setPosition(pausewindow.getSize().x / 2.f, 120);

    for (int i = 0; i < 4; i++) {
        buttons[i].setTexture(&Buttontex);
        buttons[i].setSize(Vector2f(345.f, 81.f));
        buttons[i].setOrigin(buttons[i].getSize() / 2.f);
    }
    
    buttons[0].setPosition(pausewindow.getSize().x / 2.f, 279);

    buttons[1].setPosition(pausewindow.getSize().x / 2.f, 389);

    buttons[2].setPosition(pausewindow.getSize().x / 2.f, 499);

    buttons[3].setPosition(pausewindow.getSize().x / 2.f, 609);

    Text Pause[5];
    Pause[0].setFont(pausefont);
    Pause[0].setString("Pause Menu");
    Pause[0].setCharacterSize(96);
    Pause[0].setFillColor(Color{ 245,176,38 });
    Pause[0].setOutlineColor(Color::Black);
    Pause[0].setOutlineThickness(2);
    Pause[0].setOrigin(Pause[0].getLocalBounds().left + Pause[0].getLocalBounds().width / 2, Pause[0].getLocalBounds().top + Pause[0].getLocalBounds().height / 2);
    Pause[0].setPosition(Border.getPosition());

    Pause[1].setString("Resume");
    Pause[1].setPosition(buttons[0].getPosition());

    Pause[2].setString("Options");
    Pause[2].setPosition(buttons[1].getPosition());

    Pause[3].setString("Main Menu");
    Pause[3].setPosition(buttons[2].getPosition());

    Pause[4].setString("Exit");
    Pause[4].setPosition(buttons[3].getPosition());

    for (int i = 1;i < 5;i++) {
        Pause[i].setFont(pausefont);
        Pause[i].setFillColor(Color{ 245,176,38 });
        Pause[i].setOutlineColor(Color::Black);
        Pause[i].setOutlineThickness(1);
        Pause[i].setCharacterSize(48);
        Pause[i].setOrigin(Pause[i].getLocalBounds().left + Pause[i].getLocalBounds().width / 2, Pause[i].getLocalBounds().top + Pause[i].getLocalBounds().height / 2);
    }

    while (pausewindow.isOpen())
    {
        gameclock.restart();
        Event event;
        while (pausewindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                pausewindow.close();
            }
        }
        page = cursor_select_pause(Pause, buttons, pausewindow);
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            PAUSE = false;
            return 1;
        }
        else if (page == 1) { Volume(pausewindow); }//volume
        else if (page == 0) {
            PAUSE = false;
            return 1;
        }//return 
        else if (page == 2) {
            Round_Trans = false;
            win1 = 0;
            win2 = 0;
            PAUSE = false;
            return 0;
        }//main menu
        else if (page == 3) { pausewindow.close(); }//exit

        pausewindow.clear();
        pausewindow.draw(Pausemenu_background);
        pausewindow.draw(Border);

        for (int i = 0; i < 4; i++) {
            pausewindow.draw(buttons[i]);
        }
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
    nameback.loadFromFile("Name Entry/name enternce.png");
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
    frame[1].setPosition(935, 340);
    frame[2].setOrigin(240, 70);
    frame[2].setPosition(namewindow.getSize().x / 2, 100);
    
    bool name_ = false;

    Font font;
    font.loadFromFile("Canterbury.ttf");

    Text text1("", font);
    Text text2("", font);

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
                if (name1.size() < 12)
                {
                    if (event.type == Event::TextEntered) {
                        if (isprint(event.text.unicode))
                            name1 += event.text.unicode;
                    }
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::BackSpace) {
                        if (!name1.empty())
                            name1.pop_back();
                    }
                    
                }
            }
            if (name_ ) {
                if ( name2.size() < 12)
                {
                    if (event.type == Event::TextEntered)
                    {
                        if (isprint(event.text.unicode))
                            name2 += event.text.unicode;
                    }
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::BackSpace) {
                        if (!name2.empty())
                            name2.pop_back();
                    }
                 
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

        //Text wins
        string fullstring = player1.name + ' ' + "wins";
        string fullstring2 = player2.name + ' ' + "wins";

        for (int i = 0;i < 3;i++) {
            player1.Round_won[i].setString(fullstring);
            player2.Round_won[i].setString(fullstring2);
        }


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

// function for updating health bar according to player's health
int update_healthbar(int health);

// function for setting setting initial properties to a player
void setprop(Sprite &, Texture &, int, int, int);

// function for checking the colliding the hitbox of attack with the hitbox of player
bool intersection(RectangleShape &, RectangleShape &);

// function for checking the colliding the hitbox of player and the plates
bool platecoliode_1(RectangleShape &, RectangleShape &);

Texture hp_bar[12];

int main()
{
    RenderWindow get_window(VideoMode(1280, 720), "The Battlefield of Abbasya");
    
    get_window.setFramerateLimit(60);

    while (get_window.isOpen())
    {
        
        MainMenu(get_window);
        if (pagenum == 0) { MainMenu(get_window); }
        else if (pagenum == 1) {
            player1.name.clear();
            player2.name.clear();
            name__ = true;
            roundelay = 1.0f;
            Round_Trans = false;
            player1.health = 100;
            player2.health = 100;
            player1.sprite.setColor(Color::White);
            player2.sprite.setColor(Color::White);
            Deathindex = 0;
            game(win1, win2, get_window);
        }
        else if (pagenum == 4)
        {
            Volume(get_window);
        }
        else if (pagenum == 2)
        {
            Credits(get_window);
        }
        else if (pagenum == 3)
        {
            get_window.close();
        }
    }
    return 0;
}

// function definition above

void init_health_bar()
{
    
    hp_bar[10].loadFromFile(path + "health_bar/100health.png");
    hp_bar[9].loadFromFile(path + "health_bar/90health.png");
    hp_bar[8].loadFromFile(path + "health_bar/80health.png");
    hp_bar[7].loadFromFile(path + "health_bar/70health.png");
    hp_bar[6].loadFromFile(path + "health_bar/60health.png");
    hp_bar[5].loadFromFile(path + "health_bar/50health.png");
    hp_bar[4].loadFromFile(path + "health_bar/40health.png");
    hp_bar[3].loadFromFile(path + "health_bar/30health.png");
    hp_bar[2].loadFromFile(path + "health_bar/20health.png");
    hp_bar[1].loadFromFile(path + "health_bar/10health.png");
    hp_bar[0].loadFromFile(path + "health_bar/0health.png");

}

int update_healthbar(int health)
{
    if (health == 100) 
    {
        return 10;
    }
    else if (health == 90)
    {
        return 9;
    }
    else if (health == 80)
    {
        return 8;
    }
    else if (health == 70)
    {
        return 7;
    }
    else if (health == 60)
    {
        return 6;
    }
    else if (health == 50)
    {
        return 5;
    }
    else if (health == 40)
    {
        return 4;
    }
    else if (health == 30)
    {
        return 3;
    }
    else if (health == 20)
    {
        return 2;
    }
    else if (health == 10)
    {
        return 1;
    }
    else if (health == 0)
    {
        return 0;
    }
    return -1;
}

void setprop(Sprite &x, Texture &y, int z, int l, int m)
{

    x.setTexture(y);
    x.setOrigin(60, 40);
    x.setPosition(l, m);
    x.setTextureRect(IntRect(0, 0, 120, 80));
    x.setScale(z, 3);
}
void setprop2(RectangleShape& x, Texture& y, float z, float b, float l, float m) {
    x.setTexture(&y);
    x.setOrigin(60, 40);
    x.setPosition(l, m);
    x.setScale(z, b);
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
    else
    {
        return false;
    }
}

void game(int win1, int win2, RenderWindow& window)
{
    int attackpow1 = 0;
    int attackpow2 = 0;
    int healthpow = 0;
    bool toucher = false;
    bool toucher2 = false;
    bool toucherhealthp1 = false;
    bool toucherhealthp2 = false;
    int arr_index = 10;
    srand(time(0));

    // Textures
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

    // setting prop to plates
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
    if (win1 + win2 == 2)
    {
        plt1.plat_set(plateform_1, plt1.platrec, 150, 50, 1000, 450, 0, 0);
        plt2.plat_set(plateform_round3, plt2.platrec, 750, 70, 250, 450, 1, 1);
        plt3.plat_set(plateform_3, plt3.platrec, 150, 50, 100, 450, 0, 0);
        plt4.plat_set(plateform_2, plt4.platrec, 150, 50, 100, 300, 0, 0);
        plt5.plat_set(plateform_3, plt5.platrec, 150, 50, 1000, 300, 0, 0);
    }

    // Player 1 health bar prop
    RectangleShape p1_healthBar(Vector2f(305.f, 100.f));
    p1_healthBar.setScale(1.f, 1.f);
    p1_healthBar.setOrigin(p1_healthBar.getPosition().x / 2, p1_healthBar.getPosition().y / 2);
    P1_HealthBar_Texture = hp_bar[arr_index];
    p1_healthBar.setTexture(&P1_HealthBar_Texture);
    p1_healthBar.setPosition(50, 30);

    // Player 2 health bar prop
    RectangleShape p2_healthBar(Vector2f(305.f, 100.f));
    p2_healthBar.setScale(-1.f, 1.f);
    p2_healthBar.setOrigin(p2_healthBar.getPosition().x / 2, p2_healthBar.getPosition().y / 2);
    P2_HealthBar_Texture = hp_bar[arr_index];
    p2_healthBar.setTexture(&P2_HealthBar_Texture);
    p2_healthBar.setPosition(1230, 30);

    //Players initial prop
    power_draw();
    if (timerpow.getElapsedTime().asSeconds() >= 6) {

    }
    if (win1 + win2 == 0) {
        setprop(player1.sprite, Idle, 3, 320, 480);
        setprop(player2.sprite, Idle2, -3, 960, 480);
        setprop2(Powers_sp[0], Powers_tex[0], 0.5, 0.5, 1075, 425);
        setprop2(Powers_sp[2], Powers_tex[2], 0.5, 0.5, 630, 375);
        setprop2(Powers_sp[1], Powers_tex[1], 0.5, 0.5, 175, 425);

    }
    else if (win1 + win2 == 1)
    {
        setprop(player1.sprite, Idle, 3, 180, 350);
        setprop(player2.sprite, Idle2, -3, 1050, 350);
        setprop2(Powers_sp[0], Powers_tex[0], 0.5, 0.5, 175, 275);
        setprop2(Powers_sp[2], Powers_tex[2], 0.5, 0.5, 635, 375);
        setprop2(Powers_sp[1], Powers_tex[1], 0.5, 0.5, 1075, 275);
    }
    else if (win1 + win2 == 2)
    {
        setprop(player1.sprite, Idle, 3, 330, 150);
        setprop(player2.sprite, Idle2, -3, 900, 150);
        setprop2(Powers_sp[0], Powers_tex[0], 0, 0, rand() % window.getSize().x, rand() % window.getSize().y);
        setprop2(Powers_sp[1], Powers_tex[1], 0, 0, rand() % window.getSize().x, rand() % window.getSize().y);
        setprop2(Powers_sp[2], Powers_tex[2], 0, 0, rand() % window.getSize().x, rand() % window.getSize().y);
    }

    // Hitboxes initial prop
    player1.hitbox.sethitbox(player1.sprite, player1.hitbox.attack, 150.f, 40.f, Color::Yellow);
    player2.hitbox.sethitbox(player2.sprite, player2.hitbox.attack, 150.f, 40.f, Color::Yellow);
    player1.hitbox.sethitbox(player1.sprite, player1.hitbox.player, 50.f, 115.f, Color::Blue);
    player2.hitbox.sethitbox(player2.sprite, player2.hitbox.player, 50.f, 115.f, Color::Blue);
    player1.hitbox.attack.setOrigin(0, 0);
    player2.hitbox.attack.setOrigin(0, 0);

    window.setFramerateLimit(60);


    power_draw();
    while (window.isOpen()) {

        gameclock.restart();
        if (name__) {
            name(player1, window);

            interactionwindow1.interactionSetProp(arrayOfInteractions, player1.name, 300, 200);
            interactionWindow2.interactionSetProp(arrayOfInteractions, player2.name, 1000, 200);
            for (int i = 0;i < 3;i++)
            {
                setTextprop(player1.Round_won[i], 96, 2);
                setTextprop(player2.Round_won[i], 96, 2);
                player1.Round_won[i].setPosition(window.getSize().x / 2, -70);
                player2.Round_won[i].setPosition(window.getSize().x / 2, -70);
            }
        }

        if (!interactionwindow1.finishedInteracting and !interactionWindow2.finishedInteracting and player1.health > 0 and player2.health > 0)
        {
            Round_Interacting = true;
            // cout << "interaction mode on\n";
            interactionwindow1.update(deltatime, window);
        }
        else if (interactionwindow1.finishedInteracting and !interactionWindow2.finishedInteracting and player1.health > 0 and player2.health > 0)
        {
            Round_Interacting = true;
            interactionWindow2.update(deltatime, window);
        }
        else if (interactionwindow1.finishedInteracting and interactionWindow2.finishedInteracting)
        {
            Round_Interacting = false;
            // interactionwindow1.destroyInteractionWindow();
            // cout << "interaction off\n";
        }

        if (!PAUSE)
        {
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                {
                    window.close();
                }
                if (e.type == Event::KeyPressed)
                {
                    if (e.key.code == Keyboard::Escape)
                    {
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
                    if (e.key.code == Keyboard::W && player1.grounded == true && !player1.attackbool && !player1.hitbool && !Round_Trans && !Round_Interacting) {
                        timer = 0;
                        playerindex = 0;
                        player1.velocity.y = -10;
                        player1.sprite.move(0, player1.velocity.y - Jumpheight);
                    }

                    //Player 1 Attacking button
                    if (e.key.code == Keyboard::X && player1.grounded == true && !player1.attackbool && !player1.hitbool && !Round_Trans && !Round_Interacting) {
                        player1.attackbool = true;
                        attacktimer = 0;
                        attackindex = 0;
                        //Attacksound.play();
                        if (intersection(player1.hitbox.attack, player2.hitbox.player) && player1.attackbool) {


                            // Attacksound.play();
                            if (intersection(player1.hitbox.attack, player2.hitbox.player) && player1.attackbool && !player1.hitbool)
                            {
                                if (toucher2 == false || player2.health == 10) {
                                    player2.health -= 10;

                                }
                                else {
                                    player2.health -= attackpow1;
                                }

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
                    }

                        //Death Animation & Round transition
                        if ((player2.health == 0 && win2 < 2 && win1 < 2) || (player1.health == 0 && win2 < 2 && win1 < 2))
                        {
                            Round_Trans = true;
                            if (roundelay < 0 && e.key.code == Keyboard::Enter)
                            {
                                Deathindex = 0;
                                if (player2.health == 0) {
                                    player1.Round_won[win1 + win2].setPosition(player2.Round_won[win1 + win2].getPosition());
                                    win1++;
                                }
                                else if (player1.health == 0) {
                                    player2.Round_won[win1 + win2].setPosition(player1.Round_won[win1 + win2].getPosition());
                                    win2++;
                                }
                                roundelay = 1.0f;
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

                        // player 2 Jumping button
                        if (e.key.code == Keyboard::Up && player2.grounded == true && !player2.attackbool && !player2.hitbool && !Round_Trans && !Round_Interacting)
                        {
                            timer2 = 0;
                            index2 = 0;
                            player2.velocity.y = -10;
                            player2.sprite.move(0, player2.velocity.y - Jumpheight);
                        }


                        //Player 2 Attacking button
                        if (e.key.code == Keyboard::J && player2.grounded == true && !player2.attackbool && !player2.hitbool && !Round_Trans && !Round_Interacting) {
                            player2.attackbool = true;
                            attacktimer2 = 0;
                            attackindex2 = 0;
                            //Attacksound.play();
                            if (intersection(player2.hitbox.attack, player1.hitbox.player) && player2.attackbool) {
                                if (toucher == false || player1.health == 10) {
                                    player1.health -= 10;
                                }
                                else {
                                    player1.health -= attackpow2;
                                }
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

                        // space to stop interacting
                        if (!interactionwindow1.finishedInteracting)
                        {
                            if (e.key.code == Keyboard::Space)
                                interactionwindow1.abort();
                        }
                        if (!interactionWindow2.finishedInteracting)
                        {
                            if (e.key.code == Keyboard::Space)
                                interactionWindow2.abort();
                        }
                    }
                }
                // Round Transition & Death
                if ((player2.health == 0 && win2 < 2 && win1 < 2) || (player1.health == 0 && win2 < 2 && win1 < 2))
                {
                    roundelay -= deltatime;
                    if (player1.health == 0) {
                        if (player2.Round_won[win1 + win2].getPosition().y < window.getSize().y / 4)
                            player2.Round_won[win1 + win2].move(0, 5);
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
                        if (player1.Round_won[win1 + win2].getPosition().y < window.getSize().y / 4)
                            player1.Round_won[win1 + win2].move(0, 5);
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
                for (int i = 0; i < 2; i++) {
                    if (player1.hitbox.player.getGlobalBounds().intersects(Powers_sp[i].getGlobalBounds())) {
                        toucher2 = true;
                        attackpow1 = 20;
                        Powers_sp[i].setPosition(1000, 1000);
                        cout << attackpow1;
                    }
                }

                if (player1.hitbox.player.getGlobalBounds().intersects(Powers_sp[1].getGlobalBounds())) {
                    toucherhealthp1 = true;
                    if (player1.health + 20 <= 100)
                        player1.health += 20;
                    else if (player1.health == 90)
                        player1.health += 10;
                    arr_index = update_healthbar(player1.health);
                    if (arr_index != -1)
                    {
                        P1_HealthBar_Texture = hp_bar[arr_index];
                        p1_healthBar.setTexture(&P1_HealthBar_Texture);
                    }
                }
                for (int i = 0; i < 2; i++) {
                    if (player2.hitbox.player.getGlobalBounds().intersects(Powers_sp[i].getGlobalBounds()))
                    {
                        toucher = true;
                        attackpow2 = 20;
                        Powers_sp[i].setPosition(10000, 10000);
                        cout << "TOUCH";
                    }
                }

                if (player2.hitbox.player.getGlobalBounds().intersects(Powers_sp[2].getGlobalBounds())) {
                    toucherhealthp2 = true;
                    if (player2.health + 20 <= 100)
                        player2.health += 20;
                    else if (player2.health == 90)
                        player2.health += 10;
                    Powers_sp[2].setPosition(1000, 1000);
                    arr_index = update_healthbar(player2.health);
                    if (arr_index != -1)
                    {
                        P2_HealthBar_Texture = hp_bar[arr_index];
                        p2_healthBar.setTexture(&P2_HealthBar_Texture);
                    }
                }
                if (player1.hitbox.player.getGlobalBounds().intersects(Powers_sp[2].getGlobalBounds())) {
                    toucherhealthp1 = true;
                    if (player1.health + 20 <= 100)
                        player1.health += 20;
                    else if (player1.health == 90)
                        player1.health += 10;
                    Powers_sp[2].setPosition(1000, 1000);
                    arr_index = update_healthbar(player1.health);
                    if (arr_index != -1)
                    {
                        P1_HealthBar_Texture = hp_bar[arr_index];
                        p1_healthBar.setTexture(&P1_HealthBar_Texture);
                    }
                }
                //PLAYER 1
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

                // Gravity and Plates
                if (((platecoliode_1(player1.sprite, player1.hitbox.player, plt1.platrec)) || (platecoliode_1(player1.sprite, player1.hitbox.player, plt2.platrec)) || (platecoliode_1(player1.sprite, player1.hitbox.player, plt3.platrec)) || (platecoliode_1(player1.sprite, player1.hitbox.player, plt4.platrec)) || (platecoliode_1(player1.sprite, player1.hitbox.player, plt5.platrec)) || player1.hitbox.player.getPosition().y > window.getSize().y) && player1.velocity.y >= 0)
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
                        if (Keyboard::isKeyPressed(Keyboard::D) && player1.sprite.getPosition().x < (window.getSize().x - player1.sprite.getGlobalBounds().width / 100) && !Round_Trans && !Round_Interacting) {
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
                        if (Keyboard::isKeyPressed(Keyboard::A) && player1.sprite.getPosition().x > 0 && !Round_Trans && !Round_Interacting) {
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
                        if (Keyboard::isKeyPressed(Keyboard::Right) && player2.sprite.getPosition().x < (window.getSize().x - player2.sprite.getGlobalBounds().width / 100) && !Round_Trans && !Round_Interacting) {
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
                        if (Keyboard::isKeyPressed(Keyboard::Left) && player2.sprite.getPosition().x > 0 && !Round_Trans && !Round_Interacting) {
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
                window.draw(player1.hitbox.player);
                window.draw(player2.hitbox.player);
                window.draw(player1.hitbox.attack);
                window.draw(player2.hitbox.attack);
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
                if (timerpow.getElapsedTime().asSeconds() >= 10.0f) {
                    for (int i = 0; i < 3; i++) {
                        window.draw(Powers_sp[i]);
                    }
                }
                interactionwindow1.draw(window);
                interactionWindow2.draw(window);
                for (int i = 0;i < 3;i++)
                {
                    window.draw(player1.Round_won[i]);
                    window.draw(player2.Round_won[i]);
                }
                window.display();
                deltatime = gameclock.getElapsedTime().asSeconds();
         
        }
    }
}
void game2(int win1, int win2, RenderWindow& game2window) {

}