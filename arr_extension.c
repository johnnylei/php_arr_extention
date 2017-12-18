/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:  johnny                                                      |
  | Email :  leiyuqing_jing@163.com										 |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_arr_extension.h"

/* If you declare any globals in php_arr_extension.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(arr_extension)
*/

/* True global resources - no need for thread safety here */
static int le_arr_extension;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("arr_extension.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_arr_extension_globals, arr_extension_globals)
    STD_PHP_INI_ENTRY("arr_extension.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_arr_extension_globals, arr_extension_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_arr_extension_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_arr_extension_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "arr_extension", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_arr_extension_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_arr_extension_init_globals(zend_arr_extension_globals *arr_extension_globals)
{
	arr_extension_globals->global_value = 0;
	arr_extension_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(arr_extension)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(arr_extension)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(arr_extension)
{
#if defined(COMPILE_DL_ARR_EXTENSION) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(arr_extension)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(arr_extension)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "arr_extension support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ arr_extension_functions[]
 *
 * Every user visible function must have an entry in arr_extension_functions[].
 */
const zend_function_entry arr_extension_functions[] = {
	PHP_FE(confirm_arr_extension_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(arr_offset,	NULL)		/* For testing, remove later. */
	PHP_FE(arr_key_value_partner,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in arr_extension_functions[] */
};
/* }}} */

/* {{{ arr_extension_module_entry
 */
zend_module_entry arr_extension_module_entry = {
	STANDARD_MODULE_HEADER,
	"arr_extension",
	arr_extension_functions,
	PHP_MINIT(arr_extension),
	PHP_MSHUTDOWN(arr_extension),
	PHP_RINIT(arr_extension),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(arr_extension),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(arr_extension),
	PHP_ARR_EXTENSION_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ARR_EXTENSION
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(arr_extension)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

PHP_FUNCTION(arr_offset)
{
	zval * arr;
	int offset;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &offset, &arr) == FAILURE) {
        RETURN_NULL();
    }
	
	HashTable * arr_hash;
	arr_hash = Z_ARRVAL_P(arr);
	Bucket bukect = arr_hash->arData[offset];
	zval ret = bukect.val;
	RETURN_ZVAL(&ret, 1, 1);
}

PHP_FUNCTION(arr_key_value_partner) {
	zval * arr;
	char * key, * value_key;
	size_t key_len, value_key_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssa", &key, &key_len, &value_key, &value_key_len, &arr) == FAILURE) {
		RETURN_NULL();
		return ;
	}
	
	HashTable * arr_hash;
	arr_hash = Z_ARRVAL_P(arr);
	Bucket bukect, *tmp;
	zval bukect_val, *result;
	HashTable * item;
	HashTable * ret = (HashTable *)malloc(sizeof(HashTable));
	zend_hash_init(ret, arr_hash->nNumUsed, NULL, ZVAL_PTR_DTOR, 0);
	zval ret_item_value;
	char * ret_item_key;
	zend_string * zend_string_key = zend_string_init(key, key_len, 0);
	zend_string * zend_string_value_key = zend_string_init(value_key, value_key_len, 0);

	for (int i = 0; i < arr_hash->nNumUsed; i++) {
		bukect = arr_hash->arData[i];
		bukect_val = bukect.val;
		if (IS_ARRAY != Z_TYPE_P(&bukect_val)) {
			php_error(E_WARNING, "item should be array!");
		}

		item = Z_ARRVAL_P(&bukect_val);
	
		if (!zend_hash_exists(item, zend_string_key)) {
			php_error(E_WARNING, "there is no key:%s\n", key);
		}
		tmp = zend_hash_find(item, zend_string_key);
		ret_item_key = Z_STRVAL_P(&(tmp->val));
		
	//	switch (Z_TYPE_P(ret_item_key)) {
	//		case IS_DOUBLE:
	//		case IS_LONG:
	//		case IS_STRING:
	//			break;
	//		default:
	//			php_error("invlid type ret item key");
	//	}

		if (!zend_hash_exists(item, zend_string_value_key)) {
			php_error(E_WARNING, "there is no key:%s\n", value_key);
		}

		tmp = zend_hash_find(item, zend_string_value_key);
		ret_item_value = tmp->val;
		zend_string * zend_string_ret_item_key = zend_string_init(ret_item_key, strlen(ret_item_key), 0);
		result = zend_hash_add(ret, zend_string_ret_item_key, &ret_item_value);
	}
	
	zval *_ret;
	ZVAL_ARR(_ret, ret);
	RETURN_ZVAL(_ret, 1, 0);
}
