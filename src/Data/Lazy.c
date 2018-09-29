#include <purescript.h>

PURS_FFI_FUNC_1(Data_Lazy_defer, thunk, {
	__block int forced = 0;
	const purs_any_t ** v = (const purs_any_t **) purs_scope_capture(purs_new(const purs_any_t *));
	return PURS_LAMBDA(_, {
		if (forced) {
			return *v;
		} else {
			*v = purs_any_app(thunk, NULL);
			forced = 1;
			return *v;
		}
	});
})

PURS_FFI_FUNC_1(Data_Lazy_force, l, {
	return purs_any_app(l, NULL);
})
