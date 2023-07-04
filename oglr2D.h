#ifndef oglr_2D_h
#define oglr_2D_h

#define OGLR2D_BEGIN namespace oglr2D {
#define OGLR2D_END }

#ifndef _WIN32
#ifdef OGLR2D_USE_WINDOWS
#undef OGLR2D_USE_WINDOWS
#endif
#endif

#ifndef __linux__
#ifdef OGLR2D_USE_LINUX
#undef OGLR2D_USE_LINUX
#endif
#endif

#ifdef __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_MAC == 0
#ifdef OGLR2D_USE_MACOS
#undef OGLR2D_USE_MACOS
#endif
#endif
#endif

#if defined __has_include
#if __has_include(<glfw/glfw3.h>)
#define OGLR2D_PROJECT_HAS_GLFW
#endif
#endif

#ifndef OGLR2D_PROJECT_HAS_GLFW
#ifdef OGLR2D_USE_GLFW
#undef OGLR2D_USE_GLFW
#endif
#endif

#define OGLR2D_PLATFORM_NONE

#ifdef OGLR2D_USE_WINDOWS
#undef OGLR2D_PLATFORM_NONE
#ifndef _WIN32_LEAN_AND_MEAN
#define _WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#ifdef OGLR2D_USE_LINUX
#undef OGLR2D_PLATFORM_NONE
#endif

#ifdef OGLR2D_USE_MACOS
#undef OGLR2D_PLATFORM_NONE
#endif

#ifdef OGLR2D_USE_GLFW
#undef OGLR2D_PLATFORM_NONE
#include <glfw/glfw3.h>
#endif

#ifdef OGLR2D_PLATFORM_NONE
#error OGLR2D doesn't support this platform.
#endif

#if defined(_WIN32)
#define OGLR2D_DEBUGBREAK __debugbreak
#elif defined(__linux__)
#define OGLR2D_DEBUGBREAK
#elif defined(__APPLE__)
#if TARGET_OS_MAC == 0
#define OGLR2D_DEBUGBREAK
#endif
#endif

#define OGLR2D_ASSERT(x) if(!x) { OGLR2D_DEBUGBREAK(); }

#include <math.h>

#define OGLR2D_PI					3.14159265358
#define OGLR2D_TORADIANS(x)			x * (float)OGLR2D_PI / 180.0f
#define OGLR2D_TODEGREES(x)			x * 180.0f / (float)OGLR2D_PI
#define OGLR2D_COS(x)				cosf(x)
#define OGLR2D_SIN(x)				sinf(x)
#define OGLR2D_TAN(x)				tanf(x)
#define OGLR2D_SQRT(x)				sqrtf(x)
#define OGLR2D_ATAN2(y, x)			atan2f(y, x)

OGLR2D_BEGIN

typedef unsigned long long OGLR2DUInt64;
typedef unsigned int OGLR2DUInt32;
typedef unsigned short OGLR2DUInt16;
typedef unsigned char OGLR2DUInt8;

typedef long long OGLR2DInt64;
typedef signed int OGLR2DInt32;
typedef signed short OGLR2DInt16;
typedef signed char OGLR2DInt8;

enum OGLR2DClearScreenFlags
{
	DEPTH_BUFFER_BIT = 1 << 0,
	COLOR_BUFFER_BIT = 1 << 1,
	STENCIL_BUFFER_BIT = 1 << 2,
	ACCUM_BUFFER_BIT = 1 << 3
};

enum OGLR2DBufferType
{
	VERTEX_BUFFER,
	INDEX_BUFFER
};

enum OGLR2DBufferUsage
{
	STATIC_DRAW,
	DYNAMIC_DRAW
};

enum OGLR2DDrawType
{
	TRIANGLES,
	LINES
};

enum OGLR2DBufferAttributeType
{
	FLOAT,
	INT,
	FLOAT2,
	FLOAT3,
	FLOAT4
};

typedef int OGLR2DInt;
typedef float OGLR2DFloat;

struct OGLR2DFloat2
{
	OGLR2DFloat x;
	OGLR2DFloat y;

	OGLR2DFloat2()
		: x(0.0f)
		, y(0.0f)
	{
	}

	OGLR2DFloat2(OGLR2DFloat x, OGLR2DFloat y)
		: x(x)
		, y(y)
	{
	}

	OGLR2DFloat2(const OGLR2DFloat2& rhs)
		: x(rhs.x)
		, y(rhs.y)
	{
	}

	bool operator==(const OGLR2DFloat2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator!=(const OGLR2DFloat2& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	bool operator>(const OGLR2DFloat2& rhs) const
	{
		return x > rhs.x && y > rhs.y;
	}

	bool operator<(const OGLR2DFloat2& rhs) const
	{
		return x < rhs.x && y < rhs.y;
	}

	bool operator>=(const OGLR2DFloat2& rhs) const
	{
		return x >= rhs.x && y >= rhs.y;
	}

	bool operator<=(const OGLR2DFloat2& rhs) const
	{
		return x <= rhs.x && y <= rhs.y;
	}

	OGLR2DFloat2& operator=(const OGLR2DFloat2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	OGLR2DFloat2 operator+(const OGLR2DFloat2& rhs) const
	{
		return { x + rhs.x, y + rhs.y };
	}

	OGLR2DFloat2 operator-(const OGLR2DFloat2& rhs) const
	{
		return { x - rhs.x, y - rhs.y };
	}

	OGLR2DFloat2 operator*(const OGLR2DFloat2& rhs) const
	{
		return { x * rhs.x, y * rhs.y };
	}

	OGLR2DFloat2 operator/(const OGLR2DFloat2& rhs) const
	{
		return { x / rhs.x, y / rhs.y };
	}

	OGLR2DFloat2& operator+=(const OGLR2DFloat2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	OGLR2DFloat2& operator-=(const OGLR2DFloat2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	OGLR2DFloat2& operator*=(const OGLR2DFloat2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	OGLR2DFloat2& operator/=(const OGLR2DFloat2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	OGLR2DFloat* getAddress()
	{
		return &x;
	}

	const OGLR2DFloat* getAddress() const
	{
		return &x;
	}

	OGLR2DFloat& operator[](OGLR2DUInt32 idx)
	{
		return getAddress()[idx];
	}

	const OGLR2DFloat& operator[](OGLR2DUInt32 idx) const
	{
		return getAddress()[idx];
	}
};

struct OGLR2DFloat3
{
	OGLR2DFloat x;
	OGLR2DFloat y;
	OGLR2DFloat z;

	OGLR2DFloat3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{
	}

	OGLR2DFloat3(OGLR2DFloat x, OGLR2DFloat y, OGLR2DFloat z)
		: x(x)
		, y(y)
		, z(z)
	{
	}

	OGLR2DFloat3(const OGLR2DFloat3& rhs)
		: x(rhs.x)
		, y(rhs.y)
		, z(rhs.z)
	{
	}

	bool operator==(const OGLR2DFloat3& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool operator!=(const OGLR2DFloat3& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z;
	}

	bool operator>(const OGLR2DFloat3& rhs) const
	{
		return x > rhs.x && y > rhs.y && z > rhs.z;
	}

	bool operator<(const OGLR2DFloat3& rhs) const
	{
		return x < rhs.x && y < rhs.y && z < rhs.z;
	}

	bool operator>=(const OGLR2DFloat3& rhs) const
	{
		return x >= rhs.x && y >= rhs.y && z >= rhs.z;
	}

	bool operator<=(const OGLR2DFloat3& rhs) const
	{
		return x <= rhs.x && y <= rhs.y && z <= rhs.z;
	}

	OGLR2DFloat3& operator=(const OGLR2DFloat3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	OGLR2DFloat3 operator+(const OGLR2DFloat3& rhs) const
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	OGLR2DFloat3 operator-(const OGLR2DFloat3& rhs) const
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	OGLR2DFloat3 operator*(const OGLR2DFloat3& rhs) const
	{
		return { x * rhs.x, y * rhs.y, z * rhs.z };
	}

	OGLR2DFloat3 operator/(const OGLR2DFloat3& rhs) const
	{
		return { x / rhs.x, y / rhs.y, z / rhs.z };
	}

	OGLR2DFloat3& operator+=(const OGLR2DFloat3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	OGLR2DFloat3& operator-=(const OGLR2DFloat3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	OGLR2DFloat3& operator*=(const OGLR2DFloat3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	OGLR2DFloat3& operator/=(const OGLR2DFloat3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	OGLR2DFloat* getAddress()
	{
		return &x;
	}

	const OGLR2DFloat* getAddress() const
	{
		return &x;
	}

	OGLR2DFloat& operator[](OGLR2DUInt32 idx)
	{
		return getAddress()[idx];
	}

	const OGLR2DFloat& operator[](OGLR2DUInt32 idx) const
	{
		return getAddress()[idx];
	}
};

struct OGLR2DFloat4
{
	OGLR2DFloat x;
	OGLR2DFloat y;
	OGLR2DFloat z;
	OGLR2DFloat w;

	OGLR2DFloat4()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{
	}

	OGLR2DFloat4(OGLR2DFloat x, OGLR2DFloat y, OGLR2DFloat z, OGLR2DFloat w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
	}

	OGLR2DFloat4(const OGLR2DFloat4& rhs)
		: x(rhs.x)
		, y(rhs.y)
		, z(rhs.z)
		, w(rhs.w)
	{
	}

	bool operator==(const OGLR2DFloat4& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	bool operator!=(const OGLR2DFloat4& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
	}

	bool operator>(const OGLR2DFloat4& rhs) const
	{
		return x > rhs.x && y > rhs.y && z > rhs.z && w > rhs.w;
	}

	bool operator<(const OGLR2DFloat4& rhs) const
	{
		return x < rhs.x&& y < rhs.y && z < rhs.z && w < rhs.w;
	}

	bool operator>=(const OGLR2DFloat4& rhs) const
	{
		return x >= rhs.x && y >= rhs.y && z >= rhs.z && w >= rhs.w;
	}

	bool operator<=(const OGLR2DFloat4& rhs) const
	{
		return x <= rhs.x && y <= rhs.y && z <= rhs.z && w <= rhs.w;
	}

	OGLR2DFloat4& operator=(const OGLR2DFloat4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	OGLR2DFloat4 operator+(const OGLR2DFloat4& rhs) const
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
	}

	OGLR2DFloat4 operator-(const OGLR2DFloat4& rhs) const
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
	}

	OGLR2DFloat4 operator*(const OGLR2DFloat4& rhs) const
	{
		return { x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w };
	}

	OGLR2DFloat4 operator/(const OGLR2DFloat4& rhs) const
	{
		return { x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w };
	}

	OGLR2DFloat4& operator+=(const OGLR2DFloat4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	OGLR2DFloat4& operator-=(const OGLR2DFloat4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	OGLR2DFloat4& operator*=(const OGLR2DFloat4& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	OGLR2DFloat4& operator/=(const OGLR2DFloat4& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	OGLR2DFloat* getAddress()
	{
		return &x;
	}

	const OGLR2DFloat* getAddress() const
	{
		return &x;
	}

	OGLR2DFloat& operator[](OGLR2DUInt32 idx)
	{
		return getAddress()[idx];
	}

	const OGLR2DFloat& operator[](OGLR2DUInt32 idx) const
	{
		return getAddress()[idx];
	}
};

struct OGLR2DMatrix4
{
	OGLR2DFloat4 rows[4];

	OGLR2DMatrix4()
	{
		reset();
	}

	OGLR2DMatrix4(float x)
	{
		setIdentity(x);
	}

	OGLR2DFloat4& operator[](OGLR2DUInt32 idx)
	{
		return rows[idx];
	}

	const OGLR2DFloat4& operator[](OGLR2DUInt32 idx) const
	{
		return rows[idx];
	}

	void reset()
	{
		for (OGLR2DUInt32 x = 0; x < 4; x++)
		{
			for (OGLR2DUInt32 y = 0; y < 4; y++)
			{
				rows[x][y] = 0.0f;
			}
		}
	}

	void setIdentity(float x)
	{
		reset();
		rows[0][0] = x;
		rows[1][1] = x;
		rows[2][2] = x;
		rows[3][3] = x;
	}

	void setOrtho(float left, float right, float bottom, float top, float near, float far)
	{
		rows[0][0] = 2.0f / (right - left);
		rows[1][1] = 2.0f / (top - bottom);
		rows[2][2] = 2.0f / (near - far);
		rows[3][0] = (left + right) / (left - right);
		rows[3][1] = (bottom + top) / (bottom - top);
		rows[3][2] = (far + near) / (far - near);
	}

	OGLR2DMatrix4 operator*(const OGLR2DMatrix4& other) const
	{
		OGLR2DMatrix4 m;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += rows[i][e] * other[e][j];
				}
				m[i][j] = sum;
			}
		}

		return m;
	}

	static OGLR2DMatrix4 translate(const OGLR2DFloat3& pos)
	{
		OGLR2DMatrix4 mat(1.0f);
		mat[0][3] = pos.x;
		mat[1][3] = pos.y;
		mat[2][3] = pos.z;
		return mat;
	}

	static OGLR2DMatrix4 scale(const OGLR2DFloat3& scale)
	{
		OGLR2DMatrix4 mat(1.0f);
		mat[1][1] = scale.x;
		mat[2][2] = scale.y;
		mat[3][3] = scale.z;
		return mat;
	}

	static OGLR2DMatrix4 rotateZ(float angle)
	{
		float rad = OGLR2D_TORADIANS(angle);
		float c = OGLR2D_COS(rad);
		float s = OGLR2D_SIN(rad);

		OGLR2DMatrix4 mat(1.0f);
		mat[0][0] = c;
		mat[1][1] = c;
		mat[0][1] = -s;
		mat[1][0] = s;
		return mat;
	}

	OGLR2DFloat* getAddress()
	{
		return &rows[0][0];
	}

	const OGLR2DFloat* getAddress() const
	{
		return &rows[0][0];
	}
};

OGLR2DFloat2 multipyFloat2Matrix4(const OGLR2DFloat2& f2, const OGLR2DMatrix4& m4);
OGLR2DFloat3 multipyFloat3Matrix4(const OGLR2DFloat3& f2, const OGLR2DMatrix4& m4);
OGLR2DFloat4 multipyFloat4Matrix4(const OGLR2DFloat4& f2, const OGLR2DMatrix4& m4);

using OGLR2DVertexArray = struct VertexArray*;
using OGLR2DBuffer = struct Buffer*;
using OGLR2DShader = struct Shader*;
using OGLR2DTexture = struct Texture*;

struct OGLR2DBufferAttribute
{
	OGLR2DUInt32 type;
	bool normalized;
	OGLR2DUInt32 elementSize;
	OGLR2DUInt32 offset;
};

struct OGLR2DColor
{
	int r;
	int g;
	int b;
	int a;

	OGLR2DColor() : r(0), g(0), b(0), a(255) { }
	OGLR2DColor(int r, int g, int b) : r(r), g(g), b(b), a(255) { }
};

struct OGLR2DViewport
{
	int x;
	int y;
	int width;
	int height;

	OGLR2DViewport() : x(0), y(0), width(0), height(0) { }
	OGLR2DViewport(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) { }
};

template<typename T>
class OGLR2DBasicArray
{
public:
	OGLR2DBasicArray()
		: m_data(nullptr)
		, m_capacity(0)
		, m_size(0)
	{
	}

	~OGLR2DBasicArray()
	{
	}

	void push(const T& x)
	{
		if (m_size >= m_capacity)
			allocate(m_capacity == 0 ? 4 : m_capacity << 1);
		
		m_data[m_size] = x;
		m_size++;
	}

	void erase(OGLR2DUInt64 idx)
	{
		if (idx > 0)
		{
			m_data[idx].~T();
			for (OGLR2DUInt64 i = 1; i < m_size - idx; i++)
				m_data[idx + i - 1] = m_data[idx + i];

			--m_size;
		}
	}

	void pop()
	{
		if (m_size > 0)
		{
			--m_size;
			m_data->~T();
		}
	}

	void allocate(OGLR2DUInt64 newSize)
	{
		T* ptr = new T[newSize];
		if (m_data)
		{
			memCopy(ptr, m_data, newSize);
			delete[] m_data;
		}

		m_data = ptr;
		m_capacity = newSize;
	}

	T* memCopy(T* dst, const T* src, OGLR2DUInt64 size)
	{
		for (OGLR2DUInt64 i = 0; i < size; i++)
			dst[i] = src[i];

		return dst;
	}

	const T& operator[](OGLR2DUInt64 idx) const
	{
		return m_data[idx];
	}

	T& operator[](OGLR2DUInt64 idx)
	{
		return m_data[idx];
	}

	OGLR2DUInt64 size() const
	{
		return m_size;
	}

	void removeIfContains(const T& member)
	{
		for (OGLR2DUInt64 i = 0; i < m_size; i++)
		{
			if (m_data[i] == member)
			{
				erase(i);
				break;
			}
		}
	}

private:
	T* m_data;
	OGLR2DUInt64 m_capacity;
	OGLR2DUInt64 m_size;
};

namespace ogl_loader
{
	typedef void* (*GLLoaderProc)(const char* name);
	void setOpenGLLoaderFunc(GLLoaderProc proc);
}

void loadOpenGL();

#ifdef OGLR2D_USE_GLFW

OGLR2DUInt64 findGLFWContext(GLFWwindow* context);
void makeContextCurrentGLFW(GLFWwindow* window);
void swapBuffersGLFW(GLFWwindow* context);

#endif

#ifdef OGLR2D_USE_WINDOWS

u64 findWindowsContext(HDC hDC);
void makeContextCurrentWindows(HWND hWnd);
void swapBuffersWindows(HWND hWnd);

#endif

#ifdef OGLR2D_USE_LINUX
#endif

#ifdef OGLR2D_USE_MACOS
#endif

void clearScreen(const OGLR2DColor& color, OGLR2DUInt32 clearFlags);
void setViewport(const OGLR2DViewport& viewport);
OGLR2DViewport getViewport();
OGLR2DVertexArray createVertexArray();
void deleteVertexArray(const OGLR2DVertexArray vao);
void bindVertexArray(OGLR2DVertexArray vao);
OGLR2DBuffer createBuffer(OGLR2DUInt32 type);
void deleteBuffer(const OGLR2DBuffer buffer);
void bindBuffer(OGLR2DBuffer buffer);
void pushBufferAttribute(OGLR2DBuffer buffer, const char* name, OGLR2DUInt32 type, bool normalized);
void prepareBufferAttributes(OGLR2DVertexArray vao, OGLR2DBuffer buffer);
void setBufferData(OGLR2DBuffer buffer, const void* src, OGLR2DUInt32 size, OGLR2DUInt32 usage);
void setBufferSubData(OGLR2DBuffer buffer, const void* src, OGLR2DUInt32 size);
OGLR2DShader createShader(const char* vertSrc, const char* fragSrc);
void deleteShader(const OGLR2DShader shader);
void bindShader(OGLR2DShader shader);
void setUniformFloat(OGLR2DShader shader, const char* name, const OGLR2DFloat& val);
void setUniformFloat2(OGLR2DShader shader, const char* name, const OGLR2DFloat2& val);
void setUniformFloat3(OGLR2DShader shader, const char* name, const OGLR2DFloat3& val);
void setUniformFloat4(OGLR2DShader shader, const char* name, const OGLR2DFloat4& val);
void setUniformInt(OGLR2DShader shader, const char* name, const OGLR2DInt& val);
void setUniformMatrix4(OGLR2DShader shader, const char* name, const OGLR2DMatrix4& val);

OGLR2D_END

#include "oglr2D.inl"

#endif
