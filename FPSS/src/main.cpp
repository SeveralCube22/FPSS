#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <assimp\Importer.hpp>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>

#include <chrono>
#include <sstream>
#include <iomanip>

#include "buffer.hpp"
#include "buffer_layout.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"
#include "player.hpp"
#include "scene.hpp"
#include "model_node.hpp"

#include <vld.h>

// use Nvidia's drivers instead of Intel
extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

std::string* filePath = nullptr;

void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message,
                                const void* userParam) {
    
    std::string severityStr;
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         severityStr = "Severity: high "; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "Severity: medium "; break;
        case GL_DEBUG_SEVERITY_LOW:          severityStr = "Severity: low "; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Severity: notification "; break;
    }

    std::string mode = "a";
    if (!filePath) {
        auto now = std::chrono::system_clock::now();
        std::time_t tt = std::chrono::system_clock::to_time_t(now);
        std::tm tm;
        ::gmtime_s(&tm, &tt);

        std::stringstream ss;
        ss << std::put_time(&tm, " %Y-%m-%d%H_%M_%S");

        std::string formattedTime = ss.str();
        formattedTime.erase(remove(formattedTime.begin(), formattedTime.end(), ' '), formattedTime.end());
        filePath = new std::string("logs/" + formattedTime + ".txt");
        mode = "w";
    }

    FILE* logFile = nullptr;
    auto err = fopen_s(&logFile, filePath->c_str(), mode.c_str());
   
    fprintf(logFile, "%s GL CALLBACK: %s type = 0x%x, message = %s\n", 
        severityStr.c_str(),
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, message);
    fclose(logFile);
    if(severity != GL_DEBUG_SEVERITY_LOW && severity != GL_DEBUG_SEVERITY_NOTIFICATION)
        __debugbreak();
}

const int WIDTH = 1920;
const int HEIGHT = 1080;

void processInput(GLFWwindow* window, Player& cam, float deltaTime); // process keyboard movement
void loadScene(Scene& scene, const std::string& scenePath); // load scene file

int main(void)
{
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

    glm::mat4 projection = glm::perspective(45.0f, WIDTH / (float)HEIGHT, 1.0f, 1000.0f);

    Scene scene;
    loadScene(scene, "res/scene/world.json");

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

        glm::mat4x4 view = player.lookAt();
        glm::mat4x4 pv = projection * view;
        scene.setPVMatrix(pv);
        scene.Render();
      
        /* Poll for and process events */
        glfwPollEvents();
    }

    delete filePath;
    glfwTerminate();
    return 0;
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

void loadScene(Scene& scene, const std::string& scenePath) {
    std::ifstream ifs(scenePath);
    rapidjson::IStreamWrapper isw(ifs);

    rapidjson::Document doc;
    doc.ParseStream(isw);

    for (rapidjson::Value& model : doc["model"].GetArray()) {
        ModelNode* m = ModelNode::readJSON(model);
        scene.addChild(m->getProperties()->getActorId(), m);
    }
}