#pragma once
#include <list>
#include"string"
using namespace std;
class Formule
{
public:
	list<string> function = { "sin(a)","cos(a)","tan(a)","atan(a)","exp(a)" };
	list<string> variables;
	list<string> parameters = { "R1.W","R1.L","R1.Rs","R1.Freq" };
};