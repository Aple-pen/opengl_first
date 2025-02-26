﻿#include <iostream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void OnFrameBufferSizechange(GLFWwindow* window, int width, int height){
    SPDLOG_INFO("framebuffer size changed : ({},{})",width,height);
    glViewport(0,0,width,height);
}

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Render(){
    glClearColor(0.1f,0.2f,0.3f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);    
}

int main(){
    SPDLOG_INFO("Start program");

    //glfw 라이브러리 초기화. 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize Glfw");
    if(!glfwInit()){
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw : {}",description);
        return -1;
    }    

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
      nullptr, nullptr);
    if (!window) {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    const char* glVersion = (char*)glGetString(GL_VERSION);
    
    SPDLOG_INFO("OpenGL context version: {}", glVersion);

    OnFrameBufferSizechange(window,WINDOW_WIDTH,WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window,OnFrameBufferSizechange);
    glfwSetKeyCallback(window,OnKeyEvent);

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {    
        glfwPollEvents();        
        glClearColor(0.0f,0.1f,0.2f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}