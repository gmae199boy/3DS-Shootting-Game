/* -------------------------------------------------------------------------- */
/* File:main.cpp                                                              */
/*                                                                            */
/*     �|���S���`��̒���                                                     */
/*                                                                            */
/*                                                Author : HAL Tokyo - Youhei */
/*                                                Date   : 2018.07.27         */
/* -------------------------------------------------------------------------- */


/* �C���N���[�h */
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
/* �萔��`                                                                   */
/* -------------------------------------------------------------------------- */
#define GX_HEAP_SIZE (0x400000) // GX�i�O���t�B�b�N�p�j�q�[�v�������T�C�Y => 4MB


/* -------------------------------------------------------------------------- */
/* �O���[�o���ϐ��錾                                                         */
/* -------------------------------------------------------------------------- */
static nn::fnd::ExpHeap g_Heap;  // �q�[�v�������Ǘ�
static uptr g_pHeapForGx = NULL; // GX�i�O���t�B�b�N�p�j�q�[�v�������A�h���X�i�[�p�|�C���^

static demo::RenderSystem g_RenderSystem; // �f�������_�[�V�X�e���i�`��@�\�t���j

static GLuint g_PgID; // �v���O����ID
static GLuint g_ShID; // �V�F�[�_�[ID

// �p�b�h���[�_�[
static nn::hid::PadReader* g_pPadReader = NULL;


/* -------------------------------------------------------------------------- */
/*�@�v���g�^�C�v�錾�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@*/
/* -------------------------------------------------------------------------- */
void Initialize(void); //������
void Finalize(void); //�I������
void Update(void); //�X�V
void Draw_0(void); //���ʕ`��
void Draw_1(void); //����ʕ`��
void Set2DMatrix(int display);


/* -------------------------------------------------------------------------- */
/*  �֐���`                                                                  */
/* -------------------------------------------------------------------------- */

/* �G���g���[�i���C���j�֐� */
void nnMain(void)
{
	/* ������ */
	Initialize();

	/* �Q�[�����[�v */
	while( true )
    {
		// �V�[���̊m�F
		Scene_Check();

		/* �X�V */
		Update();

		/* �`�� */
		Draw_0();//���ʕ`��
		Draw_1();//����ʕ`��

		// ���������҂��i����ʁj
		g_RenderSystem.WaitVsync(NN_GX_DISPLAY_BOTH);
    }

	//Finalize();

} //end of main

void Initialize(void)
{
	/* ������ */

	// �����_�[�V�X�e��������
	g_Heap.Initialize(nn::os::GetDeviceMemoryAddress(), nn::os::GetDeviceMemorySize()); // �q�[�v�������̏�����
	g_pHeapForGx = (uptr)g_Heap.Allocate(GX_HEAP_SIZE);                                  // Gx(�O���t�B�b�N�p)�q�[�v�������̊m��
	g_RenderSystem.Initialize(g_pHeapForGx, GX_HEAP_SIZE);                               // �f�������_�[�V�X�e��������

	// �t�@�C���V�X�e��������
	nn::fs::Initialize();
	const size_t ROMFS_BUFFER_SIZE = 1024 * 64;
	static char buffer[ROMFS_BUFFER_SIZE];
	NN_UTIL_PANIC_IF_FAILED(nn::fs::MountRom(16, 16, buffer, ROMFS_BUFFER_SIZE));

	// �V�F�[�_������(�V�F�[�_�[�̐���)
	g_PgID = glCreateProgram();
	g_ShID = glCreateShader(GL_VERTEX_SHADER);

	// �V�F�[�_�[�t�@�C���̓ǂݍ���
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

	// ��ʂ̃N���A
	glClearColor(0.05f, 0.1f, 0.1f, 1.0f);
	glClearDepthf(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND); // �L��
	glBlendFunc(GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA);

	glUniform3i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].srcRgb"), GL_TEXTURE0, GL_PRIMARY_COLOR, GL_PRIMARY_COLOR);
	glUniform3i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].srcAlpha"), GL_TEXTURE0, GL_PRIMARY_COLOR, GL_PRIMARY_COLOR);
	glUniform1i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].combineRgb"), GL_MODULATE);
	glUniform1i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].combineAlpha"), GL_MODULATE);
	glUniform3i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
	glUniform3i(glGetUniformLocation(g_PgID, "dmp_TexEnv[0].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
	glUniform1i(glGetUniformLocation(g_PgID, "dmp_Texture[0].samplerType"), GL_TEXTURE_2D);

	// HID���C�u�����̏�����
	nn::hid::Initialize();

	g_pPadReader = new nn::hid::PadReader;

	// �e�N�X�`���}�l�[�W���[�̏�����
	TextureManager_Initialize();

	// �|���S�����W���[���̏�����
	Polygon_Initialize();

	// �V�[���Ǘ����W���[���̏�����
	Scene_Initialize();
}

void Finalize(void)
{
	/* �I������ */
	TextureManager_Release();

	delete g_pPadReader;

	g_RenderSystem.Finalize();
	g_Heap.Free((void*)g_pHeapForGx);
	g_Heap.Finalize();
}

void Update(void)
{
	/* �p�b�h���̓ǂݍ��� */
	nn::hid::PadStatus padStatus;

	g_pPadReader->ReadLatest(&padStatus);

	/* �X�V */
	Scene_Update(&padStatus);
}

void Draw_0(void)
{
	// �����_�����O�Ώۉ�ʂ�DISPLAY0�i���ʁj�ɂ���
	g_RenderSystem.SetRenderTarget(NN_GX_DISPLAY0);

	// ��ʂ̃N���A
	g_RenderSystem.Clear();
	Set2DMatrix(NN_GX_DISPLAY0);

	Scene_Draw();

	// ����ʂƕ\��ʂ����ւ���
	g_RenderSystem.SwapBuffers();
}

void Draw_1(void)
{
	// �����_�����O�Ώۉ�ʂ�DISPLAY1�i����ʁj�ɂ���
	g_RenderSystem.SetRenderTarget(NN_GX_DISPLAY1);

	// ��ʂ̃N���A�i�΁j
	g_RenderSystem.Clear();
	Set2DMatrix(NN_GX_DISPLAY1);

	// ����ʂƕ\��ʂ����ւ���
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
