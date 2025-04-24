#ifndef ID_H
#define ID_H

#include <QMetaType>

#include <cstddef>
#include <iosfwd>
#include <string>
#include <unordered_map>

class Id final {
public:
	using type = std::size_t;
	
	enum class FirstBits : type
	{
		ONE   = ~(~type(0) >> 1),
		TWO   = ~(~type(0) >> 2),
		THREE = ~(~type(0) >> 3)
	};

	Id() noexcept
		: m_value(0)
	{}

	Id(type value) noexcept
		: m_value(value)
	{
	}

	Id operator ++ () noexcept
	{
		++m_value;
		return *this;
	}

	Id operator ++ (int) noexcept
	{
		Id id(m_value);
		m_value++;
		return id;
	}

	Id &operator += (const type value) noexcept
	{
		m_value += value;

		return *this;
	}

	bool operator < (const Id other) const noexcept
	{
		return m_value < other.m_value;
	}

	bool operator > (const Id other) const noexcept
	{
		return m_value > other.m_value;
	}

	bool operator == (const Id other) const noexcept
	{
		return m_value == other.m_value;
	}

	bool operator != (const Id other) const noexcept
	{
		return m_value != other.m_value;
	}

	explicit operator bool () const noexcept
	{
		return m_value != 0;
	}

	template <typename T>
		friend T static_id_cast(const Id) noexcept;

		template <typename T>
	friend T reinterpret_id_cast(const Id) noexcept;


	template <typename T>
		friend struct std::hash;

	//
	// Unusual operations:
	//

	// In some places certain values are ored/multiplied to the id, but the comments don't explain 
	// the intent properly, only that it is done to avoid collisions.
	
	Id operator | (FirstBits bits) const noexcept
	{
		return m_value | static_cast<type>(bits);
	}
	
	Id operator * (const type value) const noexcept
	{
		return m_value * value;
	}

private:
	type m_value;
};

Q_DECLARE_METATYPE(Id)

template <typename T>
	T static_id_cast(const Id id) noexcept
	{
		// Use brace initializer to get warning about narrowing conversion:
		return T{ id.m_value };
	}

template <typename T>
	T reinterpret_id_cast(const Id id) noexcept
	{
		return T( id.m_value );
	}

std::string to_string(const Id id);
std::wstring to_wstring(const Id id);

std::ostream &operator << (std::ostream &os, const Id id);
std::wostream &operator << (std::wostream &os, const Id id);

// Support for unordered_map:
namespace std
{
	template<>
		struct hash<Id> {
			public:
				std::size_t operator()(const Id id) const noexcept;

			private:
				std::hash<Id::type> m_hash;
		};
}

#endif
