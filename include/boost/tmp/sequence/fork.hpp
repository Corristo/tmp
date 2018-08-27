#ifndef BOOST_TMP_FORK_HPP_INCLUDED
#define BOOST_TMP_FORK_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "../detail/dispatch.hpp"
namespace boost {
	namespace tmp {
		template <typename... Fs>
		struct fork_ {};
		struct forward_as_pack_ {}; // only allowed as last closure before the continuation
		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, fork_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<
				        typename dispatch<(N + (N > sizeof...(Ts))), F>::template f<Ts...>>;
			};
			template <unsigned N, typename F0, typename F1, typename C>
			struct dispatch<N, fork_<F0, F1, C>> {
				template <typename... Ts>
				using f = typename dispatch<2, C>::template f<
				        typename dispatch<find_dispatch(sizeof...(Ts)), F0>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F1>::template f<Ts...>>;
			};
			template <unsigned N, typename F0, typename C>
			struct dispatch<N, fork_<F0, forward_as_pack_, C>> {
				template <typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<
				        typename dispatch<find_dispatch(sizeof...(Ts)), F0>::template f<Ts...>,
				        Ts...>;
			};
			template <unsigned N, typename F0, typename F1, typename F2, typename C>
			struct dispatch<N, fork_<F0, F1, F2, C>> {
				template <typename... Ts>
				using f = typename dispatch<3, C>::template f<
				        typename dispatch<find_dispatch(sizeof...(Ts)), F0>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F1>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F2>::template f<Ts...>>;
			};
			template <unsigned N, typename F0, typename F1, typename C>
			struct dispatch<N, fork_<F0, F1, forward_as_pack_, C>> {
				template <typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 2), C>::template f<
				        typename dispatch<find_dispatch(sizeof...(Ts)), F0>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F1>::template f<Ts...>,
				        Ts...>;
			};
			template <unsigned N, typename F0, typename F1, typename F2, typename F3, typename C>
			struct dispatch<N, fork_<F0, F1, F2, F3, C>> {
				template <typename... Ts>
				using f = typename dispatch<4, C>::template f<
				        typename dispatch<find_dispatch(sizeof...(Ts)), F0>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F1>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F2>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F3>::template f<Ts...>>;
			};
			template <unsigned N, typename F0, typename F1, typename F2, typename C>
			struct dispatch<N, fork_<F0, F1, F2, forward_as_pack_, C>> {
				template <typename... Ts>
				using f = typename dispatch<find_dispatch(sizeof...(Ts) + 3), C>::template f<
				        typename dispatch<find_dispatch(sizeof...(Ts)), F0>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F1>::template f<Ts...>,
				        typename dispatch<find_dispatch(sizeof...(Ts)), F2>::template f<Ts...>,
				        Ts...>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
