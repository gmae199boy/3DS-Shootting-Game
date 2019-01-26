/* -------------------------------------------------------------------------- */
/* File:main.cpp                                                              */
/*                                                                            */
/*     ポリゴン描画の挑戦                                                     */
/*                                                                            */
/*                                                Author : HAL Tokyo - Youhei */
/*                                                Date   : 2018.07.27         */
/* -------------------------------------------------------------------------- */


/* インクルード */
#include <nn/os.h>
#include <nn/gx.h>
#include <nn/init.h>
#include <nn/fnd/fnd_ExpHeap.h>
#include <nn/fs.h>   
#include <nn/math.h> 
#include <demo.h>
#include <algorithm>
#include "textureManager.h"
#include "Polygon.h"

#include <nn/hid.h>

#include "scene.h"


/* -------------------------------------------------------------------------- */
/* 定数定義                                                                   */
/* -------------------------------------------------------------------------- */
#define GX_HEAP_SIZE (0x400000) // GX（グラフィック用）ヒープメモリサイズ => 4MB


/* -------------------------------------------------------------------------- */
/* グローバル変数宣言                                                         */
/* -------------------------------------------------------------------------- */
static nn::fnd::ExpHeap g_Heap;  // ヒープメモリ管理
static uptr g_pHeapForGx = NULL; // GX（グラフィック用）ヒープメモリアドレス格納用ポインタ

static demo::RenderSystem g_RenderSystem; // デモレンダーシステム（描画機能付き）

static GLuint g_PgID; // プログラムID
static GLuint g_ShID; // シェーダーID

// パッドリーダー
static nn::hid::PadReader* g_pPadReader = NULL;


/* -------------------------------------------------------------------------- */
/*　プロトタイプ宣言　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/* -------------------------------------------------------------------------- */
void Initialize(void); //初期化
void Finalize(void); //終了処理
void Update(void); //更新
void Draw_0(void); //上画面描画
void Draw_1(void); //下画面描画
void Set2DMatrix(int display);


/* -------------------------------------------------------------------------- */
/*  関数定義                                                                  */
/* -------------------------------------------------------------------------- */

/* エントリー（メイン）関数 */
void nnMain(void)
{
	/* 初期化 */
	Initialize();

	/* ゲームループ */
	while( true )
    {
		// シーンの確認
		Scene_Check();

		/* 更新 */
		Update();

		/* 描画 */
		Draw_0();//上画面描画
		Draw_1();//下画面描画

		// 垂直同期待ち（両画面）
		g_RenderSystem.WaitVsync(NN_GX_DISPLAY_BOTH);
    }

	//Finalize();

} //end of main

void Initialize(void)
{
	/* 初期化 */

	// レンダーシステム初期化
	g_Heap.Initialize(nn::os::GetDeviceMemoryAddress(), nn::os::GetDeviceMemorySize()); // ヒープメモリの初期化
	g_pHeapForGx = (uptr)g_Heap.Allocate(GX_HEAP_SIZE);                                  // Gx(グラフィック用)ヒープメモリの確保
	g_RenderSystem.Initialize(g_pHeapForGx, GX_HEAP_SIZE);                               // デモレンダーシステム初期化

	// ファイルシステム初期化
	nn::fs::Initialize();
	const size_t ROMFS_BUFFER_SIZE = 1024 * 64;
	static char buffer[ROMFS_BUFFER_SIZE];
	NN_UTIL_PANIC_IF_FAILED(nn::fs::MountRom(16, 16, buffer, ROMFS_BUFFER_SIZE));

	// シェーダ初期化(シェーダーの生成)
	g_PgID = glCreateProgram();
	g_ShID = glCreateShader(GL_VERTEX_SHADER);

	// シェーダーファイルの読み込み
	nn::fs::FileReader file("rom:/VertexShader.shbin");
	size_t fileSize = file.GetSize();
	void* buf = g_Heap.Allocate(fileSize);
	s32 read = file.Read(buf, fileSize);
	glShaderBinary(1, &g_ShID, GL_PLATFORM_BINARY_DMP, buf, read);
	file.Finalize();
	g_Heap.Free(buf);

	glAttachShader(g_PgID, g_ShID);
	glAttachShader(g_PgID, GL_DMP_FRAGMENT_SHADER_DMP);

	glBindAttribLocation(g_PgID, 0, "aPosition");
	glBindAttribLocation(g_PgID, 1, "aColor");
	glBindAttribLocation(g_PgID, 2, "aTexCoord");

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glLinkProgram(g_PgID);
	glValidateProgram(g_PgID);
	glUseProgram(g_PgID);

	// 画面のクリア
	glClearColor(0.05f, 0.1f, 0.1f, 1.0f);
	glClearDepthf(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND); // 有効
	glBlendFunc(GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA);

	glUniform3i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].srcRgb"), GL_TEXTURE0, GL_PRIMARY_COLOR, GL_PRIMARY_COLOR);
	glUniform3i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].srcAlpha"), GL_TEXTURE0, GL_PRIMARY_COLOR, GL_PRIMARY_COLOR);
	glUniform1i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].combineRgb"), GL_MODULATE);
	glUniform1i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].combineAlpha"), GL_MODULATE);
	glUniform3i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
	glUniform3i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
	glUniform1i(glGetUniformLocation(g_PgID, "dmp_Texture[0].samplerType"), GL_TEXTURE_2D);

	// HIDライブラリの初期化
	nn::hid::Initialize();

	g_pPadReader = new nn::hid::PadReader;

	// テクスチャマネージャーの初期化
	TextureManager_Initialize();

	// ポリゴンモジュールの初期化
	Polygon_Initialize();

	// シーン管理モジュールの初期化
	Scene_Initialize();
}

void Finalize(void)
{
	/* 終了処理 */
	TextureManager_Release();

	delete g_pPadReader;

	g_RenderSystem.Finalize();
	g_Heap.Free((void*)g_pHeapForGx);
	g_Heap.Finalize();
}

void Update(void)
{
	/* パッド情報の読み込み */
	nn::hid::PadStatus padStatus;

	g_pPadReader->ReadLatest(&padStatus);

	/* 更新 */
	Scene_Update(&padStatus);
}

void Draw_0(void)
{
	// レンダリング対象画面をDISPLAY0（上画面）にする
	g_RenderSystem.SetRenderTarget(NN_GX_DISPLAY0);

	// 画面のクリア
	g_RenderSystem.Clear();
	Set2DMatrix(NN_GX_DISPLAY0);

	Scene_Draw();

	// 裏画面と表画面を入れ替える
	g_RenderSystem.SwapBuffers();
}

void Draw_1(void)
{
	// レンダリング対象画面をDISPLAY1（下画面）にする
	g_RenderSystem.SetRenderTarget(NN_GX_DISPLAY1);

	// 画面のクリア（緑）
	g_RenderSystem.Clear();
	Set2DMatrix(NN_GX_DISPLAY1);

	// 裏画面と表画面を入れ替える
	g_RenderSystem.SwapBuffers();
}

void Set2DMatrix(int display)
{
	nn::math::Matrix44 projection;
	f32 left, bottom;

	if( display == NN_GX_DISPLAY0 ) {
		left = nn::gx::DISPLAY0_HEIGHT;
		bottom = nn::gx::DISPLAY0_WIDTH;
	}
	else if( display == NN_GX_DISPLAY1 ) {
		left = nn::gx::DISPLAY1_HEIGHT;
		bottom = nn::gx::DISPLAY1_WIDTH;
	}

	nn::math::MTX44Ortho(&projection, left , 0, bottom, 0, 0, 1);

	std::swap(projection.v[0], projection.v[1]);
	glUniformMatrix4fv(glGetUniformLocation(1, "uProjection"), 1, GL_TRUE, (f32*)projection);

	nn::math::Matrix44 modelView;
	nn::math::MTX44Identity(&modelView);
	glUniformMatrix4fv(glGetUniformLocation(1, "uModelView"), 1, GL_TRUE, (f32*)modelView);
}

nn::fnd::ExpHeap* GetHeap(void)
{
	return &g_Heap;
}
