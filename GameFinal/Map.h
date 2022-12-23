#pragma once
#include"Textures.h"
#include "Game.h"
#include "Sprites.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

#define FrameHeight 16
#define FrameWidth	16
#define MAX	300

class Map
{
	LPCWSTR FilepathMap;
	int id;
	int collumns;
	int rows;
	int TileSetWidth;
	int TileSetHeight;
	int TileMapID[MAX][MAX];

public:
	Map(int ID, LPCWSTR Filepath, int Rows, int Cols, int Tiles, int TileColumn);
	void ReadMap();
	void DrawMap();
	void Load();
	int GetMapWidth() { return collumns * TileSetWidth; }
	int GetMapHeight() { return rows * TileSetWidth; }
	~Map();
};
