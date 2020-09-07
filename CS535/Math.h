#pragma once
#include <iostream>
namespace CS535 {
	class vec3 {
	public:
		union {
			float v[3];
			struct { float x, y, z; };
			struct { float m0, m1, m2; };
		};
		vec3() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}
		vec3(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		vec3(vec3 const& v1) {
			this->x = v1.x;
			this->y = v1.y;
			this->z = v1.z;
		}
		float& operator[](int i) {
			return v[i];
		}
		vec3 operator+(vec3 v1) {
			v1.x += this->x;
			v1.y += this->y;
			v1.z += this->z;
			return v1;
		}
		vec3 operator-(vec3 v1) {
			v1.x -= this->x;
			v1.y -= this->y;
			v1.z -= this->z;
			return v1;
		}
		float operator*(vec3 v1) {
			v1.x *= this->x;
			v1.y *= this->y;
			v1.z *= this->z;
			return v1.x + v1.y + v1.z;
		}
		vec3 operator^(vec3 v1) {
			return vec3(
				y * v1.z - v1.y * z,
				z * v1.x - v1.z * x,
				x * v1.y - v1.x * y
			);
		}
		vec3 operator*(float d) {
			vec3 v1 = vec3(this->x, this->y, this->z);
			v1.x *= this->x;
			v1.y *= this->y;
			v1.z *= this->z;
			return v1;
		}
		vec3 operator/(float d) {
			return vec3(this->x / d, this->y / d, this->z / d);
		}
		vec3 Normalize() {
			return *this / Length();
		}
		float Length() {
			return sqrt(((*this) * (*this)));
		}
		//Rotation of ¡°this¡± point about arbitrary axis
		vec3 RotateAxis(vec3 axisAnchor, vec3 axisDirection, float angle) {
			return vec3();
		}
		//Rotation of ¡°this¡± vector about arbitrary direction
		vec3 Rotate(vec3 direction, float angle) {
			return vec3();
		}
		friend std::ostream& operator<<(std::ostream& output, const vec3& v1) {
			return output << v1.x << " " << v1.y << " " << v1.z << std::endl;
		}
		friend std::istream& operator>>(std::istream& input, vec3& v1) {
			input >> v1.x;
			input >> v1.y;
			input >> v1.z;
		}
	};

	class mat3 {
	public:
		union {
			vec3 v[3];
			struct { 
				float m00, m01, m02,
					m10, m11, m12,
					m20, m21, m22;
			};
		};

	};
}
