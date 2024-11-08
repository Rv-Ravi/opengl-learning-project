#pragma once
#include <vector>
#include "glad/glad.h"

class VertexBuffers
{

	//member variables
private:
	uint32_t m_arrayObj, m_vBufferObj, m_iBufferObj;

//constructor and destructor
public:

	VertexBuffers();
	VertexBuffers(size_t bufferMemSize);
	~VertexBuffers();

//member function
public:
	void clearBuffers();

	//non-standard data template
	void setBufferAttribArrays(float* arr, size_t offSet, size_t size, uint32_t index, uint32_t stride, int32_t length, GLenum type);
	void setBufferAttribArrays(std::vector<float> vertexArr, size_t offSet, size_t size, uint32_t index, uint32_t stride, int32_t length, GLenum type);


	//
	void setBufferIndices(uint32_t* indices);
	void setBufferIndices(std::vector<uint32_t> indices);


	void bufferData(GLenum target, size_t allocSize,GLenum usage, const void* data = nullptr);

	void bindArray();
	void bindBuffer(GLenum target);


	void unbindArray();
	void unbindBuffer(GLenum target);

	void setBufferData(GLenum target, size_t allocSize, size_t offSet, const void* data);


};

