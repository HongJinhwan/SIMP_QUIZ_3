#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
using namespace std;

const int width = 1000;
const int height = 600;
const int line_width = 2;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawBoldLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		for (int a = i - line_width; a <= i + line_width; a++) {
			for (int b = j - line_width; b <= j + line_width; b++) {
				drawPixel(a, b, red, green, blue);
			}
		}
	}
}

void drawHeightLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int j = j0; j >= j1; j--)
	{
		drawPixel(i0, j, red, green, blue);
	}
}

void drawSquare(const int& i0, const int& j0, const int& length,  const float& red, const float& green, const float& blue)
{
	for (int i = i0-length/2; i <= i0 +length/2; i++)
	{
		drawPixel(i, j0+length/2, red, green, blue);
	}
	for (int i = i0 - length / 2; i <= i0 + length / 2; i++)
	{
		drawPixel(i, j0-length/2, red, green, blue);
	}
	for (int j = j0 - length / 2; j <= j0 + length / 2; j++)
	{
		drawPixel(i0 - length / 2, j, red, green, blue);
	}
	for (int j = j0 - length / 2; j <= j0 + length / 2; j++)
	{
		drawPixel(i0 + length / 2, j, red, green, blue);
	}
}

void drawFilledSquare(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		for (int j = j1; j <= j0; j++)
		{
			drawPixel(i, j, red, green, blue);
		}
	}
}

void drawTriangle(const int& i0, const int& j0, const float& length, const float& red, const float& green, const float& blue) {
	drawLine(i0, j0, i0 + length, j0, 1.0f, 0.0f, 0.0f);
	drawLine(i0, j0, i0 + length / 2, j0 + length / 2 * 1.732, 1.0f, 0.0f, 0.0f);
	drawLine(i0 + length / 2, j0 + length / 2 * 1.732, i0 + length, j0, 1.0f, 0.0f, 0.0f);
}

void drawPentagon(const int& i0, const int& j0, const float& length, const float& red, const float& green, const float& blue) {
	drawLine(i0 - length / 2, j0 - 1.732 / 2 * length, i0 + length / 2, j0 - 1.732 / 2 * length, 1.0f, 0.0f, 0.0f);
	drawLine(i0 + length / 2, j0 - 1.732 / 2 * length, i0 + length, j0, 1.0f, 0.0f, 0.0f);
	drawLine(i0, j0 + length, i0 + length, j0, 1.0f, 0.0f, 0.0f);
	drawLine(i0 - length, j0, i0, j0 + length, 1.0f, 0.0f, 0.0f);
	drawLine(i0 - length, j0, i0 - length / 2, j0 - 1.732 / 2 * length, 1.0f, 0.0f, 0.0f);
}

void drawCircle(const int& i0, const int& j0, const float& r, const int& bold, const float& red, const float& green, const float& blue) {
	for (int i = i0 - r; i <= i0 + r; i++) {
		for (int j = j0 - r; j <= j0 + r; j++) {
			int f = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;
			if (f <= 0 && f >= -bold) {
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	const int i0 = 100, i1 = 200;
	const int j0 = 50, j1 = 80;

	//TODO: try moving object
}

void drawArrow(const char& direction,const int& i0, const int& j0, const int& length, const float& red, const float& green, const float& blue) {
	
	if (direction == 'L' || direction == 'l') {
		drawLine(i0 - length, j0, i0, j0, red, green, blue);
		drawLine(i0 - length, j0, i0 - length+15, j0+15, red, green, blue);
		drawLine(i0 - length, j0, i0 - length+15, j0-15, red, green, blue);
	}
	else if (direction == 'R' || direction == 'r') {
		drawLine(i0, j0, i0 + length, j0, red, green, blue);
		drawLine(i0 + length -15, j0+15, i0 + length, j0, red, green, blue);
		drawLine(i0 +length -15, j0-15, i0 + length, j0, red, green, blue);
	}
	else if (direction == 'U' || direction == 'u') {
		for (int j = j0; j <= j0 + length; j++)
		{
			drawPixel(i0, j, red, green, blue);
		}
		drawLine(i0 - 15, j0 + length - 15, i0, j0 + length, red, green, blue);
		drawLine(i0, j0 + length, i0 + 15, j0 + length - 15, red, green, blue);
	}
	else if (direction == 'D' || direction == 'd') {
		for (int j = j0; j >= j0 - length; j--)
		{
			drawPixel(i0, j, red, green, blue);
		}
		drawLine(i0 - 15, j0 - length + 15, i0, j0 - length, red, green, blue);
		drawLine(i0, j0 - length, i0 + 15, j0 -length + 15, red, green, blue);
	}
}

void drawA(const int& i0, const int& j0, const int& length, const float& red, const float& green, const float& blue) {
	drawLine(i0+length/4, j0+length/4 * 1.732, i0 + length*3/4, j0+length/4*1.732, 1.0f, 0.0f, 0.0f);
	drawLine(i0, j0, i0 + length / 2, j0 + length / 2 * 1.732, 1.0f, 0.0f, 0.0f);
	drawLine(i0 + length / 2, j0 + length / 2 * 1.732, i0 + length, j0, 1.0f, 0.0f, 0.0f);
}

bool isInCircle(const int& i0, const int& j0, int i1, int j1, const float& r) {
	int f = (i1 - i0)*(i1 - i0) + (j1 - j0)*(j1 - j0) - r*r;
	if (f <= 0) {
		return 1;
	}
	else
		return 0;
}

int main(void)
{
	GLFWwindow* window;
	double xpos, ypos;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function
		glfwGetCursorPos(window, &xpos, &ypos);
		
		drawCircle(100, 450, 75, 300,1.0f, 0.0f, 0.0f);
		if (isInCircle(100, 150, xpos, ypos, 75)) {
			drawCircle(100, 450, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawBoldLine(70, 420, 130, 480, 1.0f, 0.0f, 0.0f);
		//사선

		drawCircle(300, 450, 75, 300, 1.0f, 0.0f, 0.0f);
		if (isInCircle(300, 150, xpos, ypos, 75)) {
			drawCircle(300, 450, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawCircle(300, 450, 40, 450, 1.0f, 0.0f, 0.0f);
		//작은원

		drawCircle(500, 450, 75, 300, 1.0f, 0.0f, 0.0f);
		if (isInCircle(500, 150, xpos, ypos, 75)) {
			drawCircle(500, 450, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawSquare(500, 450, 50, 1.0f, 0.0f, 0.0f);
		//사각형

		drawCircle(700, 450, 75, 300, 1.0f, 0.0f, 0.0f);
		if (isInCircle(700, 150, xpos, ypos, 75)) {
			drawCircle(700, 450, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawLine(670, 420, 730, 480, 1.0f, 0.0f, 0.0f);
		drawLine( 670, 480, 730, 420, 1.0f, 0.0f, 0.0f);
		//X자

		drawCircle(900, 450, 75, 300, 1.0f, 0.0f, 0.0f);
		if (isInCircle(900, 150, xpos, ypos, 75)) {
			drawCircle(900, 450, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawArrow('d', 900, 480, 60, 1.0f, 0.0f, 0.0f);
		//아래화살표

		drawCircle(100, 150, 75, 300, 1.0f, 0.0f, 0.0f);
		if (isInCircle(100, 450, xpos, ypos, 75)) {
			drawCircle(100, 150, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawArrow('r', 70, 150, 60, 1.0f, 0.0f, 0.0f);
		//오른쪽화살표

		drawCircle(300, 150, 75, 300, 1.0f, 0.0f, 0.0f);
		if (isInCircle(300, 450, xpos, ypos, 75)) {
			drawCircle(300, 150, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawA(250,120,100, 1.0f, 0.0f, 0.0f);
		//A

		drawCircle(500, 150, 75, 300, 1.0f, 0.0f, 0.0f);
		if (isInCircle(500, 450, xpos, ypos, 75)) {
			drawCircle(500, 150, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawHeightLine(500, 180, 500, 120, 1.0f, 0.0f, 0.0f);
		//세로선
		
		drawCircle(700, 150, 75, 300, 1.0f, 0.0f, 0.0f);
		if (isInCircle(700, 450, xpos, ypos, 75)) {
			drawCircle(700, 150, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawArrow('l', 730, 150, 60, 1.0f, 0.0f, 0.0f);
		//왼쪽 화살표

		drawCircle(900, 150, 75, 300, 1.0f, 0.0f, 0.0f); 
		if (isInCircle(900, 450, xpos, ypos, 75)) {
			drawCircle(900, 150, 75, 300, 0.0f, 0.0f, 1.0f);
		}
		drawArrow('u', 900, 120, 60, 1.0f, 0.0f, 0.0f);
		//위 화살표

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}