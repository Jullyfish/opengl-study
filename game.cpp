#include <GL/freeglut.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool IS_FULLSCREEN = false;
bool KEYSTATES[256];

class Background
{
    unsigned int texture;
    float vertex[12] = {
        -2, -1, 0,
        2, -1, 0,
        2, 1, 0,
        -2, 1, 0
    };
    float texCoord[8] = {
        0, 1,
        1, 1,
        1, 0,
        0, 0
    };
public:
    void InitTexture();
    void DrawBackground();
};

void Background::InitTexture()
{
    int width, height, cnt;
    unsigned char *data = stbi_load("background1.png", &width, &height, &cnt, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                                    0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

void Background::DrawBackground()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glColor4f(1, 1, 1, 1);
    glPushMatrix();

        glEnableClientState(GL_VERTEX_ARRAY); 
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}   



class Player 
{
    float x, y;
    float vertex[12]; /*= {
        -0.1, -0.1, 0,
        0.1, -0.1, 0,
        0.1, 0.1, 0,
        -0.1, 0.1, 0
    };*/
    float texCoord[8] = {
        0, 1,
        1, 1,
        1, 0,
        0, 0
    };
    unsigned int texture;
public:
    Player(float a_x, float a_y)
        { x = a_x; y = a_y; } 
    void InitVertex();
    void InitTexture();    
    float GetX() { return x; }
    float GetY() { return y; }     
    void MovePlayer(float a_x, float a_y);
    void DrawPlayer();       
};

void Player::InitVertex()
{
    vertex[0] = -0.2; 
    vertex[1] = -0.2;
    vertex[2] = 0;
    vertex[3] = 0.2;
    vertex[4] = -0.2;
    vertex[5] = 0;
    vertex[6] = 0.2;
    vertex[7] = 0.2;
    vertex[8] = 0;
    vertex[9] = -0.2;   
    vertex[10] = 0.2;
    vertex[11] = 0;
} 

void Player::InitTexture()
{
    int width, height, cnt;
    unsigned char *data = stbi_load("2.png", &width, &height, &cnt, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                                    0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

void Player::MovePlayer(float a_x, float a_y)
{
    x += a_x;
    y += a_y;
    vertex[0] += a_x; 
    vertex[1] += a_y; 

    vertex[3] += a_x; 
    vertex[4] += a_y; 

    vertex[6] += a_x; 
    vertex[7] += a_y; 

    vertex[9] += a_x; 
    vertex[10] += a_y;   
}

void Player::DrawPlayer()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glColor4f(1, 1, 1, 1);
    glPushMatrix();
        /*glPointSize(30);
        glBegin(GL_POINTS);
            
            glVertex2f(x, y);
        glEnd();*/

        glEnableClientState(GL_VERTEX_ARRAY); 
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}


Player player = Player(0, 0);
Background background = Background();
void init()
{
    player.InitVertex();   
    player.InitTexture();

    background.InitTexture();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    float aspect = 480.0/848.0  ;
    glScalef(aspect, 1, 1);

}

void keyboard_down(unsigned char key, int x, int y)
{
    KEYSTATES[key] = true;

    if (key == 27) //escape
    {
        glutLeaveMainLoop();         
    }
   
    if (key == 'f')
    {
        if (!IS_FULLSCREEN)
        {
            glutFullScreen();
            IS_FULLSCREEN = true;
        }
        else 
        {
            glutReshapeWindow(848, 480);
            glutPositionWindow(400,400);
            IS_FULLSCREEN = false;
        }   
            
    }

    if (key =='r')
     {
        player.InitVertex();
     } 
}

void keyboard_up(unsigned char key, int x, int y)
{
    KEYSTATES[key] = false; 
}

void control()
{
    if (KEYSTATES['a']) //left
    {
        //player.MovePlayer(player.GetX() - 0.01, player.GetY()); 
        player.MovePlayer(-0.05, 0);   
    }
    if (KEYSTATES['w']) //up
    {
        //player.MovePlayer(player.GetX(), player.GetY()+0.01); 
        player.MovePlayer(0, 0.05); 
    }

    if (KEYSTATES['d']) //right
    {
        //player.MovePlayer(player.GetX() + 0.01, player.GetY());
        player.MovePlayer(0.05, 0); 
    }
    if (KEYSTATES['s']) //down
    {
        //player.MovePlayer(player.GetX(), player.GetY() - 0.01);
        player.MovePlayer(0, -0.05); 
    }  
}



void display()
{
    control();
    glClearColor(0.3f, 1.0f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    background.DrawBackground();

    player.DrawPlayer();

    glEnd();
    glutPostRedisplay();
    glutSwapBuffers();
   
}   

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(848, 480);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Game");

    glClearColor(1, 1, 1, 0);

    /*glViewport(0, 0, 848, 480);
    glMatrixMode(GL_PROJECTION);
    float aspect = 848.0 / 480.0;
    glOrtho(-aspect, aspect, -1, 1, -1, 1);*/
    //glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    //glOrtho(-10, 10, -10, 10, 0, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard_down);
    glutKeyboardUpFunc(keyboard_up);
    init();    
    glutMainLoop();
    return 0;
}