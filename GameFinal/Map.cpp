#include"Map.h"
#include "AssetIDs.h"
#include "Camera.h"
#include "debug.h"
Map::Map(int ID, LPCWSTR Filepath, int Rows, int Cols, int Tiles, int TileColumn)
{
	this->id = ID;
	this->FilepathMap = Filepath;
	this->rows = Rows;
	this->collumns = Cols;
	this->TileSetWidth = Tiles;


	ReadMap();
	Load();
	//DrawMap();
}
void Map::Load() {
	std::ifstream f;
	f.open(FilepathMap);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < collumns; j++)
		{
			f >> TileMapID[i][j];
		}
	}
}

void Map::ReadMap()
{
	CTextures* texture = CTextures::GetInstance();
	LPTEXTURE texMap = texture->Get(id);
	int id_sprite = 1;
	for (UINT i = 0; i < TileSetWidth; i++)
	{
		for (UINT j = 0; j < TileSetWidth; j++)
		{
			int id_Sprites = id + id_sprite;
			CSprites::GetInstance()->Add(id_Sprites, FrameWidth * j, FrameHeight * i, FrameWidth * (j + 1), FrameHeight * (i + 1), texMap);
			id_sprite = id_sprite + 1;
		}
	}


}
void Map::DrawMap()
{
	CSprites* sprites = CSprites::GetInstance();
	int firstcol = (int)Camera::GetInstance()->GetCamPosX() /8 ;
	
	if (firstcol < 0) { firstcol = 0; }
	int lastcol = firstcol + 20;
	for (UINT i = 0; i < rows; i++)
		for (UINT j = firstcol; j < lastcol; j++)
		{
			
			RECT r;
			UINT x = (TileMapID[i][j] - 1) % TileSetWidth;// nums column in Map1-1
			UINT y; // nums row in Map 1-1
			if (TileMapID[i][j] % TileSetWidth == 0)
			{
				y = floor((TileMapID[i][j] - 1) / TileSetWidth);
			}
			else
			{
				y = floor(TileMapID[i][j] / TileSetWidth);
			}
			r.left = x * FrameWidth;
			r.top = y * FrameHeight;
			r.right = r.left + FrameWidth;
			r.bottom = r.top + FrameHeight;
			CGame::GetInstance()->Draw((j * FrameWidth), (i * FrameHeight) - 238, CTextures::GetInstance()->Get(id), r.left, r.top, r.right, r.bottom);
		}
}