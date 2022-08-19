#pragma once

#include "Engine/Core/Core.h"
#include <string_view>
#include <vector>

namespace eng
{
	using BufferUsage_ = uint8;
	enum BufferUsage : BufferUsage_
	{
		BufferUsage_StreamDraw,  BufferUsage_StreamRead,  BufferUsage_StreamCopy,
		BufferUsage_StaticDraw,  BufferUsage_StaticRead,  BufferUsage_StaticCopy,
		BufferUsage_DynamicDraw, BufferUsage_DynamicRead, BufferUsage_DynamicCopy
	};

	using VertexBufferElementType_ = uint8;
	enum VertexBufferElementType : VertexBufferElementType_
	{
		VertexBufferElementType_Int,
		VertexBufferElementType_Int2,
		VertexBufferElementType_Int3,
		VertexBufferElementType_Int4,

		VertexBufferElementType_UInt,
		VertexBufferElementType_UInt2,
		VertexBufferElementType_UInt3,
		VertexBufferElementType_UInt4,

		VertexBufferElementType_Float,
		VertexBufferElementType_Float2,
		VertexBufferElementType_Float3,
		VertexBufferElementType_Float4
	};

	struct VertexBufferElement
	{
		constexpr VertexBufferElement(VertexBufferElementType type, bool normalized = false) noexcept;

		VertexBufferElementType type;
		bool normalized;
		uint32 count;
		uint32 size;
		uint64 offset = 0;
	};

	class VertexBufferLayout
	{
	public:
		constexpr VertexBufferLayout() noexcept = default;
		constexpr VertexBufferLayout(std::initializer_list<VertexBufferElement> elements) noexcept;
	public:
		constexpr const std::vector<VertexBufferElement>& GetElements() const noexcept;
		constexpr uint32 GetStride() const noexcept;
	public:
		constexpr auto begin() noexcept;
		constexpr auto begin() const noexcept;
		constexpr auto end() noexcept;
		constexpr auto end() const noexcept;
		constexpr auto rbegin() noexcept;
		constexpr auto rbegin() const noexcept;
		constexpr auto rend() noexcept;
		constexpr auto rend() const noexcept;
		constexpr auto cbegin() const noexcept;
		constexpr auto cend() const noexcept;
		constexpr auto crbegin() const noexcept;
		constexpr auto crend() const noexcept;
	private:
		std::vector<VertexBufferElement> m_Elements;
		uint32 m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		static Ref<VertexBuffer> CreateRef(uint32 size, const void* cpData = nullptr, BufferUsage usage = BufferUsage_StaticDraw);
		virtual ~VertexBuffer() = default;
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* cpData, uint32 size) = 0;

		virtual const VertexBufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const VertexBufferLayout& crLayout) = 0;
	};

	using IndexBufferElementType_ = uint8;
	enum IndexBufferElementType : IndexBufferElementType_
	{
		IndexBufferElementType_UInt32,
		IndexBufferElementType_UInt16,
		IndexBufferElementType_UInt8,
	};

	class IndexBuffer
	{
	public:
		static Ref<IndexBuffer> CreateRef(uint32 count, const void* cpData = nullptr, BufferUsage usage = BufferUsage_StaticDraw, IndexBufferElementType type = IndexBufferElementType_UInt32);
		virtual ~IndexBuffer() = default;
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* cpData, uint32 count) = 0;

		virtual uint32 GetCount() const = 0;
		virtual IndexBufferElementType GetType() const = 0;
	};

	class UniformBuffer
	{
	public:
		static Ref<UniformBuffer> CreateRef(uint32 size, uint32 binding, const void* cpData = nullptr, BufferUsage usage = BufferUsage_StaticDraw);
		virtual ~UniformBuffer() = default;
	public:
		virtual void SetData(const void* cpData, uint32 size, uint32 offset = 0) = 0;
	};
}

#include "Buffer.inl"
