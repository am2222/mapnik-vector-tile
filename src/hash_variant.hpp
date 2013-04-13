// TODO: Remove this file once the minimum Boost version is bumped to 1.50

#ifndef BOOST_HASH_VARIANT_FUNCTION_HPP
#define BOOST_HASH_VARIANT_FUNCTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/variant/variant_fwd.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/functional/hash_fwd.hpp>

namespace boost {

    namespace detail { namespace variant {
        struct variant_hasher: public boost::static_visitor<std::size_t> {
            template <class T>
            std::size_t operator()(T const& val) const {
                using namespace boost;
                hash<T> hasher;
                return hasher(val);
            }
        };
    }}

    template < BOOST_VARIANT_ENUM_PARAMS(typename T) >
    std::size_t hash_value(variant< BOOST_VARIANT_ENUM_PARAMS(T) > const& val) {
        std::size_t seed = boost::apply_visitor(detail::variant::variant_hasher(), val);
        hash_combine(seed, val.which());
        return seed;
    }
}

#endif
