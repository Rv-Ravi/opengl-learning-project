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

	//constructors and destructor
	VertexBuffers();
	VertexBuffers(size_t bufferMemSize);

	VertexBuffers(const VertexBuffers& buffer) noexcept;
	VertexBuffers(VertexBuffers&& buffer) noexcept;
	~VertexBuffers();

	//copy and assignment operators
	VertexBuffers& operator=(const VertexBuffers& buffer) noexcept;

	VertexBuffers& operator=(VertexBuffers&& buffer) noexcept;

//member function
public:
	void clearBuffers();

	//non-standard data template
	void setBufferAttribArrays(float* arr, size_t offSet, size_t size, uint32_t index, uint32_t stride, int32_t length, GLenum type);
	void setBufferAttribArrays(const std::vector<float>& vertexArr, size_t offSet, size_t size, uint32_t index, uint32_t stride, int32_t length, GLenum type);


	//methods to set the data for indices of the array buffer
	void setBufferIndices(uint32_t* indices, size_t memSize);
	void setBufferIndices(const std::vector<uint32_t>& indices);

	//methods to allocate or set the data for array buffer
	void bufferData(GLenum target, size_t allocSize,GLenum usage, const void* data = nullptr);
	void setBufferData(GLenum target, size_t allocSize, size_t offSet, const void* data);

	//methods to bind and unbind the vertex array and vertex buffer
	void bindArray();
	void bindBuffer(GLenum target);


	void unbindArray();
	void unbindBuffer(GLenum target);

	


};

