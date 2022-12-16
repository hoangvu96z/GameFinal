#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Map.h"
#include "Grid.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	CMap* current_map = NULL;
	Grid* grid;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_TILEMAP_DATA(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void SetCam(float cx, float cy, DWORD dt = 0);

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();
	void PushBack(CGameObject* obj)
	{
		Unit* unit = new Unit(grid, obj, obj->x, obj->y);
	}
	Grid* GetGrid() { return grid; }
	CMap* GetMap() { return current_map; }

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	//grid
	void GetObjectFromGrid();
	void UpdateGrid();
};

typedef CPlayScene* LPPLAYSCENE;

