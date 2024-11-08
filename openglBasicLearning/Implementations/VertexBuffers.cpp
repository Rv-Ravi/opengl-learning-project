#include "../Headers/VertexBuffers.h"

VertexBuffers::VertexBuffers()
	:m_arrayObj(0),m_vBufferObj(0),m_iBufferObj(0)
{
	glGenVertexArrays(1, &m_arrayObj);
	glGenBuffers(1, &m_vBufferObj);
	glGenBuffers(1, &m_iBufferObj);
}

VertexBuffers::VertexBuffers(size_t bufferMemSize)
	:m_arrayObj(0), m_vBufferObj(0), m_iBufferObj(0)
{
	glGenVertexArrays(1, &m_arrayObj);
	glGenBuffers(1, &m_vBufferObj);
	glGenBuffers(1, &m_iBufferObj);

	bufferData(GL_ARRAY_BUFFER, bufferMemSize, GL_STATIC_DRAW);

}

VertexBuffers::~VertexBuffers()
{
	clearBuffers();
}

void VertexBuffers::clearBuffers()
{
	glDeleteBuffers(1, &m_vBufferObj);
	glDeleteBuffers(1, &m_iBufferObj);
	glDeleteVertexArrays(1, &m_arrayObj);
}

void VertexBuffers::setBufferAttribArrays(float* arr,size_t offSet,size_t size, uint32_t index, uint32_t stride, int32_t length,GLenum type)
{
	
	setBufferData(GL_ARRAY_BUFFER, size, offSet, arr);

	bindArray();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(index, length, type, GL_FALSE, stride, (void*)offSet);

	unbindBuffer(GL_ARRAY_BUFFER);
	unbindArray();

}

void VertexBuffers::setBufferAttribArrays(std::vector<float> vertexArr, size_t offSet, size_t size, uint32_t index, uint32_t stride, int32_t length, GLenum type)
{
	setBufferAttribArrays(&vertexArr[0], offSet, size, index, stride, length, type);
}

void VertexBuffers::bufferData(GLenum target, size_t allocSize, GLenum usage, const void* data)
{
	bindBuffer(target);
	glBufferData(target, allocSize, data, usage);

}

void VertexBuffers::setBufferData(GLenum target, size_t allocSize, size_t offSet, const void* data)
{
	bindBuffer(target);
	glBufferSubData(target,offSet,allocSize,data);
}

void VertexBuffers::bindArray()
{
	glBindVertexArray(m_arrayObj);
}

void VertexBuffers::bindBuffer(GLenum target)
{
	switch (target)
	{
	case GL_ARRAY_BUFFER: glBindBuffer(target, m_vBufferObj); break;
	case GL_ELEMENT_ARRAY_BUFFER : glBindBuffer(target, m_iBufferObj); break;
	}
}

void VertexBuffers::unbindArray()
{
	glBindVertexArray(0);
}

void VertexBuffers::unbindBuffer(GLenum target)
{
	glBindBuffer(target, 0);
}
