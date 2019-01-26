
#include <nn/fs.h> // �t�@�C���̓ǂݍ��݃��W���[��
#include <nn/gx.h>
#include "main.h"


unsigned int LoadTexture(const char *FileName)
{
	nn::fs::FileReader file(FileName);

	unsigned int	texture;
	unsigned char	header[18];
	unsigned char	*image;
	unsigned int	width, height;
	unsigned char	depth;
	unsigned int	bpp;
	unsigned int	format;


	// �w�b�_�ǂݍ���
	file.Read(header, sizeof(header));

	// �摜�T�C�Y�擾
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];
	depth = header[16];

	if (depth == 32)
	{
		bpp = 4;
		format = GL_RGBA;
	}
	else if (depth == 24)
	{
		bpp = 3;
		format = GL_RGB;
	}
	else
	{
		NN_PANIC( "LoadTexture" );
	}


	// �������m��
	image = (unsigned char*)GetHeap()->Allocate(width * height * bpp);

	// �摜�ǂݍ���
	file.Read(image, width * height * bpp);

	// R<->B
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			unsigned char c;
			c = image[(y * width + x) * bpp + 0];
			image[(y * width + x) * bpp + 0] = image[(y * width + x) * bpp + 2];
			image[(y * width + x) * bpp + 2] = c;
		}
	}

	file.Finalize();

	// �e�N�X�`������
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);


	glBindTexture(GL_TEXTURE_2D, 0);

	GetHeap()->Free(image);

	return texture;
}



void UnloadTexture(unsigned int Texture)
{

	glDeleteTextures(1, &Texture);

}



