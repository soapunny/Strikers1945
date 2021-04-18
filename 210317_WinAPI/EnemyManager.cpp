#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
    //// 1) 배열
    //Enemy* enemys = new Enemy[10];
    //for (int i = 0; i < 10; i++)
    //{
    //    enemys[i].Init();               //클래스니까 .
    //}

    //// 2) vector push_back()
    //for (int i = 0; i < 10; i++)
    //{
    //    vEnemys.push_back(new Enemy());
    //    vEnemys[i]->Init();             //포인터니까 ->
    //}

    //// 3) vector resize()   :포인터 타입으로 enemy 개수 만큼 동적 할당 할 수 있는 공간을 잡아준다(메모리 공간을 잡고 타입까지 걸어준다)
    //vEnemys.resize(10);     //vEnemys.push_back(nullptr); 이걸 10번 해 준다는 것이다
    //for (int i = 0; i < 10; i++)
    //{
    //    vEnemys[i] = new Enemy();           //이거 바로 가능
    //    vEnemys[i]->Init(); 
    //}

    //// 4) vector reserve()  :포인터 없이 enemy 개수 만큼 동적 할당 할 수 있는 공간을 잡아준다(메모리 공간만 잡아둔다)
    //vEnemys.reserve(10);
    //for (int i = 0; i < 10; i++)
    //{
    //    vEnemys.push_back(new Enemy());  
    //    vEnemys[i]->Init();
    //}

    /*
    vEnemys.resize(10);   
    for (int i = 0; i < 10; i++)
    {
        vEnemys[i] = new Enemy();          
        vEnemys[i]->Init(100 + 100 * (i%5), 100 + 500 * (i / 5));
    }
    */

    vEnemys.resize(1);
    for (int i = 0; i < 1; i++)
    {
        vEnemys[i] = new Enemy();
        vEnemys[i]->Init(300, 200);
    }

    return S_OK;
}

void EnemyManager::Release()
{
    //반복자(iterator) :  STL 자료구조를 구성하는 원소의 메모리를 저장하는 객체
    vector<Enemy*>::iterator myIt;
    for (myIt = vEnemys.begin(); myIt != vEnemys.end(); myIt++)
    {
        (*myIt)->Release();     //iterator를 통해서 얻어온 값이 Enemy*(포인터)니까 ->를 사용한다 (*(*myIt)).Release();로 적어줄 수도 있다
        delete (*myIt);
        (*myIt) = nullptr;
    }
    vEnemys.clear();
}

void EnemyManager::Update()
{
    vector<Enemy*>::iterator myIt;
    for (myIt = vEnemys.begin(); myIt != vEnemys.end(); myIt++)
    {
        (*myIt)->Update();
        (*myIt)->SetPlayerPos(this->playerPos);
    }
}

void EnemyManager::Render(HDC hdc)
{
    vector<Enemy*>::iterator myIt;
    for (myIt = vEnemys.begin(); myIt != vEnemys.end(); myIt++)
    {
        (*myIt)->Render(hdc);
    }
}

void EnemyManager::AddEnemy(int size)
{
}
