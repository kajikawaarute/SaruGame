#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "RenderTarget.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "DirectXTK/Inc/SpriteBatch.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class BananaPeel;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
	/// <summary>
	/// Effekserの初期化
	/// </summary>
	void InitEffekseer();
private:
	CSoundEngine m_soundEnigne;					//サウンドエンジン
	CSoundSource m_gameBGM;						//ゲームのBGM

	//ID3D11Device* m_device;									//構築済み
	//ID3D11DeviceContext* m_deviceContext;					//構築済み
	//std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;	//スプライトバッチ
	//ID3D11ShaderResourceView* m_shaderResourceView;			//読み込んだ画像ファイルの保存先

	//Effekseerマネージャー管理
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_effekt = nullptr;		//エフェクト
	Effekseer::Handle m_playEffectHandle = -1;
	Player* m_pl = nullptr;						//プレイヤーのインスタンス
	Stage* m_stage = nullptr;					//ステージのインスタンス
	Enemy* m_ene = nullptr;						//エネミーのインスタンス
	GameCamera* m_gCamera = nullptr;			//ゲームカメラのインスタンス
	Saru* m_saru[2] = {nullptr, nullptr};		//サルクラスのインスタンス

	BananaPeel* m_banaPeel = nullptr;
};

