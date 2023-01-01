#include "GameObject.h"
#include "AssetIDs.h"
#define Frame 16
class CPipe : public CGameObject
{
public:
	float width, height;
	float cellWidth;
	float cellHeight;
	int length;
	bool isSwitchScene;
	int typePipe;
	int sprites_id_1, sprites_id_2, sprites_id_3, sprites_id_4;
public:
	CPipe(float x, float y, float w, float h, float cw, float ch, int l, int sprites1, int sprites2,int sprites3,int sprites4, int typeP) : CGameObject(x, y) {
		width = w;
		height = h;
		cellWidth = cw;
		cellHeight = ch;
		length = l;
		sprites_id_1 = sprites1;
		sprites_id_2 = sprites2;
		sprites_id_3 = sprites3;
		sprites_id_4 = sprites4;
		typePipe = typeP;
		isSwitchScene = false;
		type = OBJECT_TYPE_PIPE;
	}
	void RenderBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual float GetWidth() { return width; };
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	//virtual int IsBlockingOnSide(){ return 0; };
	//virtual int IsBlockingOnTop() { return 1; };
	virtual void DirectBlocking(int& l, int& t, int& r, int& b) {
		l = 1; 
		if (!isSwitchScene)
		{
			t = 1;
		}
		else
			t = 0;
		b = 1; 
		r = 1; 
	}
};