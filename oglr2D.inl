#include "oglr2D.h"
#include "oglr2D_khrplatform.h"

#define OGLR2D_BEGIN_SPECIAL_INLINE namespace oglr2D_inline {
#define OGLR2D_END_SPECIAL_INLINE }

#ifndef OGLR2D_USE_GLFW
#include <gl/GL.h>
#endif

#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_STATIC_DRAW                    0x88E4
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31

#include <stddef.h>
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef char GLchar;

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#define OGLR2D_OPENGL_FUNC(type, name, fnname, args) \
			typedef type(APIENTRYP name) args;		 \
			static name	fnname = NULL;			

#include "oglr2D_gl_funcs.h"

#undef OGLR2D_OPENGL_FUNC

OGLR2D_BEGIN

OGLR2DFloat2 multipyFloat2Matrix4(const OGLR2DFloat2& f2, const OGLR2DMatrix4& m4)
{
	OGLR2DFloat2 res;
	res.x = f2[0] * m4[0][0] + f2[1] * m4[0][1] + m4[0][2] + m4[0][3];
	res.y = f2[0] * m4[1][0] + f2[1] * m4[1][1] + m4[1][2] + m4[1][3];
	return res;
}

OGLR2DFloat3 multipyFloat3Matrix4(const OGLR2DFloat3& f2, const OGLR2DMatrix4& m4)
{
	OGLR2DFloat3 res;
	res.x = f2[0] * m4[0][0] + f2[1] * m4[0][1] + f2[2] * m4[0][2] + m4[0][3];
	res.y = f2[0] * m4[1][0] + f2[1] * m4[1][1] + f2[2] * m4[1][2] + m4[1][3];
	res.z = f2[0] * m4[2][0] + f2[1] * m4[2][1] + f2[2] * m4[2][2] + m4[2][3];
	return res;
}

OGLR2DFloat4 multipyFloat4Matrix4(const OGLR2DFloat4& f2, const OGLR2DMatrix4& m4)
{
	OGLR2DFloat4 res;
	res.x = f2[0] * m4[0][0] + f2[1] * m4[0][1] + f2[2] * m4[0][2] + f2[3] * m4[0][3];
	res.y = f2[0] * m4[1][0] + f2[1] * m4[1][1] + f2[2] * m4[1][2] + f2[3] * m4[1][3];
	res.z = f2[0] * m4[2][0] + f2[1] * m4[2][1] + f2[2] * m4[2][2] + f2[3] * m4[2][3];
	res.w = f2[0] * m4[3][0] + f2[1] * m4[3][1] + f2[2] * m4[3][2] + f2[3] * m4[3][3];
	return res;
}

struct VertexArray
{
	GLuint id;
};

struct Buffer
{
	GLuint id;
	GLenum type;
	OGLR2DBasicArray<OGLR2DBufferAttribute> attributes;
	OGLR2DUInt32 attributesStride;
};

struct Shader
{
	GLuint program;
};

struct Texture
{
};

struct GLContext;

OGLR2D_BEGIN_SPECIAL_INLINE

static GLenum attributeTypeToOpenGL(OGLR2DUInt32 type)
{
	switch (type)
	{
	case FLOAT: return GL_FLOAT;
	case INT: return GL_INT;
	case FLOAT2: return GL_FLOAT;
	case FLOAT3: return GL_FLOAT;
	case FLOAT4: return GL_FLOAT;
	}

	return -1;
}

static struct
{
	OGLR2DBasicArray<GLContext> contexts;
} s_ogl_contexts;

static struct
{
	OGLR2DViewport currViewport;
} s_ogl_gpu_data;

static VertexArray* allocateVertexArray()
{
	return new VertexArray();
}

static Buffer* allocateBuffer()
{
	return new Buffer();
}

static Shader* allocateShader()
{
	return new Shader();
}

static Texture* allocateTexture()
{
	return new Texture();
}

OGLR2D_END_SPECIAL_INLINE

struct GLContext
{
#if defined(OGLR2D_USE_GLFW)
	GLFWwindow* glfwContext;
#elif defined(OGLR2D_USE_WINDOWS)
	HDC windowsContext;
#elif defined(OGLR2D_USE_LINUX)
#elif defined(OGLR2D_USE_MACOS)
#endif

	bool operator==(const GLContext& rhs) const
	{
#if defined(OGLR2D_USE_GLFW)
		return glfwContext == rhs.glfwContext;
#elif defined(OGLR2D_USE_WINDOWS)
		return windowsContext == rhs.windowsContext;
#elif defined(OGLR2D_USE_LINUX)
#elif defined(OGLR2D_USE_MACOS)
#endif

		return false;
	}
};

#ifdef OGLR2D_USE_GLFW

OGLR2DUInt64 findGLFWContext(GLFWwindow* ctx)
{
	for (OGLR2DUInt64 i = 0; i < oglr2D_inline::s_ogl_contexts.contexts.size(); i++)
	{
		if (oglr2D_inline::s_ogl_contexts.contexts[i].glfwContext == ctx)
			return i;
	}

	return -1;
}

void makeContextCurrentGLFW(GLFWwindow* window)
{
	GLFWwindow* _ctx = glfwGetCurrentContext();
	GLContext ctx;
	if (_ctx == nullptr)
	{
		glfwMakeContextCurrent(window);
		ctx.glfwContext = window;
	}
	else
	{
		ctx.glfwContext = _ctx;
	}

	oglr2D_inline::s_ogl_contexts.contexts.removeIfContains(ctx);
	oglr2D_inline::s_ogl_contexts.contexts.push(ctx);
}

void swapBuffersGLFW(GLFWwindow* context)
{
	OGLR2DUInt64 i = findGLFWContext(context);
	if (i != -1)
		glfwSwapBuffers(context);
}

#endif

#ifdef OGLR2D_USE_WINDOWS

u64 findWindowsContext(HDC hDC)
{
}

void makeContextCurrentWindows(HWND hWnd)
{
}

void swapBuffersWindows(HWND hWnd)
{
}

#endif

namespace ogl_loader
{
	static struct
	{
		GLLoaderProc loadFunc;
	} s_ogl_loader;

	void setOpenGLLoaderFunc(GLLoaderProc proc)
	{
		s_ogl_loader.loadFunc = proc;
	}

	static void* openGLGetProcAddress(const char* name)
	{
		return s_ogl_loader.loadFunc(name);
	}
}

void loadOpenGL()
{
#ifdef OGLR2D_USE_GLFW
	ogl_loader::setOpenGLLoaderFunc((ogl_loader::GLLoaderProc)glfwGetProcAddress);
#else
#endif

#define OGLR2D_OPENGL_FUNC(type, name, fnname, args) fnname = (name)ogl_loader::openGLGetProcAddress(#fnname)

#include "oglr2D_gl_funcs.h"

#undef OGLR2D_OPENGL_FUNC
}

void clearScreen(const OGLR2DColor& color, OGLR2DUInt32 clearFlags)
{
	GLbitfield mask = 0;
	if (clearFlags & COLOR_BUFFER_BIT)
		mask |= GL_COLOR_BUFFER_BIT;
	if (clearFlags & DEPTH_BUFFER_BIT)
		mask |= GL_DEPTH_BUFFER_BIT;
	if (clearFlags | ACCUM_BUFFER_BIT)
		mask |= GL_ACCUM_BUFFER_BIT;
	if (clearFlags | STENCIL_BUFFER_BIT)
		mask |= GL_STENCIL_BUFFER_BIT;

	glClear(mask);
	glClearColor((float)color.r / 255, (float)color.g / 255, (float)color.b / 255, (float)color.a / 255);
}

void setViewport(const OGLR2DViewport& viewport)
{
	oglr2D_inline::s_ogl_gpu_data.currViewport = viewport;
	glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
}

OGLR2DViewport getViewport()
{
	return oglr2D_inline::s_ogl_gpu_data.currViewport;
}

OGLR2DVertexArray createVertexArray()
{
	VertexArray* res = oglr2D_inline::allocateVertexArray();
	glGenVertexArrays(1, &res->id);
	return res;
}

void deleteVertexArray(const OGLR2DVertexArray vao)
{
	OGLR2D_ASSERT(vao != 0);
	glDeleteVertexArrays(1, &vao->id);
}

void bindVertexArray(OGLR2DVertexArray vao)
{
	glBindVertexArray(vao ? vao->id : 0);
}

OGLR2DBuffer createBuffer(OGLR2DUInt32 type)
{
	Buffer* buffer = oglr2D_inline::allocateBuffer();
	if (type == INDEX_BUFFER)
		buffer->type = GL_ELEMENT_ARRAY_BUFFER;
	if (type == VERTEX_BUFFER)
		buffer->type = GL_ARRAY_BUFFER;

	glGenBuffers(1, &buffer->id);
	return buffer;
}

void deleteBuffer(const OGLR2DBuffer buffer)
{
	OGLR2D_ASSERT(buffer != 0);
	glDeleteBuffers(1, &buffer->id);
}

void bindBuffer(OGLR2DBuffer buffer)
{
	OGLR2D_ASSERT(buffer != 0);
	glBindBuffer(buffer->type, buffer->id);
}

void pushBufferAttribute(OGLR2DBuffer buffer, const char* name, OGLR2DUInt32 type, bool normalized)
{
	OGLR2D_ASSERT(buffer != 0);

	OGLR2DUInt32 elmSize = 0;
	OGLR2DUInt32 sz = 0;
	switch (type)
	{
	case FLOAT: elmSize = 1; sz = sizeof(OGLR2DFloat); break;
	case INT: elmSize = 1; sz = sizeof(OGLR2DInt); break;
	case FLOAT2: elmSize = 2; sz = sizeof(OGLR2DFloat2); break;
	case FLOAT3: elmSize = 3; sz = sizeof(OGLR2DFloat3); break;
	case FLOAT4: elmSize = 4; sz = sizeof(OGLR2DFloat3); break;
	}

	OGLR2DBufferAttribute attribute;
	attribute.type = type;
	attribute.normalized = normalized;
	attribute.elementSize = elmSize;
	attribute.offset = buffer->attributesStride;
	buffer->attributes.push(attribute);

	buffer->attributesStride += sz * elmSize;
}

void prepareBufferAttributes(OGLR2DVertexArray vao, OGLR2DBuffer buffer)
{
	OGLR2D_ASSERT(buffer != 0);
	bindVertexArray(vao);

	OGLR2DBufferAttribute attr;
	for (OGLR2DUInt32 i = 0; i < (OGLR2DUInt32)buffer->attributes.size(); i++)
	{
		attr = buffer->attributes[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attr.elementSize, GL_FLOAT, attr.normalized ? GL_TRUE : GL_FALSE, buffer->attributesStride, (const void*)attr.offset);
	}
}

void setBufferData(OGLR2DBuffer buffer, const void* src, OGLR2DUInt32 size, OGLR2DUInt32 usage)
{
	OGLR2D_ASSERT(buffer != 0);
	bindBuffer(buffer);

	GLenum gl_usage = 0;
	if (usage == STATIC_DRAW)
		gl_usage = GL_STATIC_DRAW;
	if (usage == DYNAMIC_DRAW)
		gl_usage = GL_DYNAMIC_DRAW;

	glBufferData(buffer->type, size, src, gl_usage);
}

void setBufferSubData(OGLR2DBuffer buffer, const void* src, OGLR2DUInt32 size)
{
	OGLR2D_ASSERT(buffer != 0);
	bindBuffer(buffer);

	glBufferSubData(buffer->type, 0, size, src);
}

OGLR2DShader createShader(const char* vertSrc, const char* fragSrc)
{
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	Shader* res = oglr2D_inline::allocateShader();
	res->program = glCreateProgram();

	glAttachShader(res->program, vertexShader);
	glAttachShader(res->program, fragmentShader);

	glLinkProgram(res->program);

	return res;
}

void deleteShader(const OGLR2DShader shader)
{
	OGLR2D_ASSERT(shader != 0);

	glDeleteProgram(shader->program);
}

void bindShader(OGLR2DShader shader)
{
	OGLR2D_ASSERT(shader != 0);

	glUseProgram(shader ? shader->program : 0);
}

void setUniformFloat(OGLR2DShader shader, const char* name, const OGLR2DFloat& val)
{
	OGLR2D_ASSERT(shader != 0);

	glUniform1f(glGetUniformLocation(shader->program, name), val);
}

void setUniformFloat2(OGLR2DShader shader, const char* name, const OGLR2DFloat2& val)
{
	OGLR2D_ASSERT(shader != 0);

	glUniform2f(glGetUniformLocation(shader->program, name), val.x, val.y);
}

void setUniformFloat3(OGLR2DShader shader, const char* name, const OGLR2DFloat3& val)
{
	OGLR2D_ASSERT(shader != 0);

	glUniform3f(glGetUniformLocation(shader->program, name), val.x, val.y, val.z);
}

void setUniformFloat4(OGLR2DShader shader, const char* name, const OGLR2DFloat4& val)
{
	OGLR2D_ASSERT(shader != 0);

	glUniform4f(glGetUniformLocation(shader->program, name), val.x, val.y, val.z, val.w);
}

void setUniformInt(OGLR2DShader shader, const char* name, const OGLR2DInt& val)
{
	OGLR2D_ASSERT(shader != 0);

	glUniform1i(glGetUniformLocation(shader->program, name), val);
}

void setUniformMatrix4(OGLR2DShader shader, const char* name, const OGLR2DMatrix4& val)
{
	OGLR2D_ASSERT(shader != 0);

	glUniformMatrix4fv(glGetUniformLocation(shader->program, name), 1, GL_FALSE, val.getAddress());
}

OGLR2D_END

