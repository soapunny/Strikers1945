#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
    //// 1) �迭
    //Enemy* enemys = new Enemy[10];
    //for (int i = 0; i < 10; i++)
    //{
    //    enemys[i].Init();               //Ŭ�����ϱ� .
    //}

    //// 2) vector push_back()
    //for (int i = 0; i < 10; i++)
    //{
    //    vEnemys.push_back(new Enemy());
    //    vEnemys[i]->Init();             //�����ʹϱ� ->
    //}

    //// 3) vector resize()   :������ Ÿ������ enemy ���� ��ŭ ���� �Ҵ� �� �� �ִ� ������ ����ش�(�޸� ������ ��� Ÿ�Ա��� �ɾ��ش�)
    //vEnemys.resize(10);     //vEnemys.push_back(nullptr); �̰� 10�� �� �شٴ� ���̴�
    //for (int i = 0; i < 10; i++)
    //{
    //    vEnemys[i] = new Enemy();           //�̰� �ٷ� ����
    //    vEnemys[i]->Init(); 
    //}

    //// 4) vector reserve()  :������ ���� enemy ���� ��ŭ ���� �Ҵ� �� �� �ִ� ������ ����ش�(�޸� ������ ��Ƶд�)
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
    //�ݺ���(iterator) :  STL �ڷᱸ���� �����ϴ� ������ �޸𸮸� �����ϴ� ��ü
    vector<Enemy*>::iterator myIt;
    for (myIt = vEnemys.begin(); myIt != vEnemys.end(); myIt++)
    {
        (*myIt)->Release();     //iterator�� ���ؼ� ���� ���� Enemy*(������)�ϱ� ->�� ����Ѵ� (*(*myIt)).Release();�� ������ ���� �ִ�
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
