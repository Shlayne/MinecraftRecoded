namespace eng
{
	inline bool Event::IsInCategories(EventCategory categories) const
	{
		return categories == (categories & GetCategories());
	}

	inline bool Event::IsHandled() const
	{
		return m_Handled;
	}

	inline void Event::Handle()
	{
		m_Handled = true;
	}

	template<typename C, typename E>
	inline void Event::Dispatch(C* object, void(C::*callback)(E&))
	{
		if (!IsHandled() && GetType() == E::GetStaticType())
			(object->*callback)(static_cast<E&>(*this));
	}

	template<typename E>
	inline void Event::Dispatch(void(*callback)(E&))
	{
		if (!IsHandled() && GetType() == E::GetStaticType())
			callback(static_cast<E&>(*this));
	}
}
