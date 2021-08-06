#include <Game.hpp>

constexpr unsigned REFRESH_DISPLAY = 13u; // 60 fps
constexpr unsigned TIME = 100u; // 100 milisekund
constexpr char WINDOW_NAME[] = "Uratuj choinkê!";

std::unique_ptr<Engine::ProcessManagement> processManagement;

void Display()
{
	// Background color
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Start painting
	processManagement->Display();
	// End painting
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	Display();
}

void Special(int key, int x, int y)
{
	processManagement->Special(key, x, y);
}

void OnKeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case constants::Engine::ESCAPE:
		exit(0);
		break;
	}
	processManagement->OnKeyDown(key, x, y);
}

void OnMouseClick(int button, int state, int x, int y)
{
	processManagement->OnMouseClick(button, state, x, y);
}

void RefreshDisplay(int t)
{
	glutPostRedisplay();
	glutTimerFunc(REFRESH_DISPLAY, RefreshDisplay, 0);
}

void Time(int t)
{
	processManagement->Time(t);
	glutTimerFunc(TIME, Time, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));

	int argc = 1;
	char* argv[1] = { (char*)"" };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN)); // Maximum resolution
	glutCreateWindow(WINDOW_NAME);
	glutFullScreen();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Special);
	glutKeyboardFunc(OnKeyDown);
	glutMouseFunc(OnMouseClick);
	glutSetCursor(GLUT_CURSOR_NONE); // Nothing

	/* Timer functions */
	glutTimerFunc(REFRESH_DISPLAY, RefreshDisplay, 0);
	glutTimerFunc(TIME, Time, 0);

	// OpenGL initialization
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	processManagement = std::make_unique<Engine::ProcessManagement>();
	processManagement->createProcess = [](Engine::ProcessManagement* ptr)
	{
		int menu = ptr->addProcess<Game::Menu>(),
			intro = ptr->addProcess<Game::Intro>(),
			scene = ptr->addProcess<Game::Scene>(),
			gameplay = ptr->addProcess<Game::Gameplay>(),
			badending = ptr->addProcess<Game::BadEnding>(),
			goodending = ptr->addProcess<Game::GoodEnding>();
		if ((menu == -1) || (intro == -1) ||
			(scene == -1) || (gameplay == -1) || 
			(badending == -1) || (goodending == -1))
			exit(EXIT_FAILURE);
		ptr->setProcess(menu);
	};
	processManagement->createProcess(dynamic_cast<Engine::ProcessManagement*>(processManagement.get()));

	glutMainLoop();

	processManagement.reset();
	return EXIT_SUCCESS;
}