#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "DirectXTK/Inc/SpriteBatch.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
	Player* GetPlayer()
	{
		return m_pl;
	}
private:
	CSoundEngine m_soundEnigne;					//サウンドエンジン
	CSoundSource m_gameBGM;						//ゲームのBGM

	ID3D11Device* m_device;									//構築済み
	ID3D11DeviceContext* m_deviceContext;					//構築済み
	DirectX::SpriteBatch* m_spriteBatch;					//スプライトバッチ
	ID3D11ShaderResourceView* m_shaderResourceView;			//読み込んだ画像ファイルの保存先

	Player* m_pl = nullptr;						//プレイヤーのインスタンス
	Stage* m_stage = nullptr;					//ステージのインスタンス
	Enemy* m_ene = nullptr;						//エネミーのインスタンス
	GameCamera* m_gCamera = nullptr;			//ゲームカメラのインスタンス
	Saru* m_saru[2] = {nullptr, nullptr};		//サルクラスのインスタンス
};

