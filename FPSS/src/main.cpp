#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <assimp\Importer.hpp>

#include <CGAL/Simple_cartesian.h>

#include "buffer.hpp"
#include "buffer_layout.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"
#include "player.hpp"
#include "building.hpp"
#include "mass_hall.hpp"


// use Nvidia's drivers instead of Intel
extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message,
                                const void* userParam) {
    
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high "; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium "; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low "; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification "; break;
    }

    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, message);

    if(severity != GL_DEBUG_SEVERITY_LOW && severity != GL_DEBUG_SEVERITY_NOTIFICATION)
        __debugbreak();
}

const int WIDTH = 1920;
const int HEIGHT = 1080;

void processInput(GLFWwindow* window, Player& cam, float deltaTime); // process keyboard movement
std::vector<glm::mat4> setupBuildingModels(); // setup building model matrices

int main(void)
{
    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef Kernel::Point_2 Point_2;
    typedef Kernel::Segment_2 Segment_2;

    Point_2 p(1, 1), q(10, 10);
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q.x() << " " << q.y() << std::endl;
    std::cout << "sqdist(p,q) = "
        << CGAL::squared_distance(p, q) << std::endl;
    Segment_2 s(p, q);
    Point_2 m(5, 9);
    std::cout << "m = " << m << std::endl;
    std::cout << "sqdist(Segment_2(p,q), m) = "
        << CGAL::squared_distance(s, m) << std::endl;
    // Configurations

    /* Initialize the library */
    if(!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "FPSS", NULL, NULL);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // moved here because have to call after context is created according to documentation
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // BEGIN OPENGL CONFIGURATIONS

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);
    glEnable(GL_DEPTH_TEST); 
    glDepthFunc(GL_LESS);

    // END CONFIGURATIONS

    Player player(50.0f, glm::vec3(0.0f, 30.0f, -70.0f), glm::vec3(0.1f, 30.0f, -70.0f), glm::vec3(0.0f, 1.0f, 0.0f), .1f);

    float prevX = 300;
    float prevY = 240;
    float prevTime = 0;

    glm::mat4 projection = glm::perspective(45.0f, WIDTH / (float) HEIGHT, 1.0f, 1000.0f);
 
    std::vector<glm::mat4> buildingModels = setupBuildingModels();
    Building* build = new MassHall("res/objects/buildings/Mass_Hall/Mass_Hall.obj", buildingModels);
    
    /* Loop until the user closes the window */
    while(!glfwWindowShouldClose(window))
    {

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currX, currY;
        glfwGetCursorPos(window, &currX, &currY);

        float xOffset = currX - prevX;
        float yOffset = prevY - currY;
        float currTime = glfwGetTime();
        float delta = currTime - prevTime;
        
        prevX = currX;
        prevY = currY;
        prevTime = currTime;

        player.incrementYaw(xOffset);
        player.incrementPitch(yOffset);

        processInput(window, player, delta);
        //player.calculateVertPos(delta);

        glm::mat4 view = player.lookAt();
        glm::mat4 PV = projection * view;

        build->setPVMatrix(PV);

        build->draw();
      
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

std::vector<glm::mat4> setupBuildingModels() {
    std::vector<glm::mat4> matrices;
    glm::mat4 curr = glm::mat4(1.0f);
    for (int i = 0; i < 3; i++) {
        matrices.push_back(curr);
        curr = glm::translate(curr, glm::vec3(100.0f, 0.0f, 0.0f)); // Spacing buildings across X-axis
    }
    return matrices;
}

void processInput(GLFWwindow* window, Player& cam, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.moveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.strafeLeft(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.strafeRight(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam.jump(50.0f);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwDestroyWindow(window);
}