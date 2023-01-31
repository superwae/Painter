#include <iostream>
#include <GLFW/glfw3.h>
#include <vector> 
#include <math.h>
using namespace std;
int counter = 0;
int callcase = 0;
int countpoly = -1;
float r = 0.1, g = 0.1, b = 0.1;
vector<pair<int, int>>tri;
void drawCircle(float cx, float cy, float ra, int num_segments)
{
    float theta = 3.1415926 * 2 / float(num_segments);
    float tangetial_factor = tanf(theta);

    float radial_factor = cosf(theta);

    float x = ra;

    float y = 0;
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3f(r, g, b);
    for (int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);


        float tx = -y;
        float ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}
void drow_tri()
{

    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    for (int i = 0; i < 3; i++)
    {
        glVertex2f(tri[i].first, tri[i].second);
    }
    tri.clear();
    glEnd();
}
void drow_quad()
{

    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    for (int i = 0; i < 4; i++)
    {
        glVertex2f(tri[i].first, tri[i].second);
    }
    tri.clear();
    glEnd();
}
void drow_line()
{

    glBegin(GL_LINES);
    glColor3f(r, g, b);
    glVertex2f(tri[0].first, tri[0].second);
    glVertex2f(tri[1].first, tri[1].second);
    tri.clear();
    glEnd();
}
void drow_point()
{
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2f(tri[0].first, tri[0].second);
    tri.clear();
    glEnd();
}
void drow_poly(int number_of_points)
{
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for (int i = 0; i < number_of_points; i++)
    {
        glVertex2f(tri[i].first, tri[i].second);
    }
    tri.clear();
    countpoly = -1;
    glEnd();
}
void keycalback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        tri.clear();
        countpoly = -1;
        counter = callcase = 1;
        cout << "R,G,B:" << r << " " << g << " " << b << endl;
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        countpoly = -1;
        tri.clear();
        counter = callcase = 2;
        cout << "R,G,B:" << r << " " << g << " " << b << endl;
    }
    else if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        countpoly = -1;
        tri.clear();
        counter = callcase = 3;
        cout << "R,G,B:" << r << " " << g << " " << b << endl;
    }
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        tri.clear();
        countpoly = -1;
        counter = callcase = 4;
        cout << "R,G,B:" << r << " " << g << " " << b << endl;
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        tri.clear();
        countpoly = 0;
        cout << "R,G,B:" << r << " " << g << " " << b << endl;
    }
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (r < 1)
            r += 0.1;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (g < 1)
            g += 0.1;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (b < 1)
            b += 0.1;
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (r > 0)
            r -= 0.1;
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (g > 0)
            g -= 0.1;
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (b > 0)
            b -= 0.1;
    }
    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        tri.clear();
        countpoly = -1;
        counter = 2, callcase = 5;
        cout << "R,G,B:" << r << " " << g << " " << b << endl;
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    if (counter < 0)
        counter = 0;
    if ((button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && counter > 0))
    {
        counter--;
        glfwGetCursorPos(window, &xpos, &ypos);
        pair<int, int>temp;
        temp.first = xpos;
        temp.second = 480 - ypos;
        tri.push_back(temp);
        if (counter == 0)
        {
            switch (callcase)
            {
            case 1:
                drow_point();
                break;
            case 2:
                drow_line();
                break;
            case 3:
                drow_tri();
                break;
            case 4:
                drow_quad();
                break;
            case 5:
                float r = sqrt((pow((tri[0].first - tri[1].first), 2)) + (pow((tri[0].second - tri[1].second), 2)));
                drawCircle(tri[0].first, tri[0].second, r, 360);
                break;

            }
        }
    }
    if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_PRESS && countpoly >= 0)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            countpoly++;
            glfwGetCursorPos(window, &xpos, &ypos);
            pair<int, int>temp;
            temp.first = xpos;
            temp.second = 480 - ypos;
            tri.push_back(temp);
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            drow_poly(countpoly);
        }
    }


}
int main()
{
    int  y1 = 0, y2 = 0, y3 = 200, y4 = 200;

    GLFWwindow* window;
    if (!glfwInit())
    {
        return -1;
    }
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keycalback);
    glfwSwapBuffers(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glViewport(0.0f, 0.0f, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 0, 480, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window))
    {

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}