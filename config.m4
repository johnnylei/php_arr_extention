dnl $Id$
dnl config.m4 for extension arr_extension

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(arr_extension, for arr_extension support,
Make sure that the comment is aligned:
[  --with-arr_extension             Include arr_extension support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(arr_extension, whether to enable arr_extension support,
dnl Make sure that the comment is aligned:
dnl [  --enable-arr_extension           Enable arr_extension support])

if test "$PHP_ARR_EXTENSION" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-arr_extension -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/arr_extension.h"  # you most likely want to change this
  dnl if test -r $PHP_ARR_EXTENSION/$SEARCH_FOR; then # path given as parameter
  dnl   ARR_EXTENSION_DIR=$PHP_ARR_EXTENSION
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for arr_extension files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ARR_EXTENSION_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ARR_EXTENSION_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the arr_extension distribution])
  dnl fi

  dnl # --with-arr_extension -> add include path
  dnl PHP_ADD_INCLUDE($ARR_EXTENSION_DIR/include)

  dnl # --with-arr_extension -> check for lib and symbol presence
  dnl LIBNAME=arr_extension # you may want to change this
  dnl LIBSYMBOL=arr_extension # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ARR_EXTENSION_DIR/$PHP_LIBDIR, ARR_EXTENSION_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ARR_EXTENSIONLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong arr_extension lib version or lib not found])
  dnl ],[
  dnl   -L$ARR_EXTENSION_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ARR_EXTENSION_SHARED_LIBADD)

  PHP_NEW_EXTENSION(arr_extension, arr_extension.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi

if test -z "$PHP_DEBUG"; then   
    AC_ARG_ENABLE(debug,  
    [ --enable-debug      compile with debugging symbols],
	[PHP_DEBUG=$enableval],
	[ PHP_DEBUG=no])  
fi  
