#include <Gl/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
static void ErrorClear() {
    //geterror() returns 0 if no error
    while (glGetError()!=GL_NO_ERROR);
}
static void ErrorMsg() {
    //
    while (GLenum error = glGetError()) {
        std::cout << "OPENGL ERROR :: [" << error << "]" << std::endl;
    }
}
struct ShaderSource {
    std::string vSource;
    std::string fSource;
};
static void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout<<"OpenGL error "<<err<<" at "<<fname<<": "<<line <<" for "<< stmt<<std::endl;
    }
}
static ShaderSource parseshader(const std::string& path) {
    std::ifstream stream(path);
    std::string line;
    enum class Stype {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::stringstream ss[2];
    Stype type = Stype::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = Stype::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = Stype::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };

}
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    //ERROR HANDLING
    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);

    if (res == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char * mes = (char*)alloca(len *sizeof(char));
        glGetShaderInfoLog(id, len, &len, mes);
        std::cout << " Compilation of"<< (type == GL_VERTEX_SHADER ? " vertex":" fragment")<<" shader failed !"<<std::endl;
        std::cout << mes<<std::endl;

        glDeleteShader(id);
        return 0;

    }

    return id;
}
static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
   /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (GLEW_OK != glewInit())
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "\n ERROR" << std::endl;

    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    /* Loop until the user closes the window */
    //Making buffers

    float positions[] = {
        -0.1f,-0.1f,
        0.1f , 0.1f,
        0.1f ,-0.1f,
        -0.1f , 0.1f
    };
    unsigned int index[] = {
        0,1,2,
        0,1,3
    };//indices we want to use , make an array of useful indices, so we dont allotmemory for same data again and again (use draw elements insted of draw arrays)


        float movx = 0.0f,movy=0.0f;
        unsigned int buffer;//buffers have integer id
        glGenBuffers(1, &buffer);//we say buffer 1 has to be made and connect it to a intger variable int buffer
        glBindBuffer(GL_ARRAY_BUFFER, buffer);//now int buffer points to a standard array buffer
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float),positions,GL_STATIC_DRAW);//size in bytes( check documentation ) glenum usage indiacates type of usage (static or dynamic or stream)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,0 );/*vertex can hold alot of data other than coordinates, and
                                                                              thereby increasing the size. */
        unsigned int ibo;//buffers have integer id
        glGenBuffers(1, &ibo);//we say buffer 1 has to be made and connect it to a intger variable int buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);//now int buffer points to a standard array buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), index, GL_STATIC_DRAW);
        
    ShaderSource s = parseshader("Res/shader/traingle.shader");
    unsigned int shader = createShader(s.vSource, s.fSource);

    std::cout << "VERTEX" << std::endl;
    std::cout <<s.vSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << s.fSource << std::endl;

    glUseProgram(shader);
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        ErrorClear();//clear any previous errors

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);

        ErrorMsg();//show current error
        
        /*
        movx = 0.0f, movy = 0.0f;
        switch (_getch()) {
        case 97:
            movx = -1.0f;
            break;
        case 115:
            movy = -1.0f;
            break;
        case 100:
            movx = 1.0f;
            break;
        case 119:
            movy = 1.0f;
            break;
        }
        
        for (int z = 0; z < 6; z++)
            if (z % 2 == 0)
                positions[z] += movy;
            else
                positions[z] += movx;
        
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);*/
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}