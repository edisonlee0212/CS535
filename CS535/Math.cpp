#include "Math.h"

using namespace CS535;


vec3 CS535::Normalize(const vec3& v) {
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return vec3(v.x / length, v.y / length, v.z / length);
}

vec4 CS535::Normalize(const vec4& v) {
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	return vec3(v.x / length, v.y / length, v.z / length);
}

float CS535::Dot(const vec3& v1, const vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float CS535::Dot(const vec4& v1, const vec4& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

vec3 CS535::Cross(const vec3& v1, const vec3& v2) {
	return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

vec4 CS535::Cross(const vec4& v1, const vec4& v2) {
	return vec4(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x, 0.0f);
}

mat4 CS535::Inverse(mat4 m) {
	float c00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
	float c02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
	float c03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

	float c04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	float c06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
	float c07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

	float c08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	float c10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
	float c11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

	float c12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	float c14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
	float c15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

	float c16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	float c18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
	float c19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

	float c20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	float c22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
	float c23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

	vec4 f0(c00, c00, c02, c03);
	vec4 f1(c04, c04, c06, c07);
	vec4 f2(c08, c08, c10, c11);
	vec4 f3(c12, c12, c14, c15);
	vec4 f4(c16, c16, c18, c19);
	vec4 f5(c20, c20, c22, c23);

	vec4 v0(m[1][0], m[0][0], m[0][0], m[0][0]);
	vec4 v1(m[1][1], m[0][1], m[0][1], m[0][1]);
	vec4 v2(m[1][2], m[0][2], m[0][2], m[0][2]);
	vec4 v3(m[1][3], m[0][3], m[0][3], m[0][3]);

	vec4 Inv0(v1 * f0 - v2 * f1 + v3 * f2);
	vec4 Inv1(v0 * f0 - v2 * f3 + v3 * f4);
	vec4 Inv2(v0 * f1 - v1 * f3 + v3 * f5);
	vec4 Inv3(v0 * f2 - v1 * f4 + v2 * f5);

	vec4 SignA(+1, -1, +1, -1);
	vec4 SignB(-1, +1, -1, +1);
	mat4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

	vec4 Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

	vec4 Dot0(m[0] * Row0);
	float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

	float OneOverDeterminant = static_cast<float>(1) / Dot1;

	return Inverse * OneOverDeterminant;
}

mat4 CS535::Transpose(mat4 m)
{
	return mat4(
		vec4(m[0][0], m[1][0], m[2][0], m[3][0]),
		vec4(m[0][1], m[1][1], m[2][1], m[3][1]),
		vec4(m[0][2], m[1][2], m[2][2], m[3][2]),
		vec4(m[0][3], m[1][3], m[2][3], m[3][3])
	);
}

mat4 CS535::Translate(mat4 m, vec3 position) {
	mat4 ret(m);
	m[3] = m[0] * position[0] + m[1] * position[1] + m[2] * position[2] + m[3];
	return m;
}

mat4 CS535::Rotate(mat4 m, float angle, vec3 axis) {
	float const a = angle;
	float const c = cos(a);
	float const s = sin(a);

	vec3 normalizedAxis(Normalize(axis));
	vec3 temp(normalizedAxis * (float(1) - c));

	mat4 r;
	r[0][0] = c + temp[0] * normalizedAxis[0];
	r[0][1] = temp[0] * normalizedAxis[1] + s * normalizedAxis[2];
	r[0][2] = temp[0] * normalizedAxis[2] - s * normalizedAxis[1];

	r[1][0] = temp[1] * normalizedAxis[0] - s * normalizedAxis[2];
	r[1][1] = c + temp[1] * normalizedAxis[1];
	r[1][2] = temp[1] * normalizedAxis[2] + s * normalizedAxis[0];

	r[2][0] = temp[2] * normalizedAxis[0] + s * normalizedAxis[1];
	r[2][1] = temp[2] * normalizedAxis[1] - s * normalizedAxis[0];
	r[2][2] = c + temp[2] * normalizedAxis[2];

	mat4 ret;
	ret[0] = m[0] * r[0][0] + m[1] * r[0][1] + m[2] * r[0][2];
	ret[1] = m[0] * r[1][0] + m[1] * r[1][1] + m[2] * r[1][2];
	ret[2] = m[0] * r[2][0] + m[1] * r[2][1] + m[2] * r[2][2];
	ret[3] = m[3];
	return ret;
}
mat4 CS535::LookAt(vec3 eye, vec3 center, vec3 up) {
	vec3 const front(Normalize(center - eye));
	vec3 const side(Normalize(Cross(front, up)));
	vec3 const u(Cross(side, front));

	mat4 ret(1);
	ret[0][0] = side.x;
	ret[1][0] = side.y;
	ret[2][0] = side.z;
	ret[0][1] = u.x;
	ret[1][1] = u.y;
	ret[2][1] = u.z;
	ret[0][2] = -front.x;
	ret[1][2] = -front.y;
	ret[2][2] = -front.z;
	ret[3][0] = -Dot(side, eye);
	ret[3][1] = -Dot(u, eye);
	ret[3][2] = Dot(front, eye);
	return ret;
}

vec4 CS535::mat4::operator*(const vec4& v)
{
	return vec4(
		Dot(value[0], v),
		Dot(value[1], v),
		Dot(value[2], v),
		Dot(value[3], v)
	);
}

