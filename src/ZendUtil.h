#ifndef HAVE_BITARRAY_ZEND_UTIL_CPP_H
#define HAVE_BITARRAY_ZEND_UTIL_CPP_H

extern "C" {
#include "php.h"
}

#if PHP_VERSION_ID >= 80600
#define CHUNKUTILS2_PARSE_PARAMETER_START(min_num_args, max_num_args) ZEND_PARSE_PARAMETERS_START(min_num_args, max_num_args)
#define chunkutils_parse_parameters_none() zend_parse_parameters_none()
#else
#define CHUNKUTILS2_PARSE_PARAMETER_START(min_num_args, max_num_args) ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, min_num_args, max_num_args)
#define chunkutils_parse_parameters_none() zend_parse_parameters_none_throw()
#endif

template<typename class_name>
static inline class_name * fetch_from_zend_object(zend_object *obj) {
	return (class_name *)((char *)obj - offsetof(class_name, std));
}

template<typename class_name>
static class_name* alloc_custom_zend_object(zend_class_entry* ce, zend_object_handlers *handlers) {
	class_name* object = (class_name*)emalloc(sizeof(class_name) + zend_object_properties_size(ce));

	zend_object_std_init(&object->std, ce);
	object_properties_init(&object->std, ce);

	object->std.handlers = handlers;

	return object;
}

static void chunkutils_zval_dtor(zval *val) {
#if PHP_VERSION_ID >= 80600
	zval_ptr_dtor_nogc(val);
#else
	zval_dtor(val);
#endif
}

#endif

