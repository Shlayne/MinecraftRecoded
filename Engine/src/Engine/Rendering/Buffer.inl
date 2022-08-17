namespace eng
{
	static constexpr uint32 GetElementCount(VertexBufferElementType type)
	{
		switch (type)
		{
			case VertexBufferElementType_Int:    return 1;
			case VertexBufferElementType_Int2:   return 2;
			case VertexBufferElementType_Int3:   return 3;
			case VertexBufferElementType_Int4:   return 4;
			case VertexBufferElementType_UInt:   return 1;
			case VertexBufferElementType_UInt2:  return 2;
			case VertexBufferElementType_UInt3:  return 3;
			case VertexBufferElementType_UInt4:  return 4;
			case VertexBufferElementType_Float:  return 1;
			case VertexBufferElementType_Float2: return 2;
			case VertexBufferElementType_Float3: return 3;
			case VertexBufferElementType_Float4: return 4;
		}

		CORE_ASSERT(false, "Unknown Vertex Buffer Element Type!");
		return 0;
	}

	static constexpr uint32 GetElementSize(VertexBufferElementType type)
	{
		switch (type)
		{
			case VertexBufferElementType_Int:    return 4;
			case VertexBufferElementType_Int2:   return 8;
			case VertexBufferElementType_Int3:   return 12;
			case VertexBufferElementType_Int4:   return 16;
			case VertexBufferElementType_UInt:   return 4;
			case VertexBufferElementType_UInt2:  return 8;
			case VertexBufferElementType_UInt3:  return 12;
			case VertexBufferElementType_UInt4:  return 16;
			case VertexBufferElementType_Float:  return 4;
			case VertexBufferElementType_Float2: return 8;
			case VertexBufferElementType_Float3: return 12;
			case VertexBufferElementType_Float4: return 16;
		}

		CORE_ASSERT(false, "Unknown Vertex Buffer Element Type!");
		return 0;
	}

	constexpr VertexBufferElement::VertexBufferElement(VertexBufferElementType type, bool normalized) noexcept
		: type(type), normalized(normalized), count(GetElementCount(type)), size(GetElementSize(type)) {}

	constexpr VertexBufferLayout::VertexBufferLayout(std::initializer_list<VertexBufferElement> elements) noexcept
		: m_Elements(elements)
	{
		uint64 offset = 0;

		for (VertexBufferElement& element : m_Elements)
		{
			element.offset = offset;
			offset += element.size;
			m_Stride += element.size;
		}
	}

	constexpr const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const noexcept { return m_Elements; }
	constexpr uint32 VertexBufferLayout::GetStride() const noexcept { return m_Stride; }

	constexpr auto VertexBufferLayout::begin() noexcept { return m_Elements.begin(); }
	constexpr auto VertexBufferLayout::begin() const noexcept { return m_Elements.begin(); }
	constexpr auto VertexBufferLayout::end() noexcept { return m_Elements.end(); }
	constexpr auto VertexBufferLayout::end() const noexcept { return m_Elements.end(); }
	constexpr auto VertexBufferLayout::rbegin() noexcept { return m_Elements.rbegin(); }
	constexpr auto VertexBufferLayout::rbegin() const noexcept { return m_Elements.rbegin(); }
	constexpr auto VertexBufferLayout::rend() noexcept { return m_Elements.rend(); }
	constexpr auto VertexBufferLayout::rend() const noexcept { return m_Elements.rend(); }
	constexpr auto VertexBufferLayout::cbegin() const noexcept { return m_Elements.cbegin(); }
	constexpr auto VertexBufferLayout::cend() const noexcept { return m_Elements.cend(); }
	constexpr auto VertexBufferLayout::crbegin() const noexcept { return m_Elements.crbegin(); }
	constexpr auto VertexBufferLayout::crend() const noexcept { return m_Elements.crend(); }

	static constexpr uint32 GetIndexBufferElementSize(IndexBufferElementType type)
	{
		switch (type)
		{
			case IndexBufferElementType_UInt32: return sizeof(uint32);
			case IndexBufferElementType_UInt16: return sizeof(uint16);
			case IndexBufferElementType_UInt8:  return sizeof(uint8);
		}

		CORE_ASSERT(false, "Unknown Index Buffer Element Type!");
		return 0;
	}
}
