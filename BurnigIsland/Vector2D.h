#pragma once
#include<cmath>

// Vector2D�N���X
class Vector2D {
public:
	// �f�t�H���g�R���X�g���N�^
	Vector2D();

	// �����t���R���X�g���N�^
	Vector2D(float x, float y);

	// ���Z�q�I�[�o�[���[�h�u+�v
	Vector2D operator +(const Vector2D& vec);

	// ���Z�q�I�[�o�[���[�h�u+=�v
	Vector2D& operator += (const Vector2D& vec);

	// ���Z�q�I�[�o�[���[�h�u-�v
	Vector2D operator -(const Vector2D& vec);

	// ���Z�q�I�[�o�[���[�h�u-=�v
	Vector2D& operator -=(const Vector2D& vec);

	// ���Z�q�I�[�o�[���[�h�u*�v
	Vector2D operator *(const float& num);

	// ����
	float Dot(const Vector2D& vec);

	// �O��
	float Cross(const Vector2D& vec);

	// ���������߂�
	float Magnitude();

	// ���K��
	Vector2D Normalized();

public:
	float x;
	float y;
};