#include"Vector2D.h"

// コンストラクタ
Vector2D::Vector2D() :x(0), y(0) {

}

// 引数付きコンストラクタ
Vector2D::Vector2D(float x, float y) : x(x), y(y) {

}

// 演算子オーバーロード「+」
Vector2D Vector2D :: operator +(const Vector2D& vec) {
	Vector2D t(this->x + vec.x, this->y + vec.y);

	return t;
}

// 演算子オーバーロード「+=」
Vector2D& Vector2D::operator +=(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D Vector2D::operator - (const Vector2D& vec) {
	Vector2D h(this->x - vec.x, this->y - vec.y);

	return h;
}

Vector2D& Vector2D::operator -=(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D Vector2D::operator * (const float& num) {
	Vector2D k(this->x * num, this->y * num);

	return k;
}

float Vector2D::Dot(const Vector2D & vec)
{
	return this->x * vec.x + this->y * vec.y;
}

float Vector2D::Cross(const Vector2D & vec)
{
	return this->x * vec.y - this->y * vec.x;
}

float Vector2D::Magnitude()
{
	return sqrt(x * x + y + y);
}

Vector2D Vector2D::Normalized()
{
	Vector2D t(0, 0);
	t.x = x / Magnitude();
	t.y = y / Magnitude();

	return t;
}


