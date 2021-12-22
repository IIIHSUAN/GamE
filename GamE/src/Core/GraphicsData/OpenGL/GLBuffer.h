#pragma once

#include "../Buffer.h"

namespace GE {

	class GLVertexBuf : public VertexBuf
	{
	public:
		GLVertexBuf(float* vertices, uint32_t size);
		virtual ~GLVertexBuf();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufLayout& get() override { return _layout; }
		virtual void setLayout(const BufLayout& layout) override { _layout = layout; }
	private:
		uint32_t _vertexBuf;
		BufLayout _layout;
	};

	class GLIndexBuf : public IndexBuf
	{
	public:
		GLIndexBuf(uint32_t* vertices, uint32_t count);
		virtual ~GLIndexBuf();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t getCount() const override { return _count; }


	private:
		uint32_t _indexBuf, _count;
	};

}