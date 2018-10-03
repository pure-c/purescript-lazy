#include <purescript.h>

struct _lazy {
	int has_run;
	const purs_any_t * fn;
	const ANY* result;
};

const ANY * _lazy_cont_fn(const void * ctx, const ANY * _, va_list __) {
	struct _lazy * x = (struct _lazy *) ctx;
	if (x->has_run == 0) {
		x->result = purs_any_app(x->fn, NULL);
		x->has_run = 1;
	}
	return x->result;
}

PURS_FFI_FUNC_1(Data_Lazy_defer, fn, {
	struct _lazy * x = purs_new(struct _lazy);
	x->fn = fn;
	x->has_run = 0;
	x->result = NULL;
	return purs_any_cont_new(x, _lazy_cont_fn);
});

PURS_FFI_FUNC_1(Data_Lazy_force, l, {
	return purs_any_app(l, NULL);
});
