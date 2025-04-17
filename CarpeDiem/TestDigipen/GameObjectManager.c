//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file			  GameObjectManager.c
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief            Responsible for game object pooling and gameobjects Update and Render Cycle
*//*______________________________________________________________________*/

#include "GameObjectManager.h"

void GameManager_Init(void)
{
	//////////////////////////////////////////////////////////////////////////////
	//Initialise the entire ObjData with basic values
	for (int i = 0; i < NUM_OF_TYPES_OBJS; i++)
	{
		_ObjData[i].m_LocalPos = CP_Vector_Set(0, 0);
		_ObjData[i].m_GlobalPos = CP_Vector_Set(0, 0);
		_ObjData[i].m_Vel = CP_Vector_Set(0, 0);
		_ObjData[i].m_AngularVel = CP_Vector_Set(0, 0);
		_ObjData[i].m_RenderAngle = 0;
		_ObjData[i].m_RenderScale = 1;
		_ObjData[i].m_Scale = 1;
		_ObjData[i].m_ID = -1; //Invalid ID as second checking to make sure to skip
		_ObjData[i].m_Active = false;
		_ObjData[i].m_Mass = 1.0;

		_ObjData[i].OBJ_Init = NULL;
		_ObjData[i].OBJ_Update = NULL;
		_ObjData[i].OBJ_Render = NULL;
		_ObjData[i].OBJ_Destroy = NULL;
	}

	//////////////////////////////////////////////////////////////////////////////
	//Setting in values for empty GameOBJ
	_EmptyGameOBJ.m_LocalPos = CP_Vector_Set(0, 0);
	_EmptyGameOBJ.m_GlobalPos = CP_Vector_Set(0, 0);
	_EmptyGameOBJ.m_Vel = CP_Vector_Set(0, 0);
	_EmptyGameOBJ.m_RenderAngle = 0;
	_EmptyGameOBJ.m_RenderScale = 1;
	_EmptyGameOBJ.m_ID = -1; //Invalid ID as second checking to make sure to skip
	_EmptyGameOBJ.m_Active = false;
	_EmptyGameOBJ.m_Mass = 1.0;
	_EmptyGameOBJ.OBJ_Init = NULL;
	_EmptyGameOBJ.OBJ_Update = NULL;
	_EmptyGameOBJ.OBJ_Render = NULL;
	_EmptyGameOBJ.OBJ_Destroy = NULL;

	//////////////////////////////////////////////////////////////////////////////
	//Setting in respective OBJ database values
	//Player
	_ObjData[id_Player].m_ID = id_Player;
	_ObjData[id_Player].OBJ_Init = (fnPtr)GameObject_Player_Init;
	_ObjData[id_Player].OBJ_Update = (fnPtr)GameObject_Player_Update;
	_ObjData[id_Player].OBJ_Render = (fnPtr)GameObject_Player_Render;
	_ObjData[id_Player].OBJ_Destroy = (fnPtr)GameObject_Player_Destroy;
	_ObjData[id_Player].OBJ_Init(&_ObjData[id_Player], m_WorldCenter);

	//Asteroid
	_ObjData[id_Asteroid].m_ID = id_Asteroid;
	_ObjData[id_Asteroid].OBJ_Init = (fnPtr)GameObject_Asteroid_Init;
	_ObjData[id_Asteroid].OBJ_Update = (fnPtr)GameObject_Asteroid_Update;
	_ObjData[id_Asteroid].OBJ_Render = (fnPtr)GameObject_Asteroid_Render;
	_ObjData[id_Asteroid].OBJ_Destroy = (fnPtr)GameObject_Asteroid_Destroy;
	_ObjData[id_Asteroid].OBJ_Init(&_ObjData[id_Asteroid], m_WorldCenter);

	//Bullet
	_ObjData[id_Player_Bullet].m_ID = id_Player_Bullet;
	_ObjData[id_Player_Bullet].OBJ_Init = (fnPtr)GameObject_Bullet_Init;
	_ObjData[id_Player_Bullet].OBJ_Update = (fnPtr)GameObject_Bullet_Update;
	_ObjData[id_Player_Bullet].OBJ_Render = (fnPtr)GameObject_Bullet_Render;
	_ObjData[id_Player_Bullet].OBJ_Destroy = (fnPtr)GameObject_Bullet_Destroy;
	_ObjData[id_Player_Bullet].OBJ_Init(&_ObjData[id_Player_Bullet], m_WorldCenter);

	//Enemy Bullet
	_ObjData[id_Enemy_Bullet].m_ID = id_Enemy_Bullet;
	_ObjData[id_Enemy_Bullet].OBJ_Init = (fnPtr)GameObject_EnemyBullet_Init;
	_ObjData[id_Enemy_Bullet].OBJ_Update = (fnPtr)GameObject_EnemyBullet_Update;
	_ObjData[id_Enemy_Bullet].OBJ_Render = (fnPtr)GameObject_EnemyBullet_Render;
	_ObjData[id_Enemy_Bullet].OBJ_Destroy = (fnPtr)GameObject_EnemyBullet_Destroy;
	_ObjData[id_Enemy_Bullet].OBJ_Init(&_ObjData[id_Enemy_Bullet], m_WorldCenter);

	//Enemy Bullet TypeS
	_ObjData[id_Enemy_BulletTypeS].m_ID = id_Enemy_BulletTypeS;
	_ObjData[id_Enemy_BulletTypeS].OBJ_Init = (fnPtr)GameObject_EnemyBulletTypeS_Init;
	_ObjData[id_Enemy_BulletTypeS].OBJ_Update = (fnPtr)GameObject_EnemyBulletTypeS_Update;
	_ObjData[id_Enemy_BulletTypeS].OBJ_Render = (fnPtr)GameObject_EnemyBulletTypeS_Render;
	_ObjData[id_Enemy_BulletTypeS].OBJ_Destroy = (fnPtr)GameObject_EnemyBulletTypeS_Destroy;
	_ObjData[id_Enemy_BulletTypeS].OBJ_Init(&_ObjData[id_Enemy_BulletTypeS], m_WorldCenter);

	//Enemy Hare
	_ObjData[id_Enemy_Hare].m_ID = id_Enemy_Hare;
	_ObjData[id_Enemy_Hare].OBJ_Init = (fnPtr)GameObject_Enemy_Hare_Init;
	_ObjData[id_Enemy_Hare].OBJ_Update = (fnPtr)GameObject_Enemy_Hare_Update;
	_ObjData[id_Enemy_Hare].OBJ_Render = (fnPtr)GameObject_Enemy_Hare_Render;
	_ObjData[id_Enemy_Hare].OBJ_Destroy = (fnPtr)GameObject_Enemy_Hare_Destroy;
	_ObjData[id_Enemy_Hare].OBJ_Init(&_ObjData[id_Enemy_Hare], m_WorldCenter);

	//Enemy Bandit
	_ObjData[id_Enemy_Bandit].m_ID = id_Enemy_Bandit;
	_ObjData[id_Enemy_Bandit].OBJ_Init = (fnPtr)GameObject_Enemy_Bandit_Init;
	_ObjData[id_Enemy_Bandit].OBJ_Update = (fnPtr)GameObject_Enemy_Bandit_Update;
	_ObjData[id_Enemy_Bandit].OBJ_Render = (fnPtr)GameObject_Enemy_Bandit_Render;
	_ObjData[id_Enemy_Bandit].OBJ_Destroy = (fnPtr)GameObject_Enemy_Bandit_Destroy;
	_ObjData[id_Enemy_Bandit].OBJ_Init(&_ObjData[id_Enemy_Bandit], m_WorldCenter);

	//Enemy Bomber
	_ObjData[id_Enemy_Bomber].m_ID = id_Enemy_Bomber;
	_ObjData[id_Enemy_Bomber].OBJ_Init = (fnPtr)GameObject_Enemy_Bomber_Init;
	_ObjData[id_Enemy_Bomber].OBJ_Update = (fnPtr)GameObject_Enemy_Bomber_Update;
	_ObjData[id_Enemy_Bomber].OBJ_Render = (fnPtr)GameObject_Enemy_Bomber_Render;
	_ObjData[id_Enemy_Bomber].OBJ_Destroy = (fnPtr)GameObject_Enemy_Bomber_Destroy;
	_ObjData[id_Enemy_Bomber].OBJ_Init(&_ObjData[id_Enemy_Bomber], m_WorldCenter);

	//Score Orb
	_ObjData[id_ScoreOrb].m_ID = id_ScoreOrb;
	_ObjData[id_ScoreOrb].OBJ_Init = (fnPtr)GameObject_ScoreOrb_Init;
	_ObjData[id_ScoreOrb].OBJ_Update = (fnPtr)GameObject_ScoreOrb_Update;
	_ObjData[id_ScoreOrb].OBJ_Render = (fnPtr)GameObject_ScoreOrb_Render;
	_ObjData[id_ScoreOrb].OBJ_Destroy = (fnPtr)GameObject_ScoreOrb_Destroy;
	_ObjData[id_ScoreOrb].OBJ_Init(&_ObjData[id_ScoreOrb], m_WorldCenter);

	//////////////////////////////////////////////////////////////////////////////
	//Initalising linked list
	for (int i = 0; i < NUM_OF_OBJS; i++)
	{
		_List[i].node_num = i;
		_List[i].next_node_num = -1;
		_List[i].last_node_num = -1;
		_List[i]._OBJ = _ObjData[NUM_OF_TYPES_OBJS-1];
	}

	//Setting up Player
	_List[id_Player]._OBJ = _ObjData[id_Player];

	//////////////////////////////////////////////////////////////////////////////
    // Initalising Game World Variables
	m_WorldCenter = CP_Vector_Set(m_NewWindowScale.x / 2, m_NewWindowScale.y / 2);

	//Again, I'm writing this here because I'm too lazy to write a good solution to this.
	m_AsteroidSmallPNG1 = CP_Image_Load("Assets/GameObject_EAsteroidSmall.png");
	m_AsteroidSmallPNG2 = CP_Image_Load("Assets/GameObject_EAsteroidSmall2.png");
	m_AsteroidMediumPNG1 = CP_Image_Load("Assets/GameObject_EAsteroidMed.png");
	m_AsteroidMediumPNG2 = CP_Image_Load("Assets/GameObject_EAsteroidMed2.png");
	m_AsteroidLargePNG1 = CP_Image_Load("Assets/GameObject_EAsteroidBIG.png");
	m_AsteroidLargePNG2 = CP_Image_Load("Assets/GameObject_EAsteroidBIG2.png");
}

void GameManager_Update(void)
{
	if (_List == NULL || isGamePaused)
		return;

	//////////////////////////////////////////////////////////////////////////////
	//Run Collision Checking
	for (int HeaderNum = 1; HeaderNum < NUM_OF_TYPES_OBJS; HeaderNum++)
	{
		RunCheckCollision(HeaderNum);
		//Destroy 
	}
	//////////////////////////////////////////////////////////////////////////////
	//Update Player
	_List[0]._OBJ.OBJ_Update(&_List[0]._OBJ, &m_WorldCenter);
	//////////////////////////////////////////////////////////////////////////////
	//Update Other Linked List
	int tempNodeNum = 0;
	for (int HeaderNum = 1; HeaderNum < NUM_OF_TYPES_OBJS; HeaderNum++)
	{
		tempNodeNum = _List[HeaderNum].next_node_num;
		if (tempNodeNum < 1)//Exception checking in case array checks for lower than 0
			continue;

		int dataholder;
		while (tempNodeNum != -1 && _List[tempNodeNum]._OBJ.m_ID != -1)
		{
			dataholder = _List[tempNodeNum].next_node_num;

			//Run GameObject Update
			_List[tempNodeNum]._OBJ.OBJ_Update(&_List[tempNodeNum]._OBJ, &m_WorldCenter);
			
			//Despawn if too far
			if(CP_Vector_Distance(_List[id_Player]._OBJ.m_GlobalPos, _List[tempNodeNum]._OBJ.m_GlobalPos)>2000)
				GameManager_DestroyOBJ(tempNodeNum);

			tempNodeNum = dataholder;
		}
	}
}

void GameManager_Render(void)
{
	if (_List == NULL)
		return;
	
	//////////////////////////////////////////////////////////////////////////////
    //Render Player
	_List[0]._OBJ.OBJ_Render(&_List[0]._OBJ, &m_WorldCenter);
	//////////////////////////////////////////////////////////////////////////////
	//Render Other Linked List
	int tempNodeNum = 0;
	for (int HeaderNum = 1; HeaderNum < NUM_OF_TYPES_OBJS; HeaderNum++)
	{
		tempNodeNum = _List[HeaderNum].next_node_num;
		if (tempNodeNum < 1)//Exception checking in case array checks for lower than 0
			continue;

		while (tempNodeNum != -1 && _List[tempNodeNum]._OBJ.m_ID != -1)
		{
			_List[tempNodeNum]._OBJ.OBJ_Render(&_List[tempNodeNum]._OBJ, &m_WorldCenter);
			tempNodeNum = _List[tempNodeNum].next_node_num;
		}
	}
}


void GameManager_End(void)
{
	if (_List == NULL)
		return;

	for (int i = 0; i < NUM_OF_OBJS; i++)
	{
		if (_ObjData[i].m_ID == -1)
			break;

		CP_Image_Free(&_ObjData[i].m_PNG);
	}

	//Again, I'm writing this here because I'm too lazy to write a good solution to this.
	CP_Image_Free(&m_AsteroidSmallPNG1); 
	CP_Image_Free(&m_AsteroidSmallPNG2); 
	CP_Image_Free(&m_AsteroidMediumPNG1);
	CP_Image_Free(&m_AsteroidMediumPNG2);
	CP_Image_Free(&m_AsteroidLargePNG1);
	CP_Image_Free(&m_AsteroidLargePNG2);

}

int GameManager_GetEmptyNode(void)
{
	for (int i = NUM_OF_TYPES_OBJS; i < NUM_OF_OBJS; i++)
	{
		//Continue in the array if current element is occupied
		if (_List[i]._OBJ.m_ID != -1)
			continue;

		return i;
	}

	return -1;//Throw error
}

int GameManager_SpawnOBJ(ObjData type)
{
	GameObject tempOBJ;
	tempOBJ = _ObjData[type];
	int num = GameManager_GetEmptyNode();

	//////////////////////////////////////////////////////////////////////////////
	//Create GameObject in that element
	_List[num]._OBJ = tempOBJ;
	_List[num]._OBJ.m_NodeID = num;
	//////////////////////////////////////////////////////////////////////////////
	//Link to the correct linked list
	int tempNodeNum = _List[type].next_node_num;
	if (tempNodeNum == -1)//if the linklist currently has no objs
	{
		_List[type].next_node_num = num;
		_List[num].last_node_num = type;
	}
	else//if the linklist currently has objs
	{
		while (_List[tempNodeNum].next_node_num != -1)
		{
			tempNodeNum = _List[tempNodeNum].next_node_num;
		}
		_List[tempNodeNum].next_node_num = num;
		_List[num].last_node_num = tempNodeNum;
	}
	return num;
}

void GameManager_DestroyOBJ(int NodeNum)
{
	_List[NodeNum]._OBJ.OBJ_Destroy(_List[NodeNum]);
	_List[_List[NodeNum].last_node_num].next_node_num = _List[NodeNum].next_node_num;
	_List[_List[NodeNum].next_node_num].last_node_num = _List[NodeNum].last_node_num;
	_List[NodeNum].next_node_num = _List[NodeNum].last_node_num = -1;
	_List[NodeNum]._OBJ = _EmptyGameOBJ;
}

void RunCheckCollision(int HeaderNum)
{
	//////////////////////////////////////////////////////////////////////////////
	//GameObjects Collision Checks
	int tempNodeNum = 0;
	tempNodeNum = _List[HeaderNum].next_node_num;
	if (tempNodeNum < 1)//Exception checking in case array checks for lower than 0
		return;
	switch (HeaderNum)
	{
	case id_Asteroid://Asteroid
		while (tempNodeNum != -1 && _List[tempNodeNum]._OBJ.m_ID != -1)
		{
			//////////////////////////////////////////////////////////////////////////////////////////
			//With Each Other
			int dataholder = _List[tempNodeNum].next_node_num;

			int nextTempNode = _List[tempNodeNum].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					HandleCollision(&_List[tempNodeNum]._OBJ, &_List[nextTempNode]._OBJ);
				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//With Player
			if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[id_Player]._OBJ))
			{
				_List[id_Player]._OBJ.m_Health -= (int)(CP_Vector_Length(CP_Vector_Subtract(_List[tempNodeNum]._OBJ.m_Vel, _List[id_Player]._OBJ.m_Vel)) 
												  * _List[tempNodeNum]._OBJ.m_Mass / 800);
				CurrentHealth = _List[id_Player]._OBJ.m_Health;

				Util_Window_Shake(0.75f, (float)(CP_Vector_Length(CP_Vector_Subtract(_List[tempNodeNum]._OBJ.m_Vel, _List[id_Player]._OBJ.m_Vel))
										* _List[tempNodeNum]._OBJ.m_Mass / 800)*5);

				HandleCollision(&_List[tempNodeNum]._OBJ, &_List[id_Player]._OBJ);

				for (int i = 0; i < _List[tempNodeNum]._OBJ.m_Mass / 20; i++)
				{
					//Spawn Score Orbs
					int temp = GameManager_SpawnOBJ(id_ScoreOrb);
					_List[temp]._OBJ.m_GlobalPos = _List[tempNodeNum]._OBJ.m_GlobalPos;
					_List[temp]._OBJ.m_LocalPos = _List[tempNodeNum]._OBJ.m_LocalPos;
					_List[temp]._OBJ.m_Vel = CP_Vector_Set(CP_Random_RangeFloat(-10, 10), CP_Random_RangeFloat(-10, 10));
					_List[temp]._OBJ.m_ColorR = CP_Random_RangeFloat(0, 255);
					_List[temp]._OBJ.m_ColorG = CP_Random_RangeFloat(0, 255);
					_List[temp]._OBJ.m_ColorB = CP_Random_RangeFloat(0, 255);
				}

				GameManager_DestroyOBJ(tempNodeNum);
			}
			tempNodeNum = dataholder;
		}
		break;
	case id_Player_Bullet:
		while (tempNodeNum != -1 && _List[tempNodeNum]._OBJ.m_ID != -1)
		{
			//////////////////////////////////////////////////////////////////////////////////////////
			//With Asteroid
			int dataholder = _List[tempNodeNum].next_node_num;

			int nextTempNode = _List[id_Asteroid].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1 && _List[tempNodeNum]._OBJ.m_Active)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					_List[nextTempNode]._OBJ.m_Health -= _List[tempNodeNum]._OBJ.m_Bullet_Dmg;
					_List[nextTempNode]._OBJ.m_DamageResponseTimer = 0.25f;
					_List[tempNodeNum]._OBJ.m_Active = false;

					if (_List[nextTempNode]._OBJ.m_Health <= 0)
					{
						for (int i = 0; i < _List[nextTempNode]._OBJ.m_Mass / 15; i++)
						{
							//Spawn Score Orbs
							int temp = GameManager_SpawnOBJ(id_ScoreOrb);
							_List[temp]._OBJ.m_GlobalPos = _List[tempNodeNum]._OBJ.m_GlobalPos;
							_List[temp]._OBJ.m_LocalPos = _List[tempNodeNum]._OBJ.m_LocalPos;
							_List[temp]._OBJ.m_Vel = CP_Vector_Set(CP_Random_RangeFloat(-10, 10), CP_Random_RangeFloat(-10, 10));
							_List[temp]._OBJ.m_ColorR = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorG = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorB = CP_Random_RangeFloat(0, 255);
						}
						GameManager_DestroyOBJ(nextTempNode);
					}
						
				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//With Enemy Hare
			nextTempNode = _List[id_Enemy_Hare].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1 && _List[tempNodeNum]._OBJ.m_Active)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					_List[nextTempNode]._OBJ.m_Health -= _List[tempNodeNum]._OBJ.m_Bullet_Dmg;
					_List[nextTempNode]._OBJ.m_DamageResponseTimer = 0.25f;
					_List[tempNodeNum]._OBJ.m_Active = false;

					if (_List[nextTempNode]._OBJ.m_Health <= 0)
					{
						for (int i = 0; i < _List[nextTempNode]._OBJ.m_Mass / 3; i++)
						{
							//Spawn Score Orbs
							int temp = GameManager_SpawnOBJ(id_ScoreOrb);
							_List[temp]._OBJ.m_GlobalPos = _List[tempNodeNum]._OBJ.m_GlobalPos;
							_List[temp]._OBJ.m_LocalPos = _List[tempNodeNum]._OBJ.m_LocalPos;
							_List[temp]._OBJ.m_Vel = CP_Vector_Set(CP_Random_RangeFloat(-10, 10), CP_Random_RangeFloat(-10, 10));
							_List[temp]._OBJ.m_ColorR = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorG = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorB = CP_Random_RangeFloat(0, 255);
						}
						GameManager_DestroyOBJ(nextTempNode);
					}
				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//With Enemy Bandit
			nextTempNode = _List[id_Enemy_Bandit].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1 && _List[tempNodeNum]._OBJ.m_Active)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					_List[nextTempNode]._OBJ.m_Health -= _List[tempNodeNum]._OBJ.m_Bullet_Dmg;
					_List[nextTempNode]._OBJ.m_DamageResponseTimer = 0.25f;
					_List[tempNodeNum]._OBJ.m_Active = false;

					if (_List[nextTempNode]._OBJ.m_Health <= 0)
					{
						for (int i = 0; i < _List[nextTempNode]._OBJ.m_Mass / 5; i++)
						{
							//Spawn Score Orbs
							int temp = GameManager_SpawnOBJ(id_ScoreOrb);
							_List[temp]._OBJ.m_GlobalPos = _List[tempNodeNum]._OBJ.m_GlobalPos;
							_List[temp]._OBJ.m_LocalPos = _List[tempNodeNum]._OBJ.m_LocalPos;
							_List[temp]._OBJ.m_Vel = CP_Vector_Set(CP_Random_RangeFloat(-10, 10), CP_Random_RangeFloat(-10, 10));
							_List[temp]._OBJ.m_ColorR = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorG = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorB = CP_Random_RangeFloat(0, 255);
						}
						GameManager_DestroyOBJ(nextTempNode);
					}
				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//With Enemy Bomber
			nextTempNode = _List[id_Enemy_Bomber].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1 && _List[tempNodeNum]._OBJ.m_Active)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					_List[nextTempNode]._OBJ.m_Health -= _List[tempNodeNum]._OBJ.m_Bullet_Dmg;
					_List[nextTempNode]._OBJ.m_DamageResponseTimer = 0.25f;
					_List[tempNodeNum]._OBJ.m_Active = false;

					if (_List[nextTempNode]._OBJ.m_Health <= 0)
					{
						for (int i = 0; i < _List[nextTempNode]._OBJ.m_Mass / 2; i++)
						{
							//Spawn Score Orbs
							int temp = GameManager_SpawnOBJ(id_ScoreOrb);
							_List[temp]._OBJ.m_GlobalPos = _List[tempNodeNum]._OBJ.m_GlobalPos;
							_List[temp]._OBJ.m_LocalPos = _List[tempNodeNum]._OBJ.m_LocalPos;
							_List[temp]._OBJ.m_Vel = CP_Vector_Set(CP_Random_RangeFloat(-10, 10), CP_Random_RangeFloat(-10, 10));
							_List[temp]._OBJ.m_ColorR = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorG = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorB = CP_Random_RangeFloat(0, 255);
						}
						GameManager_DestroyOBJ(nextTempNode);
					}
				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}
			
			if (tempNodeNum > 0 && !_List[tempNodeNum]._OBJ.m_Active)
				GameManager_DestroyOBJ(tempNodeNum);

			tempNodeNum = dataholder;
		}
		break;
	case id_Enemy_Bullet:
		while (tempNodeNum != -1 && _List[tempNodeNum]._OBJ.m_ID != -1)
		{
			//////////////////////////////////////////////////////////////////////////////////////////
			//With Asteroid
			int dataholder = _List[tempNodeNum].next_node_num;

			int nextTempNode = _List[id_Asteroid].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1 && _List[tempNodeNum]._OBJ.m_Active)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					_List[nextTempNode]._OBJ.m_Health -= _List[tempNodeNum]._OBJ.m_Bullet_Dmg;
					_List[nextTempNode]._OBJ.m_DamageResponseTimer = 0.25f;
					_List[tempNodeNum]._OBJ.m_Active = false;

					if (_List[nextTempNode]._OBJ.m_Health <= 0)
					{
						for (int i = 0; i < _List[nextTempNode]._OBJ.m_Mass / 15; i++)
						{
							//Spawn Score Orbs
							int temp = GameManager_SpawnOBJ(id_ScoreOrb);
							_List[temp]._OBJ.m_GlobalPos = _List[tempNodeNum]._OBJ.m_GlobalPos;
							_List[temp]._OBJ.m_LocalPos = _List[tempNodeNum]._OBJ.m_LocalPos;
							_List[temp]._OBJ.m_Vel = CP_Vector_Set(CP_Random_RangeFloat(-10, 10), CP_Random_RangeFloat(-10, 10));
							_List[temp]._OBJ.m_ColorR = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorG = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorB = CP_Random_RangeFloat(0, 255);
						}
						GameManager_DestroyOBJ(nextTempNode);
					}

				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//With Player
			if (tempNodeNum > 0 && AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[id_Player]._OBJ))
			{
				_List[id_Player]._OBJ.m_Health -= _List[tempNodeNum]._OBJ.m_Bullet_Dmg;
				CurrentHealth = _List[id_Player]._OBJ.m_Health;

				Util_Window_Shake(0.75f, (float)_List[tempNodeNum]._OBJ.m_Bullet_Dmg*5.0f);
				HandleCollision(&_List[tempNodeNum]._OBJ, &_List[id_Player]._OBJ);
				_List[tempNodeNum]._OBJ.m_Active = false;
			}

			if (tempNodeNum > 0 && !_List[tempNodeNum]._OBJ.m_Active)
				GameManager_DestroyOBJ(tempNodeNum);

			tempNodeNum = dataholder;
		}
		break;
	case id_Enemy_BulletTypeS:
		while (tempNodeNum != -1 && _List[tempNodeNum]._OBJ.m_ID != -1)
		{
			//////////////////////////////////////////////////////////////////////////////////////////
			//With Asteroid
			int dataholder = _List[tempNodeNum].next_node_num;

			int nextTempNode = _List[id_Asteroid].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1 && _List[tempNodeNum]._OBJ.m_Active)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					_List[nextTempNode]._OBJ.m_Health -= _List[tempNodeNum]._OBJ.m_Bullet_Dmg;
					_List[tempNodeNum]._OBJ.m_Bullet_Dmg -= (int)(_List[nextTempNode]._OBJ.m_Mass / 3.0);
					if (_List[tempNodeNum]._OBJ.m_Bullet_Dmg < 0)
						_List[tempNodeNum]._OBJ.m_Active = false;

					if (_List[nextTempNode]._OBJ.m_Health <= 0)
					{
						for (int i = 0; i < _List[nextTempNode]._OBJ.m_Mass / 15; i++)
						{
							//Spawn Score Orbs
							int temp = GameManager_SpawnOBJ(id_ScoreOrb);
							_List[temp]._OBJ.m_GlobalPos = _List[tempNodeNum]._OBJ.m_GlobalPos;
							_List[temp]._OBJ.m_LocalPos = _List[tempNodeNum]._OBJ.m_LocalPos;
							_List[temp]._OBJ.m_Vel = CP_Vector_Set(CP_Random_RangeFloat(-10, 10), CP_Random_RangeFloat(-10, 10));
							_List[temp]._OBJ.m_ColorR = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorG = CP_Random_RangeFloat(0, 255);
							_List[temp]._OBJ.m_ColorB = CP_Random_RangeFloat(0, 255);
						}
						GameManager_DestroyOBJ(nextTempNode);
					}

				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//With Player
			if (tempNodeNum > 0 && AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[id_Player]._OBJ))
			{
				_List[id_Player]._OBJ.m_Health -= _List[tempNodeNum]._OBJ.m_Bullet_Dmg;
				CurrentHealth = _List[id_Player]._OBJ.m_Health;

				Util_Window_Shake(0.75f, (float)_List[tempNodeNum]._OBJ.m_Bullet_Dmg * 3.0f);
				HandleCollision(&_List[tempNodeNum]._OBJ, &_List[id_Player]._OBJ);
				_List[tempNodeNum]._OBJ.m_Active = false;
			}

			if (tempNodeNum > 0 &&!_List[tempNodeNum]._OBJ.m_Active)
				GameManager_DestroyOBJ(tempNodeNum);

			tempNodeNum = dataholder;
		}
		break;
	case id_Enemy_Bandit:
	case id_Enemy_Hare:
	case id_Enemy_Bomber:
		while (tempNodeNum != -1 && _List[tempNodeNum]._OBJ.m_ID != -1)
		{
			//////////////////////////////////////////////////////////////////////////////////////////
			//With Each Other
			int dataholder = _List[tempNodeNum].next_node_num;

			int nextTempNode = _List[tempNodeNum].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					HandleCollision(&_List[tempNodeNum]._OBJ, &_List[nextTempNode]._OBJ);
				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//With Asteroid
			nextTempNode = _List[id_Asteroid].next_node_num;
			while (nextTempNode != -1 && _List[nextTempNode]._OBJ.m_ID != -1)
			{
				if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[nextTempNode]._OBJ))
				{
					HandleCollision(&_List[tempNodeNum]._OBJ, &_List[nextTempNode]._OBJ);
				}
				nextTempNode = _List[nextTempNode].next_node_num;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//With Player
			if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[id_Player]._OBJ))
			{
				HandleCollision(&_List[tempNodeNum]._OBJ, &_List[id_Player]._OBJ);

				if (HeaderNum == id_Enemy_Bandit)
				{
					_List[id_Player]._OBJ.m_Health -= (int)(CP_Vector_Length(CP_Vector_Subtract(_List[tempNodeNum]._OBJ.m_Vel, _List[id_Player]._OBJ.m_Vel))
						* _List[tempNodeNum]._OBJ.m_Mass / 400);
					CurrentHealth = _List[id_Player]._OBJ.m_Health;

					Util_Window_Shake(0.75f, (float)(CP_Vector_Length(CP_Vector_Subtract(_List[tempNodeNum]._OBJ.m_Vel, _List[id_Player]._OBJ.m_Vel))
						* _List[tempNodeNum]._OBJ.m_Mass / 400) * 5.0f);
				}
			}
			tempNodeNum = dataholder;
		}
		break;
	case id_ScoreOrb:
		while (tempNodeNum != -1 && _List[tempNodeNum]._OBJ.m_ID != -1)
		{
			//////////////////////////////////////////////////////////////////////////////////////////
			//With Player
			int dataholder = _List[tempNodeNum].next_node_num;
			if (AreGameObjectsIntersecting(_List[tempNodeNum]._OBJ, _List[id_Player]._OBJ))
			{
				UpdatePlayerScore(100);
				GameManager_DestroyOBJ(tempNodeNum);
			}
			tempNodeNum = dataholder;
		}
	default:
		break;

	}
}