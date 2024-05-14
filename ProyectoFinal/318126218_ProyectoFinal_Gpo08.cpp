// Bibliotecas principales.
#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Para permitir lectura de archivos
#pragma warning(disable:4996)

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacion();
float doorRotationAngle = 0.0f;
// Window dimensions

const GLuint WIDTH = 1280, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 3.128f, 15.301f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
GLfloat rotationAngle = 0.0f;
GLfloat transpHumo = 0.0f;
GLfloat posHumo = 0.0f;
GLfloat humoSpeedPos = 0.5f;
GLfloat aumentoPantalla = 0.0f;

float speedH = 2.4f;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
float doorRotationSpeed = 90.0f;
float cucharaGiro = 0.0f;
bool mano = false;
float giroboton = 0.0f;
bool animHumo = false;
bool maxHumo = false;
float tiempo;
bool active;
float pruebax = 0;
float pruebay = 0;
float pruebaz = 0;
bool animPantalla = false;

float tiempoP;
float speed = 0.0f;



//luz tacos
bool luz1 = true;
bool luz2 = false;
float luz1f = 0;
glm::vec3 Light1 = glm::vec3(0);
bool direccion = true;

//luz exterior
bool luzPoste = false;

//auto
bool compleja = true;
bool fase1 = true;
bool fase2 = false;
bool fase3 = false;
bool fase4 = false;
bool fase5 = false;

float trasrot = 0;
float autocar = 0;
float avance = 0;
float avancex = 0;
float giro = 0;
float giroComp = 0;

//termina auto

// Archivos de keyframes
char nombreArchivo1[] = "keyframes.txt";
char nombreArchivo2[] = "keyframes2.txt";
char nombreArchivo3[] = "Anim2keyframes.txt";
char nombreArchivo4[] = "Anim2keyframes2.txt";
char nombreArchivo5[] = "originalKeyframes.txt";
char nombreArchivo6[] = "originalKeyframes2.txt";
char nombreArchivo7[] = "originalAnim2keyframes.txt";
char nombreArchivo8[] = "originalAnim2keyframes2.txt";

// Animacion Porygon
float	movPory_x = 0.0f,
movPory_y = 0.0f,
movPory_z = 0.0f,
orienta_Pory = 0.0f,
rotColaP = 0.0f,
rotPataDerP = 0.0f,
rotPataIzqP = 0.0f,
varPory = 0.0f;

bool	animPory = false;
int		rutaPory = 0,
spritePory = 1;


//Animacion Pokebola
float	movPokebola_x = 0.0f,
movPokebola_y = 0.0f,
movPokebola_z = 0.0f,
rotPokebola = 0.0f;

bool	animPokebola = false;

// Animacion Tiro Parabólico
// v es qué tan lejos llega el objeto
float	g = 9.81f, v = 22.0f, ang = 60.0f, t = 45.0f;
double	n = 3.1416;
float	i = 0.0f;

// Animacion Lucario
bool	animLucario = false;
float	movLucario = 0.0f,
rotCuerpo = 0.0f,
rotCabezaY = 0.0f,
rotCabezaZ = 0.0f,
rotPiernaDer = 0.0f,
rotPiernaIzq = 0.0f,
rotAbDer = 0.0f,
rotBrazoDer = 0.0f,
rotAbIzq = 0.0f,
rotEsfera = 0.0f,
movPlataforma = 0.0f;

float	movEsfera_x = 0.0f,
movEsfera_y = 0.0f,
movEsfera_z = 0.0f,
varLucario = 0.0f;
int		actPlataforma = 0;

//Keyframes (Manipulación y dibujo)
float	rotCuerpoInc = 0.0f,
rotCabezaYInc = 0.0f,
rotCabezaZInc = 0.0f,
rotPiernaDerInc = 0.0f,
rotPiernaIzqInc = 0.0f,
rotAbDerInc = 0.0f,
rotBrazoDerInc = 0.0f,
rotAbIzqInc = 0.0f;

// Variables para Keyframes
#define MAX_FRAMES 20
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float	rotCuerpo;
	float	rotCabezaY;
	float	rotCabezaZ;
	float	rotPiernaDer;
	float	rotPiernaIzq;
	float	rotAbDer;
	float	rotBrazoDer;
	float	rotAbIzq;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex;			//introducir número en caso de tener Key guardados
bool play = false;
int playIndex = 0;

//función que carga keyframes guardados en un archivo de texto
void cargarAnimacionKeyframes(char nombreArchivo[]) {
	FILE* archivo;
	float posicion;

	if ((archivo = fopen(nombreArchivo, "rt")) == NULL)
		printf("No se puedo abrir el archivo correctamente\n");

	else {
		if ((strcmp(nombreArchivo, "keyframes.txt") == 0) || (strcmp(nombreArchivo, "Anim2keyframes.txt") == 0) || (strcmp(nombreArchivo, "originalKeyframes.txt") == 0) || (strcmp(nombreArchivo, "originalAnim2Keyframes.txt") == 0))
			FrameIndex = 9;
		else
			FrameIndex = 11;
		for (int i = 0; i < FrameIndex; i++) {
			fscanf(archivo, "%f", &posicion);
			KeyFrame[i].rotCuerpo = posicion;
			fscanf(archivo, "%f", &posicion);
			KeyFrame[i].rotCabezaY = posicion;
			fscanf(archivo, "%f", &posicion);
			KeyFrame[i].rotCabezaZ = posicion;
			fscanf(archivo, "%f", &posicion);
			KeyFrame[i].rotPiernaDer = posicion;
			fscanf(archivo, "%f", &posicion);
			KeyFrame[i].rotPiernaIzq = posicion;
			fscanf(archivo, "%f", &posicion);
			KeyFrame[i].rotAbDer = posicion;
			fscanf(archivo, "%f", &posicion);
			KeyFrame[i].rotBrazoDer = posicion;
			fscanf(archivo, "%f", &posicion);
			KeyFrame[i].rotAbIzq = posicion;
		}
	}
}

// FUNCIONES PARA REALIZAR ANIMACION POR KEYFRAMES
void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].rotCuerpo = rotCuerpo;
	KeyFrame[FrameIndex].rotCabezaY = rotCabezaY;
	KeyFrame[FrameIndex].rotCabezaZ = rotCabezaZ;
	KeyFrame[FrameIndex].rotPiernaDer = rotPiernaDer;
	KeyFrame[FrameIndex].rotPiernaIzq = rotPiernaIzq;
	KeyFrame[FrameIndex].rotAbDer = rotAbDer;
	KeyFrame[FrameIndex].rotBrazoDer = rotBrazoDer;
	KeyFrame[FrameIndex].rotAbIzq = rotAbIzq;

	std::cout << "rotCuerpo = " << rotCuerpo << std::endl;
	std::cout << "rotCabezaY = " << rotCabezaY << std::endl;
	std::cout << "rotCabezaZ = " << rotCabezaZ << std::endl;
	std::cout << "rotPiernaDer = " << rotPiernaDer << std::endl;
	std::cout << "rotPiernaIzq = " << rotPiernaIzq << std::endl;
	std::cout << "rotAbDer = " << rotAbDer << std::endl;
	std::cout << "rotBrazoDer = " << rotBrazoDer << std::endl;
	std::cout << "rotAbIzq = " << rotAbIzq << std::endl;

	FrameIndex++;
}

void resetElements(void)
{
	rotCuerpo = KeyFrame[0].rotCuerpo;
	rotCabezaY = KeyFrame[0].rotCabezaY;
	rotCabezaZ = KeyFrame[0].rotCabezaZ;
	rotPiernaDer = KeyFrame[0].rotPiernaDer;
	rotPiernaIzq = KeyFrame[0].rotPiernaIzq;
	rotAbDer = KeyFrame[0].rotAbDer;
	rotBrazoDer = KeyFrame[0].rotBrazoDer;
	rotAbIzq = KeyFrame[0].rotAbIzq;

}

void interpolation(void)
{
	rotCuerpoInc = (KeyFrame[playIndex + 1].rotCuerpo - KeyFrame[playIndex].rotCuerpo) / i_max_steps;
	rotCabezaYInc = (KeyFrame[playIndex + 1].rotCabezaY - KeyFrame[playIndex].rotCabezaY) / i_max_steps;
	rotCabezaZInc = (KeyFrame[playIndex + 1].rotCabezaZ - KeyFrame[playIndex].rotCabezaZ) / i_max_steps;
	rotPiernaDerInc = (KeyFrame[playIndex + 1].rotPiernaDer - KeyFrame[playIndex].rotPiernaDer) / i_max_steps;
	rotPiernaIzqInc = (KeyFrame[playIndex + 1].rotPiernaIzq - KeyFrame[playIndex].rotPiernaIzq) / i_max_steps;
	rotAbDerInc = (KeyFrame[playIndex + 1].rotAbDer - KeyFrame[playIndex].rotAbDer) / i_max_steps;
	rotBrazoDerInc = (KeyFrame[playIndex + 1].rotBrazoDer - KeyFrame[playIndex].rotBrazoDer) / i_max_steps;
	rotAbIzqInc = (KeyFrame[playIndex + 1].rotAbIzq - KeyFrame[playIndex].rotAbIzq) / i_max_steps;

}

glm::vec3 doorPivot = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cucharaPivot = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 botonPivot = glm::vec3(0.0f, 1.0f, 0.0f);
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 0.35f, -45.0f);

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f, 0.2f, 2.0f),
	glm::vec3(0, 0, 0),
	glm::vec3(0, 0, 0),
	glm::vec3(0, 0, 0)
};

glm::vec3 LightP1;
//luces exteriores
glm::vec3 lightColor2;


// Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "PROYECTO FINAL - NARUTO - 318126218 ", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	// Declaracion y carga de los Shaders y modelos
	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader Anim("Shaders/anim.vs", "Shaders/anim.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader Humo("Shaders/animHumo.vs", "Shaders/animHumo.frag");
	Shader AnimGlobo("Shaders/animGlobo.vs", "Shaders/animGlobo.frag");
	Shader Estatica("Shaders/animPantalla.vs", "Shaders/animPantalla.frag");

	Model Techo((char*)"Models/ProyectoFinal/techo.obj");
	Model piso((char*)"Models/ProyectoFinal/piso.obj");
	Model banqueta((char*)"Models/ProyectoFinal/banqueta.obj");
	Model Fachada((char*)"Models/ProyectoFinal/Fachada.obj");
	Model techo_entrada((char*)"Models/ProyectoFinal/techo_entrada.obj");
	Model asfalto((char*)"Models/ProyectoFinal/asfalto.obj");
	Model arbusto1((char*)"Models/ProyectoFinal/arbusto1.obj");
	Model arbusto2((char*)"Models/ProyectoFinal/arbusto2.obj");
	Model arbusto3((char*)"Models/ProyectoFinal/arbusto3.obj");
	Model arbusto4((char*)"Models/ProyectoFinal/arbusto4.obj");
	Model arbusto5((char*)"Models/ProyectoFinal/arbusto5.obj");
	Model arbusto6((char*)"Models/ProyectoFinal/arbusto6.obj");
	Model fachadaTacos((char*)"Models/facha1/fach1.obj");
	Model muebles((char*)"Models/MueblesAparte/muebles.obj");
	Model puerta((char*)"Models/Puerta/marcospuerta1.obj");
	Model vidrio((char*)"Models/puerta/Vidrio1.obj");
	Model ventanas((char*)"Models/facha1/ventanas2.obj");
	Model globo((char*)"Models/globo/globo.obj");
	Model porshe((char*)"Models/pruebauto/porshe2.obj");
	Model llanta((char*)"Models/pruebauto/llanta2.obj");
	Model lamparas1((char*)"Models/ProyectoFinal/lamparas1.obj");
	Model lamparas2((char*)"Models/ProyectoFinal/lamparas2.obj");
	Model lamparas3((char*)"Models/ProyectoFinal/lamparas3.obj");
	Model lamparas4((char*)"Models/ProyectoFinal/lamparas4.obj");
	Model lamparas5((char*)"Models/ProyectoFinal/lamparas5.obj");
	Model lamparas6((char*)"Models/ProyectoFinal/lamparas6.obj");
	Model lamparas7((char*)"Models/ProyectoFinal/lamparas7.obj");
	Model lamparas8((char*)"Models/ProyectoFinal/lamparas8.obj");
	Model carro1((char*)"Models/ProyectoFinal/carro1.obj");
	Model carro2((char*)"Models/ProyectoFinal/carro2.obj");
	Model carro3((char*)"Models/ProyectoFinal/carro3.obj");
	Model carro4((char*)"Models/ProyectoFinal/carro4.obj");
	Model carro5((char*)"Models/ProyectoFinal/carro5.obj");
	Model pokemon((char*)"Models/ProyectoFinal/pokemon.obj");
	Model sp((char*)"Models/ProyectoFinal/segundopiso1.obj");
	Model sp2((char*)"Models/ProyectoFinal/segundopiso2.obj");
	Model barandal1((char*)"Models/ProyectoFinal/barandal1.obj");
	Model barandal2((char*)"Models/ProyectoFinal/barandal2.obj");
	Model barandal3((char*)"Models/ProyectoFinal/barandal3.obj");
	Model naruto((char*)"Models/ProyectoFinal/naruto.obj");
	Model locales((char*)"Models/ProyectoFinal/locales.obj");
	Model Sea((char*)"Models/ProyectoFinal/Sea.obj");
	Model Sea2((char*)"Models/ProyectoFinal/Sea2.obj");
	Model fuente1((char*)"Models/ProyectoFinal/fuente1.obj");
	Model fuente2((char*)"Models/ProyectoFinal/fuente2.obj");
	Model TTPD((char*)"Models/ProyectoFinal/TTPD.obj");

	Model panini((char*)"Models/ProyectoFinal/panini.obj");
	Model fortnite((char*)"Models/ProyectoFinal/fortnite.obj");
	Model PH((char*)"Models/ProyectoFinal/PH.obj");
	Model banamex((char*)"Models/ProyectoFinal/banamex.obj");
	Model Pantalla((char*)"Models/ProyectoFinal/pantallaDescompuesta.obj");
	Model pokemon_logo((char*)"Models/ProyectoFinal/pokemon_logo.obj");
	Model totalplay((char*)"Models/ProyectoFinal/totalplay.obj");
	Model sears((char*)"Models/ProyectoFinal/sears.obj");
	Model tangamanga((char*)"Models/ProyectoFinal/tangamanga.obj");
	Model disney((char*)"Models/ProyectoFinal/disney.obj");
	Model max((char*)"Models/ProyectoFinal/max.obj");
	Model bancos1((char*)"Models/ProyectoFinal/bancos1.obj");
	Model bancos2((char*)"Models/ProyectoFinal/bancos2.obj");
	Model bancos3((char*)"Models/ProyectoFinal/bancos3.obj");
	Model bancos4((char*)"Models/ProyectoFinal/bancos4.obj");
	Model baños((char*)"Models/ProyectoFinal/baños.obj");
	Model EE1((char*)"Models/ProyectoFinal/EE1.obj");
	Model EE2((char*)"Models/ProyectoFinal/EE2.obj");
	Model EE3((char*)"Models/ProyectoFinal/EE3.obj");
	Model EE4((char*)"Models/ProyectoFinal/EE4.obj");
	Model papitas1((char*)"Models/ProyectoFinal/papitas1.obj");
	Model papitas2((char*)"Models/ProyectoFinal/papitas2.obj");
	Model papitas3((char*)"Models/ProyectoFinal/papitas3.obj");
	Model papitas4((char*)"Models/ProyectoFinal/papitas4.obj");
	Model bdb1((char*)"Models/ProyectoFinal/botebasura1.obj");
	Model bdb2((char*)"Models/ProyectoFinal/botebasura2.obj");
	Model gasolinera((char*)"Models/ProyectoFinal/gasolinera.obj");
	Model porygonCabeza((char*)"Models/Porygon/PorygonCabeza.obj");
	Model porygonCuerpo((char*)"Models/Porygon/PorygonCuerpo.obj");
	Model porygonCola((char*)"Models/Porygon/PorygonCola.obj");
	Model porygonPataDer((char*)"Models/Porygon/PorygonPataDer.obj");
	Model porygonPataIzq((char*)"Models/Porygon/PorygonPataIzq.obj");
	Model pokebola((char*)"Models/Pokebola/pokebola.obj");
	Model cuerpoLucario((char*)"Models/Lucario/cuerpo.obj");
	Model cabezaLucario((char*)"Models/Lucario/cabeza.obj");
	Model antebrazoDerLucario((char*)"Models/Lucario/antebrazoDer.obj");
	Model brazoDerLucario((char*)"Models/Lucario/brazoDer.obj");
	Model antebrazoIzqLucario((char*)"Models/Lucario/antebrazoIzq.obj");
	Model brazoIzqLucario((char*)"Models/Lucario/brazoIzq.obj");
	Model piernaDerLucario((char*)"Models/Lucario/piernaDer.obj");
	Model piernaIzqLucario((char*)"Models/Lucario/piernaIzq.obj");
	Model esfera((char*)"Models/Lucario/auraEsfera.obj");
	Model plataforma((char*)"Models/Lucario/Plataforma.obj");

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].rotCuerpo = 0;
		KeyFrame[i].rotCabezaY = 0;
		KeyFrame[i].rotCabezaZ = 0;
		KeyFrame[i].rotPiernaDer = 0;
		KeyFrame[i].rotPiernaIzq = 0;
		KeyFrame[i].rotAbDer = 0;
		KeyFrame[i].rotBrazoDer = 0;
		KeyFrame[i].rotAbIzq = 0;
	}


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};




	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
	   -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};

	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	//glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);


	vector<const GLchar*> faces;
	faces.push_back("SkyBox/2left.tga");
	faces.push_back("SkyBox/2right.tga");

	faces.push_back("SkyBox/2top.tga");
	faces.push_back("SkyBox/2bottom.tga");
	faces.push_back("SkyBox/2back.tga");
	faces.push_back("SkyBox/2front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);
	//lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();

		// Clear the colorbuffer
		glClearColor(0.364f, 0.760f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = (Light1.x);
		lightColor.y = (Light1.y);
		lightColor.z = (Light1.z);



		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), 22.87, 5.34, 13.57);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.20); //20 unidadeds

		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), -4.29, 4.49, 11);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor2.x, lightColor2.x, lightColor2.x);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor2.x, lightColor2.x, lightColor2.x);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), lightColor2.x, lightColor2.x, lightColor2.x);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.14f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.07f); //32 unidades

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), 4.59, 4.49, 11);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lightColor2.x, lightColor2.x, lightColor2.x);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lightColor2.x, lightColor2.x, lightColor2.x);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), lightColor2.x, lightColor2.x, lightColor2.x);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.14f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.07f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1);
		glm::mat4 tmp = glm::mat4(1);
		glm::mat4 tmpLucario = glm::mat4(1);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		TTPD.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		panini.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		baños.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bdb1.Draw(lightingShader);
		
		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bdb2.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		papitas1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		papitas2.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		papitas3.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		papitas4.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		gasolinera.Draw(lightingShader);



		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		banamex.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pokemon_logo.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		totalplay.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		max.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		disney.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sears.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		tangamanga.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PH.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fortnite.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bancos1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bancos2.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bancos3.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bancos4.Draw(lightingShader);


		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		techo_entrada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Techo.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Fachada.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		asfalto.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		banqueta.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamparas1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamparas2.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamparas3.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamparas4.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamparas5.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamparas6.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamparas7.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamparas8.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbusto1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbusto2.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbusto3.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbusto4.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbusto5.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbusto6.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		carro1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		carro2.Draw(lightingShader);


		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		carro3.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		carro4.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		carro5.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piso.Draw(lightingShader);

		model = glm::mat4(1);

		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sp.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sp2.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		barandal1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		barandal2.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		barandal3.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pokemon.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		naruto.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		locales.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		EE1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		EE2.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		EE3.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		EE4.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fuente1.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fuente2.Draw(lightingShader);

		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(20.0f, 0.3f, 8.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fachadaTacos.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-.939, -.01, -.49));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		muebles.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(24.04, .28, 13.30));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puerta.Draw(lightingShader);


		// Porygon
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movPory_x - 0.205, movPory_y + 9.201, movPory_z - 0.076));
		tmp = model = glm::rotate(model, glm::radians(orienta_Pory), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		porygonCuerpo.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(0.0, 1.064, 0.539));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		porygonCabeza.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(0.0, -0.421, -0.627));
		model = glm::rotate(model, glm::radians(rotColaP), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		porygonCola.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-0.88, -0.415, -0.025));
		model = glm::rotate(model, glm::radians(rotPataDerP), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		porygonPataDer.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(0.894, -0.395, -0.029));
		model = glm::rotate(model, glm::radians(rotPataIzqP), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		porygonPataIzq.Draw(lightingShader);

		// Pokebola
		model = glm::mat4(1);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPokebola_x - 23.094, movPokebola_y + 1.4, movPokebola_z + 25.422));
		model = glm::rotate(model, glm::radians(rotPokebola), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pokebola.Draw(lightingShader);

		// Lucario
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-16.382, movLucario + 9.797, 11.076));
		tmp = model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoLucario.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-0.128, 1.18, -0.207));
		model = glm::rotate(model, glm::radians(rotCabezaY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotCabezaZ), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cabezaLucario.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-0.804, -1.471, 0.476));
		model = glm::rotate(model, glm::radians(rotPiernaDer), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piernaDerLucario.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(0.676, -1.757, -0.364));
		model = glm::rotate(model, glm::radians(rotPiernaIzq), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piernaIzqLucario.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(-0.604, 0.595, 0.151));
		model = glm::rotate(model, glm::radians(rotAbDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.831, 0.0f, 0.8));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		tmpLucario = model = glm::rotate(model, glm::radians(rotBrazoDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.831, 0.0f, -0.8));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		antebrazoDerLucario.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmpLucario, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		brazoDerLucario.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmp, glm::vec3(0.287, 0.642, -0.66));
		tmpLucario = model = glm::rotate(model, glm::radians(rotAbIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		antebrazoIzqLucario.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(tmpLucario, glm::vec3(0.542, -0.953, -0.233));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		brazoIzqLucario.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movEsfera_x - 19.892, movEsfera_y + 11.107, movEsfera_z + 13.833));
		model = glm::rotate(model, glm::radians(rotEsfera), glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		esfera.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		plataforma.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-23.85, .35, 9));
		model = glm::translate(model, glm::vec3(avancex, 0, avance));
		model = glm::scale(model, glm::vec3(2, 2, 2));
		model = glm::rotate(model, glm::radians(giroComp), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(abest), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		porshe.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-23.85, .35, 9));
		model = glm::translate(model, glm::vec3(avancex, 0, avance));
		model = glm::rotate(model, glm::radians(giroComp), glm::vec3(0.0f, 1.0f, 0.0f));


		glm::mat4 wheelModel = glm::translate(model, glm::vec3(.91 - .89, .29 - .35, -45.85 + 45.87));
		wheelModel = glm::rotate(wheelModel, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
		wheelModel = glm::rotate(wheelModel, glm::radians(trasrot), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(pruebax, .35, pruebaz));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(wheelModel));
		llanta.Draw(lightingShader); //lanta 1

		glm::mat4 wheelModel2 = glm::translate(model, glm::vec3(-.26 - .89, .29 - .35, -45.85 + 45.87));
		wheelModel2 = glm::rotate(wheelModel2, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
		wheelModel2 = glm::rotate(wheelModel2, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		wheelModel2 = glm::rotate(wheelModel2, glm::radians(trasrot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(wheelModel2));
		llanta.Draw(lightingShader); //llanta 2


		// Llanta 3
		glm::mat4 wheelModel3 = glm::translate(model, glm::vec3(.91 - .89, .29 - .35, -47.68 + 45.87));
		wheelModel3 = glm::rotate(wheelModel3, glm::radians(trasrot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(wheelModel3));
		llanta.Draw(lightingShader); //llanta 3

		// Llanta 4
		glm::mat4 wheelModel4 = glm::translate(model, glm::vec3(-.26 - .89, .29 - .35, -47.68 + 45.87));
		wheelModel4 = glm::rotate(wheelModel4, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		wheelModel4 = glm::rotate(wheelModel4, glm::radians(trasrot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(wheelModel4));
		llanta.Draw(lightingShader); //llanta 4


		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20.01, .26, 7.97));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, .35f);
		ventanas.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(24.04, .28, 13.30));
		//model = glm::rotate(model, glm::radians(abrirp), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, .35f);
		vidrio.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(24.52, .3, 5.76));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, .35f);
		vidrio.Draw(lightingShader);










		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);


		glBindVertexArray(0);


		AnimGlobo.Use();

		tiempo = glfwGetTime() * 0.2f;
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(AnimGlobo.Program, "model");
		viewLoc = glGetUniformLocation(AnimGlobo.Program, "view");
		projLoc = glGetUniformLocation(AnimGlobo.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(23.82, 3.53, 10.30));
		model = glm::scale(model, glm::vec3(.5, .5, .5));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(AnimGlobo.Program, "time"), tiempo);
		globo.Draw(AnimGlobo);

		Anim.Use();
		tiempo = glfwGetTime() * 2.8f;
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		modelLoc = glGetUniformLocation(Anim.Program, "model");
		viewLoc = glGetUniformLocation(Anim.Program, "view");
		projLoc = glGetUniformLocation(Anim.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Sea.Draw(Anim);

		Anim.Use();
		tiempo = glfwGetTime() * 2.8f;
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		modelLoc = glGetUniformLocation(Anim.Program, "model");
		viewLoc = glGetUniformLocation(Anim.Program, "view");
		projLoc = glGetUniformLocation(Anim.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Sea2.Draw(Anim);

		glBindVertexArray(0);

		Estatica.Use();
		tiempoP = glfwGetTime() * speed;
		modelLoc = glGetUniformLocation(Estatica.Program, "model");
		viewLoc = glGetUniformLocation(Estatica.Program, "view");
		projLoc = glGetUniformLocation(Estatica.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, (aumentoPantalla)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(Estatica.Program, "time"), tiempoP);
		Pantalla.Draw(Estatica);
		glBindVertexArray(0);

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default
		glfwSwapBuffers(window);





	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}

void DoMovement()
{
	if (animHumo) {

		if (maxHumo == true) {


			transpHumo -= 0.018f * deltaTime;
			posHumo += humoSpeedPos * deltaTime;
			if (transpHumo < 0.0f) {
				transpHumo = 0.0f;
				animHumo = false;
				maxHumo = false;
			}
		}
	}
	if (animPantalla)
	{
		aumentoPantalla = 0.025f;
		speed = 30.4f;
	}
	else
	{
		aumentoPantalla = 0.0f;
	}
	if (keys[GLFW_KEY_1])
	{
		range += 0.1;
		rot += 1;
		printf("El rango es %f\n", range);
	}

	if (keys[GLFW_KEY_2])
	{
		range -= 0.1;
		printf("El rango es %f\n", range);
	}

	if (keys[GLFW_KEY_3])
	{
		range += 0.1;
		printf("El spotangle es %f\n", range);
	}

	if (keys[GLFW_KEY_4])
	{
		range -= 0.1;
		printf("El spotangle es %f\n", range);
	}


	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}


	if (keys[GLFW_KEY_Z])
	{
		pruebax += 0.01f;
	}

	if (keys[GLFW_KEY_C])
	{
		pruebay += 0.01f;
	}

	if (keys[GLFW_KEY_B])
	{
		pruebaz += 0.01f;
	}

	if (keys[GLFW_KEY_X])
	{
		pruebax -= 0.01f;
	}

	if (keys[GLFW_KEY_V])
	{
		pruebay -= 0.01f;
	}

	if (keys[GLFW_KEY_N])
	{
		pruebaz -= 0.01f;
	}

	if (compleja) {

		trasrot += 4.0f;
		if (fase1) {
			avance = avance + .03;
			if (avance >= 9) {
				fase1 = false;
				fase2 = true;
			}
		}
		if (fase2) {

			avance = avance + .01;
			avancex = avancex + .01;
			giro += 0.5f;
			giroComp = giroComp + 1;
			if (giro >= 23) {
				fase2 = false;
				fase3 = true;
			}

		}

		if (fase3) {
			giroComp = giroComp + 1;
			avance = avance + .01;
			avancex = avancex + .01;
			if (giroComp >= 90) {
				fase3 = false;
				fase4 = true;
			}


		}


		if (fase4) {
			giro -= 0.5f;
			avancex = avancex + .01;

			if (giro <= 0) {
				fase4 = false;
				fase5 = true;
			}

		}

		if (fase5) {
			avancex = avancex + .03;

			if (avancex >= 17.5) {
				fase5 = false;
				compleja = false;
			}

		}




	}


	if (active)
	{

		if (luz1) {
			if (direccion) {
				luz1f = luz1f + .05;
				Light1 = glm::vec3(1.0f, 0.0f, 1.0f) * luz1f;

			}
			if (luz1f >= 5) {
				direccion = false;
			}
			if (direccion == false) {
				luz1f = luz1f - .15;
				Light1 = glm::vec3(1.0f, 0.0f, 1.0f) * luz1f;
				if (luz1f <= 0) {
					luz2 = true;
					luz1 = false;
				}


			}


		}
		else if (luz2) {
			Light1 = glm::vec3(0.0f, 1.0f, 0.0f);
		}



		else
		{
			Light1 = glm::vec3(0);
		}



	}
	else
	{
		Light1 = glm::vec3(0);
		luz1f = 0;
	}

	if (luzPoste) {
		lightColor2.x = 1;

	}
	else {
		lightColor2.x = 0;
	}

	// Animación de Porygon
	if (animPory)
	{
		if (spritePory == 1)
		{
			rotPataDerP += 1.0f;
			rotPataIzqP -= 1.0f;
			rotColaP += 1.0f;
			if (rotPataDerP >= 45.0f && rotPataIzqP <= 45.0f && rotColaP >= 45.0f)
				spritePory++;
		}

		if (spritePory == 2)
		{
			rotPataDerP -= 1.0f;
			rotPataIzqP += 1.0f;
			rotColaP -= 1.0f;
			if (rotPataDerP <= -45.0f && rotPataIzqP >= -45.0f && rotColaP <= -45.0f)
				spritePory--;
		}

		if (rutaPory == 0)
		{
			movPory_y += 0.1f;
			if (movPory_y >= 13.426)
				rutaPory = 1;
		}

		if (rutaPory == 1)
		{
			movPory_z += 0.1f;
			if (movPory_z >= 7.131)
				rutaPory = 2;
		}

		if (rutaPory == 2)
		{
			orienta_Pory += 1.0f;
			if (orienta_Pory >= 90.0f)
				rutaPory = 3;
		}

		if (rutaPory == 3)
		{
			movPory_x += 0.1f;
			if (movPory_x >= 14.356)
				rutaPory = 4;

		}

		if (rutaPory == 4)
		{
			orienta_Pory += 1.0f;
			if (orienta_Pory >= 180.0f)
				rutaPory = 5;
		}

		if (rutaPory == 5)
		{
			movPory_z -= 0.1f;
			if (movPory_z <= -12.528)
				rutaPory = 6;
		}

		if (rutaPory == 6)
		{
			orienta_Pory += 1.0f;
			if (orienta_Pory >= 270.0f)
				rutaPory = 7;
		}

		if (rutaPory == 7)
		{
			movPory_x -= 0.1f;
			if (movPory_x <= -13.941)
				rutaPory = 8;
		}

		if (rutaPory == 8)
		{
			orienta_Pory += 1.0f;
			if (orienta_Pory >= 360.0f)
			{
				orienta_Pory = 0;
				rutaPory = 9;
			}
		}

		if (rutaPory == 9)
		{
			movPory_z += 0.1f;
			if (movPory_z >= -5.467)
				rutaPory = 10;
		}

		if (rutaPory == 10)
		{
			movPory_y += 0.1f;
			if (movPory_y >= 20.761)
				rutaPory = 11;
		}

		if (rutaPory == 11)
		{
			orienta_Pory += 1.0f;
			if (orienta_Pory >= 90.0f)
				rutaPory = 12;
		}

		if (rutaPory == 12)
		{
			movPory_x += 0.1f;
			if (movPory_x >= 0.0)
				rutaPory = 13;
		}

		if (rutaPory == 13)
		{
			orienta_Pory -= 1.0f;
			if (orienta_Pory <= 0.0f)
				rutaPory = 14;
		}

		if (rutaPory == 14)
		{
			movPory_z += 0.1f;
			if (movPory_z >= 0.0)
				rutaPory = 15;
		}

		if (rutaPory == 15)
		{
			movPory_y -= 0.1f;
			if (movPory_y <= 0.0)
			{
				rutaPory = 0;
				movPory_x = 0.0f;
				movPory_y = 0.0f;
				movPory_z = 0.0f;
				rotPataDerP = 0.0f;
				rotPataIzqP = 0.0f;
				rotColaP = 0.0f;
				animPory = false;
			}
		}
	}

	// Animación de pokebola
	if (animPokebola)
	{
		rotPokebola -= 8.85f;
		// ANIMACION DE TIRO PARABÓLICO

		i += 0.012f;
		movPokebola_x = 0 + i * v * cos(ang * n / 180);
		movPokebola_y = 0 + (i * v * sin(ang * n / 180) - (g * i * i) / 2);
		if (movPokebola_y <= 0.0f)
		{
			i = 0.0f;
			animPokebola = false;
		}
	}

	// Animación de Lucario (Esfera y plataforma)
	if (animLucario)
	{
		movEsfera_x = 10.0f * sin(varLucario);
		movEsfera_z = 10.0f * cos(varLucario);
		varLucario += 0.01f;
		rotEsfera += 10.0f;
	}

	// Animacion por keyframes
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			rotCuerpo += rotCuerpoInc;
			rotCabezaY += rotCabezaYInc;
			rotCabezaZ += rotCabezaZInc;
			rotPiernaDer += rotPiernaDerInc;
			rotPiernaIzq += rotPiernaIzqInc;
			rotAbDer += rotAbDerInc;
			rotBrazoDer += rotBrazoDerInc;
			rotAbIzq += rotAbIzqInc;

			i_curr_steps++;
		}
	}

}


void animacion()
{
	if (keys[GLFW_KEY_R]) {
		if (doorRotationAngle <= 85.0f)
			doorRotationAngle += doorRotationSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_T]) {
		if (doorRotationAngle >= 0.0f)
			doorRotationAngle -= doorRotationSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_M]) {

		if (giroboton <= 180.0f)
			giroboton += doorRotationSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_N]) {

		if (giroboton >= 0.0f)
			giroboton -= doorRotationSpeed * deltaTime;
	}
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Cargar Animaciones keyframes
	if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS) {
		cargarAnimacionKeyframes(nombreArchivo1);
		printf("Archivo cargado correctamente\n");
	}

	if (glfwGetKey(window, GLFW_KEY_F6) == GLFW_PRESS) {
		cargarAnimacionKeyframes(nombreArchivo2);
		printf("Archivo cargado correctamente\n");
	}

	if (glfwGetKey(window, GLFW_KEY_F7) == GLFW_PRESS) {
		cargarAnimacionKeyframes(nombreArchivo3);
		printf("Archivo cargado correctamente\n");
	}

	if (glfwGetKey(window, GLFW_KEY_F8) == GLFW_PRESS) {
		cargarAnimacionKeyframes(nombreArchivo4);
		printf("Archivo cargado correctamente\n");
	}

	if (glfwGetKey(window, GLFW_KEY_F9) == GLFW_PRESS) {
		cargarAnimacionKeyframes(nombreArchivo5);
		printf("Archivo cargado correctamente\n");
	}

	if (glfwGetKey(window, GLFW_KEY_F10) == GLFW_PRESS) {
		cargarAnimacionKeyframes(nombreArchivo6);
		printf("Archivo cargado correctamente\n");
	}

	if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
		cargarAnimacionKeyframes(nombreArchivo7);
		printf("Archivo cargado correctamente\n");
	}

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		cargarAnimacionKeyframes(nombreArchivo8);
		printf("Archivo cargado correctamente\n");
	}

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	// Animacion Lucario
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		animLucario ^= true;

	// Animación Pokebola
	if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
		animPokebola ^= true;
	if (key == GLFW_KEY_F4 && action == GLFW_PRESS) {
		i = 0.0;
		rotPokebola = 0.0f;
		movPokebola_x = 0.0f;
		movPokebola_y = 0.0f;
		animPokebola = false;
	}

	// Animación Porygon
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		animPory ^= true;
	if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
		rutaPory = 0;
		movPory_x = 0.0f;
		movPory_y = 0.0f;
		movPory_z = 0.0f;
		orienta_Pory = 0.0f;
		rotPataDerP = 0.0f;
		rotPataIzqP = 0.0f;
		rotColaP = 0.0f;
		animPory = false;
	}

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}

		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		luz1 = true;
		luz2 = false;
	}
	if (keys[GLFW_KEY_X])
	{
		mano = true;

	}

	if (keys[GLFW_KEY_U])
	{
		luzPoste = !luzPoste;

	}
	if (keys[GLFW_KEY_P])
	{
		animPantalla = !animPantalla;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}