#pragma once

class Display {
public:
	static void initText();
	static void print(const char* str);
	static void setChar(char x, char y, char chr, char col);
	static void disableCursor();
};
