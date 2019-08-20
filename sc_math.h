#pragma once
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

#define ToRadiand(x) (double)(((x) * M_PI / 180.0))
#define ToRadianf(x) (float)(((x) * M_PI / 180.0))

#define ToDegreed(x) (double)(((x) * 180.0 / M_PI))
#define ToDegreef(x) (float)(((x) * 180.0 / M_PI))

struct Vector2ui
{
	unsigned int a;
	unsigned int b;

	Vector2ui() 
	{
	}

	Vector2ui(unsigned int _a, unsigned int _b)
	{
		a = _a;
		b = _b;
	}

	operator const unsigned int*() const {
		return &(a);
	}

};


struct Vector3ui
{
	unsigned int a;
	unsigned int b;
	unsigned int c;

	Vector3ui() 
	{
	}

	Vector3ui(unsigned int _a, unsigned int _b, unsigned int _c)
	{
		a = _a;
		b = _b;
		c = _c;
	}

	operator const unsigned int*() const 
	{
		return &(a);
	}
};

struct Vector2d {
	double x;
	double y;

	Vector2d() 
	{
	}

	Vector2d(double _x, double _y)
	{
		x = _x;
		y = _y;
	}

	double Cross(const Vector2d& v) const {
		return  x * v.y - y * v.x;
	}
};


struct Vector3d
{
	double x;
	double y;
	double z;
		
	Vector3d() 
	{
	}

	Vector3d(double _x, double _y, double _z) 
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3d(double f) 
	{
		x = y = z = f;
	}

	Vector3d& operator+=(const Vector3d& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3d& operator-=(const Vector3d& r) 
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	Vector3d& operator*=(double f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	operator const double*() const 
	{
		return &(x);
	}

	Vector3d Cross(const Vector3d& v) const
	{
		const double _x = y * v.z - z * v.y;
		const double _y = z * v.x - x * v.z;
		const double _z = x * v.y - y * v.x;

		return Vector3d(_x, _y, _z);
	}

	double Dot(const Vector3d& v)
	{
		double mag = x * v.x + y * v.y + z * v.z;
		return mag;
	}

	Vector3d & Normalize() {
		const double Length = sqrt(x * x + y * y + z * z);

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	double dist(const Vector3d& other) 
	{
		double diffX = x - other.x;
		double diffY = y - other.y;
		double diffZ = z - other.z;
		double Length = sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
		return Length;
	}

	double length() 
	{
		double Length = sqrt(x * x + y * y + z * z);
		return Length;
	}

	void Print() const 
	{
		std::cout << "x:" << x << "y:" << y << "z:" << z << std::endl;
	}
};

struct Vector4d {
	double x;
	double y;
	double z;
	double w;

	Vector4d()
	{
	}

	Vector4d(double _x, double _y, double _z, double _w) 
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Print() const 
	{
		std::cout << "x:" << x << "y:" << y << "z:" << z << "w:" << w << std::endl;
	}

	operator const double*() const {
		return &(x);
	}

};

inline Vector3d operator+(const Vector3d& l, const Vector3d& r) {
	Vector3d Ret(l.x + r.x,
		l.y + r.y,
		l.z + r.z);

	return Ret;
}

inline Vector3d operator-(const Vector3d& l, const Vector3d& r) {
	Vector3d Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}

inline Vector2d operator-(const Vector2d& l, const Vector2d& r) {
	Vector2d Ret(l.x - r.x,l.y - r.y);

	return Ret;
}

inline Vector3d operator*(const Vector3d& l, double f) {
	Vector3d Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}
 
struct PersProjInfo_f {
	float FOV;
	float Width;
	float Height;
	float zNear;
	float zFar;

	PersProjInfo_f() {
	}

	PersProjInfo_f(float _FOV, float _Width, float _Height, float _zNear, float _zFar) {
		FOV = _FOV;
		Width = _Width;
		Height = _Height;
		zNear = _zNear;
		zFar = _zFar;
	}
};

struct PersProjInfo_d {
	double FOV;
	double Width;
	double Height;
	double zNear;
	double zFar;

	PersProjInfo_d() {
	}

	PersProjInfo_d(double _FOV, double _Width, double _Height, double _zNear, double _zFar) {
		FOV = _FOV;
		Width = _Width;
		Height = _Height;
		zNear = _zNear;
		zFar = _zFar;
	}
};


struct Quaterniond
{
	double x;
	double y;
	double z;
	double w;

	Quaterniond() {

	}

	Quaterniond(double _d, double _a, double _b, double _c) {
		w = _d;
		x = _a;
		y = _b;
		z = _c;
	}

	Quaterniond(double angle, Vector3d axis) {
		double theta = angle / 2.0;
		axis.Normalize();

		w = cos(theta);
		x = sin(theta)*axis.x;
		y = sin(theta)*axis.y;
		z = sin(theta)*axis.z;
	}

	Quaterniond& operator+=(const Quaterniond& r) {
		w += r.w;
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Quaterniond& operator*=(double f) {
		w *= f;
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	Quaterniond & Normalize() {
		const double Length = sqrt(w * w + x * x + y * y + z * z);

		w /= Length;
		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	double length() {
		double Length = sqrt(w* w + x * x + y * y + z * z);
		return Length;
	}

	void Print() const {

		std::cout << "x:" << x << "y:" << y << "z:" << z << "w:" << w << std::endl;
	}

};

inline Quaterniond operator*(const Quaterniond& p, const Quaterniond& q) {

	Quaterniond Ret(
		p.w*q.w - p.x*q.x - p.y*q.y - p.z*q.z,
		p.w*q.x + p.x*q.w + p.y*q.z - p.z*q.y,
		p.w*q.y - p.x*q.z + p.y*q.w + p.z*q.x,
		p.w*q.z + p.x*q.y - p.y*q.x + p.z*q.w
	);

	return Ret;
}


class Matrix4d {
public:
	double m[4][4];

	Matrix4d() {
	}

	Matrix4d(double a00, double a01, double a02, double a03,
		double a10, double a11, double a12, double a13,
		double a20, double a21, double a22, double a23,
		double a30, double a31, double a32, double a33) {
		m[0][0] = a00;
		m[0][1] = a01;
		m[0][2] = a02;
		m[0][3] = a03;
		m[1][0] = a10;
		m[1][1] = a11;
		m[1][2] = a12;
		m[1][3] = a13;
		m[2][0] = a20;
		m[2][1] = a21;
		m[2][2] = a22;
		m[2][3] = a23;
		m[3][0] = a30;
		m[3][1] = a31;
		m[3][2] = a32;
		m[3][3] = a33;
	}

	void SetZero() {
		memset(m, 0, sizeof(m));
	}

	Matrix4d Transpose() const {
		Matrix4d n;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				n.m[i][j] = m[j][i];
			}
		}

		return n;
	}

	 inline void InitIdentity() {
		m[0][0] = 1.0;
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[0][3] = 0.0;
		m[1][0] = 0.0;
		m[1][1] = 1.0;
		m[1][2] = 0.0;
		m[1][3] = 0.0;
		m[2][0] = 0.0;
		m[2][1] = 0.0;
		m[2][2] = 1.0;
		m[2][3] = 0.0;
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 0.0;
		m[3][3] = 1.0;
	}

	 inline Matrix4d operator*(const Matrix4d& Right) const {
		 Matrix4d Ret;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				Ret.m[i][j] = m[i][0] * Right.m[0][j] +
					m[i][1] * Right.m[1][j] +
					m[i][2] * Right.m[2][j] +
					m[i][3] * Right.m[3][j];
			}
		}

		return Ret;
	}

	Vector4d operator*(const Vector4d& v) const 
	{
		Vector4d r;

		r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
		r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
		r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
		r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

		return r;
	}

	operator const double*() const {
		return &(m[0][0]);
	}

	void Print() const {
		for (int i = 0; i < 4; i++) {
			printf("%6.2f %6.2f %6.2f %6.2f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
		}
	}

	double Determinant() const {
		return m[0][0] * m[1][1] * m[2][2] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] + m[0][0] * m[1][2] * m[2][3] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3]
			+ m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][2] * m[2][3] * m[3][0] + m[0][1] * m[1][2] * m[2][0] * m[3][3]
			- m[0][1] * m[1][3] * m[2][0] * m[3][2] + m[0][1] * m[1][3] * m[2][2] * m[3][0] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2]
			+ m[0][2] * m[1][3] * m[2][0] * m[3][1] - m[0][2] * m[1][3] * m[2][1] * m[3][0] + m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1]
			+ m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1]
			- m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][3] * m[1][2] * m[2][1] * m[3][0];
	}

	Matrix4d& Inverse() {
		// Compute the reciprocal determinant
		double det = Determinant();
		if (det == 0.0) {
			// Matrix not invertible. Setting all elements to nan is not really
			// correct in a mathematical sense but it is easy to debug for the
			// programmer.
			/*const double nan = std::numeric_limits<double>::quiet_NaN();
			*this = Matrix4f(
			nan,nan,nan,nan,
			nan,nan,nan,nan,
			nan,nan,nan,nan,
			nan,nan,nan,nan);*/
			//assert(0);
			return *this;
		}

		double invdet = 1.0 / det;

		Matrix4d res;
		res.m[0][0] = invdet * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][1] = -invdet * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][2] = invdet * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));
		res.m[0][3] = -invdet * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3]) + m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));
		res.m[1][0] = -invdet * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][1] = invdet * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][2] = -invdet * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));
		res.m[1][3] = invdet * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));
		res.m[2][0] = invdet * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][1] = -invdet * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][2] = invdet * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[2][3] = -invdet * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		res.m[3][0] = -invdet * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][1] = invdet * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][2] = -invdet * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2]) + m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[3][3] = invdet * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		*this = res;

		return *this;
	}

	void InitScaleTransform(double ScaleX, double ScaleY, double ScaleZ) {
		m[0][0] = ScaleX;
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[0][3] = 0.0;
		m[1][0] = 0.0;
		m[1][1] = ScaleY;
		m[1][2] = 0.0;
		m[1][3] = 0.0;
		m[2][0] = 0.0;
		m[2][1] = 0.0;
		m[2][2] = ScaleZ;
		m[2][3] = 0.0;
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 0.0;
		m[3][3] = 1.0;
	}

	void InitRotateTransform(double RotateX, double RotateY, double RotateZ) {
		Matrix4d rx, ry, rz;

		const double x = ToRadiand(RotateX);
		const double y = ToRadiand(RotateY);
		const double z = ToRadiand(RotateZ);

		rx.m[0][0] = 1.0;
		rx.m[0][1] = 0.0;
		rx.m[0][2] = 0.0;
		rx.m[0][3] = 0.0;
		rx.m[1][0] = 0.0;
		rx.m[1][1] = cos(x);
		rx.m[1][2] = -sin(x);
		rx.m[1][3] = 0.0;
		rx.m[2][0] = 0.0;
		rx.m[2][1] = sin(x);
		rx.m[2][2] = cos(x);
		rx.m[2][3] = 0.0;
		rx.m[3][0] = 0.0;
		rx.m[3][1] = 0.0;
		rx.m[3][2] = 0.0;
		rx.m[3][3] = 1.0;

		ry.m[0][0] = cos(y);
		ry.m[0][1] = 0.0;
		ry.m[0][2] = -sin(y);
		ry.m[0][3] = 0.0;
		ry.m[1][0] = 0.0;
		ry.m[1][1] = 1.0;
		ry.m[1][2] = 0.0;
		ry.m[1][3] = 0.0;
		ry.m[2][0] = sin(y);
		ry.m[2][1] = 0.0;
		ry.m[2][2] = cos(y);
		ry.m[2][3] = 0.0;
		ry.m[3][0] = 0.0;
		ry.m[3][1] = 0.0;
		ry.m[3][2] = 0.0;
		ry.m[3][3] = 1.0;

		rz.m[0][0] = cos(z);
		rz.m[0][1] = -sin(z);
		rz.m[0][2] = 0.0;
		rz.m[0][3] = 0.0;
		rz.m[1][0] = sin(z);
		rz.m[1][1] = cos(z);
		rz.m[1][2] = 0.0;
		rz.m[1][3] = 0.0;
		rz.m[2][0] = 0.0;
		rz.m[2][1] = 0.0;
		rz.m[2][2] = 1.0;
		rz.m[2][3] = 0.0;
		rz.m[3][0] = 0.0;
		rz.m[3][1] = 0.0;
		rz.m[3][2] = 0.0;
		rz.m[3][3] = 1.0;

		*this = rz * ry * rx;
	}

	/* axis is a unit vector about which rotation is done. angle should be in radians*/
	void InitAxisRotateTransform(const Vector3d& axis, double angle) {
		const double c = cos(angle);
		const double s = sin(angle);
		const double t = 1 - c;

		m[0][0] = t * axis.x * axis.x + c;
		m[0][1] = t * axis.x * axis.y - axis.z * s;
		m[0][2] = t * axis.x * axis.z + axis.y * s;
		m[0][3] = 0.0;
		m[1][0] = t * axis.x * axis.y + axis.z * s;
		m[1][1] = t * axis.y * axis.y + c;
		m[1][2] = t * axis.y * axis.z - axis.x * s;
		m[1][3] = 0.0;
		m[2][0] = t * axis.x * axis.z - axis.y * s;
		m[2][1] = t * axis.y * axis.z + axis.x * s;
		m[2][2] = t * axis.z * axis.z + c;
		m[2][3] = 0.0;
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 0.0;
		m[3][3] = 1.0;
	}

	void InitTranslationTransform(double x, double y, double z) {
		m[0][0] = 1.0;
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[0][3] = x;
		m[1][0] = 0.0;
		m[1][1] = 1.0;
		m[1][2] = 0.0;
		m[1][3] = y;
		m[2][0] = 0.0;
		m[2][1] = 0.0;
		m[2][2] = 1.0;
		m[2][3] = z;
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 0.0;
		m[3][3] = 1.0;
	}

	void InitCameraTransform(const Vector3d& Target, const Vector3d& Up) {
		Vector3d N = Target;
		N.Normalize();
		Vector3d U = Up;
		U.Normalize();
		U = U.Cross(N);
		Vector3d V = N.Cross(U);

		m[0][0] = U.x;
		m[0][1] = U.y;
		m[0][2] = U.z;
		m[0][3] = 0.0;
		m[1][0] = V.x;
		m[1][1] = V.y;
		m[1][2] = V.z;
		m[1][3] = 0.0;
		m[2][0] = N.x;
		m[2][1] = N.y;
		m[2][2] = N.z;
		m[2][3] = 0.0;
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 0.0;
		m[3][3] = 1.0;
	}

	void LookAt(const Vector3d& eye, const Vector3d& target, const Vector3d& up) {
		Vector3d N = target - eye;		//normal to view plane(view direction)
		N.Normalize();

		//two other orthogonal direction u, v
		Vector3d U = up.Cross(N);
		U.Normalize();

		Vector3d V = N.Cross(U);
		V.Normalize();


		m[0][0] = U.x;
		m[0][1] = U.y;
		m[0][2] = U.z;
		m[0][3] = -1.0 * (eye.x *U.x + eye.y * U.y + eye.z * U.z);
		m[1][0] = V.x;
		m[1][1] = V.y;
		m[1][2] = V.z;
		m[1][3] = -1.0 * (eye.x * V.x + eye.y * V.y + eye.z * V.z);
		m[2][0] = N.x;
		m[2][1] = N.y;
		m[2][2] = N.z;
		m[2][3] = -1.0 * (eye.x * N.x + eye.y * N.y + eye.z * N.z);
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 0.0;
		m[3][3] = 1.0;
	}

	void InitPersProjTransformLHS(const PersProjInfo_d& p) {
		const double ar = p.Width / p.Height;
		const double zRange = p.zNear - p.zFar;
		const double tanHalfFOV = tan(ToRadiand(p.FOV / 2.0));

		m[0][0] = 1.0 / (tanHalfFOV * ar);
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[0][3] = 0.0;
		m[1][0] = 0.0;
		m[1][1] = 1.0 / tanHalfFOV;
		m[1][2] = 0.0;
		m[1][3] = 0.0;
		m[2][0] = 0.0;
		m[2][1] = 0.0;
		m[2][2] = (-p.zNear - p.zFar) / zRange;
		m[2][3] = 2.0 * p.zFar * p.zNear / zRange;
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 1.0;
		m[3][3] = 0.0;
	}

	void InitPersProjTransformRHS(const PersProjInfo_d& p) {
		const double ar = p.Width / p.Height;
		const double zRange = p.zFar - p.zNear;
		const double tanHalfFOV = tan(ToRadiand(p.FOV / 2.0));

		m[0][0] = 1.0 / (tanHalfFOV * ar);
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[0][3] = 0.0;
		m[1][0] = 0.0;
		m[1][1] = 1.0 / tanHalfFOV;
		m[1][2] = 0.0;
		m[1][3] = 0.0;
		m[2][0] = 0.0;
		m[2][1] = 0.0;
		m[2][2] = (-p.zNear - p.zFar) / zRange;
		m[2][3] = -2.0  * p.zFar * p.zNear / zRange;
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = -1.0;
		m[3][3] = 0.0;
	}

	void InitQuaternionRotMat(const Quaterniond& q)
	{
		Quaterniond p = q;
		p.Normalize();

		m[0][0] = p.w*p.w + p.x*p.x - p.y*p.y - p.z*p.z;
		m[0][1] = 2.0*p.x*p.y + 2.0*p.w*p.z;
		m[0][2] = 2.0*p.x*p.z - 2.0*p.w*p.y;
		m[0][3] = 0.0;
		m[1][0] = 2.0 * p.x*p.y - 2.0 * p.w*p.z;
		m[1][1] = p.w*p.w - p.x*p.x + p.y*p.y - p.z*p.z;
		m[1][2] = 2.0*p.y*p.z + 2.0*p.w*p.x;
		m[1][3] = 0.0;
		m[2][0] = 2.0*p.x*p.z + 2.0*p.w*p.y;
		m[2][1] = 2.0*p.y*p.z - 2.0*p.w*p.x;
		m[2][2] = p.w*p.w + p.x*p.x - p.y*p.y - p.z*p.z;
		m[2][3] = 0.0;
		m[3][0] = 0.0;
		m[3][1] = 0.0;
		m[3][2] = 0.0;
		m[3][3] = p.w*p.w + p.x*p.x + p.y*p.y + p.z*p.z;
	}
};

//////////////////////////////////Library for floating points////////////////////////////////////////////////////////////////////////


struct Vector2f {
	float x;
	float y;

	Vector2f() {
	}

	Vector2f(float _x, float _y) {
		x = _x;
		y = _y;
	}

	float Cross(const Vector2f& v) const {
		return  x * v.y - y * v.x;


	}

	operator const float* () const {
		return &(x);
	}
};

struct Vector3f {
	float x;
	float y;
	float z;

	Vector3f() {
	}

	Vector3f(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f(float f) {
		x = y = z = f;
	}

	Vector3f& operator+=(const Vector3f& r) {
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	Vector3f& operator*=(float f) {
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	operator const float*() const {
		return &(x);
	}

	Vector3f Cross(const Vector3f& v) const {
		const float _x = y * v.z - z * v.y;
		const float _y = z * v.x - x * v.z;
		const float _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}

	float Dot(const Vector3f& v) {
		float mag = x * v.x + y * v.y + z * v.z;
		return mag;
	}

	Vector3f & Normalize() {
		const float Length = sqrtf(x * x + y * y + z * z);

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	float dist(const Vector3f& other) {
		float diffX = x - other.x;
		float diffY = y - other.y;
		float diffZ = z - other.z;
		float Length = sqrtf(diffX * diffX + diffY * diffY + diffZ * diffZ);
		return Length;
	}

	float length() {
		float Length = sqrtf(x * x + y * y + z * z);
		return Length;
	}

	void Print() const {
		printf("(%.02f, %.02f, %.02f)\n", x, y, z);
	}
};

struct Vector4f {
	float x;
	float y;
	float z;
	float w;

	Vector4f() {
	}

	Vector4f(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Print() const {
		printf("(%.02f, %.02f, %.02f, %.02f)\n", x, y, z, w);
	}

	operator const float*() const {
		return &(x);
	}

};

inline Vector3f operator+(const Vector3f& l, const Vector3f& r) {
	Vector3f Ret(l.x + r.x,
		l.y + r.y,
		l.z + r.z);

	return Ret;
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r) {
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}

inline Vector2f operator-(const Vector2f& l, const Vector2f& r) {
	Vector2f Ret(l.x - r.x,
		l.y - r.y);

	return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f) {
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}


struct Quaternionf
{
	float x;
	float y;
	float z;
	float w;

	Quaternionf() {

	}

	Quaternionf(float _d, float _a, float _b, float _c) {
		w = _d;
		x = _a;
		y = _b;
		z = _c;
	}

	Quaternionf(float angle, Vector3f axis) {
		float theta = angle / 2.0f;
		axis.Normalize();

		w = cos(theta);
		x = sin(theta)*axis.x;
		y = sin(theta)*axis.y;
		z = sin(theta)*axis.z;
	}

	Quaternionf& operator+=(const Quaternionf& r) {
		w += r.w;
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Quaternionf& operator*=(float f) {
		w *= f;
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	Quaternionf & Normalize() {
		const float Length = sqrtf(w * w + x * x + y * y + z * z);

		w /= Length;
		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	float length() {
		float Length = sqrtf(w* w + x * x + y * y + z * z);
		return Length;
	}

	void Print() const {
		printf("(%.02f, %.02f, %.02f,%.02f)\n", w, x, y, z);
	}

};

inline Quaternionf operator*(const Quaternionf& p, const Quaternionf& q) {

	Quaternionf Ret(
		p.w*q.w - p.x*q.x - p.y*q.y - p.z*q.z,
		p.w*q.x + p.x*q.w + p.y*q.z - p.z*q.y,
		p.w*q.y - p.x*q.z + p.y*q.w + p.z*q.x,
		p.w*q.z + p.x*q.y - p.y*q.x + p.z*q.w
	);

	return Ret;
}



class Matrix4f {
public:
	float m[4][4];

	Matrix4f() {
	}

	Matrix4f(float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33) {
		m[0][0] = a00;
		m[0][1] = a01;
		m[0][2] = a02;
		m[0][3] = a03;
		m[1][0] = a10;
		m[1][1] = a11;
		m[1][2] = a12;
		m[1][3] = a13;
		m[2][0] = a20;
		m[2][1] = a21;
		m[2][2] = a22;
		m[2][3] = a23;
		m[3][0] = a30;
		m[3][1] = a31;
		m[3][2] = a32;
		m[3][3] = a33;
	}

	void SetZero() {
		memset(m, 0, sizeof(m));
	}

	Matrix4f Transpose() const {
		Matrix4f n;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				n.m[i][j] = m[j][i];
			}
		}

		return n;
	}

	inline void InitIdentity() {
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	inline Matrix4f operator*(const Matrix4f& Right) const {
		Matrix4f Ret;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				Ret.m[i][j] = m[i][0] * Right.m[0][j] +
					m[i][1] * Right.m[1][j] +
					m[i][2] * Right.m[2][j] +
					m[i][3] * Right.m[3][j];
			}
		}

		return Ret;
	}

	inline Vector4f operator*(const Vector4f& v) const {
		Vector4f r;

		r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
		r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
		r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
		r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

		return r;
	}




	inline Vector3f operator*(const Vector3f& v) const {
		Vector3f r;

		r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * 1.0f;
		r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * 1.0f;
		r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * 1.0f;
		//r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

		return r;
	}

	operator const float*() const {
		return &(m[0][0]);
	}

	void Print() const {
		for (int i = 0; i < 4; i++) {
			printf("%6.2f %6.2f %6.2f %6.2f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
		}
	}

	  float Determinant() const {
		return m[0][0] * m[1][1] * m[2][2] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] + m[0][0] * m[1][2] * m[2][3] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3]
			+ m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][2] * m[2][3] * m[3][0] + m[0][1] * m[1][2] * m[2][0] * m[3][3]
			- m[0][1] * m[1][3] * m[2][0] * m[3][2] + m[0][1] * m[1][3] * m[2][2] * m[3][0] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2]
			+ m[0][2] * m[1][3] * m[2][0] * m[3][1] - m[0][2] * m[1][3] * m[2][1] * m[3][0] + m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1]
			+ m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1]
			- m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][3] * m[1][2] * m[2][1] * m[3][0];
	}

	Matrix4f& Inverse() {
		// Compute the reciprocal determinant
		float det = Determinant();
		if (det == 0.0f) {
			// Matrix not invertible. Setting all elements to nan is not really
			// correct in a mathematical sense but it is easy to debug for the
			// programmer.
			/*const float nan = std::numeric_limits<float>::quiet_NaN();
			*this = Matrix4f(
			nan,nan,nan,nan,
			nan,nan,nan,nan,
			nan,nan,nan,nan,
			nan,nan,nan,nan);*/
			//assert(0);
			return *this;
		}

		float invdet = 1.0f / det;

		Matrix4f res;
		res.m[0][0] = invdet * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][1] = -invdet * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][2] = invdet * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));
		res.m[0][3] = -invdet * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3]) + m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));
		res.m[1][0] = -invdet * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][1] = invdet * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][2] = -invdet * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));
		res.m[1][3] = invdet * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));
		res.m[2][0] = invdet * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][1] = -invdet * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][2] = invdet * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[2][3] = -invdet * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		res.m[3][0] = -invdet * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][1] = invdet * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][2] = -invdet * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2]) + m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[3][3] = invdet * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		*this = res;

		return *this;
	}

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ) {
		m[0][0] = ScaleX;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][0] = 0.0f;
		m[1][1] = ScaleY;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = ScaleZ;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void InitRotateTransform(float RotateX, float RotateY, float RotateZ) {
		Matrix4f rx, ry, rz;

		const float x = ToRadianf(RotateX);
		const float y = ToRadianf(RotateY);
		const float z = ToRadianf(RotateZ);

		rx.m[0][0] = 1.0f;
		rx.m[0][1] = 0.0f;
		rx.m[0][2] = 0.0f;
		rx.m[0][3] = 0.0f;
		rx.m[1][0] = 0.0f;
		rx.m[1][1] = cosf(x);
		rx.m[1][2] = -sinf(x);
		rx.m[1][3] = 0.0f;
		rx.m[2][0] = 0.0f;
		rx.m[2][1] = sinf(x);
		rx.m[2][2] = cosf(x);
		rx.m[2][3] = 0.0f;
		rx.m[3][0] = 0.0f;
		rx.m[3][1] = 0.0f;
		rx.m[3][2] = 0.0f;
		rx.m[3][3] = 1.0f;

		ry.m[0][0] = cosf(y);
		ry.m[0][1] = 0.0f;
		ry.m[0][2] = sinf(y);
		ry.m[0][3] = 0.0f;
		ry.m[1][0] = 0.0f;
		ry.m[1][1] = 1.0f;
		ry.m[1][2] = 0.0f;
		ry.m[1][3] = 0.0f;
		ry.m[2][0] = -sinf(y);
		ry.m[2][1] = 0.0f;
		ry.m[2][2] = cosf(y);
		ry.m[2][3] = 0.0f;
		ry.m[3][0] = 0.0f;
		ry.m[3][1] = 0.0f;
		ry.m[3][2] = 0.0f;
		ry.m[3][3] = 1.0f;

		rz.m[0][0] = cosf(z);
		rz.m[0][1] = -sinf(z);
		rz.m[0][2] = 0.0f;
		rz.m[0][3] = 0.0f;
		rz.m[1][0] = sinf(z);
		rz.m[1][1] = cosf(z);
		rz.m[1][2] = 0.0f;
		rz.m[1][3] = 0.0f;
		rz.m[2][0] = 0.0f;
		rz.m[2][1] = 0.0f;
		rz.m[2][2] = 1.0f;
		rz.m[2][3] = 0.0f;
		rz.m[3][0] = 0.0f;
		rz.m[3][1] = 0.0f;
		rz.m[3][2] = 0.0f;
		rz.m[3][3] = 1.0f;

		*this = rz * ry * rx;
	}

	/* axis is a unit vector about which rotation is done. angle should be in radians*/
	void InitAxisRotateTransform(const Vector3f& axis, float angle) {
		const float c = cosf(angle);
		const float s = sinf(angle);
		const float t = 1 - c;

		m[0][0] = t * axis.x * axis.x + c;
		m[0][1] = t * axis.x * axis.y - axis.z * s;
		m[0][2] = t * axis.x * axis.z + axis.y * s;
		m[0][3] = 0.0f;
		m[1][0] = t * axis.x * axis.y + axis.z * s;
		m[1][1] = t * axis.y * axis.y + c;
		m[1][2] = t * axis.y * axis.z - axis.x * s;
		m[1][3] = 0.0f;
		m[2][0] = t * axis.x * axis.z - axis.y * s;
		m[2][1] = t * axis.y * axis.z + axis.x * s;
		m[2][2] = t * axis.z * axis.z + c;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void InitTranslationTransform(float x, float y, float z) {
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = x;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = y;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = z;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void InitCameraTransform(const Vector3f& Target, const Vector3f& Up) {
		Vector3f N = Target;
		N.Normalize();
		Vector3f U = Up;
		U.Normalize();
		U = U.Cross(N);
		Vector3f V = N.Cross(U);

		m[0][0] = U.x;
		m[0][1] = U.y;
		m[0][2] = U.z;
		m[0][3] = 0.0f;
		m[1][0] = V.x;
		m[1][1] = V.y;
		m[1][2] = V.z;
		m[1][3] = 0.0f;
		m[2][0] = N.x;
		m[2][1] = N.y;
		m[2][2] = N.z;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void LookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up) {
		Vector3f N = target - eye;		//normal to view plane(view direction)
		N.Normalize();

		//two other orthogonal direction u, v
		Vector3f U = up.Cross(N);
		U.Normalize();

		Vector3f V = N.Cross(U);
		V.Normalize();


		m[0][0] = U.x;
		m[0][1] = U.y;
		m[0][2] = U.z;
		m[0][3] = -1.0f * (eye.x * U.x + eye.y * U.y + eye.z * U.z);
		m[1][0] = V.x;
		m[1][1] = V.y;
		m[1][2] = V.z;
		m[1][3] = -1.0f * (eye.x * V.x + eye.y * V.y + eye.z * V.z);
		m[2][0] = N.x;
		m[2][1] = N.y;
		m[2][2] = N.z;
		m[2][3] = -1.0f * (eye.x * N.x + eye.y * N.y + eye.z * N.z);
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void LookAtRHS(const Vector3f& eye, const Vector3f& target, const Vector3f& up) {
		Vector3f N = target - eye;		//normal to view plane(view direction)
		N.Normalize();
		N = N * -1.0f;	//flip to get correct coordinate system

		//two other orthogonal direction u, v
		Vector3f U = up.Cross(N);
		U.Normalize();

		Vector3f V = N.Cross(U);
		V.Normalize();


		m[0][0] = U.x;
		m[0][1] = U.y;
		m[0][2] = U.z;
		m[0][3] = -1.0f * (eye.x * U.x + eye.y * U.y + eye.z * U.z);
		m[1][0] = V.x;
		m[1][1] = V.y;
		m[1][2] = V.z;
		m[1][3] = -1.0f * (eye.x * V.x + eye.y * V.y + eye.z * V.z);
		m[2][0] = N.x;
		m[2][1] = N.y;
		m[2][2] = N.z;
		m[2][3] = -1.0f * (eye.x * N.x + eye.y * N.y + eye.z * N.z);
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void InitPersProjTransformLHS(const PersProjInfo_f& p) {
		const float ar = p.Width / p.Height;
		const float zRange = p.zNear - p.zFar;
		const float tanHalfFOV = tanf(ToRadianf(p.FOV / 2.0f));

		m[0][0] = 1.0f / (tanHalfFOV * ar);
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f / tanHalfFOV;
		m[1][2] = 0.0f;
		m[1][3] = 0.0;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = (-p.zNear - p.zFar) / zRange;
		m[2][3] = 2.0f * p.zFar * p.zNear / zRange;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 1.0f;
		m[3][3] = 0.0;
	}

	void InitPersProjTransformRHS(const PersProjInfo_f& p) {
		const float ar = p.Width / p.Height;
		const float zRange = (p.zFar - p.zNear);
		const float tanHalfFOV = tanf(ToRadianf(p.FOV / 2.0f));

		m[0][0] = 1.0f / (tanHalfFOV * ar);
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f / tanHalfFOV;
		m[1][2] = 0.0f;
		m[1][3] = 0.0;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = (-p.zFar - p.zNear) / zRange;
		m[2][3] = -2.0f * p.zFar * p.zNear / zRange;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = -1.0f;
		m[3][3] = 0.0;
	}

	void InitQuaternionRotMat(const Quaternionf& q)
	{
		Quaternionf p = q;
		p.Normalize();

		m[0][0] = p.w*p.w + p.x*p.x - p.y*p.y - p.z*p.z;
		m[0][1] = 2.0f*p.x*p.y + 2.0f*p.w*p.z;
		m[0][2] = 2.0f*p.x*p.z - 2.0f*p.w*p.y;
		m[0][3] = 0.0f;
		m[1][0] = 2.0f * p.x*p.y - 2.0f * p.w*p.z;
		m[1][1] = p.w*p.w - p.x*p.x + p.y*p.y - p.z*p.z;
		m[1][2] = 2.0f*p.y*p.z + 2.0f*p.w*p.x;
		m[1][3] = 0.0f;
		m[2][0] = 2.0f*p.x*p.z + 2.0f*p.w*p.y;
		m[2][1] = 2.0f*p.y*p.z - 2.0f*p.w*p.x;
		m[2][2] = p.w*p.w + p.x*p.x - p.y*p.y - p.z*p.z;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = p.w*p.w + p.x*p.x + p.y*p.y + p.z*p.z;
	}
};





