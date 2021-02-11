#include <purescript.h>

purs_any_t Data_Lazy_force_fn(const purs_scope_t *scope,
			      purs_any_t unused,
			      va_list restargs) {
	purs_any_t val;
	purs_foreign_t *v = (purs_foreign_t*) purs_any_force_foreign(scope->bindings[0]);
	purs_any_t *ref = (purs_any_t*) v->data;

	if (ref != NULL) {
		val = *ref;
		PURS_ANY_RETAIN(val);
	} else {
		purs_any_t *ref = purs_new(purs_any_t);
		v->data = ref;
		val = purs_any_app(scope->bindings[1], purs_any_null);
		PURS_ANY_RETAIN(val); /// ref retains value
		*ref = val;
	}

	PURS_RC_RELEASE(v);
	return val;
}

void Data_Lazy_force_finalize(void *tag, void *data) {
	if (data != NULL /* forced */) {
		purs_any_t v = *((purs_any_t*)data);
		PURS_ANY_RELEASE(v);
		purs_free(data);
	}
}

PURS_FFI_FUNC_1(Data_Lazy_defer, thunk) {
	const purs_foreign_t *foreign = purs_foreign_new(
		NULL,
		NULL,
		Data_Lazy_force_finalize);
	const purs_scope_t *scope = purs_scope_new(
		2,
		purs_any_foreign(foreign),
		thunk);
	const purs_cont_t *cont = purs_cont_new(scope, Data_Lazy_force_fn);
	PURS_RC_RELEASE(foreign);
	PURS_RC_RELEASE(scope);
	return purs_any_cont(cont);
}

PURS_FFI_FUNC_1(Data_Lazy_force, l) {
	return purs_any_app(l, purs_any_null);
}
