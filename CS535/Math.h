#pragma once
#include <iostream>
namespace CS535 {
	float Radians(float angle);

	class vec3 {
	public:
		union {
			float value[3];
			struct { float x, y, z; };
			struct { float r, g, b; };
		};
		vec3() {
			x = y = z = 0;
		}
		vec3(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		vec3(const vec3& v1) {
			x = v1.x;
			y = v1.y;
			z = v1.z;
		}
		float& operator[](int i) {
			return value[i];
		}
		void operator=(const vec3& v1) {
			x = v1.x;
			y = v1.y;
			z = v1.z;
		}
		vec3 operator+(const vec3& v2) {
			return vec3(v2.x + x, v2.y + y, v2.z + z);
		}
		vec3 operator-(const vec3& v2) {
			return vec3(x - v2.x, y - v2.y, z - v2.z);
		}
		vec3 operator*(const vec3& v2) {
			return vec3(x * v2.x, y * v2.y, z * v2.z);
		}
		vec3 operator*(float d) {
			return vec3(x * d, y * d, z * d);
		}
		vec3 operator/(float d) {
			return vec3(x / d, y / d, z / d);
		}
		float Length() {
			return sqrt(x * x + y * y + z * z);
		}
		friend std::ostream& operator<<(std::ostream& output, vec3& v1) {
			return output << v1.x << " " << v1.y << " " << v1.z << std::endl;
		}
		friend std::istream& operator>>(std::istream& input, vec3& v1) {
			input >> v1.x;
			input >> v1.y;
			input >> v1.z;
		}
	};

	class vec4 {
	public:
		union {
			float value[4];
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
		};
		vec4() {
			x = y = z = w = 0;
		}
		vec4(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		vec4(const vec4& v1) {
			x = v1.x;
			y = v1.y;
			z = v1.z;
			w = v1.w;
		}
		vec4(const vec3& v1) {
			x = v1.x;
			y = v1.y;
			z = v1.z;
			w = 0;
		}
		float& operator[](int i) {
			return value[i];
		}
		void operator=(const vec4& v1) {
			x = v1.x;
			y = v1.y;
			z = v1.z;
			w = v1.w;
		}
		vec4 operator+(const vec4& v2) {
			return vec4(v2.x + x, v2.y + y, v2.z + z, v2.w + w);
		}
		vec4 operator-(const vec4& v2) {
			return vec4(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
		}
		vec4 operator*(const vec4& v2) {
			return vec4(x * v2.x, y * v2.y, z * v2.z, w * v2.w);
		}
		vec4 operator*(float d) {
			return vec4(x * d, y * d, z * d, w * d);
		}
		vec4 operator/(float d) {
			return vec4(x / d, y / d, z / d, w / d);
		}
		float Length() {
			return sqrt(x * x + y * y + z * z + w * w);
		}
		friend std::ostream& operator<<(std::ostream& output, vec4& v1) {
			return output << v1.x << " " << v1.y << " " << v1.z << " " << v1.w << std::endl;
		}
		friend std::istream& operator>>(std::istream& input, vec4& v1) {
			input >> v1.x;
			input >> v1.y;
			input >> v1.z;
			input >> v1.w;
		}
	};

	vec3 Normalize(const vec3& v);
	vec4 Normalize(const vec4& v);
	float Dot(const vec3& v1, const vec3& v2);
	float Dot(const vec4& v1, const vec4& v2);
	vec3 Cross(const vec3& v1, const vec3& v2);
	vec4 Cross(const vec4& v1, const vec4& v2);

	vec3 RotateAround(const vec3& point, const vec3& lineAnchor, const vec3 lineDirection, float angle);

	class mat4 {
	public:
		union {
			vec4 value[4];
			struct {
				float m00, m01, m02, m03,
					m10, m11, m12, m13,
					m20, m21, m22, m23,
					m30, m31, m32, m33;
			};
		};
		mat4() {
			value[0] = vec4();
			value[1] = vec4();
			value[2] = vec4();
			value[3] = vec4();
		}
		mat4(vec4 v0, vec4 v1, vec4 v2, vec4 v3) {
			value[0] = v0;
			value[1] = v1;
			value[2] = v2;
			value[3] = v3;
		}
		mat4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		) {
			this->m00 = m00;
			this->m01 = m01;
			this->m02 = m02;
			this->m03 = m03;

			this->m10 = m10;
			this->m11 = m11;
			this->m12 = m12;
			this->m13 = m13;

			this->m20 = m20;
			this->m21 = m21;
			this->m22 = m22;
			this->m23 = m23;

			this->m30 = m30;
			this->m31 = m31;
			this->m32 = m32;
			this->m33 = m33;
		}
		mat4(float value) {
			m00 = m01 = m02 = m03 =
				m10 = m11 = m12 = m13 =
				m20 = m21 = m22 = m23 =
				m30 = m31 = m32 = m33 = value;
		}
		mat4(const mat4& m
		) {
			m00 = m.m00;
			m01 = m.m01;
			m02 = m.m02;
			m03 = m.m03;

			m10 = m.m10;
			m11 = m.m11;
			m12 = m.m12;
			m13 = m.m13;

			m20 = m.m20;
			m21 = m.m21;
			m22 = m.m22;
			m23 = m.m23;

			m30 = m.m30;
			m31 = m.m31;
			m32 = m.m32;
			m33 = m.m33;
		}
		void operator=(const mat4& m) {
			m00 = m.m00;
			m01 = m.m01;
			m02 = m.m02;
			m03 = m.m03;

			m10 = m.m10;
			m11 = m.m11;
			m12 = m.m12;
			m13 = m.m13;

			m20 = m.m20;
			m21 = m.m21;
			m22 = m.m22;
			m23 = m.m23;

			m30 = m.m30;
			m31 = m.m31;
			m32 = m.m32;
			m33 = m.m33;
		}
		vec4& operator[](int i) {
			return value[i];
		}
		vec4 GetColumn(int i) {
			return vec4(value[0][i], value[1][i], value[2][i], value[3][i]);
		}
		void SetColumn(int i, const vec4& v) {
			value[0][i] = v.x;
			value[1][i] = v.y;
			value[2][i] = v.z;
			value[3][i] = v.w;
		}
		vec4 operator*(const vec4& v);
		mat4 operator*(float d) {
			return mat4(value[0] * d, value[1] * d, value[2] * d, value[3] * d);
		}
		mat4 operator*(const mat4& m1) {
			vec4 SrcA0 = m1.value[0];
			vec4 SrcA1 = m1.value[1];
			vec4 SrcA2 = m1.value[2];
			vec4 SrcA3 = m1.value[3];

			vec4 SrcB0 = value[0];
			vec4 SrcB1 = value[1];
			vec4 SrcB2 = value[2];
			vec4 SrcB3 = value[3];
			return mat4(
				SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3],
				SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3],
				SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3],
				SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3]
			);
		}
		friend std::ostream& operator<<(std::ostream& output, mat4& mat) {
			return output << mat[0] << "\n" << mat[1] << "\n" << mat[2] << "\n" << mat[3] << std::endl;
		}
		friend std::istream& operator>>(std::istream& input, mat4& mat) {
			input >> mat[0];
			input >> mat[1];
			input >> mat[2];
			input >> mat[3];
		}
		const static mat4 Identity() {
			return mat4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}
	};
	mat4 Translate(mat4 m, vec3 position);
	mat4 LookAt(vec3 eye, vec3 center, vec3 up);
	mat4 Rotate(mat4 m, float angle, vec3 axis);
	mat4 Inverse(mat4 m);
	mat4 Transpose(mat4 m);
	mat4 Scale(mat4 m, vec3 scale);
}
