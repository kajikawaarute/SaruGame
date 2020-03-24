#pragma once
#include "IGameObject.h"

class Game;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	/// <summary>
	/// タイトルの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// タイトルの描画関数
	/// </summary>
	void Draw();
private:
	ID3D11Device* m_device;									//構築済み
	ID3D11DeviceContext* m_deviceContext;					//構築済み
	DirectX::SpriteBatch* m_spriteBatch;					//スプライトバッチ
	ID3D11ShaderResourceView* m_shaderResourceView;			//読み込んだ画像ファイルの保存先

	Game* m_game = nullptr;
};

