#pragma once

namespace GE {

	enum class DataType
	{
		None=0,
		Float,Float2,Float3,Float4,
		Matrix3, Matrix4,
		Int,Int2,Int3,Int4,
		Bool
	};
	static inline uint32_t size(DataType type)
	{
		switch (type)
		{
		case DataType::Float:			return 4;
		case DataType::Float2:			return 4 * 2;
		case DataType::Float3:			return 4 * 3;
		case DataType::Float4:			return 4 * 4;
		case DataType::Matrix3:			return 4 * 3 * 3;
		case DataType::Matrix4:			return 4 * 4 * 4;
		case DataType::Int:				return 4;
		case DataType::Int2:			return 4 * 2;
		case DataType::Int3:			return 4 * 3;
		case DataType::Int4:			return 4 * 4;
		case DataType::Bool:			return 1;
		}
	}
	static inline const uint32_t& count(DataType type)
	{
		switch (type)
		{
		case DataType::Float:			return 1;
		case DataType::Float2:			return 2;
		case DataType::Float3:			return 3;
		case DataType::Float4:			return 4;
		case DataType::Matrix3:			return 3 * 3;
		case DataType::Matrix4:			return 4 * 4;
		case DataType::Int:				return 1;
		case DataType::Int2:			return 2;
		case DataType::Int3:			return 3;
		case DataType::Int4:			return 4;
		case DataType::Bool:			return 1;
		}
	}

	struct Buf
	{
		std::string name;
		DataType type;
		uint32_t size;
		uint32_t offset;
		bool isNorm;

		Buf(DataType _type, const std::string& _name, bool _isNorm = false) :name(_name), type(_type), offset(0), size(GE::size(_type)), isNorm(_isNorm) {}
		const uint32_t& count() const { return GE::count(type); }
	};

	class BufLayout
	{
	public:
		BufLayout() = default;
		BufLayout(const std::initializer_list<Buf>& buf) :_buf(buf)
		{
			uint32_t offset = 0;

			for (auto& buf : _buf)
			{
				buf.offset = offset;

				offset += buf.size, _stride += buf.size;
			}
		}

		inline const std::vector<Buf>& get() const { return _buf; }
		inline const uint32_t& getStride() const { return _stride; }

		std::vector<Buf>::iterator begin() { return _buf.begin(); }
		std::vector<Buf>::iterator end() { return _buf.end(); }
		std::vector<Buf>::const_iterator begin() const { return _buf.begin(); }
		std::vector<Buf>::const_iterator end() const { return _buf.end(); }
	private:
		std::vector<Buf> _buf;
		uint32_t _stride = 0;
	};

	/* Elements ***********************************************************/

	class VertexBuf
	{
	public:
		virtual ~VertexBuf() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static VertexBuf* create(float* vertices, uint32_t size);

		virtual const BufLayout& getLayout() = 0;
		virtual void setLayout(const BufLayout& layout) = 0;
	};

	class IndexBuf
	{
	public:
		virtual ~IndexBuf() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static IndexBuf* create(uint32_t* vertices, uint32_t count);
	};

	/* OpenGL only *************************************/

	class VertexArr
	{
	public:
		virtual ~VertexArr() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertex(const std::shared_ptr<VertexBuf>& vertexBuf) = 0;
		virtual void setIndex(const std::shared_ptr<IndexBuf>& indexBuf) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuf>>& getVertexBufVec() const = 0;
		virtual const std::shared_ptr<IndexBuf >& getIndexBuf() const = 0;

		static VertexArr* create();
	};

}