#include<iostream>
#include "OnlyVAOAndVBO.cpp"
#include "VAOVBOAndEBO.cpp"
using namespace std;

int main() {
	auto draw_1 = new OnlyVAOAndVBO();
	auto draw_2 = new VAOVBOAndEBO();
	draw_2->draw();
	return 0;
}