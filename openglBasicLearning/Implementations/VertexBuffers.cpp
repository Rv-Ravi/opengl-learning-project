#include "../Headers/VertexBuffers.h"

//contrucotr with initializer list that initialize the member variables 
//and contructor that generates the vertex array and buffers
VertexBuffers::VertexBuffers()
	:m_arrayObj(0),m_vBufferObj(0),m_iBufferObj(0)
{
	glGenVertexArrays(1, &m_arrayObj);
	glGenBuffers(1, &m_vBufferObj);
	glGenBuffers(1, &m_iBufferObj);
}

//constructor with size arg
//contrucotr with initializer list that initialize the member variables 
//and contructor that generates the vertex array and buffers
//and allocate memory for the buffer
VertexBuffers::VertexBuffers(size_t bufferMemSize)
	:m_arrayObj(0), m_vBufferObj(0), m_iBufferObj(0)
{
	glGenVertexArrays(1, &m_arrayObj);
	glGenBuffers(1, &m_vBufferObj);
	glGenBuffers(1, &m_iBufferObj);

	bufferData(GL_ARRAY_BUFFER, bufferMemSize, GL_STATIC_DRAW);

}


//copy constructor. clears the current members and assgins new values
VertexBuffers::VertexBuffers(const VertexBuffers& buffer) noexcept
{
	this->clearBuffers();

	this->m_arrayObj = buffer.m_arrayObj;
	this->m_vBufferObj = buffer.m_vBufferObj;
	this->m_iBufferObj = buffer.m_iBufferObj;
}

//move constructor. clears the current members and assgins new values
//cutting of the existing ownership
VertexBuffers::VertexBuffers(VertexBuffers&& buffer) noexcept
{
	this->clearBuffers();

	this->m_arrayObj = std::move(buffer.m_arrayObj);
	this->m_vBufferObj = std::move(buffer.m_vBufferObj);
	this->m_iBufferObj = std::move(buffer.m_iBufferObj);

	buffer.m_vBufferObj = 0;
	buffer.m_arrayObj = 0;
	buffer.m_iBufferObj = 0;
}

//destructor
VertexBuffers::~VertexBuffers()
{
	clearBuffers();
}
//copy operator. clears the current members and assgins new values
VertexBuffers& VertexBuffers::operator=(const VertexBuffers& buffer) noexcept
{
	if (&buffer != this)
	{
		this->clearBuffers();

		this->m_arrayObj = buffer.m_arrayObj;
		this->m_vBufferObj = buffer.m_vBufferObj;
		this->m_iBufferObj = buffer.m_iBufferObj;
	}
	return *this;
}
//move operator. clears the current members and assgins new values
//cutting of the existing ownership
VertexBuffers& VertexBuffers::operator=(VertexBuffers&& buffer) noexcept
{
	if (&buffer != this)
	{
		this->clearBuffers();

		this->m_arrayObj = std::move(buffer.m_arrayObj);
		this->m_vBufferObj = std::move(buffer.m_vBufferObj);
		this->m_iBufferObj = std::move(buffer.m_iBufferObj);

		buffer.m_vBufferObj = 0;
		buffer.m_arrayObj = 0;
		buffer.m_iBufferObj = 0;
	}
	return *this;
}

//delete / destroying all the buffers and array and then assigning to a null value
void VertexBuffers::clearBuffers()
{
	if (m_vBufferObj) { glDeleteBuffers(1, &m_vBufferObj); m_vBufferObj = 0; };
	if (m_iBufferObj) { glDeleteBuffers(1, &m_iBufferObj); m_iBufferObj = 0; };
	if (m_arrayObj) { glDeleteVertexArrays(1, &m_arrayObj); m_arrayObj = 0; };
}

//method that allocate the memory and send buffer data to GPU
//and informing the vertex array about the buffer data like how to interpret the data
void VertexBuffers::setBufferAttribArrays(float* arr,size_t offSet,size_t size, uint32_t index, uint32_t stride, int32_t length,GLenum type)
{
	
	setBufferData(GL_ARRAY_BUFFER, size, offSet, arr);

	bindArray();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(index, length, type, GL_FALSE, stride, (void*)offSet);

	unbindArray();
	unbindBuffer(GL_ARRAY_BUFFER);

}

//call setBufferAttribArrays. functionality for both is same
void VertexBuffers::setBufferAttribArrays(const std::vector<float>& vertexArr, size_t offSet, size_t size, uint32_t index, uint32_t stride, int32_t length, GLenum type)
{
	setBufferAttribArrays((float*) & vertexArr[0], offSet, size, index, stride, length, type);
}

//method that allocate the memory and send buffer data to GPU
//and informing the vertex array about the index buffer data
void VertexBuffers::setBufferIndices(uint32_t* indices, size_t memSize)
{
	bindArray();
	bindBuffer(GL_ELEMENT_ARRAY_BUFFER);

	bufferData(GL_ELEMENT_ARRAY_BUFFER, memSize, GL_STATIC_DRAW, indices);

	unbindArray();
	unbindBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

//call setBufferIndices. functionality for both is same
void VertexBuffers::setBufferIndices(const std::vector<uint32_t>& indices)
{
	setBufferIndices((uint32_t*) & indices[0], sizeof(uint32_t) * indices.size());
}

//allocates the buffer memory and sends the data if data is not null
void VertexBuffers::bufferData(GLenum target, size_t allocSize, GLenum usage, const void* data)
{
	bindBuffer(target);
	glBufferData(target, allocSize, data, usage);

}

//sends the data for the buffer from thr particular offset till the size
void VertexBuffers::setBufferData(GLenum target, size_t allocSize, size_t offSet, const void* data)
{
	bindBuffer(target);
	glBufferSubData(target,offSet,allocSize,data);
}

//Binding and unbinding the vertex array and buffers
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

int apple = 10;